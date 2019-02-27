#include "Circle.h"

Circle::Circle()
{

}
Circle::~Circle()
{
	ofRemoveListener(ofEvents().mousePressed, this, &Circle::mousePressedHandler);
	ofRemoveListener(ofEvents().mouseDragged, this, &Circle::mouseDraggedHandler);
	ofRemoveListener(ofEvents().mouseReleased, this, &Circle::mouseReleasedHandler);
}



void Circle::setup(ofVec2f pos, ofVec2f vel, float r)
{
	font.load("verdana.ttf", 10);
	id = "";
	id_num = 0;
	position.x = pos.x;
	position.y = pos.y;

	velocity.x = vel.x;
	velocity.y = vel.y;

	radius = r;

	c = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));

	ofAddListener(ofEvents().mousePressed, this, &Circle::mousePressedHandler);
	ofAddListener(ofEvents().mouseDragged, this, &Circle::mouseDraggedHandler);
	ofAddListener(ofEvents().mouseReleased, this, &Circle::mouseReleasedHandler);

}

void Circle::draw()
{
	ofSetColor(255, 0, 0);
	id = to_string(id_num);
	font.drawString(id, position.x - 5, position.y + 5);

	ofNoFill();
	ofSetColor(c);
	ofSetCircleResolution(64);
	ofDrawCircle(position.x, position.y, radius);
}

void Circle::move()
{
	position.x += velocity.x;
	position.y += velocity.y;
}

float Circle::showRadius()
{
	return radius;
}

void Circle::mousePressedHandler(ofMouseEventArgs & mouse)
{
	if (isInside(mouse.x, mouse.y)) {
		position.x = mouse.x;
		position.y = mouse.y;
		velocity.x = 0;
		velocity.y = 0;
	}
}

void Circle::mouseDraggedHandler(ofMouseEventArgs & mouse)
{
	if (isInside(mouse.x, mouse.y)) {
		position.x = mouse.x;
		position.y = mouse.y;
	}
}

void Circle::mouseReleasedHandler(ofMouseEventArgs & mouse)
{
	velocity.x = ofRandom(-10, 10);
	velocity.y = ofRandom(-10, 10);
}

bool Circle::isInside(float x, float y)
{
	if (ofDist(x, y, position.x, position.y) <= radius) {
		return true;
	}
	return false;
}