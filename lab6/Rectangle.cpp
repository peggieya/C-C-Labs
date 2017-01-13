#include <iostream>
#include <cmath>
#include "Shape.h"
#include "easygl.h"
#include "Rectangle.h"
using namespace std;

Rectangle::Rectangle() {}

Rectangle::Rectangle (string _name, string _colour, float _xcen, float _ycen,
	float _width, float _height) 
	: Shape(_name, _colour, _xcen, _ycen) {

	width = _width;
	height = _height;
}
Rectangle::~Rectangle() {
	// No dynamic memory to delete
}
void Rectangle::print() const {
	Shape::print();
	cout << "rectangle width: " << width;
	cout << " height: " << height << endl;
}
void Rectangle::scale(float scaleFac) {
	width *= scaleFac;
	height *= scaleFac;
}
float Rectangle::computeArea() const {

	float area = height*width;
	return area;
}
float Rectangle::computePerimeter() const {

	float perimeter = height + height + width + width;
	return perimeter;
}
void Rectangle::draw(easygl* window) const {

	float x1 = getXcen() - (width*0.5);
	float x2 = getXcen() + (width*0.5);
	float y1 = getYcen() - (height*0.5);
	float y2 = getYcen() + (height*0.5);

	window->gl_setcolor(getColour());
	window->gl_fillrect(x1, y1, x2, y2);

}
bool Rectangle::pointInside(float x, float y) const {

	//check wether the point of outside of the boundary of the rectangle
	//check for x-coord: x>=x1&x<=x2 -> inside
	//check for y-coord: y>=y1&y<=y2 -> inside

	float x1 = getXcen() - (width*0.5);
	float x2 = getXcen() + (width*0.5);
	float y1 = getYcen() - (height*0.5);
	float y2 = getYcen() + (height*0.5);

	return (x>=x1 && x<=x2 && y>=y1 && y<=y2);
}