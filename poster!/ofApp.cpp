
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	
	fbo.allocate(700, 1000, GL_RGBA);
	fbo.begin();
	ofClear(0, 255, 255, 0);
	fbo.end();
	
	world.init();
	ofSetBackgroundColor(0, 0, 0);
	
	waterfallNum = 500;
	
	for (int i = 0; i < waterfallNum; i++) {
		Zephanaiah *z;
		z = new Zephanaiah;
		z->setup(ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight())));
		zarr.push_back(z);
	}

	
}


//--------------------------------------------------------------
void ofApp::update() {
	
	for (int i = 0; i < waterfallNum; i++) {
		zarr[i]->move();
	}
	
	world.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	ofEnableAlphaBlending();
	fbo.begin();
	for (int i = 0; i < waterfallNum; i++) {
		zarr[i]->draw();
	}
	fbo.end();
	fbo.draw(0, 0);
	ofDisableAlphaBlending();
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}