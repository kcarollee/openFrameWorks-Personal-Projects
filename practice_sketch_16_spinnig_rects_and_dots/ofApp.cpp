#include "ofApp.h"
float Tile::colorChange = 0;
//--------------------------------------------------------------
void ofApp::setup(){
	tileNumPerRow = 30;
	deg = 0;
	for (int j = 0; j < tileNumPerRow; j++) {
		for (int i = 0; i < tileNumPerRow; i++) {
			Tile* tile = new Tile();
			tile->setup(i * ofGetWidth() / tileNumPerRow, j * ofGetHeight() / tileNumPerRow,
				(int)ofGetWidth() / tileNumPerRow, (int)ofGetHeight() / tileNumPerRow,1, deg);
			tileArr.push_back(tile);
		}
	}
	arraySize = tileArr.size();
	mode = 0;
	modeString = "clockwise mode";
}

//--------------------------------------------------------------
void ofApp::update(){
	
	for (int i = 0; i < tileArr.size(); i++) {
		tileArr[i]->deg += (float)i / 60;
	}
	
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(0);
	for (int i = 0; i < arraySize; i++) {
		if (mode == 0) tileArr[i]->rotate(1);
		else if (mode == 1) tileArr[i]->rotate(0);
		else tileArr[i]->rotate(i % 2);
	}
	ofDrawBitmapString(modeString, 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'm':
		mode++;
		if (mode % 3 == 0) {
			mode = 0;
			modeString = "clockwise mode";
		}
		else if (mode % 3 == 1) {
			modeString = "counter clockwise mode";
		}
		else modeString = "mixed mode";
		break;
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
