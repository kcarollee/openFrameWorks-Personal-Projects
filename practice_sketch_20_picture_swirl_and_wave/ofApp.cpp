#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	image.loadImage("test2.jpg");
	image.resize(ofGetWidth(), ofGetHeight());
	rowSubsectionNum = 48;
	subsectionHeight = ofGetHeight() / rowSubsectionNum;
	subsectionWidth = ofGetWidth() / rowSubsectionNum;
	z = 0;
	for (int i = 0; i < rowSubsectionNum * rowSubsectionNum; i++) {
		heightArr.push_back(sin(i) * 100);
		heightArr2.push_back(ofRandom(-1000, 1000));
	}
	ofSetBackgroundColor(0);
	rotatePlaneDeg = 0;
	explode = false;
	cubeMode = false;
	waveMode = true;
	spiralMode = false;
	
}

//--------------------------------------------------------------
void ofApp::update(){
	rotatePlaneDeg += 3;
}

//--------------------------------------------------------------
void ofApp::draw(){	

	ofPushMatrix();
	ofSetColor(255);
	ofDrawBitmapString("'s' : spiral mode", 10, 20);
	ofDrawBitmapString("'w' : wave mode", 10, 35);
	ofDrawBitmapString("'c' : cube/plane mode", 10, 50);
	ofPopMatrix();
	cam.begin();
	if (explode) {
		//ofResetElapsedTimeCounter();
		if (spiralMode) {
			if (!cubeMode) {
				for (int i = 0; i < rowSubsectionNum; i++) {
					for (int j = 0; j < rowSubsectionNum; j++) {
						ofRotateX(rotatePlaneDeg * 0.001);
						ofPushMatrix();
						ofTranslate(i * subsectionWidth, j * subsectionHeight,
							heightArr[i * rowSubsectionNum + j] * sin(ofGetElapsedTimef()));
						ofSetColor(255);
						image.drawSubsection(0, 0,
							subsectionWidth, subsectionHeight,
							i * subsectionWidth, j * subsectionHeight);
						ofPopMatrix();
					}
				}
			}
			else {
				//ofResetElapsedTimeCounter();
				for (int i = 0; i < rowSubsectionNum; i++) {
					for (int j = 0; j < rowSubsectionNum; j++) {
						ofRotateX(rotatePlaneDeg * 0.001);
						ofPushMatrix();
						ofTranslate(i * subsectionWidth, j * subsectionHeight,
							heightArr[i * rowSubsectionNum + j] * sin(ofGetElapsedTimef()));
						ofSetColor(image.getColor(i * subsectionWidth, j * subsectionHeight));
						ofDrawBox(0, 0, 0, 10, 10, 10);
						ofPopMatrix();
					}
				}
			}
		}
		else if (waveMode) {
			if (!cubeMode) {
				for (int i = 0; i < rowSubsectionNum; i++) {
					for (int j = 0; j < rowSubsectionNum; j++) {
						ofPushMatrix();
						ofTranslate(i * subsectionWidth, j * subsectionHeight,
							heightArr2[i * rowSubsectionNum + j] * sin(ofGetElapsedTimef()));
						ofSetColor(255);
						image.drawSubsection(0, 0,
							subsectionWidth, subsectionHeight,
							i * subsectionWidth, j * subsectionHeight);
						ofPopMatrix();
					}
				}
			}
			else {
				//ofResetElapsedTimeCounter();
				for (int i = 0; i < rowSubsectionNum; i++) {
					for (int j = 0; j < rowSubsectionNum; j++) {
						ofPushMatrix();
						ofTranslate(i * subsectionWidth, j * subsectionHeight,
							heightArr2[i * rowSubsectionNum + j] * sin(ofGetElapsedTimef()));
						ofSetColor(image.getColor(i * subsectionWidth, j * subsectionHeight));
						ofDrawBox(0, 0, 0, 10, 10, 10);
						ofPopMatrix();
					}
				}
			}
		}
	}
	else {
		ofSetColor(255);
		image.draw(0, 0, 0);

		//cout << (int) ofGetElapsedTimef() << endl;
	}
	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'e' :
		explode = !explode;
		if (!explode) {
			spiralMode = false;
			waveMode = false;
		}
		break;
	case 'c':
		cubeMode = !cubeMode;
		break;
	case 's':
		spiralMode = true;
		waveMode = false;
		break;
	case 'w':
		waveMode = true;
		spiralMode = false;
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
