#pragma once
#include "ofMain.h"
#include "ofEvents.h"

class Circle
{
public:
	Circle();
	~Circle();

	void setup(ofVec2f pos, ofVec2f vel, float r);
	void draw();
	void move();//this goes in the update function
	//void collisionCheck(vector<Circle*> carr);

	void mousePressedHandler(ofMouseEventArgs & mouse);
	void mouseDraggedHandler(ofMouseEventArgs & mouse);
	void mouseReleasedHandler(ofMouseEventArgs & mouse);

	bool isInside(float x, float y);
	float showRadius();

public:
	float radius;
	ofTrueTypeFont font;
	string id;
	int id_num;

	ofColor c;
	ofVec2f position;
	ofVec2f velocity;
}; 