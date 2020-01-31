#pragma once

#include "ofMain.h"
typedef struct Tile {
	void setPos(float x, float y) {
		this->xpos = x;
		this->ypos = y;
		originalx = x;
		originaly = y;
	}

	void setImage(string fileName) {
		this->name = fileName;
		image.load(fileName);
	}

	void draw() {
		image.draw(xpos, ypos);
	}

	void reset() {
		xpos = originalx;
		ypos = originaly;
	}

	void changePos(float x, float y) {
		xpos = x;
		ypos = y;
	}

	string name;
	ofImage image;
	float xpos, ypos;
	float originalx, originaly;
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

		void switchTilePos();
		void reset();

		void moveColUp(int colNum);
		void moveColDown(int colNum);
		void moveRowLeft(int rowNum);
		void moveRowRight(int rowNum);

public:
	ofImage background;
	ofImage date;
	ofImage title;
	
	string tileFileNames[121] = {"d000.png","n000.png","n900.png","n800.png","n700.png","n600.png","n500.png","n400.png","n300.png","n200.png","n100.png",
		"n001.png","d001.png","n901.png","n801.png","n701.png","n601.png","n501.png","n401.png","n301.png","n201.png","n101.png",
		"n002.png","n902.png","d002.png","n802.png","n702.png","n602.png","n502.png","n402.png","n302.png","n202.png","n102.png",
		"n003.png","n903.png","n803.png","d003.png","n703.png","n603.png","n503.png","n403.png","n303.png","n203.png","n103.png",
		"n004.png","n904.png","n804.png","n704.png","d004.png","n604.png","n504.png","n404.png","n304.png","n204.png","n104.png",
		"n005.png","n905.png","n805.png","n705.png","n605.png","d005.png","n505.png","n405.png","n305.png","n205.png","n105.png",
		"n006.png","n906.png","n806.png","n706.png","n606.png","n506.png","d006.png","n406.png","n306.png","n206.png","n106.png",
		"n007.png","n907.png","n807.png","n707.png","n607.png","n507.png","n407.png","d007.png","n307.png","n207.png","n107.png",
		"n008.png","n908.png","n808.png","n708.png","n608.png","n508.png","n408.png","n308.png","d008.png","n208.png","n108.png",
		"n009.png","n909.png","n809.png","n709.png","n609.png","n509.png","n409.png","n309.png","n209.png","d009.png","n109.png",
		"n010.png","n910.png","n810.png","n710.png","n610.png","n510.png","n410.png","n310.png","n210.png","n110.png","d010.png" };
	vector<vector<Tile*>> tileMatrix;
	
	bool isSwitchMode = false;
	bool isRightMode = false;
	bool isLeftMode = false;
	bool isUpMode = false;
	bool isDownMode = false;
	
	

	ofColor randomHighlight, upHighlight, leftHighlight,
		downHighlight, rightHighlight, resetHighlight;
	int rowNum = 0;
};
