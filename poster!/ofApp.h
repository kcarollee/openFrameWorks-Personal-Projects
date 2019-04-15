#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
struct Zephanaiah {
	vector<char> message = { 'z', 'e', 'p', 'h', 'a', 'n', 'i', 'a', 'h' };
	float speed;
	ofVec2f pos;
	ofColor color;

	void setup(ofVec2f pos)
	{
		this->pos = pos;
		//color = ofColor(255, 255, 255);
		speed = ofRandom(0, 10);
	}

	void draw()
	{
		//ofSetColor(color);
		for (int i = 0; i < message.size(); i++) {
			if (isInZ(ofVec2f(pos.x, pos.y + 10 * i), ofVec2f(5, 5), 160, 200)) {
				ofSetColor(255, 0, 0);
				ofDrawBitmapString(message[i], pos.x, pos.y + 10 * i);
			}
			else if (isInE(ofVec2f(pos.x, pos.y + 10 * i), ofVec2f(170, 5), 160, 200)) {
				ofSetColor(255, 128, 0);
				ofDrawBitmapString(message[i], pos.x, pos.y + 10 * i);
			}
			else if (isInP(ofVec2f(pos.x, pos.y + 10 * i), ofVec2f(335, 5), 160, 200)) {
				ofSetColor(255, 255, 0);
				ofDrawBitmapString(message[i], pos.x, pos.y + 10 * i);
			}
			else if (isInH(ofVec2f(pos.x, pos.y + 10 * i), ofVec2f(5, 210), 160, 200)) {
				ofSetColor(255, 255, 0);
				ofDrawBitmapString(message[i], pos.x, pos.y + 10 * i);
			}
			else if (isInA(ofVec2f(pos.x, pos.y + 10 * i), ofVec2f(170, 210), 160, 200)) {
				ofSetColor(255, 0, 0);
				ofDrawBitmapString(message[i], pos.x, pos.y + 10 * i);
			}
			else if (isInN(ofVec2f(pos.x, pos.y + 10 * i), ofVec2f(335, 210), 160, 200)) {
				ofSetColor(255, 128, 0);
				ofDrawBitmapString(message[i], pos.x, pos.y + 10 * i);
			}
			else if (isInI(ofVec2f(pos.x, pos.y + 10 * i), ofVec2f(5, 415), 160, 200)) {
				ofSetColor(255, 128, 0);
				ofDrawBitmapString(message[i], pos.x, pos.y + 10 * i);
			}
			else if (isInA(ofVec2f(pos.x, pos.y + 10 * i), ofVec2f(170, 415), 160, 200)) {
				ofSetColor(255, 255, 0);
				ofDrawBitmapString(message[i], pos.x, pos.y + 10 * i);
			}
			else if (isInH(ofVec2f(pos.x, pos.y + 10 * i), ofVec2f(335, 415), 160, 200)) {
				ofSetColor(255, 0, 0);
				ofDrawBitmapString(message[i], pos.x, pos.y + 10 * i);
			}
			else {
				ofSetColor(128, 128, 128, 128);
				ofDrawBitmapString(message[i], pos.x, pos.y + 10 * i);
			}
		}
	}

	void move()
	{
		pos.y += speed;
		if (pos.y >= ofGetHeight()) {
			pos.y = -10 * speed;
		}
	}

	bool isInZ(ofVec2f pos, ofVec2f Zpos, float width, float height) {
		ofxBox2dPolygon p;
		p.begin();
		p.addVertex(Zpos.x, Zpos.y);
		p.addVertex(Zpos.x + width, Zpos.y);
		p.addVertex(Zpos.x + width, Zpos.y + height / 5);
		p.addVertex(Zpos.x + width / 5, Zpos.y + height * 4 / 5);
		p.addVertex(Zpos.x + width, Zpos.y + height * 4 / 5);
		p.addVertex(Zpos.x + width, Zpos.y + height);
		p.addVertex(Zpos.x , Zpos.y + height);
		p.addVertex(Zpos.x , Zpos.y + height * 4 / 5);
		p.addVertex(Zpos.x + width * 4 / 5, Zpos.y + height / 5);
		p.addVertex(Zpos.x, Zpos.y + height / 5);
		p.end();
		
		if (p.inside(pos.x, pos.y)) {
			return true;
		}
		return false;
	}

	bool isInE(ofVec2f pos, ofVec2f Epos, float width, float height) {
		ofxBox2dPolygon p;
		p.begin();
		p.addVertex(Epos.x, Epos.y);
		p.addVertex(Epos.x + width, Epos.y); 
		p.addVertex(Epos.x + width, Epos.y + height / 5);
		p.addVertex(Epos.x + width / 5, Epos.y + height / 5);
		p.addVertex(Epos.x + width / 5, Epos.y + height * 2 / 5);
		p.addVertex(Epos.x + width, Epos.y + height * 2 / 5);
		p.addVertex(Epos.x + width, Epos.y + height * 3 / 5);
		p.addVertex(Epos.x + width / 5, Epos.y + height * 3 / 5);
		p.addVertex(Epos.x + width / 5, Epos.y + height * 4 / 5);
		p.addVertex(Epos.x + width, Epos.y + height * 4 / 5);
		p.addVertex(Epos.x + width, Epos.y + height);
		p.addVertex(Epos.x, Epos.y + height);
		p.end();

		if (p.inside(pos.x, pos.y)) {
			return true;
		}
		return false;
	}

	bool isInP(ofVec2f pos, ofVec2f Ppos, float width, float height) {
		ofxBox2dPolygon p1, p2;

		p1.begin();
		p1.addVertex(Ppos.x, Ppos.y);
		p1.addVertex(Ppos.x + width, Ppos.y);
		p1.addVertex(Ppos.x + width, Ppos.y + height * 3 / 5);
		p1.addVertex(Ppos.x + width * 2 / 5, Ppos.y + height * 3 /5);
		p1.addVertex(Ppos.x + width * 2 / 5, Ppos.y + height);
		p1.addVertex(Ppos.x, Ppos.y + height);
		p1.end();

		p2.begin();
		p2.addVertex(Ppos.x + width * 2 / 5, Ppos.y + height / 5);
		p2.addVertex(Ppos.x + width * 4 / 5, Ppos.y + height / 5);
		p2.addVertex(Ppos.x + width * 4 / 5, Ppos.y + height * 2 / 5);
		p2.addVertex(Ppos.x + width * 2 / 5, Ppos.y + height * 2 / 5);

		if (p1.inside(pos.x, pos.y) && !p2.inside(pos.x, pos.y)) {
			return true;
		}
		return false;
	}
	bool isInH(ofVec2f pos, ofVec2f Hpos, float width, float height) {
		ofxBox2dPolygon p;
		p.begin();
		p.addVertex(Hpos.x, Hpos.y);
		p.addVertex(Hpos.x + width / 5, Hpos.y);
		p.addVertex(Hpos.x + width / 5, Hpos.y + height * 2 / 5);
		p.addVertex(Hpos.x + width * 4 / 5, Hpos.y + height * 2 / 5);
		p.addVertex(Hpos.x + width * 4 / 5, Hpos.y);
		p.addVertex(Hpos.x + width, Hpos.y);
		p.addVertex(Hpos.x + width, Hpos.y + height);
		p.addVertex(Hpos.x + width * 4 / 5, Hpos.y + height);
		p.addVertex(Hpos.x + width * 4 / 5, Hpos.y + height * 3 / 5);
		p.addVertex(Hpos.x + width / 5, Hpos.y + height * 3 / 5);
		p.addVertex(Hpos.x + width / 5, Hpos.y + height);
		p.addVertex(Hpos.x, Hpos.y + height);
		p.end();

		if (p.inside(pos.x, pos.y)) {
			return true;
		}
		return false;
	}

	bool isInA(ofVec2f pos, ofVec2f Apos, float width, float height) {
		ofxBox2dPolygon p1, p2;
		p1.begin();
		p1.addVertex(Apos.x, Apos.y);
		p1.addVertex(Apos.x + width, Apos.y);
		p1.addVertex(Apos.x + width, Apos.y + height);
		p1.addVertex(Apos.x + width * 4 / 5, Apos.y + height);
		p1.addVertex(Apos.x + width * 4 / 5, Apos.y + height * 3 / 5);
		p1.addVertex(Apos.x + width / 5, Apos.y + height * 3 / 5);
		p1.addVertex(Apos.x + width / 5, Apos.y + height);
		p1.addVertex(Apos.x, Apos.y + height);
		p1.end();

		p2.begin();
		p2.addVertex(Apos.x + width / 5, Apos.y + height / 5);
		p2.addVertex(Apos.x + width * 4 / 5, Apos.y + height / 5);
		p2.addVertex(Apos.x + width * 4 / 5, Apos.y + height * 2 / 5);
		p2.addVertex(Apos.x + width / 5, Apos.y + height * 2 / 5);

		p2.end();
		if (p1.inside(pos.x, pos.y) && !p2.inside(pos.x, pos.y)) {
			return true;
		}
		return false;
	}

	bool isInN (ofVec2f pos, ofVec2f Npos, float width, float height) {
		ofxBox2dPolygon p;
		p.begin();
		p.addVertex(Npos.x, Npos.y);
		p.addVertex(Npos.x + width / 5, Npos.y);
		p.addVertex(Npos.x + width * 4 / 5, Npos.y + height * 3 / 5);
		p.addVertex(Npos.x + width * 4 / 5, Npos.y);
		p.addVertex(Npos.x + width, Npos.y);
		p.addVertex(Npos.x + width, Npos.y + height);
		p.addVertex(Npos.x + width * 4 / 5, Npos.y + height);
		p.addVertex(Npos.x + width / 5, Npos.y + height * 2 / 5);
		p.addVertex(Npos.x + width / 5, Npos.y + height);
		p.addVertex(Npos.x, Npos.y + height);
		p.end();

		if (p.inside(pos.x, pos.y)) {
			return true;
		}
		return false;
	}

	bool isInI(ofVec2f pos, ofVec2f Ipos, float width, float height) {
		ofxBox2dPolygon p;
		p.begin();
		p.addVertex(Ipos.x, Ipos.y);
		p.addVertex(Ipos.x + width, Ipos.y);
		p.addVertex(Ipos.x + width, Ipos.y + height / 5);
		p.addVertex(Ipos.x + width * 3 / 5, Ipos.y + height / 5);
		p.addVertex(Ipos.x + width * 3 / 5, Ipos.y + height * 4 / 5);
		p.addVertex(Ipos.x + width, Ipos.y + height * 4 / 5);
		p.addVertex(Ipos.x + width, Ipos.y + height);
		p.addVertex(Ipos.x, Ipos.y + height);
		p.addVertex(Ipos.x, Ipos.y + height * 4 / 5);
		p.addVertex(Ipos.x + width * 2 / 5, Ipos.y + height * 4 / 5);
		p.addVertex(Ipos.x + width * 2 / 5, Ipos.y + height / 5);
		p.addVertex(Ipos.x, Ipos.y + height / 5);
		p.end();

		if (p.inside(pos.x, pos.y)) {
			return true;
		}
		return false;
	}
};



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
public:
	vector <Zephanaiah*> zarr;
	int waterfallNum;
	ofxBox2d world;
	ofFbo fbo;
};