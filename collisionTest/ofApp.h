#pragma once

#include "ofMain.h"
#include "ofPixels.h"
#include "Circle.h"

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
		void collisionCheck(vector <Circle*> carr);
		void windowCollision(vector <Circle*> carr);
public:
	ofVec2f pos;
	ofVec2f vel;
	vector <Circle*> carr;
	vector <float> varrx;
	vector <float> varry;
	string message;
	ofTrueTypeFont fnt;
	int circleID;
	bool collided;
};
