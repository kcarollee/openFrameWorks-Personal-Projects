#pragma once

#include "ofMain.h"

extern ofTrueTypeFont globalFont;
typedef struct Tile {
	ofVec2f position;
	float width, height;
	string text;
	ofTrueTypeFont font;

	void setup(ofVec2f position, float width, float height, string text) {
		this->position = position;
		this->height = height;
		this->width = width;
		this->text = text;
	}

	void draw() {
		//ofSetColor(0);
		//ofNoFill();
		//ofDrawRectangle(position, width, height);
		//ofFill();
		ofSetColor(60);
		//ofDrawBitmapString(text, position.x, position.y + height / 2);
		globalFont.drawString(text, position.x, position.y + height / 2);
	}
		
}Tile;

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
	int fontSize;
	int rowNum, colNum;

	vector<Tile*> tileArr;

	ofTrueTypeFont testfont;
};
