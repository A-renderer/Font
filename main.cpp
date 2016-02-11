#include "FrameBuffer.cpp"
#include <cstring>
#include <termios.h>
#include <fstream>
#include <pthread.h>

using namespace std;

FrameBuffer FB;

void printLetter(int font[][2], int col, float size, int x, int y);
void printLetterCounter(int font1[][2], int col1, int font2[][2], int col2, float size, int x, int y);

int main()
{
	float size = 1.0;
	int font_V[][2] = {{1,1},{9,21},{11,21},{19,1},{17,1},{10,19},{3,1},{10,20}};
	int font_A_out[][2] = {{1,21},{9,1},{11,1},{19,21},{16,21},{14,15},{6,15},{4,21},{2,20}};
	int font_A_in[][2] = {{7,13},{13,13},{10,4},{10,9}};
	int font_N[][2] = {{1,1},{4,1},{15,18},{15,1},{17,1},{17,21},{14,21},{3,4},{3,21},{1,21},{2,2}};
	int font_Y[][2] = {{1,1},{3,1},{10,10},{17,1},{19,1},{11,12},{11,21},{9,21},{9,12},{10,12}};
    	int font_E[][2] = {{1,1},{1,21},{14,21},{14,19},{3,19},
		{3,12},{14,12},{14,10},{3,10},{3,3},{14,3},{14,1},{2,2}};
	int font_I[][2] = {{1,1},{4,1},{4,21},{1,21},{2,2}};
	int font_Z[][2] = {{1,1},{14,1},{14,3},{3,19},{14,19},{14,21},{1,21},{1,18},{12,3},{1,3},{2,2}};
	int font_W[][2] = {{1,1},{4,1},{8,18},{12,1},{16,1},{20,18},{24,1},{27,1},{22,21},{18,21},{14,4},{10,21},{6,21},{14,3}};
	
	// INI YANG UKURAN 42
	int font_C[][2] = {{37,11},{36,9},{35,7},{32,4},{30,3},{27,2},{22,1},{19,1},{15,2},{11,3},
		{9,4},{6,6},{4,8},{3,10},{2,12},{1,18},{1,24},{2,30},{3,33},
		{4,35},{5,37},{6,38},{9,40},{11,41},{15,42},{20,42},{21,42},{26,41},{30,40},
		{32,39},{35,36},{36,34},{37,32},{31,30},{29,33},{26,35},{21,36},{20,36},{15,35},
		{11,33},{9,30},{8,28},{7,24},{7,20},{8,16},{9,14},{14,9},{19,7},{20,7},{26,8},{29,10},{31,13},{5,17}};
	int font_P_out[][2] = {{1,1},{11,1},{18,1},{24,2},{27,3},{28,4},{29,5},{30,6},{31,8},{31,16},{30,18},{29,19},{28,20},{27,21},
		{24,22},{18,23},{11,23},{5,23},{5,42},{1,42},{1,23},{2,2}}; // UKURAN 42
	int font_P_in[][2] = {{5,5},{16,5},{23,6},{25,8},{26,10},{26,14},{25,16},{23,18},{16,19},{5,19},{11,15}}; // UKURAN 42
	int font_J[][2] = {{19,1},{23,1},{23,32},{22,37},{20,39},{17,41},
		{13,42},{9,41},{6,39},{3,36},{2,31},{6,31},
		{7,34},{10,36},{13,37},{16,36},{18,34},
		{19,32},{21,2}}; //UKURAN 42
	int font_S[][2] = {
		{31,13},{31,11},{30,8},{26,4},{24,3},{20,2},{14,2},{10,3},{8,4},{5,7},
		{4,9},{3,12},{3,13},{4,16},{6,19},{9,21},{13,23},{21,24},{24,25},{27,27},
		{28,33},{25,37},{20,38},{17,38},{12,37},{9,36},{7,33},{6,30},{6,29},
		{2,29},{2,30},{3,34},{5,37},{7,39},{9,40},{11,41},{16,42},{21,42},{26,41},
		{28,40},{30,38},{32,35},{33,31},{33,30},{32,27},{30,24},{26,22},{21,20},{17,19},
		{13,18},{10,16},{8,14},{7,12},{8,10},{10,8},{12,7},{16,6},{18,6},{22,7},
		{24,8},{26,10},{27,13},{18,4}};
	int font_R_in[][2] = {{5,5},{16,5},{23,6},{25,8},{26,10},{26,14},{25,16},{23,18},{16,19},{5,19},{11,15}}; // UKURAN 42
	int font_R_out[][2] = {{1,1},{11,1},{18,1},{24,2},{27,3},{28,4},{29,5},{30,6},{31,8},{31,16},{30,18},{29,19},{28,20},{27,21},{24,22},{22,23},{31,42},{27,42},{18,23},{11,23},{5,23},{5,42},{1,42},{1,23},{2,2}}; // UKURAN 42


	int y_vanya = 25;
	int y_venny = 50;
	int y_pipin = 75;
	int y_azwar = 100;
	int y_jessica = 125;

	FB.clearscreen();

	while(y_jessica > 0) {
		printLetter(font_V, sizeof(font_V)/sizeof(*font_V), size, 5, y_vanya);
		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, 20, y_vanya);
		printLetter(font_N, sizeof(font_N)/sizeof(*font_N), size, 40, y_vanya);
		printLetter(font_Y, sizeof(font_Y)/sizeof(*font_Y), size, 58, y_vanya);
		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, 72, y_vanya);

		printLetter(font_V, sizeof(font_V)/sizeof(*font_V), size, 5, y_venny);
		printLetter(font_E, sizeof(font_E)/sizeof(*font_E), size, 25, y_venny);
		printLetter(font_N, sizeof(font_N)/sizeof(*font_N), size, 40, y_venny);
		printLetter(font_N, sizeof(font_N)/sizeof(*font_N), size, 60, y_venny);
		printLetter(font_Y, sizeof(font_Y)/sizeof(*font_Y), size, 78, y_venny);

		printLetterCounter(font_P_out, sizeof(font_P_out)/sizeof(*font_P_out), font_P_in, sizeof(font_P_in)/sizeof(*font_P_in), size/2, 5*2, y_pipin*2);
		printLetter(font_I, sizeof(font_I)/sizeof(*font_I), size, 22, y_pipin);
		printLetterCounter(font_P_out, sizeof(font_P_out)/sizeof(*font_P_out), font_P_in, sizeof(font_P_in)/sizeof(*font_P_in), size/2, 30*2, y_pipin*2);
		printLetter(font_I, sizeof(font_I)/sizeof(*font_I), size, 47, y_pipin);
		printLetter(font_N, sizeof(font_N)/sizeof(*font_N), size, 52, y_pipin);

		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, 5, y_azwar);
		printLetter(font_Z, sizeof(font_Z)/sizeof(*font_Z), size, 25, y_azwar);
		printLetter(font_W, sizeof(font_W)/sizeof(*font_W), size, 39, y_azwar);
		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, 62, y_azwar);
		printLetterCounter(font_R_out, sizeof(font_R_out)/sizeof(*font_R_out), font_R_in, sizeof(font_R_in)/sizeof(*font_R_in), size/2,  82*2, y_azwar*2);

		printLetter(font_J, sizeof(font_J)/sizeof(*font_J), size/2, 5*2, y_jessica*2);
		printLetter(font_E, sizeof(font_E)/sizeof(*font_E), size, 20, y_jessica);
		printLetter(font_S, sizeof(font_S)/sizeof(*font_S), size/2, 35*2, y_jessica*2);
		printLetter(font_S, sizeof(font_S)/sizeof(*font_S), size/2, 52*2, y_jessica*2);
		printLetter(font_I, sizeof(font_I)/sizeof(*font_I), size, 70, y_jessica);
		printLetter(font_C, sizeof(font_C)/sizeof(*font_C), size/2, 78*2, y_jessica*2);
		printLetterCounter(font_A_out, sizeof(font_A_out)/sizeof(*font_A_out), font_A_in, sizeof(font_A_in)/sizeof(*font_A_in), size, 98, y_jessica);

		y_vanya-=1; y_venny-=1; y_pipin-=1; y_azwar-=1; y_jessica-=1;
		size = size+0.05;
        	usleep(100000);
        	FB.clearscreen();
	}

	return 0;
}

void printLetter(int font[][2], int col, float size, int x, int y) {
	if(y > 0 &&  y < 512-size*y) {
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
	else {
		//gausah digambar
	}
}

void printLetterCounter(int font1[][2], int col1, int font2[][2], int col2, float size, int x, int y) {
	if(y > 0 && y < 512-size*y) {
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
	else {
		//gausah digambar
	}	
}
