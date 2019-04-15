#include "ofApp.h"
#include "windows.h"

//--------------------------------------------------------------
void ofApp::setup(){
	font.load("verdana.ttf", 12);
	snake = new Snake;
	snake->setup();

	food = new ofRectangle(ofRandom(0, ofGetWidth() - 20), ofRandom(0, ofGetHeight() - 20), 20, 20);
	timeGap = 200;
}

//--------------------------------------------------------------
void ofApp::update(){
	cout << snake->headPositions.size() << endl;
	snake->move();
	message = "";
	if (snake->collidedWithWindow()) {
		message = "Game Over";
		snake->headPositions.clear();
		snake->bodyPositions.clear();
		snake->setup();
		timeGap = 200;
	}
	if (snake->touchedRectangle(food)) { 
		snake->getLonger(snake->headPositions);
		
		food = new ofRectangle(ofRandom(0, ofGetWidth() - 20), ofRandom(0, ofGetHeight() - 20), 20, 20);
		
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
	snake->draw();
	if (!snake->moveFlag) {
		message = "Press any arrow key to start";
		font.drawString(message, ofGetWidth() / 2, ofGetHeight() / 2 - 20);
	}

	ofSetColor(0, 255, 0);
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
