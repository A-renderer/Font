#include "FrameBuffer.cpp"
#include <cstring>
#include <termios.h>
#include <fstream>

using namespace std;


FrameBuffer FB;

int main()
{
	int size = 20;
	int col;
	vector<Point> e;
	
	int font_V[][2] = {{1,1},{9,21},{11,21},{19,1},{17,1},{10,19},{3,1},{10,20}};	

	FB.clearscreen();
	col = sizeof(font_V)/sizeof(*font_V);
	for(int i=0;i<sizeof(font_V)/sizeof(*font_V)-1;i++) {
		e.push_back(Point(font_V[i][0]*size,font_V[i][1]*size));
	}
	Polygon Poly_V(e);
	Poly_V.firePoint = Point(font_V[col-1][0]*size,font_V[col-1][1]*size);
	
	FB.drawPolygon(Poly_V.e,0,255,255,0);
	FB.floodFill(Poly_V.firePoint.x, Poly_V.firePoint.y, 0, 255, 0, 255, 0, 0);

	e.clear();
	
	return 0;
}