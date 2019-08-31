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
		
public:
	ofVboMesh mesh;
	ofVboMesh mesh2;

	int gridX;
	int gridY;

	float waveHeight;
	float rotation;
	float sphereRotate;
	float rectHeight;
	float rectWidth;
	float planeGap;
	float maxHeight;

	float sphereHeight;

	float sphereRadius;
	vector<float> heightArr;

	ofLight light;
	ofMaterial material;

	ofEasyCam camera;
};
