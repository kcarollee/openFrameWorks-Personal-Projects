#pragma once

#include "ofMain.h"
#include "Camera.h"
#include "ofxHapPlayer.h"

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
		void updateSeeds();
		void manageShader(glm::mat4 mvp, int sourceNum,
			int textureIndex, float* seedArr, ofTexture& tex, int translateMode, ofMesh* mesh);

public:
	ofVideoGrabber webcam;
	ofShader shader;
	vector<ofImage*> imgArr;
	vector<ofxHapPlayer*> videoArr;
	deque<ofImage*> webcamFrameDeque;
	vector<ofMesh*> quadMeshArr;
	int seedNum; // half of seedArr's size
	int layerNum; // number of layers(quads)
	int visibleTextureNum;

	float seedArr[30]; // [x0, y0, x1, y1, x2, y2 ....]
	float seedArrArr[40][30] = { {0} }; // [layerNum][seedArr's size]
	float colorArr[15]; // half of seedArr's size
	float greyDiv; // for calculating greyscale values (1.0 / seedNum)

	// cameras and mvp matrices
	Camera camera;
	glm::mat4 sketchMvp, sketchModel, sketchView, sketchProj;
	glm::vec3 shapeCenter;

	// random velocities
	vector<float> velXFront, velXBack;
	vector<float> velYFront, velYBack;

	// modes
	bool discardMode, imageMode, videoMode, webcamMode, greyScaleMode, showCubeOnly;
	string mode;
};

