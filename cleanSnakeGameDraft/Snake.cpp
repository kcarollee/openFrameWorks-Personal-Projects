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
	//set radius
	headRadius = 10;
	//body side is equal to the diameter of the head
	bodySide = 2 * headRadius;
	//start from the center of the screen
	headPosition.set(ofVec2f(ofGetWidth() / 2, ofGetHeight() / 2));
	//set velocity. velocity will remain constant since it's Sleep that
	//takes care of the actual speed
	//initial velocity takes the snake upwards
	velocity.set(ofVec2f(headRadius * 2, 0));
	
	ofAddListener(ofEvents().keyPressed, this, &Snake::keyPressedHandler);
}
void Snake::draw()
{
	ofDrawCircle(headPosition, headRadius);
}
void Snake::move()
{
	//add velocity to the position
	headPosition += velocity;
}
bool Snake::touchedFood(ofRectangle * food)
{
	//Hit from top and bottom
	if (((headPosition.y + headRadius) >= food->position.y) &&
		(headPosition.y <= food->position.y) &&
		(headPosition.x >= (food->position.x) - headRadius) &&
		(headPosition.x <= (food->position.x) + (food->width) + headRadius)) {
		return true;
	}
	else if (((headPosition.y - headRadius) <= (food->position.y) + (food->height)) &&
		(headPosition.y >= food->position.y + food->height) &&
		(headPosition.x >= (food->position.x) - headRadius) &&
		(headPosition.x <= (food->position.x) + (food->width) + headRadius)) {
		return true;
	}
	//Hit from sides
	else if ((headPosition.x + headRadius >= food->position.x) &&
		(headPosition.x <= food->position.x) &&
		(headPosition.y >= (food->position.y) - headRadius) &&
		(headPosition.y <= (food->position.y) + (food->height) + headRadius)) {
		return true;
	}
	else if ((headPosition.x - headRadius <= (food->position.x) + (food->width)) &&
		(headPosition.x >= (food->position.x + food->width)) &&
		(headPosition.y >= (food->position.y) - headRadius) &&
		(headPosition.y <= (food->position.y) + (food->height) + headRadius)) {
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
		}
		break;
	case OF_KEY_DOWN:
		if (velocity.y != 0) {}
		else {
			velocity.x = 0;
			velocity.y = bodySide;
		}
		break;
	case OF_KEY_LEFT:
		//left, right keys should register only when the snake is
		//moving vertically
		if (velocity.x != 0) {}
		else {
			velocity.x = bodySide * -1;
			velocity.y = 0;
		}
		break;
	case OF_KEY_RIGHT:
		if (velocity.x != 0) {}
		else {
			velocity.x = bodySide;
			velocity.y = 0;
		}
		break;

	}
}