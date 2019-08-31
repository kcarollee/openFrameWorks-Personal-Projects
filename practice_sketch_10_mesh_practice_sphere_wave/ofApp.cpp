#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetFullscreen(true);
	gridX = 50;
	gridY = 50;
	//waveHeight = 20;

	rotation = 120;
	sphereRotate = 0;
	rectHeight = 20;
	rectWidth = 40;
	maxHeight = 100;
	planeGap = 200;
	sphereRadius = 50;
	camera.setPosition(ofGetWidth() / 2, ofGetHeight(), 50);
	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			mesh.addVertex(ofVec3f((gridX / 2 - j) * rectWidth,
				(gridY / 2 - i) * rectHeight, 0.0f));
			mesh.addColor(ofColor(255 * ofMap(j, 0, gridX, 0.0, 1.0),
				255 * ofMap(i, 0, gridY, 0.0, 1.0), 255 * ofMap(j, 0, gridX, 0.0, 1.0)));
			heightArr.push_back(ofRandom(10, maxHeight));
		}
	}
	for (int i = 0; i < gridY - 1; i++) {
		for (int j = 0; j < gridX - 1; j++) {
			mesh.addIndex(i * gridX + j);
			mesh.addIndex(i * gridX + j + 1);
			mesh.addIndex((i + 1) * gridX + j);
			mesh.addIndex(i * gridX + j + 1);
			mesh.addIndex((i + 1) * gridX + j + 1);
			mesh.addIndex((i + 1) * gridX + j);
		}
	}		


	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			mesh2.addVertex(ofVec3f((gridX / 2 - j) * rectWidth,
				(gridY / 2 - i) * rectHeight, planeGap));
			mesh2.addColor(ofColor(255 * ofMap(j, 0, gridX, 0.0, 1.0),
				255 * ofMap(i, 0, gridY, 0.0, 1.0), 255 * ofMap(i, 0, gridY, 0.0, 1.0)));
		}
	}
	for (int i = 0; i < gridY - 1; i++) {
		for (int j = 0; j < gridX - 1; j++) {
			mesh2.addIndex(i * gridX + j);
			mesh2.addIndex(i * gridX + j + 1);
			mesh2.addIndex((i + 1) * gridX + j);
			mesh2.addIndex(i * gridX + j + 1);
			mesh2.addIndex((i + 1) * gridX + j + 1);
			mesh2.addIndex((i + 1) * gridX + j);
		}
	}
	ofSetLineWidth(2);
	//mesh.setMode(OF_PRIMITIVE_LINE_LOOP);	
	light.setAreaLight(1000, 1000);
	light.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 500);
	light.setAmbientColor(ofColor(255, 0, 0));
	ofEnableDepthTest();
	ofEnableSmoothing();
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			mesh.setVertex(i * gridX + j, ofVec3f((gridX / 2 - j) * rectWidth, (gridY / 2 - i) * rectHeight,
				heightArr[gridY * i + j] * sin(ofGetElapsedTimef() * 3)));
		}
	}	
	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			mesh2.setVertex(i * gridX + j, ofVec3f((gridX / 2 - j) * rectWidth, (gridY / 2 - i) * rectHeight,
				planeGap +heightArr[gridY * i + j] * -sin(ofGetElapsedTimef() * 3)));
		}
	}
	//rectHeight = 50 * sin(ofGetElapsedTimef() / 60);
	//rectWidth = 50 * sin(ofGetElapsedTimef() / 60);
	sphereRotate += 1;
	light.setAmbientColor(ofColor(100 * abs(sin(ofGetElapsedTimef())), 60 * abs(cos(ofGetElapsedTimef())), 0));
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofSetBackgroundColor(0);
	//camera.begin();
	ofEnableLighting();
	light.enable();
	
	//spheres
	
	for (int i = 0; i < gridY; i++) {
		for (int j = 0; j < gridX; j++) {
			ofPushMatrix();
			
			ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
			ofRotate(rotation, 1.0f, 0.0f, 0.0f);
			ofSetColor(ofColor(255 * sin(ofGetElapsedTimeMicros()), 255 * cos(ofGetElapsedTimef()), 255 * sin(ofGetElapsedTimef())));
			ofDrawSphere((gridX / 2 - j) * rectWidth,
				(gridY / 2 - i) * rectHeight, planeGap / 2, 10 * cos(ofGetElapsedTimef() * 2 - 10 * j));
			ofPopMatrix();
		}
	}
	
	// mesh
	ofPushMatrix();
	//ofNoFill();
	
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofRotate(rotation, 1.0f, 0.0f, 0.0f);
	
	//mesh.drawFaces();
	mesh.drawWireframe();
	mesh2.drawFaces();
	ofPopMatrix();
	
	light.disable();
	//camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'e':
		rectHeight += 2;
		rectWidth += 2;
		break;
	case 's':
		rectHeight -= 2;
		rectWidth -= 2;
		break;
	case 'r':
		rotation += 1;
		break;
	case 'u':
		rotation -= 1;
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
