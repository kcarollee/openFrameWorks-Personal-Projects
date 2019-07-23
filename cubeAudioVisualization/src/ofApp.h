#pragma once

#include "ofMain.h"

typedef struct Cube {
	void setup(float length, ofVec3f initPos, int ID) {
		this->length = length;
		this->pos = initPos;
		this->cubeID = ID;
		
		originalPos = initPos;
		ofSetBoxResolution(1);
	}
	void draw() {
		if (fill) ofFill();
		else ofNoFill();
	
		ofSetColor(color);
		ofSetLineWidth(2);		
		ofDrawBox(pos, length);
	}

	void changePosition(ofVec3f newPos){
		pos = newPos;
	}

	float length;
	ofVec3f pos;
	ofVec3f originalPos;
	ofColor color;
	int cubeID;
	bool fill = false;
	

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
	vector<Cube*> cubeArr;
	int sideNum;
	int cubeNum;
	int cubeID;
	int centerIndex;
	float sideLength;
	float waveHeight;
	ofVec3f centerPos;
	ofVec3f cubePos;
	
	bool isFill;
	ofLight light;

	
	float rotation;
	float cubeArrCenterHeight;
		
	ofSoundPlayer beat;
	float * fftSmooth; // how fast/ slow the shape changes
	int bandIndex;
	int bands;
	vector<float> lowestFreqHistory;
	
	string fillMode;

	vector<ofRectangle*> rectArr;
	vector<float> fftSmoothArr;

	float elapsedTime_2 = 0;

	int red = 0;
	int blue = 0;
	int green = 100;

	float rotatex, rotatey, rotatez;

};
