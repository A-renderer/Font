#include "FrameBuffer.cpp"
#include <cstring>
#include <termios.h>
#include <fstream>

using namespace std;


FrameBuffer FB;

int main()
{
	FB.drawLine(Point(10,56), Point(45,40), 0, 255, 255,0);
	FB.drawLine(Point(599,0), Point(599,400), 0, 167, 254,0);
	cout << FB.getR(599,0) << "\n";
	cout << FB.getG(599,0) << "\n";
	cout << FB.getB(599,0) << "\n";
	cout << FB.getA(599,0) << "\n";
	
	return 0;
}