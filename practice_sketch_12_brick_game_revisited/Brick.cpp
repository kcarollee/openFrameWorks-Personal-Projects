#include "Brick.h"

Brick::Brick()
{

}

Brick::~Brick()
{

}

void Brick::setup(float x, float y, float w, float h)
{
	pos.x = x;
	pos.y = y;
	width = w;
	height = h;
}

void Brick::draw()
{
	ofSetColor(150);
	ofDrawRectangle(pos, width, height);
}