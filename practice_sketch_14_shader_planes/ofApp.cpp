#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	rectNum = 0;
	shader.load("shadersGL3/shader");
	shader2.load("shadersGL3/shader2");
	shader3.load("shadersGL3/shader3");
	shader4.load("shadersGL3/shader4");

}

//--------------------------------------------------------------
void ofApp::update(){
	if (circleArr.size() > 0) {
		for (auto circle : circleArr) {
			circle->move();
		}
	}
	if (rectArr.size() > 0) {
		for (auto rect : rectArr) {
			rect->move();
		}
	}
	rectNum = 10 - 5 * cos(ofGetElapsedTimef());

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(255);

	ofSetCircleResolution(255);


	shader3.begin();
	shader3.setUniform1f("time", ofGetElapsedTimef() / 150);
	shader3.setUniform1f("random", ofRandom(0, 50));

	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	
	shader3.end();

	shader.begin();

	
	
	shader.setUniform1f("time", ofGetElapsedTimef() / 100);
	shader.setUniform1f("random", ofRandom(0, 50));
	ofDrawRectangle(0, 0, ofGetWidth() / 2, ofGetHeight() / 2);
	ofDrawRectangle(ofGetWidth() / 2, ofGetHeight() / 2, ofGetWidth() / 2, ofGetHeight() / 2);

	shader.end();
	
	shader2.begin();
	shader2.setUniform1f("time", ofGetElapsedTimef() / 40);
	shader2.setUniform1f("random", ofRandom(0, 50));

	if (rectArr.size() > 0) {
		for (auto rect : rectArr) {
			rect->draw();

		}
	}

	if (circleArr.size() > 0) {
		for (auto circle : circleArr) {
			circle->draw();
			shader2.end();
			shader3.begin();
			ofDrawCircle(circle->position, circle->radius / 2);
			shader3.end();
			shader2.begin();
		}
	}
	shader2.end();

	shader4.begin();
	shader4.setUniform1f("time", ofGetElapsedTimef() / 150);
	shader4.setUniform1f("random", ofRandom(0, 50));
	if (rectNum > 0) {
		drawDiagonalRect(rectNum);
	}
	shader4.end();
	

	
}
void ofApp::drawDiagonalRect(int rectNum) {
	rectNum *= 2;
	for (int i = 0; i < rectNum; i++) {
		ofDrawRectangle(i * ofGetWindowWidth() / rectNum, i * ofGetWindowHeight() / rectNum,
			ofGetWidth() / rectNum, ofGetHeight() / rectNum);
	}
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

	if (x < ofGetWidth() / 2 && y > ofGetHeight() / 2) {
		Rect *rect = new Rect();
		rect->x = x;
		rect->y = y;
		rect->width = ofRandom(10, 90);
		rect->height = ofRandom(10, 90);
		rect->velocity = ofVec2f(ofRandom(-10, 10), ofRandom(-10, 10));
		rect->setBoundary(0, ofGetWidth() / 2, ofGetHeight() / 2, ofGetHeight());
		rectArr.push_back(rect);
	}
	else if (x > ofGetWidth() / 2 && y < ofGetHeight() / 2) {
		DoubleCircle *circle = new DoubleCircle();
		circle->setup(ofVec2f(x, y), ofRandom(10, 60));
		circle->setBoundary(ofGetWidth() / 2, ofGetWidth(), 0, ofGetHeight() / 2);
		circleArr.push_back(circle);
	}
	
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
