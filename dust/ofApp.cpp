#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	blue = 50;
	for (int i = 0; i < 2; i++) {
		Cluster_1* c = new Cluster_1();
		c->setup(ofRandom(30, 60));
		clusterOneArr.push_back(c);
	}


	for (int i = 0; i < 15; i++) {
		Cluster_2 *c = new Cluster_2();
		c->setup(ofRandom(50, 80), ofRandom(25, 40), ofRandom(4, 9));
		clusterTwoArr.push_back(c);
	}

	for (int i = 0; i < 200; i++) {
		ofVec2f flakePos;
		flakePos = ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
		flakePosArr.push_back(flakePos);
	}
}

//--------------------------------------------------------------
void ofApp::update(){


	if (blue >= 50) {
		blue += 1;
		if (blue == 150) {
			while (blue != 50) {
				blue -= 1;
			}
		}
	}

	for (int i = 0; i < clusterOneArr.size(); i++) {
		clusterOneArr[i]->move();
	}
	for (int i = 0; i < clusterTwoArr.size(); i++) {
		clusterTwoArr[i]->move();
	}
	for (int i = 0; i < clusterOneArr.size(); i++) {
		clusterOneArr[i]->windowCollision();
	}
	for (int i = 0; i < clusterTwoArr.size(); i++) {
		clusterTwoArr[i]->windowCollision();
	}


	for (int i = 0; i < flakePosArr.size();  i++) {
		flakePosArr[i] += ofVec2f(ofRandom(-3, 3), ofRandom(-3, 3));
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(0, 0, blue);
	for (int i = 0; i < clusterOneArr.size(); i++) {
		clusterOneArr[i]->draw();
	}
	for (int i = 0; i < clusterTwoArr.size(); i++) {
		clusterTwoArr[i]->draw();
	}

	// draw flakes
	ofFill();
	ofSetColor(255, 107, 255);
	for (int i = 0; i < flakePosArr.size(); i++) {
		ofDrawCircle(flakePosArr[i], 4);
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
