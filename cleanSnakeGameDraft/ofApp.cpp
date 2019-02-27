#include "ofApp.h"
#include "windows.h"

//--------------------------------------------------------------
void ofApp::setup(){
	snake.setup();
	food = new ofRectangle(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), 20, 20);
	timeGap = 200;
}

//--------------------------------------------------------------
void ofApp::update(){
	snake.move();

	if (snake.touchedFood(food)) {
		food = new ofRectangle(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), 20, 20);
		if (timeGap <= 20) {
			timeGap = 20;
		}
		else
			timeGap -= 20;
	}

	Sleep(timeGap);
}

//--------------------------------------------------------------
void ofApp::draw(){
	snake.draw();
	ofDrawRectangle(*food);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
