#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(ofColor(0, 0, 0));
	circleRes = 3;
	extra = 0;
	beat.loadSound("beat_1.mp3");
	fftSmooth = new float[30];
	for (int i = 0; i < 30; i++) {
		fftSmooth[i] = 0;
	}
	bands = 30;

	beat.setVolume(0.2);
	maxMessage = "";
	rotation = 0;
	rotAccel = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSoundUpdate();
	float * value = ofSoundGetSpectrum(bands);
	for (int i = 0; i < bands; i++) {
		fftSmooth[i] *= 0.97f;
		
		if (fftSmooth[i] < value[i]) {
			fftSmooth[i] = value[i];
		}
	}
	rotation += 0.01 + rotAccel;
	ofSetCircleResolution(circleRes);
}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	radius = (fftSmooth[0] * 150);
	radius2 = radius / 2;
	for (int i = 0; i < 6; i++) {
		ofNoFill();
		ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
		ofDrawCircle(ofGetWidth() / 2 + (radius + radius2) * cos(rotation + i * 2 * PI / 6), \
			ofGetHeight() / 2 + (radius + radius2) * sin(rotation + i * 2 * PI / 6), \
			radius2);
	}
	
	ofFill();
	ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
	ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, radius);	
	
	for (int i = 0; i < 6; i++) {
		ofSetColor(255, 150, 50);
		ofDrawRectangle(ofGetWidth() * i / 6, 10, ofGetWidth() / bands, fftSmooth[i] * 450 + 100);
		if (i == 0) {
			lowestFreqHistory.push_back(fftSmooth[i] * 450 + 100);
			if (fftSmooth[i] * 450 + 100 == 550.0) {
				if (circleRes < 13) {
					circleRes += 1;
				}
				else
					circleRes -= 10;
				if (rotAccel > 10) {
					rotAccel -= 2;
				}

				else if (rotAccel >= 0 && rotAccel <= 10) {
					rotAccel += 1;
				}

				else if (rotAccel < 0 && rotAccel >= -10) {
					rotAccel -= 1;
				}

				else if (rotAccel < -10) {
					rotAccel += 2;
				}
			}
		}
	}
	findMax();
	//lowestFreqHistory.clear();
}

void ofApp::rotate(ofVec2f about, float d1, ofVec2f pos, float d2, float angle)
{
	pos = ofVec2f(about.x + (d1 + d2) * cos(angle), about.y + (d1 + d2) * sin(angle));
}

void ofApp::findMax()
{
	float max;
	max = lowestFreqHistory[0];
	for (int i = 0; i < lowestFreqHistory.size() - 1; i++) {
		if (lowestFreqHistory[i + 1] > lowestFreqHistory[i]) {
			max = lowestFreqHistory[i + 1];
		}
	}
	ofDrawBitmapString(to_string(max), 50, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'r' : 
		circleRes += 1;
		break;
	case 'e' : 
		circleRes -= 1;
		break;
	case 's' :
		radius -= 1;
		break;
	case 'l' : 
		radius += 1;
		break;
	case 'p' : 
		beat.play();
		break;
	case 'o' : 
		beat.stop();
		break;
	case OF_KEY_RIGHT : 
		rotAccel -= 1;
		break;
	case OF_KEY_LEFT :  
		rotAccel += 1;
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
