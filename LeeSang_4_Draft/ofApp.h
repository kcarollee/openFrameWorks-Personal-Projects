#pragma once

#include "ofMain.h"
typedef struct Tile {
	void setPos(float x, float y) {
		this->xpos = x;
		this->ypos = y;
	}

	void setImage(string fileName) {
		this->name = fileName;
		image.load(fileName);
	}

	void draw() {
		image.draw(xpos, ypos);
	}

	void changePos(float x, float y) {
		xpos = x;
		ypos = y;
	}

	string name;
	ofImage image;
	float xpos, ypos;
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
		string getNumberID(string fileName);
		string getNumberName(string fileName);

public:
	ofImage background;
	
	string numberNames[121];
	vector<vector<Tile*>> tileMatrix;
		
};
