#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	glPointSize(3);
	ofSetLineWidth(3);
	ofSetBackgroundColor(30);

	int flockNum = 3;
	for (int i = 0; i < flockNum; i++) {
		Flock* f = new Flock(400, 100 * (i + 1));
		f->setCoefs(1.0, 0.4, 0.3);
		flockArr.push_back(f);
	}

	cam.setPosition(ofGetWidth() * 0.5, ofGetHeight() * 0.5, 800);
	light.setPosition(glm::vec3(ofGetWidth() * 0.5, ofGetHeight() * 0.5, 500));
	light.setPointLight();
	//light.setAmbientColor(200);


	sketchShader.load("sketchShader");
	ofDisableArbTex();
	ofEnableDepthTest();

	frameBuffer = new ofFbo;
	frameBuffer->allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	frameBuffer->begin();
	ofClear(0);
	frameBuffer->end();
	
	sketchPlane.set(ofGetWidth(), ofGetHeight());
	sketchPlane.enableTextures();
	sketchPlane.setPosition(glm::vec3(-ofGetWidth() * 0.5, ofGetHeight() * 0.5, 0));

}

//--------------------------------------------------------------
void ofApp::update() {
	for (auto f : flockArr) f->update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	frameBuffer->begin();
	cam.begin();
	// drawing boids on a 2D plane
	light.enable();


	ofPushMatrix();
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5, 0);
	if (flockArr[0]->mode % 3 == 2) {
		ofRotateX(ofGetMouseY() * 0.5);
		ofRotateY(-ofGetMouseX() * 0.5);
	}
	//for (auto f : flockArr) f->display();

	for (int i = 0; i < flockArr.size(); i++) {
		if (flockArr[i]->mode % 3 == 0) {
			ofPushMatrix();
			ofTranslate(-180 + 180 * i, -180 + 180 * i, 0);
			ofSetColor(flockArr[i]->color);
			ofDrawBitmapString("flock " + to_string(i + 1), glm::vec2(-180, 180 + 3));
			flockArr[i]->display();
			ofPopMatrix();
		}
		else flockArr[i]->display();
	}
	ofPopMatrix();

	light.disable();
	cam.end();


	frameBuffer->end();

	sketchShader.begin();
	sketchShader.setUniform2f("resolution", glm::vec2(ofGetWidth(), ofGetHeight()));
	sketchShader.setUniformTexture("tex", frameBuffer->getTexture(), 0);
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
	ofDrawRectangle(-ofGetWidth() * 0.5, -ofGetHeight() * 0.5, ofGetWidth(), ofGetHeight());
	//sketchPlane.draw();
	sketchShader.end();
	frameBuffer->allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	frameBuffer->begin();
	ofClear(0);
	frameBuffer->end();

	ofDisableDepthTest();
	ofPushMatrix();
	ofDrawBitmapString("press 'r' to add random velocity ", 10 - ofGetWidth() * 0.5, 30 - 0.5 * ofGetHeight());
	ofPopMatrix();
	ofEnableDepthTest();


	/*
	if (textureArr.size() < textureNum) {
		textureArr.push_back(frameBuffer->getTexture());
	}
	else {
		textureArr.erase(textureArr.begin());
		textureArr.push_back(frameBuffer->getTexture());
	}

	frameBuffer->allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	frameBuffer->begin();
	ofClear(0);
	frameBuffer->end();


	for (int i = 0; i < textureArr.size(); i++) {
		textureArr[i].draw(glm::vec3(0, 0, -PLANE_DOMAIN_MAX + cubeDiv * i));
	}
	*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case 'w':
		for (auto f : flockArr) f->mode++;
		break;
	case 'r':
		for (auto f : flockArr) {
			for (auto b : f->particleArr) b->velocity += glm::vec2(ofRandom(-3, 3), ofRandom(-3, 3));
		}
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
