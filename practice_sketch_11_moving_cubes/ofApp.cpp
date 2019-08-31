#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableDepthTest();
	ofSetBackgroundColor(0);
	matrixWidth = 40;
	matrixHeight = 40;
	deg = 0;
	boxWidth = 15;
	boxHeight = 15;
	red = 100;
	green = 100;
	light.setAmbientColor(ofColor(red, green, 0));
	//light.setAreaLight(boxWidth * matrixWidth, boxHeight * matrixHeight);
	light.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, lightHeight);

	boxDepth = 30;

	for (int i = 0; i < matrixHeight; i++) {
		for (int j = 0; j < matrixWidth; j++) {
			Box* box = new Box();
			box->setup(ofVec3f(j * boxWidth, i * boxHeight, 0), boxWidth, boxHeight, boxDepth);
			boxArr.push_back(box);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < matrixHeight; i++) {
		for (int j = 0; j < matrixWidth; j++) {
			boxArr[i * matrixWidth + j]->changeDepth(sin(ofGetElapsedTimef() * 2) * (sin((i + 1) * (j + 1)) * boxDepth * matrixWidth / 4));
		}
	}
	deg += 1;

	lightHeight = 500 * sin(ofGetElapsedTimef());

	light.setAmbientColor(ofColor(100 * cos(ofGetElapsedTimef()), 100 * sin(ofGetElapsedTimef()), 0));
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (fill) ofFill();
	else ofNoFill();
	light.enable();
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2 - matrixWidth * boxWidth / 2, ofGetHeight() / 2 - matrixHeight * boxHeight/ 2);
	ofRotate(deg, 1, 1, 0);
	for (auto box : boxArr) {
		box->draw();
	}
	ofPopMatrix();
	light.disable();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'f') {
		fill = !fill;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
