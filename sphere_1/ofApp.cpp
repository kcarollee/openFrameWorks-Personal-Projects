#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	radius = 300;
	rotation = 60;
	initialHeightInc = heightIncrement = 10;
	
	circleRes = 60; 
	mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
	
	for (float h = 0; h <= radius; h += heightIncrement, index++) {
		for (int i = 0; i < circleRes; i++) {
			mesh.addVertex(ofVec3f(sqrt(2 * radius * h - pow(h, 2)) * cos(2 * PI * (i % (int)circleRes) / circleRes),
				sqrt(2 * radius * h - pow(h, 2)) * sin(2 * PI *  (i % (int)circleRes) / circleRes),
				h - radius ));
			mesh.addColor(ofColor(0, green, blue));
			mesh.addIndex(i  + circleRes * index);		
		}
	}
	

	for (float h = radius + 1; h <= 2 * radius; h += heightIncrement, index++) {
		for (int i = 0; i < circleRes; i++) {
			mesh.addVertex(ofVec3f(sqrt(2 * radius * h - pow(h, 2)) * cos(2 * PI *  (i % (int)circleRes) / circleRes),
				sqrt(2 * radius * h - pow(h, 2)) * sin(2 * PI *  (i % (int)circleRes) / circleRes),
				h - radius ));
			
			mesh.addColor(ofColor(0, green, blue));
			mesh.addIndex(i  + circleRes * index);

		}
		
	}

	//mesh.setMode(OF_PRIMITIVE_LINES);
	
	light.setAreaLight(radius, radius);
	light.setPosition(0, 0, 500);

	ofEnableDepthTest();
	ofEnableSmoothing();
}

//--------------------------------------------------------------
void ofApp::update(){
	changeColor();
	rotation += 0;
	index = 0;
	float elapasedTime = ofGetElapsedTimef() * 0.6;
	for (float h = 0; h <= radius; h += heightIncrement, index++) {
		for (int i = 0; i < circleRes; i++) {
			mesh.setVertex(i + circleRes * index, 
				ofVec3f(sqrt(2 * radius * h - pow(h, 2)) * cos(2 * PI * (i % (int)circleRes) * elapasedTime / circleRes),
				sqrt(2 * radius * h - pow(h, 2)) * sin(2 * PI *  (i % (int)circleRes) * elapasedTime / circleRes),
				h - radius));		

			mesh.setColor(i + circleRes * index,
				ofColor(0, green, blue));
		}
	}
	
	for (float h = radius + 1; h <= 2 * radius; h += heightIncrement, index++) {
		for (int i = 0; i < circleRes; i++) {
			mesh.setVertex(i + circleRes * index,
				ofVec3f(sqrt(2 * radius * h - pow(h, 2)) * cos(2 * PI *  (i % (int)circleRes) * elapasedTime / circleRes),
				sqrt(2 * radius * h - pow(h, 2)) * sin(2 * PI *  (i % (int)circleRes) * elapasedTime / circleRes),
				h - radius));
			mesh.setColor(i + circleRes * index,
				ofColor(0, green, blue));
			
		}
	}
	
	
}
void ofApp::changeColor() {
	blue = sin(ofGetElapsedTimef()) * 50 + 150;
	green = cos(ofGetElapsedTimef()) * 50 + 150;

}
//--------------------------------------------------------------
void ofApp::draw(){
	//camera.begin();
	ofBackground(255);
	ofEnableLighting();
	light.enable();

	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight()  / 2);//, radius);
	ofRotate(rotation, 1.0f, 0.0f, 0.0f);

	mesh.drawFaces();
	//mesh.drawWireframe();

	ofPopMatrix();
	light.disable();
	//camera.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case 'i':
		if (heightIncrement == initialHeightInc) {}
		else
			heightIncrement -= 1;
		break;
	case 'd':
		heightIncrement += 1;		
		break;
	case 'r':
		rotation += 1;
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
