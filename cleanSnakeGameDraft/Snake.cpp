#include "Snake.h"

Snake::Snake()
{

}
Snake::~Snake()
{
	ofRemoveListener(ofEvents().keyPressed, this, &Snake::keyPressedHandler);
}
void Snake::setup()
{
	//set trigger to false
	moveFlag = false;
	//set length
	length = 0;
	//set radius
	headRadius = 10;
	//body side is equal to the diameter of the head
	bodySide = 2 * headRadius;
	//start from the center of the screen
	headPosition.set(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2));
	//set velocity. velocity will remain constant since it's Sleep that
	//takes care of the actual speed
	//initial velocity takes the snake upwards
	velocity.set(ofVec2f(0, 0));
	//vector of head positions is needed to keep track of 
	//body positions
	headPositions.push_back(headPosition);
	
	ofAddListener(ofEvents().keyPressed, this, &Snake::keyPressedHandler);
}

void Snake::draw()
{
	//set color
	ofSetColor(255, 0, 0);
	//draw head
	ofDrawCircle(headPosition, headRadius);
	//draw body
	if (length >= 1) {
		for (auto bp : bodyPositions) {
			//set color
			ofSetColor(0, 0, 255);
			//rectifying body position
			ofDrawRectangle(bp.x - headRadius, bp.y - headRadius, 20, 20);
		}
	}
}
void Snake::move()
{
	if (moveFlag) {
		//add velocity to the position
		headPosition += velocity;
		//append new head position to the vector headPositions
		headPositions.push_back(headPosition);
		//continuously update bodyPositions
		if (length >= 1) {
			for (int i = 0; i < bodyPositions.size(); i++) {
				bodyPositions[i] = headPositions[headPositions.size() - i - 2];
			}
		}
	}
}
void Snake::getLonger(vector<ofVec2f> headPositions)
{
	//increase length
	length += 1;
	//position for new body
	ofVec2f bodyPosition;
	bodyPosition = headPositions[headPositions.size() - 1 - length];
	bodyPositions.push_back(bodyPosition);

}
bool Snake::touchedRectangle(ofRectangle * rect)
{
	//Hit from top and bottom
	if (((headPosition.y + headRadius) >= rect->position.y) &&
		(headPosition.y <= rect->position.y) &&
		(headPosition.x >= (rect->position.x) - headRadius) &&
		(headPosition.x <= (rect->position.x) + (rect->width) + headRadius)) {
		return true;
	}
	else if (((headPosition.y - headRadius) <= (rect->position.y) + (rect->height)) &&
		(headPosition.y >= rect->position.y + rect->height) &&
		(headPosition.x >= (rect->position.x) - headRadius) &&
		(headPosition.x <= (rect->position.x) + (rect->width) + headRadius)) {
		return true;
	}
	//Hit from sides
	else if ((headPosition.x + headRadius >= rect->position.x) &&
		(headPosition.x <= rect->position.x) &&
		(headPosition.y >= (rect->position.y) - headRadius) &&
		(headPosition.y <= (rect->position.y) + (rect->height) + headRadius)) {
		return true;
	}
	else if ((headPosition.x - headRadius <= (rect->position.x) + (rect->width)) &&
		(headPosition.x >= (rect->position.x + rect->width)) &&
		(headPosition.y >= (rect->position.y) - headRadius) &&
		(headPosition.y <= (rect->position.y) + (rect->height) + headRadius)) {
		return true;
	}
	return false;
}
/*
bool Snake::collidedWithSelf()
{
	for (int i = 1; i < bodyPositions.size(); i++) {
		ofRectangle *temp;
		temp = new ofRectangle(bodyPositions[i].x - headRadius, bodyPositions[i].y - headRadius, 20, 20);
		if (touchedRectangle(temp)) {
			return true;
		}
	}
	return false;
}
*/
bool Snake::collidedWithWindow()
{
	if ((headPosition.x - headRadius < 0) ||
		(headPosition.x + headRadius > ofGetWidth())) {
		return true;
	}
	if ((headPosition.y - headRadius < 0) ||
		(headPosition.y + headRadius > ofGetHeight())) {
		return true;
	}
	return false;
}
void Snake::keyPressedHandler(ofKeyEventArgs & key)
{
	switch (key.key) {
	case OF_KEY_UP:
		//down, up keys should register only when the snake is 
		//moving horizontally
		if (velocity.y != 0) {}
		else {
			velocity.x = 0;
			velocity.y = bodySide * -1;
			moveFlag = true;
		}
		break;
	case OF_KEY_DOWN:
		if (velocity.y != 0) {}
		else {
			velocity.x = 0;
			velocity.y = bodySide;
			moveFlag = true;
		}
		break;
	case OF_KEY_LEFT:
		//left, right keys should register only when the snake is
		//moving vertically
		if (velocity.x != 0) {}
		else {
			velocity.x = bodySide * -1;
			velocity.y = 0;
			moveFlag = true;
		}
		break;
	case OF_KEY_RIGHT:
		if (velocity.x != 0) {}
		else {
			velocity.x = bodySide;
			velocity.y = 0;
			moveFlag = true;
		}
		break;

	}
}