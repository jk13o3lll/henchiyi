# henchiyi
Ta hen chi yi.

## Reference

Video source: [https://youtu.be/6WImPscMmfw](https://youtu.be/6WImPscMmfw)

![ta hen chi yi](tahenchiyi.jpg)

## How to use it

1. Compile the source code

        (For Linux)
        g++ -I<opencv include dir> main.cpp -o henchiyi.exe -L<opencv lib dir> -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui -lopencv_videoio -lopencv_dnn -lopencv_face

        (For Windows)
        g++ -I<opencv include dir> main.cpp -o henchiyi.exe -L<opencv lib dir> -lopencv_coreXXX -lopencv_imgcodecsXXX -lopencv_imgprocXXX -lopencv_highguiXXX -lopencv_videoioXXX -lopencv_dnnXXX -lopencv_faceXXX
        (XXX is the version number of your OpenCV)

1. Run the program

        ./henciyi.exe                               // use webcam
        ./henciyi.exe <your video>.mp4              // use video
        ./henciyi.exe <your video>.mp4.mp4 10 310   // use video and export processed frames (last two arguments are the frame to start and end respectively)

1. Ta hen chi YEEEEEEEEEEEE

    Video source: [https://youtu.be/GcdwBoqW6TU](https://youtu.be/GcdwBoqW6TU)
    ![ta hen chi yi](result1.gif)

    Video source: [https://youtu.be/ZVKVXzSGxC8](https://youtu.be/ZVKVXzSGxC8)
    ![ta hen chi yi](result2.gif)

## Contact

ccwang.jack@gmail.com