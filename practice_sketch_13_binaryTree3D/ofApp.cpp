#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetBackgroundColor(50, 50, 70);
	zPos = 300;
	tree = new Tree(ofVec3f(0, 0, zPos));
	viewFlag = false;
	deg = 0.1;

	light.setPosition(ofGetWidth() / 2, ofGetHeight(), 300);
	light.setAreaLight(500, 500);

	camXpos = 400;
	camYpos = 400;
	camZpos = 300;
	lookatPos = ofVec3f(camXpos / 2, camYpos / 2, camZpos / 2);
	camera.setPosition(camXpos, camYpos, camZpos);
	camera.lookAt(lookatPos);	
	plane.setPosition(0, 0, -302);
	plane.setHeight(800);
	plane.setWidth(800);
	plane.drawWireframe();
}

//--------------------------------------------------------------
void ofApp::update() {
	tree->dragNode(tree->root);
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofPushMatrix();
	ofSetColor(0);
	ofDrawBitmapString("'c' : generate tree", 10, 10);
	ofDrawBitmapString("'w' : wiggle tree", 10, 20);
	ofDrawBitmapString("'v' : view data of each node", 10, 30);
	ofDrawBitmapString("'i' : insert new node", 10, 40);
	ofDrawBitmapString("'s' : spin tree", 10, 50);
	ofDrawBitmapString("'a' : spin each node at differing velocities", 10, 60);
	ofDrawBitmapString("'z' : zoom in", 10, 70);
	ofDrawBitmapString("'o' : zoom out", 10, 80);	
	ofPopMatrix();
	camera.begin();
	ofEnableDepthTest();
	light.enable();	
	ofSetColor(200);		
	ofRotate(-90, 1, 0, 0);
	ofSetColor(150, 100, 50, 100);	
	plane.draw();	
	ofSetLineWidth(0.5);
	tree->drawInOrder(tree->root);
	if (viewFlag) {
		tree->viewData(tree->root);
	}
	if (initFlag) {
		ofDrawBitmapString("Tree initialized", tree->rootPos);
	}
	light.disable();
	camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'c') {
		delete tree;
		tree = new Tree(ofVec3f(0, 0, zPos));
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
	if (key == 's') {
		tree->spinTree(tree->root, 0.1);
	}

	if (key == 'a') {
		tree->spinNode(tree->root);
	}
	if (key == 'x') {
		tree->moveTowardsMouse(tree->root);
	}
	if (key == 'z') {
		camXpos-=3;
		camYpos-=3;
		camZpos-=3;
		camera.setPosition(camXpos, camYpos, camZpos);
	}
	if (key == 'o') {
		camXpos+=3;
		camYpos+=3;
		camZpos+=3;
		camera.setPosition(camXpos, camYpos, camZpos);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	treePos = ofVec2f(x, y);	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}