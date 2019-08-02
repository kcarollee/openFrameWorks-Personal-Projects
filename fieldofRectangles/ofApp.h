#pragma once

#include "ofMain.h"
struct Rect {
	ofVec2f c1, c2, c3, c4;
	ofColor color;
	vector<ofVec2f*> vertArr;
	// c1: initial position
	void setup(ofVec2f c1, float side) {
		this->c1 = c1;
		c2.x = c1.x + side;
		c2.y = c1.y;

		c3.x = c1.x + side;
		c3.y = c1.y + side;

		c4.x = c1.x;
		c4.y = c1.y + side;

		vertArr.push_back(&this->c1);
		vertArr.push_back(&this->c2);
		vertArr.push_back(&this->c3);
		vertArr.push_back(&this->c4);

		color = ofColor(ofRandom(50, 200), ofRandom(50, 200), ofRandom(50, 200));
	}

	void draw() {
		ofNoFill();
		ofSetLineWidth(1);
		ofSetColor(color);
		ofSetPolyMode(OF_POLY_WINDING_NONZERO);
		ofBeginShape();
		ofVertex(c1);
		ofVertex(c2);
		ofVertex(c3);
		ofVertex(c4);
		ofEndShape();
	}

	
	void react(float x, float y) {
		for (ofVec2f* vp : vertArr) {
			vp->x -= ((vp->x - x) / 1000) * ofRandom(-1, 1.7);
			vp->y -= ((vp->y - y) / 1000) * ofRandom(-1, 1.7);
		}
	}

	void react2(float x, float y) {
		
			c2.x -= ((c2.x - x) / 100) * ofRandom(-0.7, 1);
			c2.y -= ((c2.y - y) / 100) * ofRandom(-0.7, 1);
		
	}
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
		void reset();

public:
	vector<Rect*> rectArr;
	Rect* test = new Rect;
	float sideLength;
	float gap;

	bool start = false;

	int widthNum;
	int heightNum;
		
};
