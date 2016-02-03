#include "Line.h"

class FrameBuffer {
public:

	FrameBuffer() {
		fbfd = open("/dev/fb0",O_RDWR);
		if (!fbfd) {
			printf("Error: cannot open framebuffer device.\n");
			exit(1);
		}
		printf ("The framebuffer device was opened successfully.\n");

		/* get the fixed screen information */
		if (ioctl (fbfd, FBIOGET_FSCREENINFO, &finfo)) {
			printf("Error reading fixed information.\n");
			exit(2);
		}

		/* get variable screen information */
		if (ioctl (fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
			printf("Error reading variable information.\n");
			exit(3);
		}

		/* map the device to memory */
		fbp = (char*)mmap(0, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);

		if ((int)fbp == -1) {
			printf ("Error: failed to map framebuffer device to memory.\n");
			exit(4);
		}
		printf ("Framebuffer device was mapped to memory successfully.\n");
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

	void putPixel(Point P, int r, int g, int b, int t) {
		int location = (P.x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                           (P.y+vinfo.yoffset) * finfo.line_length;

		*(fbp + location) = b; // blue 
        *(fbp + location + 1) = g;  // green
        *(fbp + location + 2) = r; // red
        *(fbp + location + 3) = t; // transparency
	}

	void drawLine(Point P1, Point P2, int r, int g, int b, int t) {
		int dx =  abs(P2.x-P1.x), sx = P1.x<P2.x ? 1 : -1;
	   	int dy = -abs(P2.y-P1.y), sy = P1.y<P2.y ? 1 : -1; 
	   	int err = dx+dy, e2; /* error value e_xy */
	 
	   	for(;;){  /* loop */
	   		Point Ptemp(P1.x,P1.y);
	    	putPixel(Ptemp,r,g,b,t);

	      	if (P1.x==P2.x && P1.y==P2.y) break;
	      	e2 = 2*err;
	      	if (e2 >= dy) { err += dy; P1.x += sx; } /* e_xy+e_x > 0 */
	      	if (e2 <= dx) { err += dx; P1.y += sy; } /* e_xy+e_y < 0 */
	   	}
	}

	void drawLinePrimitive(int x1, int y1, int x2, int y2, int r, int g, int b, int t) {
		int dx =  abs(x2-x1), sx = x1<x2 ? 1 : -1;
	   	int dy = -abs(y2-y1), sy = y1<y2 ? 1 : -1; 
	   	int err = dx+dy, e2; /* error value e_xy */
	 
	   	for(;;){  /* loop */
	   		Point P(x1,y1);
	    	putPixel(P,r,g,b,t);
	      	if (x1==x2 && y1==y2) break;
	      	e2 = 2*err;
	      	if (e2 >= dy) { err += dy; x1 += sx; } /* e_xy+e_x > 0 */
	      	if (e2 <= dx) { err += dx; y1 += sy; } /* e_xy+e_y < 0 */
	   	}
	}

private:
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	int fbfd;					/* frame buffer file descriptor */
	char* fbp;
};
