#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
// #include <opencv2/face.hpp>

typedef cv::Point3_<uint8_t> Pixel;

int t = 0, xc = 0, yc = 0;
struct Magic {
    void operator ()(Pixel &pixel, const int *position) const {
        float d = sqrt((position[1]-xc)*(position[1]-xc)+(position[0]-yc)*(position[0]-yc));
        float val = cv::saturate_cast<uchar>((sin(2*M_PI*(d-t*5)/120) - 0.7) * 300);
        pixel.x = val;
        pixel.y = val;
        pixel.z = val;
    }
};

// xxx.exe
// xxx.exe ooo.mp4
// xxx.exe ooo.mp4 123 456 (frame start, frame end)
int main(int argc, char *argv[]){
    const char wnd[] = "ta hen chi yeeeeeeee";
    // const char caffeConfig[] = "./model/deploy.prototxt";
    const char caffeConfig[] = "./model/deploy_lowres.prototxt";
    const char caffeWeight[] = "./model/res10_300x300_ssd_iter_140000.caffemodel";
    const char facemarkPath[] = "./model/lbfmodel.yaml";
    const cv::Scalar red = cv::Scalar(0, 0, 255);
    const cv::Scalar green = cv::Scalar(0, 255, 0);

    int i, j;
    bool ret;
    cv::VideoCapture cap;
    cv::Mat frame;
    int frameWidth, frameHeight;
    int key;
    cv::dnn::Net net;
    cv::Mat inputBlob, outputBlob;
    cv::Mat detection;
    float confidence;
    float x1, y1, x2, y2;
    std::vector<cv::Rect> faces;
    // cv::Ptr<cv::face::Facemark> facemark;
    // std::vector<std::vector<cv::Point2f>> landmarks; // [face, 68 points]
    cv::Mat chiyi;
    bool exportGif = false;
    char exportName[101];
    int iExport = 0, iStart = 0, iEnd = 1000;

    if(argc == 1) // use webcam
        cap.open(0);
    else
        cap.open(argv[1]);

    if(argc == 4){
        exportGif = true;
        iStart = atoi(argv[2]);
        iEnd = atoi(argv[3]);
    }

    // load model
    net = cv::dnn::readNetFromCaffe(caffeConfig, caffeWeight);
    // facemark = cv::face::createFacemarkLBF();
    // facemark->loadModel(facemarkPath);

    // hen chi yi
    cv::namedWindow(wnd);
    while(1){
        ret = cap.read(frame);
        if(frame.empty())
            break;
        frameHeight = frame.rows;
        frameWidth = frame.cols;
        // detect face
        inputBlob = cv::dnn::blobFromImage(frame, 1., cv::Size(300, 300), cv::Scalar(104., 117., 123.), false, false); // after resize face might become too small
        net.setInput(inputBlob, "data");
        outputBlob = net.forward("detection_out");
        detection = cv::Mat(outputBlob.size[2], outputBlob.size[3], CV_32F, outputBlob.ptr<float>()); // NHWC (1x1x200x7) -> WC (200x7)
        faces.clear();
        for(i = 0; i < detection.rows; ++i){
            confidence = detection.at<float>(i, 2);
            if(confidence > 0.7){
                x1 = detection.at<float>(i, 3) * frameWidth;
                y1 = detection.at<float>(i, 4) * frameHeight;
                x2 = detection.at<float>(i, 5) * frameWidth;
                y2 = detection.at<float>(i, 6) * frameHeight;
                faces.push_back(cv::Rect(cv::Point(x1, y1), cv::Point(x2, y2)));                
                // faces.push_back(cv::Rect(cv::Point(x1-10, y1-10), cv::Point(x2+10, y2+10))); // expand
            }
        }
        // // align facemark
        // ret = facemark->fit(frame, faces, landmarks);
        // display
        chiyi.create(frame.rows, frame.cols, CV_8UC3);
        for(i = 0; i < faces.size(); ++i){
            xc = faces[i].x + faces[i].width / 2;
            yc = faces[i].y + faces[i].height / 3;
            chiyi.setTo(0);
            chiyi.forEach<Pixel>(Magic());
            cv::add(frame, chiyi, frame);
            // cv::rectangle(frame, faces[i], green, 1, 4);
            // cv::circle(frame, cv::Point(xc, yc), 5, red, 2);
            // update
            // curr.push_back()
        }
        // if(ret)
        //     for(i = 0; i < faces.size(); ++i) // draw each face
        //         cv::face::drawFacemarks(frame, landmarks[i], red);
        cv::imshow(wnd, frame);
        // cv::imshow("test", chiyi);
        key = cv::waitKey(1);
        if(key == 27)
            break;

        // export
        if(exportGif && t >= iStart && t < iEnd){
            sprintf(exportName, "./result/tmp%d.jpg", iExport++);
            cv::imwrite(exportName, frame);
        }
        // update
        ++t;
    }
    cv::destroyAllWindows();

    return 0;
}

// https://github.com/opencv/opencv/tree/master/samples/dnn