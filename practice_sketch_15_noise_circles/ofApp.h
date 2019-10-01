#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Blob {
public:

	~Blob() {
		/*
		for (int i = 0; i < vertArr.size(); i++) {
			delete[] vertArr[i];
		}
		*/
	}
	void setup(int vertexNum, ofVec2f initPos, int radius) {
		this->vertexNum = vertexNum;
		this->initPos = initPos;
		this->radius = radius;
		for (int i = 0; i < vertexNum; i++) {
			ofVec2f *pt = new ofVec2f;
			pt->set(initPos.x +  radius * cos(i * 2 * PI / vertexNum), 
				initPos.y +  radius * sin(i * 2 * PI / vertexNum));
			vertArr.push_back(pt);
		}
	
		this->initVel = ofVec2f(ofRandom(-5, 5), ofRandom(-5, 5));
		this->vel = this->initVel;
		
		
		this->alpha = 255;
		//noise = 0.5;
	}

	void draw(float alphaDec) {
		ofSetColor(255, alpha);
		for (int i = 0; i < vertexNum; i++) {
			if (i == vertexNum - 1) {
				//ofSetColor(255, 0, 0);
				ofDrawLine(*vertArr[0], *vertArr[i]);
				
			}
			else {
				//ofSetColor(0, 255, 0);
				ofDrawLine(*vertArr[i], *vertArr[i + 1]);
			}
		}
		/*
		for (int i = 0; i < vertexNum; i++) {
			ofDrawBitmapString(to_string(i), *vertArr[i]);
		}
		*/
		alpha -= alphaDec;
	}

	void move_1(float noise) {
		for (int i = 0; i < vertexNum; i++) {
			*vertArr[i] += ofVec2f(ofRandom(-noise, noise), ofRandom(-noise, noise));
		}
	}



	void move_2(float vel) {
		for (int i = 0; i < vertexNum; i++) {
			
			vertArr[i]->set(vertArr[i]->x + vel  * cos(i * 2 * PI / vertexNum),
				vertArr[i]->y + vel * sin(i * 2 * PI / vertexNum));
		}
		
	}

	// not accurate
	bool isOutOfBounds() {
		if (alpha <= 0) {
			return true;
		}
		return false;
	}
	void deleteSelf() {
		if (isOutOfBounds()) {
			//cout << "deleted" << endl;
			//this->~Blob();
		}
	}
public:
	int vertexNum;
	int radius;
	float noise;
	ofVec2f initPos;
	ofVec2f initVel,vel, accel;
	vector <ofVec2f*> vertArr;
	float alpha;
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
	deque <Blob*> blobArr;
	float radius;
	
	
	ofxPanel gui;
	ofParameter<float> noise;
	ofParameter<float> vel;
	ofParameter<float> alphaDecrement;
	
};
