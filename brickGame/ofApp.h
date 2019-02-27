#pragma once

#include "ofMain.h"
#include "Bar.h"
#include "Ball.h"
#include "Brick.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
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
	Bar *server;
	Ball *ball;
	vector <Brick*> bricks;
	Brick *brick;
	int touchedBrickID;
	bool touchedFlag;

	ofVec2f ballVelocity;

		
};
