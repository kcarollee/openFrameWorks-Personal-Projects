#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	vertNum = 500;
	edgeNum = 4000;
	graph = new GraphType();
	graph->setup(170);
	graph->insertVertices(vertNum);
	graph->insertRandomEdges(edgeNum);
	deg = 90;
	
}

//--------------------------------------------------------------
void ofApp::update(){
	graph->updateDrawIndex();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableAntiAliasing();
	ofBackground(0);
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0);
	ofRotateX(deg);
	graph->draw();
	
	deg += 0.2;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'r':
		graph->reset();
		graph->insertVertices(vertNum);
		graph->insertRandomEdges(edgeNum);
		break;
	case 'd':
		graph->dijkstraMode = true;
		graph->inc = 0;
		break;
	case 'n':
		graph->toggleNumbers = !graph->toggleNumbers;
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
