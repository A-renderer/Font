#include "FrameBuffer.cpp"
#include <cstring>
#include <termios.h>
#include <fstream>

using namespace std;


FrameBuffer FB;

int main()
{
	FB.drawLine(Point(10,56), Point(45,40), 0, 255, 255,0);
	FB.drawLine(Point(599,0), Point(599,400), 0, 255, 255,0);
	
	return 0;
}