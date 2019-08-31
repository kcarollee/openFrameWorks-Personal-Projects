#pragma once

#include "ofMain.h"

#include "Ball.h"
#include "Brick.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void windowCollision();
	void brickCollision();

public:

	Ball *ball;
	vector <Brick*> bricks;
	Brick *brick;
	int touchedBrickID;
	bool touchedFlag;

	float brickWidth;
	float brickHeight;

	int brickHorizontalNum;
	int brickVerticalNum;
	

	ofVec2f ballVelocity;


};