#include "Polygon.h"

Polygon::Polygon() {
	n = 0;
}

Polygon::Polygon(vector<Point> P) {
	n = P.size();
	e = P;
	e.push_back(e[0]); //harus balik ke titik awal
}

Polygon& Polygon::operator<<(const vector<Point>& P) {
	n = P.size();
	e = P;
	e.push_back(e[0]);

	return *this;
}

void Polygon::insert(Point point) {
	e[n] = point;
	e.push_back(e[0]);
	++n;
}

float Polygon::getMaxX() {
	int i=1;
	float maxX=e[0].x;
	while(i<n) {
		if(e[i].x>maxX) {
			maxX=e[i].x;
		}
		i++;
	}
	return maxX;
}

float Polygon::getMinX() {
	int i=1;
	float minX=e[0].x;
	while(i<n) {
		if(e[i].x<minX) {
			minX=e[i].x;
		}
		i++;
	}
	return minX;
}

float Polygon::getMaxY() {
	int i=1;
	float maxY=e[0].y;
	while(i<n) {
		if(e[i].y>maxY) {
			maxY=e[i].y;
		}
		i++;
	}
	return maxY;
}

float Polygon::getMinY() {
	int i=1;
	float minY=e[0].y;
	while(i<n) {
		if(e[i].y<minY) {
			minY=e[i].y;
		}
		i++;
	}
	return minY;
}

float Polygon::getMidY() {
	int i=1;
	float maxY=getMaxY();

	i=1;
	float minY=getMinY();

	return (maxY + minY)/2;
}

float Polygon::getMidX() {
	int i=1;
	float maxX=getMaxY();

	i=1;
	float minX=getMinX();

	return (maxX + minX)/2;
}

void Polygon::moveRight(float dx) {
	int i=0;
	while(i<n)
	{
		e[i].x+=dx;
		i++;
	}
	firePoint.x+=dx;
}

void Polygon::moveLeft(float dx) {
	int i=0;
	while(i<n)
	{
		e[i].x-=dx;
		i++;
	}
	firePoint.x-=dx;
}


void Polygon::moveUp(float dy) {
	int i=0;
	while(i<n)
	{
		e[i].y-=dy;
		i++;
	}
	firePoint.x-=dy;
}

void Polygon::moveDown(float dy) {
	int i=0;
	while(i<n)
	{
		e[i].y+=dy;
		i++;
	}
	firePoint.y+=dy;
}
