#pragma once
#include "ofMain.h"
#include "ofEvents.h"

class Circle
{
public:
	Circle();
	~Circle();

	void setup(int x, int y, int r, ofColor c);
	void draw();


	void keyPressedHandler();
	void moveCircleLinear(float x, float y);


public:
	ofColor color;
	float radius;
	float posX;
	float posY;
};