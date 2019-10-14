#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	//ofSetupOpenGL(600,768,OF_WINDOW);			// <-------- setup the GL context

	ofGLFWWindowSettings settings;
	
	//settings.decorated = false;
	settings.setGLVersion(3, 2);
	settings.setSize(600, 768);
	ofCreateWindow(settings);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
	
}
