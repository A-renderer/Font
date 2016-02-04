all:
	g++ -o main FrameBuffer.cpp Point.cpp Line.cpp Polygon.cpp main.cpp

run:
	./main

clean:
	rm main
