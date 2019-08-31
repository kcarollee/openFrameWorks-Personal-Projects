#pragma once
#include "ofMain.h"

#include "Brick.h"

class Ball
{
public:
	Ball();
	~Ball();

	void setup();
	void draw();
	void move(ofVec2f vel);
	int touchedBrick(Brick *br);


public:
	float radius;
	ofVec2f pos;

};