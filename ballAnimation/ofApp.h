#pragma once

#include "ofMain.h"

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
		void applyForce(ofVec2f force);
		void showStatus();
public:
	ofVec2f location;
	ofVec2f velocity;
	ofVec2f acceleration;
	float radius;
	ofTrueTypeFont font;

	string message;

	ofVec2f maxLimit;
	ofFbo fbo;
};
