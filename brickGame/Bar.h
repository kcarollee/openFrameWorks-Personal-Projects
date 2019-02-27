#pragma once
#include "ofMain.h"
#include "ofEvents.h"

class Bar
{
public:
	Bar();
	~Bar();
	void setup();
	void draw();
	void keyPressedHandler(ofKeyEventArgs & key);


public:
	ofVec2f pos;
	float width;
	float height;
};