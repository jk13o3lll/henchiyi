main:
	g++ -I/usr/local/include/opencv4 main.cpp -o henchiyi.exe -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui -lopencv_videoio -lopencv_dnn -lopencv_face

test1:
	./henchiyi.exe './video/Original Video of Nick Young Meme.mp4'

test2:
	./henchiyi.exe './video/America was built by John Lewises, says former U.S. president Barack Obama in a eulogy.mp4'

export1:
	./henchiyi.exe './video/Original Video of Nick Young Meme.mp4' 480 630

export2:
	./henchiyi.exe './video/America was built by John Lewises, says former U.S. president Barack Obama in a eulogy.mp4' 10 310