#include <iostream>
#include <cmath>
#include "Shape.h"
#include "easygl.h"
#include "Circle.h"

using namespace std;

//constructor
Circle::Circle(string _name, string _colour, float _xcen, float _ycen,
	float _radius) 
	: Shape (_name, _colour, _xcen, _ycen) {

	radius = _radius;
}

//distructor
Circle::~Circle() {
	// No dynamic memory to delete
}

void Circle::print() const {
	Shape::print();
	cout << "circle radius: " << radius <<endl;
}
void Circle::scale(float scaleFac) {
	radius *= scaleFac;
}
float Circle::computeArea() const {
	float area = PI*radius*radius;
	return area;
}
float Circle::computePerimeter() const {
	float perimeter = PI*radius * 2;
	return perimeter;
}
void Circle::draw(easygl* window) const {
	// Load up the data structure needed by easygl, and draw the triangle
	// using the easygl::draw_polygon call.

	window->gl_setcolor(getColour());
	window->gl_fillarc(getXcen(), getYcen(), radius, 0, 360);
}
bool Circle::pointInside(float x, float y) const {

	//in order to check wether a point is inside of a circle
	//check wether the distance from the centre to the point is less than radius
	//yes -> inside -> return true
	//no -> outside -> return false

	float x_con = getXcen() - x;//x-conponment of the distance
	float y_con = getYcen() - y;//y-conpinment of the distance
	float distance = sqrt((x_con*x_con) + (y_con*y_con));

	return (distance <= radius);
}