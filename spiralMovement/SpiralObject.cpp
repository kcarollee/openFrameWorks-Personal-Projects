#include "SpiralObject.h"

SpiralObject::SpiralObject() {}
SpiralObject::~SpiralObject() {
	
}


void SpiralObject::setup(float diameter, ofVec2f centerPos)
{
	angle = 0;

	incLength = diameter / 2;
	
	this->diameter = diameter;
	this->centerPos = centerPos;

	velocity = 0.1;

	pos.x = centerPos.x + diameter / 2;
	pos.y = centerPos.y;

	

	rValue = bValue = gValue = 10;
}

void SpiralObject::move()
{
	
	prevPos.x = pos.x;
	prevPos.y = pos.y;
	if (0 <= angle && angle < PI) {
		
		pos.x = centerPos.x + (diameter / 2) * cos(angle);
		pos.y = centerPos.y + (diameter / 2) * sin(angle);

		angle += velocity;

		if (angle >= PI) {
			diameter += incLength;
		}
		
	}

	else if (PI <= angle && angle < 2 * PI) {
		pos.x = (centerPos.x + incLength / 2) + (diameter / 2) * cos(angle);
		pos.y = centerPos.y + (diameter / 2) * sin(angle);

		angle += velocity;

		if (angle >= 2 * PI) {
			diameter += incLength;
			angle = 0;
		}
	}
}


void SpiralObject::draw(ofFbo fbo)
{
	ofSetCircleResolution(120);
	fbo.begin();
	ofSetColor(ofColor(rValue += 1, bValue += 5, gValue += 10));
	ofDrawCircle(pos, ofRandom(1, 4));
	fbo.end();
}

void SpiralObject::draw()
{
	ofSetCircleResolution(60);
	ofSetColor(ofColor(rValue += 1, bValue += 5, gValue += 10));
	ofDrawCircle(pos, 1);
}

void SpiralObject::drawLineMode(ofFbo fbo)
{
	fbo.begin();
	ofSetColor(0);
	ofSetLineWidth(2);
	ofDrawLine(prevPos, pos);
	fbo.end();
}