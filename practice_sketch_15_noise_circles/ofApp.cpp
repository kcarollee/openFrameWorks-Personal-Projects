#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(0);
	radius = 30;

	gui.setup();
	gui.add(noise.set("noise", 0.5, 0.0, 3.0));
	gui.add(vel.set("vel", 0.5, 0.1, 3.0));
	gui.add(alphaDecrement.set("alpha decrement", 0.5, 0.1, 1.5));
}

//--------------------------------------------------------------
void ofApp::update(){
	if (blobArr.size()) {
		for (auto blob : blobArr) {
			//blob->move_1(noise);
			blob->move_1(noise);
			blob->move_2(vel);
			//blob->deleteSelf();
		}
		

		if (blobArr[0]->isOutOfBounds()) {
			delete blobArr[0];
			blobArr.pop_front();
			//cout << "POPPED" << endl;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();
	if (blobArr.size()) {
		for (auto blob : blobArr) {
			blob->draw(alphaDecrement);
		}
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
	Blob* blob = new Blob;
	blob->setup(100, ofVec2f(x, y), radius);
	blobArr.push_back(blob);
	//radius += 5;
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
