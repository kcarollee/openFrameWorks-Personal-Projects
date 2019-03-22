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
		void findMax();
		void rotate(ofVec2f about, float d1, ofVec2f pos, float d2, float angle);

public:
	typedef struct Circle {
		ofVec2f pos;
		float radius;
		void setup(float x, float y, float r)
		{
			pos = ofVec2f(x, y);
			radius = r;
		}

		void draw()
		{
			ofDrawCircle(pos, radius);
		}
	};
	
	ofSoundPlayer beat;

	float * fftSmooth; // how fast/ slow the shape changes
	int bands;
	int circleRes;
	float radius;

	float posX;
	float posY;

	float cx;
	float cy;

	float radius2;

	float extra;

	vector<float> lowestFreqHistory;
	vector<Circle> circleArr;

	string maxMessage;
	ofBitmapFont str;

	float rotation;
	float rotAccel;
		
};
