#pragma once

#include "ofMain.h"
#include "Rectangle.h"


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
		void Clear();
		void Compare();
		void setupInitial();
		bool isInsideButton(int x, int y, ofRectangle rect);

public:
	vector<Block*> rectArr;

	ofRectangle registerButton;
	ofRectangle resultsButton;
	ofRectangle allClearButton;

	string recordStatus;

	vector<int> initialAvail;
	vector<string> days = { "MON", "TUE", "WED", "THUR", "FRI" };
	vector<string> period = { "1st", "2nd", "3rd", "4th", "5th",
								"6th", "7th", "8th", "9th" };

	ofTrueTypeFont font;
	ofTrueTypeFont smallFont;

	int blockID;

	ofColor registerColor;
	ofColor resultsColor;
	ofColor clearColor;



};
