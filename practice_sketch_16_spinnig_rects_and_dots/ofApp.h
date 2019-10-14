#pragma once

#include "ofMain.h"
class Tile {
public:
	void setup(int xpos, int ypos, int width, int height, int velocity, float deg) {
		this->xpos = xpos;
		this->ypos = ypos;
		this->width = width;
		this->height = height;
		this->dotxpos = 0;
		this->dotypos = 0;
		this->velocity = velocity;
		this->c = colorChange;
		this->deg = deg;
		colorChange += 0.5;
	}
	
	void rotate(int mode) { //mode 1: clockwise mode 0: counterclockwise
		ofPushMatrix();
		ofTranslate(xpos + width / 2, ypos + height / 2);
		ofRotate(deg);
		ofSetColor(255, 0, c, 255 - c);
		ofNoFill();
		ofDrawRectangle(- width / 2, - height / 2, width, height);	
		ofSetColor(0, 255, c, 50 + c);
		ofFill();
		ofDrawCircle(dotxpos-width / 2, dotypos-height / 2, 2);
		if (mode) moveDotClockwiseRotateMode();
		else moveDotCounterClockwiseRotateMode();
		ofPopMatrix();
	}

	void moveDotClockwiseRotateMode() {
		if (dotxpos >= 0 && dotxpos < width && dotypos == 0) {
			dotxpos += velocity;
		}
		else if (dotypos >= 0 && dotypos < height && dotxpos == width) {
			dotypos += velocity;
		}
		else if (dotxpos > 0 && dotxpos <= width  && dotypos == height) {
			dotxpos -= velocity;
		}
		else if (dotypos > 0 && dotypos <= height  && dotxpos == 0) {
			dotypos -= velocity;
		}
	}

	void moveDotCounterClockwiseRotateMode() {
		if (dotxpos > 0 && dotxpos <= width && dotypos == 0) {
			dotxpos -= velocity;
		}
		else if (dotypos > 0 && dotypos <= height && dotxpos == width) {
			dotypos -= velocity;
		}
		else if (dotxpos >= 0 && dotxpos < width && dotypos == height) {
			dotxpos += velocity;
		}
		else if (dotypos >= 0 && dotypos < height && dotxpos == 0) {
			dotypos += velocity;
		}
	}	
public:
	int xpos, ypos;
	int width, height;
	int dotxpos, dotypos;
	int velocity;
	static float colorChange;
	int c;
	float deg;
};
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
public:
	vector<Tile*> tileArr;
	int arraySize;
	int tileNumPerRow;
	float deg;

	int mode;

	string modeString;
};
