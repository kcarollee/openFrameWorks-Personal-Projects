#pragma once

#include "ofMain.h"

typedef struct Wave {
	float height;
	float width;
	float ypos;
	float resolution;
	float xInc;
	vector<ofVec2f> pointsArr;

	void setup(float height, float width, float ypos, float resolution) {
		this->height = height;
		this->width = width;
		this->ypos = ypos;
		this->resolution = resolution;
		ofVec2f currentPoint;
		currentPoint.x = 0;
		currentPoint.y = ypos;
		xInc = ofGetWidth() / resolution;
		pointsArr.push_back(currentPoint);
		while (currentPoint.x <= ofGetWidth()) {
			currentPoint.x += xInc;
			
			currentPoint.y = height * sin((1 / width) * currentPoint.x) + ypos;
			pointsArr.push_back(currentPoint);
		}
	}
	// sine on sine
	void update() {
		for (int i = 0; i < pointsArr.size(); i++) {
			pointsArr[i].y += sin(ofGetElapsedTimeMicros());
		}
	}
	// wave movement
	void update2() {
		for (int i = 0; i < pointsArr.size(); i++) {
			if (pointsArr[i].x >= ofGetWidth() - xInc && pointsArr[i].x <= ofGetWidth() + xInc) {
				pointsArr[i].x = 0;
			}
			else {
				pointsArr[i].x += xInc;			
			}
		}
	}
	// for static sine 
	void draw() {	
		for (int i = 0; i < pointsArr.size() - 1; i++) {
			ofDrawLine(pointsArr[i], pointsArr[i + 1]);
		}
	}
	// for moving sine
	void draw2() {
		for (int i = 0; i < pointsArr.size(); i++) {
			if (i == pointsArr.size() - 1) {
				ofDrawLine(pointsArr[i], pointsArr[0]);
			}
			else {
				ofDrawLine(pointsArr[i], pointsArr[i + 1]);
			}
		}	
	}
};
class ofApp : public ofBaseApp{
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
	vector<Wave*> waveArr;
	int waveNum;
	float gapBetweenWaves;
	float deg;
	float deg2;
	float camDeg = 0;
	vector<Wave*> waveArr2;
	vector<Wave*> waveArr3;

	ofCamera cam;

	ofVec3f camCenter;
	ofVec3f camPosition;

	bool move = false;
};
