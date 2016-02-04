#ifndef POLYGON_H
#define POLYGON_H

#include "Point.h"
#include <string>
#include "math.h"

class Polygon {
public:
	Polygon();

	Polygon(vector<Point> P);

	Polygon& operator<<(const vector<Point>& P);
	
	void insert(Point point);

	float getMaxX();

	float getMinX();

	float getMaxY();

	float getMinY();

	float getMidY();

	float getMidX();

	void moveRight(float dx);

	void moveLeft(float dx);

	void moveUp(float dy);

	void moveDown(float dy);

	int n; //jumlah titik
	vector<Point> e; //titik2 poligon
	Point firePoint;

private:

};

#endif
