#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	tree = new Tree(ofVec2f(0, 0));
	viewFlag = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	tree->dragNode(tree->root);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(0);
	ofDrawBitmapString("Press 'c' to generate tree", 10, 10);
	ofDrawBitmapString("Press 'w' to wiggle tree", 10, 20);
	ofDrawBitmapString("Press 'v' to view data of each node", 10, 30);
	tree->drawInOrder(tree->root);
	if (viewFlag) {
		tree->viewData(tree->root);
	}
	if (initFlag) {
		ofDrawBitmapString("Tree initialized", tree->rootPos);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'c') {
		tree = new Tree(treePos);
		initFlag = true;
	}

	else {
		initFlag = false;
	}
	
	if (key == 'w') {
		tree->wiggle(tree->root);
	}
	
	if (key == 'i') {
		tree->insert(ofRandom(1, 100));
	}
	
	if (key == 'v') {
		viewFlag = true;
	}
	else {
		viewFlag = false;
	}	

	if (key == 'x') {
		tree->moveTowardsMouse(tree->root);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
	treePos = ofVec2f(x, y);
	/*
	tree = new Tree(treePos);
	for (int i = 0; i < 128; i++) {
		tree->insert(ofRandom(1, 100));
	}
	*/
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
