#pragma once

#include "ofMain.h"
#include "Cluster_1.h"
#include "Cluster_2.h"

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
	float blue;
	float red;
	float green;
	vector <ofVec2f> flakePosArr;
	vector <Cluster_1*> clusterOneArr;
	vector <Cluster_2*> clusterTwoArr;
};
