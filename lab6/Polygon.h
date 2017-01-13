#ifndef POLYGON_H
#define	POLYGON_H

#include "Shape.h"
#include "easygl.h"
#include <iostream>
#include <cmath>
using namespace std;

class Polygon : public Shape {

private:
	t_point *relVertex;
	int numOfPoint;

	//helper functions
	t_point getVecBetweenPoints(t_point start, t_point end) const;
	float getCrossProduct(t_point vec1, t_point vec2) const;

public:
	Polygon(string _name, string _colour, float _xcen, float _ycen,
		t_point *_relVertex, int _numOfPoint);
	virtual ~Polygon();
    virtual void print() const;
	virtual void scale(float scaleFac);
	virtual float computeArea() const;
	virtual float computePerimeter() const;
	virtual void draw(easygl* window) const;
	virtual bool pointInside(float x, float y) const;
};


#endif
