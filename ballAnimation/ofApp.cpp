#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	font.load("verdana.ttf", 12);
	message = "";
	location.set(ofGetWidth() / 2, ofGetHeight() / 2);
	velocity.set(3.0f, 5.0f);
	acceleration.set(0.05, 0.08);
	radius = 30;
	maxLimit.set(50.0, 60.0);

	fbo.allocate(1024, 768, GL_RGBA);
	fbo.begin();
	ofClear(255, 255, 255, 0);
	fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
	location += velocity;
	velocity += acceleration;

	applyForce(ofVec2f(0.0f, 0.0f));// no acceleration along the x axis

	if (velocity.x > maxLimit.x) {
		velocity.x = maxLimit.x;
	}
	if (velocity.y > maxLimit.y) {
		velocity.y = maxLimit.y;
	}
	if ((location.x - radius < 0) ||
		(location.x + radius > ofGetWidth())) {
		velocity.x *= -1.0;
	}
	if ((location.y - radius < 0) ||
		(location.y + radius > ofGetWidth())) {
		velocity.y *= -1.0;
	}

	showStatus();

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 0, 0);
	font.drawString(message, 20, 60);

	fbo.begin();
	ofNoFill();
	ofSetColor(0, 0, 0, 100);
	ofDrawCircle(location, 30);
	fbo.end();
	fbo.draw(0, 0);

	ofSetColor(255, 0, 0);
	ofDrawCircle(location, 30);
}

void ofApp::showStatus()
{
	message = "Velocity vector: " + to_string(velocity.x) + "/" +
			to_string(velocity.y) + "\n" + "Accelration vector: " +
			to_string(acceleration.x) + to_string(acceleration.y);
}

void ofApp::applyForce(ofVec2f force)
{
	acceleration = force;
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
