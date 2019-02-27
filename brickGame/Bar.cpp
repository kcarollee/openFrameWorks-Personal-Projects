#include "Bar.h"

Bar::Bar()
{
	
}

Bar::~Bar()
{
	ofRemoveListener(ofEvents().keyPressed, this, &Bar::keyPressedHandler);
}

void Bar::setup()
{
	pos.x = ofGetWidth() / 2;
	pos.y = ofGetHeight() - 80;
	
	width = 80;
	height = 20;

	ofAddListener(ofEvents().keyPressed, this, &Bar::keyPressedHandler);
}

void Bar::draw()
{
	ofSetColor(0, 200, 200);
	ofDrawRectangle(pos, width, height);
}

void Bar::keyPressedHandler(ofKeyEventArgs & key)
{
	
	if (key.key == OF_KEY_RIGHT) {
		pos.x += 30;
	}

	if (key.key == OF_KEY_LEFT) {
		pos.x -= 30;
	}
}
