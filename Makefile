all:
	g++ -c Point.h Point.cpp
	g++ -c Line.h Line.cpp
	g++ -c FrameBuffer.cpp
	g++ -o gg FrameBuffer.o Point.o Line.o main.cpp

run:
	./gg

clean:
	rm *.o
	rm *.gch
	rm gg