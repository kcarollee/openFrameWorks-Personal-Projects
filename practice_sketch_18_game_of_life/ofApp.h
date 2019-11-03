#pragma once

#include "ofMain.h"

typedef struct Cell{
	int xpos, ypos, ncount, aliveCount;
	bool alive;

}Cell;
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
		void countNeighbors();
		void updateStatus();
	public:
		vector<vector<Cell*>> cellArr;
		float cellWidth, cellHeight;
		int cellNumPerRow;
		int allowedNumberOfNeighbors;
		int mouseMode;
		float deg;
		string clickMode;
		ofLight light;
		ofEasyCam camera;
};
