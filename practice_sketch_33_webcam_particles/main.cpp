#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
	ofGLWindowSettings glSettings;
	glSettings.setSize(600, 600);
	glSettings.windowMode = OF_WINDOW;
	glSettings.setGLVersion(3, 2);
	ofCreateWindow(glSettings);
	ofRunApp(new ofApp());
}