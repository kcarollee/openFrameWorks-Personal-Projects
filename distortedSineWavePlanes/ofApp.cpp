#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//wave.setup(50, 50, ofGetHeight() / 2, 1000);
	ofBackground(0);
	//ofSetFullscreen(true);
	camCenter.set(ofGetWidth() / 2, ofGetHeight() / 2, 0.0);
	camPosition = camCenter;
	camPosition.z += 800;
	cam.setPosition(camPosition);
	cam.lookAt(camCenter);
	
	
	
	float firstypos;
	waveNum = 20;
	gapBetweenWaves = ofGetHeight() / waveNum;
	firstypos = gapBetweenWaves;
	deg = 0;
	deg2 = 0;
	for (int i = 0; i < waveNum; i++) {
		Wave* wave = new Wave();
		wave->setup(50, 50, firstypos, 200);
		firstypos += gapBetweenWaves;
		waveArr.push_back(wave);
	}
	firstypos = gapBetweenWaves;
	for (int i = 0; i < waveNum; i++) {
		Wave* wave = new Wave();
		wave->setup(50, 50, firstypos, 200);
		firstypos += gapBetweenWaves;
		waveArr2.push_back(wave);
	}

	firstypos = gapBetweenWaves;
	for (int i = 0; i < waveNum; i++) {
		Wave* wave = new Wave();
		wave->setup(50, 50, firstypos, 50);
		firstypos += gapBetweenWaves;
		waveArr3.push_back(wave);
	}
	
}

//--------------------------------------------------------------
void ofApp::update(){
	//wave.update();
	for (auto wave : waveArr) {
		wave->update();
		wave->update2();
	}
	for (auto wave : waveArr2) {
		wave->update();
		wave->update2();
	}
	for (auto wave : waveArr3) {
		wave->update();
		wave->update2();
	}
	deg += 1.5;
	deg2 -= 1.5;
	
	//camPosition.z += 1;
	if (move) {
		camPosition.x = 800 * (1 - sin(ofGetElapsedTimef()));
		camPosition.z = 800 * cos(ofGetElapsedTimef());
		cam.setPosition(camPosition);
		cam.lookAt(camCenter);
	}
	
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	//wave.draw();
	
	//ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	cam.begin();
	ofPushMatrix();
	
	for (auto wave : waveArr3) {
		ofSetColor(255, 0, 255);
		ofSetLineWidth(0);
		
		wave->draw2();
	}
	ofPopMatrix();
	ofPushMatrix();
	ofRotate(deg, 1, 1, 0);
	
	for (auto wave : waveArr) {
		ofSetColor(255, 255, 0);
		
		wave->draw2();
	}
	ofPopMatrix();
	
	ofPushMatrix();
	ofRotate(deg2, 1, 1, 0);

	for (auto wave : waveArr2) {
		ofSetColor(0, 255, 255);
		
		wave->draw2();
	}
	ofPopMatrix();

	cam.end();
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'm') {
		move = !move;
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
