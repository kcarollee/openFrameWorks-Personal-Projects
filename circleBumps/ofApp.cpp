#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	radius = 30;
	incX = ofRandomf() * 10;
	incY = ofRandomf() * 10;
	posX = ofRandom(0, ofGetWidth());
	posY = ofRandom(0, ofGetHeight());
	font.load("verdana.ttf", 24);
	message = " ";
	bumps = 0;
	cout << ofGetWidth() << " " << ofGetHeight() << endl;
}

//--------------------------------------------------------------
void ofApp::update()
{	

	for (int i = 0; i < circles.size(); i++) {
		circles[i]->moveCircleLinear(xarr[i], yarr[i]);
		if (circles[i]->posX < circles[i]->radius || circles[i]->posX > 1024 - circles[i]->radius) {
			xarr[i] = -1 * xarr[i];
			bumps += 1;
			message = "Bumps: " + to_string(bumps);
		}
		if (circles[i]->posY < circles[i]->radius || circles[i]->posY > 749 - circles[i]->radius) {
			yarr[i] = -1 * yarr[i];
			bumps += 1;
			message = "Bumps: " + to_string(bumps);
		}
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(133, 133, 133);
	font.drawString(message, 30, 60);
	
	for (int i = 0; i < circles.size(); i++) {
		circles[i]->draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	/*
	if (key == 'a') {
		Circle c;
		c.setup(posX, posY, radius, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)));
		circles.push_back(c);

		incX = ofRandomf() * 10;
		xarr.push_back(incX);

		incY = ofRandomf() * 10;
		yarr.push_back(incY);
	}
	*/
	if (key == 'd') {
		if (circles.size() == 0);
		else {
			circles.pop_back();
			xarr.pop_back();
			yarr.pop_back();
		}
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
	posX = x;
	posY = y;
	Circle* c;
	c = new Circle();
	c->setup(posX, posY, radius, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)));
	circles.push_back(c);

	incX = ofRandomf() * 10;
	xarr.push_back(incX);

	incY = ofRandomf() * 10;
	yarr.push_back(incY);

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
