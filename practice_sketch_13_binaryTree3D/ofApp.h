#pragma once

#include "ofMain.h"
#include "Tree.h"

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
	Tree *tree;
	ofVec3f treePos;
	ofVec3f lookatPos;
	bool viewFlag;
	bool initFlag;
	float deg;
	float zPos;
	ofLight light;
	ofCamera camera;

	float camXpos;
	float camYpos;
	float camZpos;
	
	ofPlanePrimitive plane;
		
};
