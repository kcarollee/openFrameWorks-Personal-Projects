#pragma once
#include "ofMain.h"
#include "ofEvents.h"

class Snake
{
public:
	Snake();
	~Snake();
	void setup();
	void draw();
	void keyPressedHandler(ofKeyEventArgs & key);
	void move();
	bool touchedFood(ofRectangle * food);

public:
	int length;
	float headRadius;
	float bodySide;
	ofVec2f headPosition;
	ofVec2f velocity;

	
};