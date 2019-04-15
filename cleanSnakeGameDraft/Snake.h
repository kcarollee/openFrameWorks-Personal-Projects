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
	void getLonger(vector<ofVec2f> headPositions);
	bool touchedRectangle(ofRectangle * rect);
	//bool collidedWithSelf();
	bool collidedWithWindow();

public:
	int length;
	float headRadius;
	float bodySide;
	//trigger movement
	bool moveFlag;
	ofVec2f headPosition;
	ofVec2f velocity;

	vector<ofVec2f> headPositions;
	vector<ofVec2f> bodyPositions;
	
};