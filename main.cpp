#include "FrameBuffer.cpp"
#include <cstring>
#include <termios.h>
#include <fstream>

using namespace std;

FrameBuffer FB;

void printLetter(int font[][2], int col, int size, int x, int y);
void printLetterCounter(int font1[][2], int col1, int font2[][2], int col2, int size, int x, int y);

int main()
{
	int size = 5;
	int font_V[][2] = {{1,1},{9,21},{11,21},{19,1},{17,1},{10,19},{3,1},{10,20}};
	int font_A_out[][2] = {{1,21},{9,1},{11,1},{19,21},{16,21},{14,15},{6,15},{4,21},{2,20}};
	int font_A_in[][2] = {{7,13},{13,13},{10,4},{10,9}};
	int font_N[][2] = {{1,1},{4,1},{15,18},{15,1},{17,1},{17,21},{14,21},{3,4},{3,21},{1,21},{3,3}};

	int col_V = sizeof(font_V)/sizeof(*font_V);
	int col_A_out = sizeof(font_A_out)/sizeof(*font_A_out);
	int col_A_in = sizeof(font_A_in)/sizeof(*font_A_in);
	int col_N = sizeof(font_N)/sizeof(*font_N);

	FB.clearscreen();

	printLetter(font_V, col_V, size, 0, 0);
	printLetterCounter(font_A_out, col_A_out, font_A_in, col_A_in, size, 12, 0);
	printLetter(font_N, col_N, size, 31, 0);

	printLetter(font_V, col_V, size, 0, 25);
	printLetterCounter(font_A_out, col_A_out, font_A_in, col_A_in, size, 12, 25);
	printLetter(font_N, col_N, size, 31, 25);

	return 0;
}

void printLetter(int font[][2], int col, int size, int x, int y) {
	vector<Point> points;
	points.clear();
	for(int i=0;i<col-1;i++) {
		points.push_back(Point(font[i][0]*size+size*x,font[i][1]*size+size*y));
	}
	Polygon Poly(points);
	Poly.firePoint = Point(font[col-1][0]*size+size*x,font[col-1][1]*size+size*y);
	FB.drawPolygon(Poly.e,25,25,122,0);
	FB.floodFill(Poly.firePoint.x, Poly.firePoint.y, 255, 182, 193, 100, 149, 237);
}

void printLetterCounter(int font1[][2], int col1, int font2[][2], int col2, int size, int x, int y) {
	vector<Point> points;
	vector<Point> points2;

	points.clear();
	for(int i=0;i<col1-1;i++) {
		points.push_back(Point(font1[i][0]*size+size*x,font1[i][1]*size+size*y));
	}
	Polygon Poly1(points);
	FB.drawPolygon(Poly1.e,25,25,122,0);
	
	points2.clear();
	for(int i=0;i<col2-1;i++) {
		points2.push_back(Point(font2[i][0]*size+size*x,font2[i][1]*size+size*y));
	}
	Polygon Poly2(points2);

	FB.drawPolygon(Poly2.e,25,25,122,0);
	
	Poly1.firePoint = Point(font1[col1-1][0]*size+size*x,font1[col1-1][1]*size+size*y);
	
	FB.floodFill(Poly1.firePoint.x, Poly1.firePoint.y, 255, 182, 193, 100, 149, 237);
}