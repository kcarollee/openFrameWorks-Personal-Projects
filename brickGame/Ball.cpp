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
	radius = 10;
}

void Ball::draw()
{
	ofDrawCircle(pos, radius);
}

int Ball::touchedBar(Bar * b)
{
	if (((pos.y + radius) > b->pos.y) && 
		(pos.y < b->pos.y) &&
		(pos.x >= (b->pos.x) - radius) && 
		(pos.x <= (b->pos.x) + (b ->width) + radius)) {
		return 1;
	}
	else if (((pos.y - radius) < (b->pos.y) + (b->height)) &&
		(pos.y > b->pos.y + b->height) &&
		(pos.x >= (b->pos.x) - radius) &&
		(pos.x <= (b->pos.x) + (b->width) + radius)) {
		return 1;
	}
	//Hit from sides
	else if ((pos.x + radius > b->pos.x) &&
		(pos.x < b->pos.x) &&
		(pos.y >= (b->pos.y) - radius) &&
		(pos.y <= (b->pos.y) + (b->height) + radius)) {
		return 2;
	}
	else if ((pos.x - radius < (b->pos.x) + (b->width)) &&
		(pos.x > (b->pos.x + b->width)) &&
		(pos.y >= (b->pos.y) - radius) &&
		(pos.y <= (b->pos.y) + (b->height) + radius)) {
		return 2;
	}
	return 0;
}

int Ball::touchedBrick(Brick *br)
{
	//Hit from top and bottom
	if (((pos.y + radius) > br->pos.y) &&
		(pos.y < br ->pos.y) &&
		(pos.x >= (br->pos.x) - radius) &&
		(pos.x <= (br->pos.x) + (br->width) + radius)) {
		return 1;
	}
	else if (((pos.y - radius) < (br->pos.y) + (br->height)) &&
		(pos.y > br ->pos.y + br ->height) &&
		(pos.x >= (br->pos.x) - radius) &&
		(pos.x <= (br->pos.x) + (br->width) + radius)) {
		return 1;
	}
	//Hit from sides
	else if ((pos.x + radius > br->pos.x) &&
		(pos.x < br ->pos.x) &&
		(pos.y >= (br->pos.y) - radius) &&
		(pos.y <= (br->pos.y) + (br->height) + radius)) {
		return 2;
	}
	else if ((pos.x - radius < (br->pos.x) + (br ->width)) &&
		(pos.x > (br ->pos.x + br ->width)) &&
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
