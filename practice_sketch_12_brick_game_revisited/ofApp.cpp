#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {

	ball = new Ball();
	ball->setup();
	ballVelocity.x = 6;
	ballVelocity.y = 6;

	ofSetBackgroundColor(0);

	brickHorizontalNum = 150;
	brickVerticalNum = 150;


	brickWidth = 1.5;
	brickHeight = 1.5;
	touchedFlag = false;
	for (int i = 0; i < brickVerticalNum; i++) {
		for (int j = 0; j < brickHorizontalNum; j++) {
			brick = new Brick();
			brick->setup(ofGetWidth() / brickHorizontalNum * j, ofGetHeight() / brickVerticalNum * i , brickWidth, brickHeight);
			bricks.push_back(brick);
		}
	}

}

//--------------------------------------------------------------
void ofApp::update() {
	ball->move(ballVelocity);
	windowCollision();

	for (int i = 0; i < bricks.size(); i++) {

		if (ball->touchedBrick(bricks[i]) == 1) {
			ballVelocity.x += ofRandom(-6, 6);
			ballVelocity.x = ofClamp(ballVelocity.x, -6, 6);
			ballVelocity.y *= -1;
			touchedBrickID = i;
			touchedFlag = true;
			//cout << "col 1" << endl;
		}
		else if (ball->touchedBrick(bricks[i]) == 2) {
			ballVelocity.y += ofRandom(-6, 6);
			ballVelocity.y = ofClamp(ballVelocity.y, -6, 6);
			ballVelocity.x *= -1;
			touchedBrickID = i;
			touchedFlag = true;
			//cout << "col 2" << endl;
		}
	}
	//wihtout the flag and the if statement below, bricks.erase erases every 
	//brick on screen. 
	if (touchedFlag) {
		bricks.erase(bricks.begin() + touchedBrickID);
		touchedFlag = false;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	ball->draw();
	for (auto b : bricks) {
		b->draw();
	}
}

void ofApp::windowCollision()
{
	if (((ball->pos.x) - (ball->radius) <= 0) ||
		((ball->pos.x) + (ball->radius) >= ofGetWidth())) {
		ballVelocity.x *= -1;
	}
	if (((ball->pos.y) - (ball->radius) <= 0) ||
		((ball->pos.y) + (ball->radius) >= ofGetHeight())) {
		ballVelocity.y *= -1;
	}

}

void ofApp::brickCollision()
{

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

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