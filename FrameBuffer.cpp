#include "Polygon.h"

class FrameBuffer {
public:

	FrameBuffer() {
	fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    int screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (atoi (fbp) == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    printf("The framebuffer device was mapped to memory successfully.\n");
	}

	~FrameBuffer() {
		munmap(fbp, 0);
		close(fbfd);
	}

	fb_var_screeninfo getvinfo() {
		return vinfo;
	}

	fb_fix_screeninfo getfinfo() {
		return finfo;
	}

	int getfbfd() {
		return fbfd;
	}

	char* getfbp() {
		return fbp;
	}

	void putPixel(Point P, int r, int g, int b, int a) {
		location = (P.x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                           (P.y+vinfo.yoffset) * finfo.line_length;

		*(fbp + location) = b; // blue 
        *(fbp + location + 1) = g;  // green
        *(fbp + location + 2) = r; // red
        *(fbp + location + 3) = a; // transparency
	}

	void drawLine(Point P1, Point P2, int r, int g, int b, int a) {
		int dx =  abs(P2.x-P1.x), sx = P1.x<P2.x ? 1 : -1; //sign value for x
	   	int dy = -abs(P2.y-P1.y), sy = P1.y<P2.y ? 1 : -1;  //sign value for y
	   	int err = dx+dy; int e2; /* error value e_xy */
	 
	   	for(;;){  /* loop */
	   		Point Ptemp(P1.x,P1.y);
	    	putPixel(Ptemp,r,g,b,a);

	      	if (P1.x==P2.x && P1.y==P2.y) break; //berarti titik berhimpit
	      	e2 = 2*err;
	      	if (e2 >= dy) { err += dy; P1.x += sx; } /* e_xy+e_x > 0 */
	      	if (e2 <= dx) { err += dx; P1.y += sy; } /* e_xy+e_y < 0 */
	   	}
	}

	void drawPolygon(Polygon P, int r, int g, int b, int a) {
		for (int i=0; i<P.n-1; ++i) {
			drawLine(P.e[i], P.e[i+1], r, g, b, a);
		}
	}

	int getB(int x, int y){
		int blue;
		int color = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                           (y+vinfo.yoffset) * finfo.line_length;
		blue = *(fbp + color); 
		if(blue < 0) {
			blue+=256;
		}
		return blue;
	}

	int getG(int x, int y){
		int green;
		int color = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                           (y+vinfo.yoffset) * finfo.line_length;
		green = *(fbp + color + 1); 
		if(green < 0){
			green+=256;
		}	
		return green;	
	}	

	int getR(int x, int y){
		int red;
		int color = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                           (y+vinfo.yoffset) * finfo.line_length;
		red = *(fbp + color + 2); 
		if(red < 0){
			red+=256;
		}
		return red;
	}		
		
	int getA(int x, int y){
		int trans;
		int color = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                           (y+vinfo.yoffset) * finfo.line_length;
		trans = *(fbp + color + 3); 
		if(trans < 0){
			trans+=256;
		}
		return trans;
	}

private:
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	int fbfd;					/* frame buffer file descriptor */
	char* fbp;
	long int screensize;
	long int location;
};
