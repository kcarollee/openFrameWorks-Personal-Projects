#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	beat.loadSound("beat.mp3");
	bands = 30; // must be even 
	bandIndex = bands / 2 - 1;
	fftSmooth = new float[bands];
	for (int i = 0; i < bands; i++) {
		fftSmooth[i] = 0;
		
	}
	
	for (int i = 0; i < bands; i++) {
		ofRectangle *newRect = new ofRectangle;
		newRect->setPosition(i * ofGetScreenWidth() / bands, ofGetScreenHeight() / 2);
		newRect->setWidth(ofGetScreenWidth() / bands);
		rectArr.push_back(newRect);
	}

	beat.setVolume(0.2);

	rotatex = 1;
	rotatey = 1;
	rotatez = 0;
	
	ofSetFullscreen(true);
	ofEnableDepthTest();
	cubeID = 0;
	sideNum = 7; // must be odd
	
	sideLength = 15;
	waveHeight = 3.5;
	
	cubeNum = pow(sideNum, 3);
	if (sideNum % 2 == 1)
		centerIndex = cubeNum / 2;
	rotation = 5;
	centerPos =  ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 0);
	
	cubeArrCenterHeight = 0;
	cubePos = ofVec3f(centerPos.x - sideLength * sideNum / 2, 
		centerPos.y - sideLength * sideNum / 2, 
		centerPos.z + sideLength * sideNum / 2);
	
	light.setAreaLight(400, 400);

	light.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 500);
	
	
	
	// setting positions of cubes and color
	for (int i = 0; i < sideNum; i++) {
		for (int j = 0; j < sideNum; j++) {
			for (int k = 0; k < sideNum; k++) {
				Cube* cube = new Cube();
				cube->setup(sideLength, cubePos, cubeID);
				cubeArr.push_back(cube);
				cubeID++;
				cubePos.x += sideLength;
				cube->color.set(red, green, blue);
				green = 100 + 50 * sin(ofGetElapsedTimef());
				if (cube->cubeID == centerIndex) {
					cubeArrCenterHeight == cube->pos.z;
				}
			}
			cubePos.x = centerPos.x - sideLength * sideNum / 2;
			cubePos.y += sideLength;
		}
		cubePos.y = centerPos.y - sideLength * sideNum / 2;
		cubePos.z += sideLength;
	}

	fillMode = "NO FILL MODE";
	isFill = false;
	
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSoundUpdate();
	float * value = ofSoundGetSpectrum(bands);
	for (int i = 0; i < bands; i++) {
		fftSmooth[i] *= 0.9f;
		if (fftSmooth[i] < value[i]) {
			fftSmooth[i] = value[i];
		}
		if (i == bandIndex) {
			fftSmoothArr.push_back(fftSmooth[i]);
		}
		if (i == 0) {
			rectArr[i]->height = -fftSmooth[i] * 500;
		}
		
		else if (0 < i && i < bands / 2) {
			rectArr[i]->height = -fftSmooth[i] * 4000;
		}
		else
			rectArr[i]->height = -rectArr[bands - 1 - i]->height;
	}

	if (fftSmoothArr.size() >= 3) {
		if (fftSmoothArr[fftSmoothArr.size() - 1] < fftSmoothArr[fftSmoothArr.size() - 2] &&
			fftSmoothArr[fftSmoothArr.size() - 2] > fftSmoothArr[fftSmoothArr.size() - 3]) {
			rotatex = ofRandom(-1, 1);
			rotatey = ofRandom(-1, 1);
			rotatez = ofRandom(-1, 1);
			
		}
		
	}

	if (fftSmoothArr.size() >= 1000) {
		fftSmoothArr.clear();
	}

	for (auto cube : cubeArr) {
		float xdet = cube->originalPos.x - centerPos.x;
		float ydet = cube->originalPos.y - centerPos.y;
		float zdet = cube->originalPos.z - centerPos.z;
		float xpos, ypos, zpos;
		
		
		green = 100 + 50 * sin(ofGetElapsedTimef() / 60);
		blue = 100 + 50 * sin(3 * ofGetElapsedTimef());
		red = 100 + 50 * sin(5 * ofGetElapsedTimef());
		
		
		cube->color.set(red, green, blue);
		float timeElapsed = ofGetElapsedTimef() / 3;
		//cout << fftSmooth[0] << endl;
		waveHeight = 250 * fftSmooth[bands / 2 - 1];
		
		if (xdet >= 0) {
			xpos = cube->originalPos.x + waveHeight * abs((sin(timeElapsed)) * abs(xdet));
			
		}
		else {
			xpos = cube->originalPos.x - waveHeight * abs((sin(timeElapsed)) * abs(xdet));
			
		}

		if (ydet >= 0) {
			ypos = cube->originalPos.y + waveHeight * abs((sin(timeElapsed)) * abs(ydet));
		}
		else {
			ypos = cube->originalPos.y - waveHeight * abs(( sin(timeElapsed)) * abs(ydet));
		}

		if (zdet >= 0) {
			zpos = cube->originalPos.z + waveHeight * abs((sin(timeElapsed)) * abs(zdet));
			if (cube->cubeID == centerIndex) {
				cubeArrCenterHeight = zpos;
			}
		}
		else {
			zpos = cube->originalPos.z - waveHeight * abs((sin(timeElapsed)) * abs(zdet));
			if (cube->cubeID == centerIndex) {
				cubeArrCenterHeight = zpos;
			}
		}

		cube->changePosition(ofVec3f(xpos, ypos, zpos));
			
		rotation += 0.001;
		
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//cam.begin();
	int blue_2;
	int green_2;
	green = 100 + 50 * sin(ofGetElapsedTimef() / 60);
	blue = 100 + 50 * sin(3 * ofGetElapsedTimef());
	red = 0;
	ofBackground(225 - red, 225 - green, 225 - blue);	
	ofPushMatrix();
	
	ofDrawBitmapString(fillMode, 10, 500);
	ofDrawBitmapString("Press 'P' to play music.", 10, 510);
	ofDrawBitmapString("Press 'S' to stop music.", 10, 520);
	ofDrawBitmapString("Press 'F' to enable fill mode.", 10, 530);
	ofEnableLighting();
	light.enable();

	// draw 2D visualizer
	
	for (int i = 0; i < bands; i++) {
		blue_2 = 100 + 50 * sin(ofGetElapsedTimef());
		green_2 = 100 + 50 * sin(ofGetElapsedTimef());
		ofSetColor(10, green_2, blue_2);
		ofDrawRectangle(*rectArr[i]);
	}

	
	// rotate big cube
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, cubeArrCenterHeight);	
	ofRotate(rotation, rotatex, rotatey, rotatez);
	ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2, -cubeArrCenterHeight);

	for (auto cube : cubeArr) {
		cube->draw();
	}
	light.disable();
	ofPopMatrix();
	

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
	if (key == 'f') {
		for (auto cube : cubeArr) {
			cube->fill = !(cube->fill);
		}
		
		isFill = !isFill;
		if (isFill) fillMode = "FILL MODE";
		else fillMode = "NO FILL MODE";		
		
	}

	else if (key == 'p') {
		beat.play();
	}

	else if (key == 's') {
		beat.stop();
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
