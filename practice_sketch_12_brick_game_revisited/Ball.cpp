#include "Ball.h"

Ball::Ball()
{

}

Ball::~Ball()
{

}

void Ball::setup()
{
	pos.x = ofGetWidth() / 2;
	pos.y = ofGetHeight() / 2;
	radius = 1;
}

void Ball::draw()
{
	ofSetColor(255, 0, 255);
	ofDrawCircle(pos, radius);
}


int Ball::touchedBrick(Brick *br)
{
	//Hit from top and bottom
	if (((pos.y + radius) > br->pos.y) &&
		(pos.y < br->pos.y) &&
		(pos.x >= (br->pos.x) - radius) &&
		(pos.x <= (br->pos.x) + (br->width) + radius)) {
		return 1;
	}
	else if (((pos.y - radius) < (br->pos.y) + (br->height)) &&
		(pos.y > br->pos.y + br->height) &&
		(pos.x >= (br->pos.x) - radius) &&
		(pos.x <= (br->pos.x) + (br->width) + radius)) {
		return 1;
	}
	//Hit from sides
	else if ((pos.x + radius > br->pos.x) &&
		(pos.x < br->pos.x) &&
		(pos.y >= (br->pos.y) - radius) &&
		(pos.y <= (br->pos.y) + (br->height) + radius)) {
		return 2;
	}
	else if ((pos.x - radius < (br->pos.x) + (br->width)) &&
		(pos.x > (br->pos.x + br->width)) &&
		(pos.y >= (br->pos.y) - radius) &&
		(pos.y <= (br->pos.y) + (br->height) + radius)) {
		return 2;
	}
	return 0;
}

void Ball::move(ofVec2f vel)
{
	pos += vel;
}