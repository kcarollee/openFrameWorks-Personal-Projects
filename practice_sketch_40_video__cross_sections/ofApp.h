#pragma once

#include "ofMain.h"
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
		void videoShaderSetupAndDraw(int frameIndex, int mode, glm::vec2 pos, float radius, float divWidth, float divHeight);

public:
	ofVideoGrabber webcam;
	ofxHapPlayer movie;
	deque<ofImage*> webcamFrameDeque;
	deque<ofFbo*> videoFboDeque;
	int dequeSize;
	int viewMode, dispMode, randomMode;
	int smallFrameSize;
	ofShader SketchShader, VideoShader;
	ofFbo sketchFbo;
	ofMesh sketchMesh;
	string modeString, dispModeString, randString, loadingString;
	bool loadingFrames, automateModes, webcamMode, videoMode;
	float randomSelectionRange;
	ofMesh videoMesh;
	ofSoundPlayer track;
};
