#pragma once
#include "ofMain.h"

typedef struct Box {
	void setup(ofVec3f position, float width, float height, float depth) {
		this->position = position;
		this->width = width;
		this->height = height;
		this->depth = depth;
	}

	void draw() {
		ofDrawBox(position, width, height, depth);
	}

	void changeDepth(float val) {
		position.z = val;
	}

	ofVec3f position;
	float width;
	float height;
	float depth;
	ofColor color;
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
	vector<Box*> boxArr;
	int matrixWidth;
	int matrixHeight;

	float boxWidth;
	float boxHeight;

	float boxDepth;
	float deg;

	float lightHeight = 0;

	ofLight light;

	bool fill = false;

	float red;
	float green;

};
