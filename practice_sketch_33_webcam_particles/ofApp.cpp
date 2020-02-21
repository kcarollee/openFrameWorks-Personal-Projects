#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0);

	ofSetCircleResolution(4);
	tileRowNum = tileColNum = 80;
	float tileDim = ofGetWidth() / (float) tileRowNum;
	for (int i = 0; i < tileRowNum; i++) {
		for (int j = 0; j < tileColNum; j++) {
			Tile* temp = new Tile(glm::vec2(j * tileDim, i * tileDim), tileDim, tileDim, (int) ofRandom(1, 3));
			TileArr.push_back(temp);
		}
	}

	webcam.setVerbose(true);
	//webcam.initGrabber(ofGetWidth(), ofGetHeight());
	webcam.setup(ofGetWidth(), ofGetHeight());
	

	webcamCapture.allocate(ofGetHeight(), ofGetWidth());
	webcamGray.allocate(ofGetWidth(), ofGetHeight());
	webcamGrayPrev.allocate(ofGetWidth(), ofGetHeight());
	webcamGrayDiff.allocate(ofGetWidth(), ofGetHeight());
	
	
	threshold = 110.0;
	snapshot = false;
	webcamFeed = true;
	contMode = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	webcam.update();
	if (webcam.isFrameNew()) {
		webcamCapture.setFromPixels(webcam.getPixels());
		webcamGray = webcamCapture;
		webcamGrayDiff.absDiff(webcamGrayPrev, webcamGray);
		//webcamGrayPrev = webcamGray;
		webcamGrayDiff.threshold(threshold);
	}

	if (contMode) {
		ofColor* randomColor = new ofColor;
		randomColor->set(ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255)));
		for (auto t : TileArr) {
			
			if (t->checkCenterColor(webcamGrayDiff)) {
				t->toggleParticle = true;
			}
			else t->toggleParticle = false;
		}
	}
	else {
		if (snapshot) {
			ofColor* randomColor = new ofColor;
			randomColor->set(ofColor(ofRandom(50, 255), ofRandom(50, 255), ofRandom(50, 255)));
			for (auto t : TileArr) {
				if (t->toggleParticle) {
					if (t->checkCenterColor(webcamGrayDiff)) t->setColor(randomColor);
					continue;
				}
				t->checkColorByPixels(webcamGrayDiff, 3);
				t->setColor(randomColor);
				t->updateParticle();
			}
		}
	}
	for (auto t : TileArr) t->updateParticle();
	snapshot = false;
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetHexColor(0xffffff);
	
	if(webcamFeed) webcamGrayDiff.draw(0, 0, ofGetWidth(), ofGetHeight());
	
	ofSetLineWidth(0.1);
	for (auto t : TileArr) t->draw();
	
	ofSetColor(255);
	ofDrawBitmapString("s: take snapshot\nv: toggle video\nf: free particles\nc: continuous", glm::vec2(4, 10));
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case OF_KEY_UP:
		threshold += 0.5;
		cout << threshold << endl;
		break;
	case OF_KEY_DOWN:
		threshold -= 0.5;
		break;
	case 'r':
		for (auto t : TileArr) { t->toggleRect = !t->toggleRect; }
		break;
	case'f':
		for (auto t : TileArr) { t->toggleBoundary = !t->toggleBoundary; }
		break;
	case 'c':
		contMode = !contMode;
		break;
	case's':
		snapshot = true;
		break;
	case 'v':
		webcamFeed = !webcamFeed;
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
