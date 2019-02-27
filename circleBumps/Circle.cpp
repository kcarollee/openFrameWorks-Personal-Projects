#include "Circle.h"

Circle::Circle()
{

}
Circle::~Circle()
{

}
void Circle::setup(int x, int y, int r, ofColor c)
{
	radius = r;
	posX = x;
	posY = y;
	color = c;

	ofSetCircleResolution(64);
}

void Circle::draw()
{
	ofSetColor(color);
	ofDrawCircle(posX, posY, radius);
}

void Circle::moveCircleLinear(float x, float y)
{
	/*This goes in the update function.*/
	posX += x;
	posY += y;
}



void Circle::keyPressedHandler()
{
	
}