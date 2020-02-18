#pragma once

#include "ofMain.h"
#include "Camera.h"
#include "ofxGui.h"

typedef struct DirectionalLight {
	vec3 direction;
	vec3 color;
	float intensity;
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
public:
	ofMesh top, bottom, left, right, front, back;
	Camera camera;
	mat4 model, view, proj, mvp;
	ofShader waterShader;
	ofImage waterNormal;

	DirectionalLight directionalLight;

	ofParameter<bool> discardMode;
	ofParameter<float> discardThreshold;
	ofParameter<float> exponent;
	ofxPanel gui;
};
