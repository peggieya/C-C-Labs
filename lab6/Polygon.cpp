#include <iostream>
#include <cmath>
#include "Shape.h"
#include "easygl.h"
#include "Polygon.h"

using namespace std;

#define infinite 100000000000000000; //it is not the real infinite but is big enough

Polygon::Polygon(string _name, string _colour, float _xcen, float _ycen,
	t_point *_relVertex, int _numOfPoint) 
   : Shape (_name, _colour, _xcen, _ycen){

	relVertex = new t_point[_numOfPoint];

	for (int i = 0; i < _numOfPoint; i++) {
		relVertex[i].x = _relVertex[i].x;
		relVertex[i].y = _relVertex[i].y;
	}

	numOfPoint = _numOfPoint;
}

Polygon::~Polygon() {
	delete relVertex;
}

void Polygon::print() const {

	Shape::print();
	cout << "polygon";
	for (int i = 0; i < numOfPoint; i++) {
		cout << " (" << getXcen() + relVertex[i].x << "," << getYcen() + relVertex[i].y << ")";
	}
	cout << endl;
}

void Polygon::scale(float scaleFac) {
	for (int i = 0; i < numOfPoint; i++) {
		relVertex[i].x *= scaleFac;
		relVertex[i].y *= scaleFac;
	}
}

float Polygon::computeArea() const {


	float area = 0;
	int i = 0;
	int j = numOfPoint - 1;
	for (i = 0; i<numOfPoint; i++) {
		area = area + ((relVertex[j].x + relVertex[i].x) * (relVertex[j].y - relVertex[i].y));
		j = i;
	}
	area = area * 0.5;
	return area;
}

float Polygon::computePerimeter() const {
	float perimeter =0 ;
	float oneSide;
	int endpoint;
	t_point distance;

	for (int i = 0; i < numOfPoint; i++) {
		endpoint = (i + 1) % (numOfPoint);
		distance = getVecBetweenPoints(relVertex[i], relVertex[endpoint]);
		oneSide = sqrt(distance.x * distance.x + distance.y * distance.y);
		perimeter += oneSide;
	}
	return perimeter;
}

void Polygon::draw(easygl* window) const {

	t_point *coordinates = new t_point[numOfPoint];

	for (int i = 0; i < numOfPoint; i++) {
		coordinates[i].x = getXcen() + relVertex[i].x;
		coordinates[i].y = getYcen() + relVertex[i].y;
	}

	window->gl_setcolor(getColour());
	window->gl_fillpoly(coordinates, numOfPoint);

	delete coordinates;
}

bool Polygon::pointInside(float x, float y) const {

	t_point inputPoint; //the point which the user click
	inputPoint.x = x - getXcen();
	inputPoint.y = y - getYcen();

	//inorder to check wether a point is inside of the polygon
	//form a ray from the input point to its left
	//if the ray does not intersect with any sides of the triangle at its left -> outside -> return false
	//if the ray intersect two sides of the triangle -> outside -> return false
	//if the ray intersect only one side of the triangle -> indside -> return true

	t_point vectorOfSide;
	float distance, yDistance;
	int endpoint;
	int intersectSide =0; //count the number of sides intersect with the ray

	for (int startpoint = 0; startpoint < numOfPoint; startpoint++) {
		endpoint = (startpoint + 1) % numOfPoint; // Next vertex after startpoint
		vectorOfSide = getVecBetweenPoints(relVertex[startpoint], relVertex[endpoint]);
		yDistance = (inputPoint.y - relVertex[startpoint].y);
		if (vectorOfSide.y != 0) {
			distance = yDistance / vectorOfSide.y;
		}
		else if (yDistance == 0) {
			distance = 0;
		}
		else {
			distance = infinite; 
		}

		if (distance >= 0 && distance < 1) {
			float xIntersection = relVertex[startpoint].x + vectorOfSide.x * distance;
			if (xIntersection <= inputPoint.x)
				intersectSide++;
		}
	}
	bool result = (intersectSide == 1);
	return (result);
}

t_point Polygon::getVecBetweenPoints(t_point start, t_point end) const {
	t_point vec;
	vec.x = end.x - start.x;
	vec.y = end.y - start.y;
	return (vec);
}

float Polygon::getCrossProduct(t_point vec1, t_point vec2) const {
	float crossProduct;
	crossProduct = (vec1.x * vec2.x) - (vec1.y * vec2.y);
	return crossProduct;
}
