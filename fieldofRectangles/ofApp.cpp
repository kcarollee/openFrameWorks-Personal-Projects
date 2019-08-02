#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	sideLength = 40;
	gap = 4;

	widthNum = 20;
	heightNum = 20;

	for (int i = 1; i <= heightNum; i++) {
		for (int j = 1; j <= widthNum; j++) {
			Rect* temp = new Rect;
			temp->setup(ofVec2f(j * (sideLength + gap), i * (sideLength + gap)), sideLength);
			rectArr.push_back(temp);
		}
	}
	
}

void ofApp::reset() {
	for (int i = 1; i <= widthNum; i++) {
		for (int j = 1; j <= heightNum; j++) {
			rectArr[heightNum * (i - 1) + j - 1]->setup(ofVec2f(j * (sideLength + gap), i * (sideLength + gap)), sideLength);
			
		}
	}
}
//--------------------------------------------------------------
void ofApp::update(){
	if (start) {
		for (Rect* r : rectArr) {
			r->react2(ofGetMouseX(), ofGetMouseY());
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	for (Rect* r : rectArr) {
		r->draw();
	}
	

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'r') {
		reset();
	}

	if (key == 's') {
		start = !start;
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
