#pragma once
#pragma once
#include "ofMain.h"
#include "ofEvents.h"

//extern vector<int> schedule;
//extern vector<vector<int>> scheduleArr;
class Block
{
public:
	Block();
	~Block();
	void setup(int x, int y, int w, int h);
	void draw();
	void reset();
	void mouseMovedHandler(ofMouseEventArgs & mouse);
	void mousePressedHandler(ofMouseEventArgs & mouse);
	bool isInside(int x, int y);
public:
	float posX;
	float posY;
	float width;
	float height;
	ofRectangle rect;
	ofColor color;
	int blockID;
	bool pressedFlag;
	static vector<int> schedule;
	static vector<vector<int>> scheduleArr;

	
};