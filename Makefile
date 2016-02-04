all:
	g++ -o main FrameBuffer.cpp Point.cpp Line.cpp main.cpp

run:
	./main

clean:
	rm main