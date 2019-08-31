#pragma once

#include "ofMain.h"


class Brick
{
public:
	Brick();
	~Brick();
	void setup(float x, float y, float w, float h);
	void draw();

public:
	ofVec2f pos;
	float width;
	float height;

};