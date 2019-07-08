#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	fbo.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update(){
	

	if (spiralArr.size() > 0) {
		for (SpiralObject* s : spiralArr) {
			if (s->pos.x < 0 || s->pos.x > ofGetWidth()||
				s->pos.y < 0 || s->pos.y > ofGetHeight()) {
			}
			else
				s->move();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	fbo.draw(0, 0);
	ofDrawBitmapString("Press 'd' to switch modes", 10, 10);
	ofSetCircleResolution(120);

	if (spiralArr.size() > 0) {
		if (default_mode) {
			for (SpiralObject* s : spiralArr) {
				s->drawLineMode(fbo);
			}
			ofDrawBitmapString("Line Mode", 10, 20);
		}
		else {
			for (SpiralObject* s : spiralArr) {
				s->draw(fbo);
			}
			ofDrawBitmapString("Circle Mode", 10, 20);
		}
	}	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'd') {
		default_mode = !default_mode;
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
	ofVec2f *temp = new ofVec2f(x, y);
	SpiralObject *newObj = new SpiralObject;
	newObj->setup(20, *temp);
	spiralArr.push_back(newObj);
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
