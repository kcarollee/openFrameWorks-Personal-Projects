#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	glPointSize(2);
	ofDisableArbTex();
	videoSource.load("test13.mov"); //  video file name please
	//ofSetWindowShape(videoSource.getWidth(), videoSource.getHeight());
	videoSource.play();
	videoSourceShader.load("videoSourceShader");
	backbufferShader.load("backbufferShader");
	finalOutputShader.load("finalOutputShader");
	windowDiv = 75;
	cellWidth = ofGetWidth() / windowDiv;
	cellHeight = ofGetHeight() / windowDiv;

	videoFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	videoFbo.begin();
	ofClear(0);
	videoFbo.end();

	for (int i = 0; i < windowDiv; i++) {
		for (int j = 0; j < windowDiv; j++) {
			ParticleCell* tc = new ParticleCell(cellWidth * j, cellHeight * i, cellWidth, cellHeight);
			particleCellArr.push_back(tc);
		}
	}

	particlesFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	particlesFbo.begin();
	ofClear(0);
	particlesFbo.end();

	midbuffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	midbuffer.begin();
	ofClear(0);
	midbuffer.end();

	backbuffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	backbuffer.begin();
	ofClear(0);
	backbuffer.end();

	videoSourceFbo.allocate(videoSource.getWidth(), videoSource.getHeight(), GL_RGBA);
	videoSourceFbo.begin();
	ofClear(0);
	videoSourceFbo.end();

	finalOutputFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	

	webcam.setup(ofGetWidth(), ofGetHeight());
	webcam.setVerbose(true);

	mode = 1;
	

	
}

//--------------------------------------------------------------
void ofApp::update(){
	switch (mode) {
	case 0:
		videoSource.update();
		break;
	case 1:
		webcam.update();
		break;
	}
	for (auto c : particleCellArr) c->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	videoSourceFbo.begin();
	switch (mode) {
	case 0:
		videoSource.draw(0, 0);
		break;
	case 1:
		webcam.draw(0, 0);
		break;
	}
	videoSourceFbo.end();

	videoSourceFbo.readToPixels(videoSourcePixels);

	videoFbo.begin();
	videoSourceShader.begin();
	videoSourceShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	switch (mode) {
	case 0:
		videoSourceShader.setUniformTexture("videoTex", *videoSource.getTexture(), 0);
		break;
	case 1:
		videoSourceShader.setUniformTexture("videoTex", webcam.getTexture(), 0);
		break;
	}
	videoSourceShader.setUniform1f("windowDiv", 1.0 / windowDiv);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	videoSourceShader.end();
	videoFbo.end();

	//videoFbo.draw(0, 0);
	videoFbo.readToPixels(videoPixels);
	videoFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	
	particlesFbo.begin();
	for (int i = 0; i < windowDiv; i++) {
		for (int j = 0; j < windowDiv; j++) {
			//ofSetColor(videoPixels.getColor(cellWidth * i, cellHeight * j));
			//ofDrawRectangle(cellWidth * i, cellHeight * j, cellWidth, cellHeight);
			particleCellArr[i * windowDiv + j]->setGreyscaleColor(videoPixels.getColor(cellWidth * j, cellHeight * i));
			particleCellArr[i * windowDiv + j]->createParticles();
			particleCellArr[i * windowDiv + j]->setDisplayColor(videoSourcePixels.getColor(cellWidth * j, cellHeight * i));
			particleCellArr[i * windowDiv + j]->display();
		}
	}
	particlesFbo.end();
	//particlesFbo.draw(0, 0); 

	midbuffer.clear();
	midbuffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	midbuffer.begin();
	backbufferShader.begin();
	backbufferShader.setUniform2f("resolution", glm::vec2(ofGetWidth(), ofGetHeight()));
	backbufferShader.setUniformTexture("currentBuffer", particlesFbo.getTexture(), 0);
	backbufferShader.setUniformTexture("backBuffer", backbuffer.getTexture(), 1);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	backbufferShader.end();
	midbuffer.end();

	backbuffer.clear();
	backbuffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	backbuffer.begin();
	midbuffer.draw(0, 0);
	backbuffer.end();

	//midbuffer.draw(0, 0);


	finalOutputShader.begin();
	finalOutputShader.setUniform2f("resolution", glm::vec2(ofGetWidth(), ofGetHeight()));
	finalOutputShader.setUniformTexture("sketchTex", midbuffer.getTexture(), 0);
	switch (mode) {
	case 0:
		finalOutputShader.setUniformTexture("videoSource", *videoSource.getTexture(), 1);
		break;
	case 1:
		finalOutputShader.setUniformTexture("videoSource", webcam.getTexture(), 1);
		break;
	}
	ofDrawRectangle(0, 0, -1, ofGetWidth(), ofGetHeight());
	finalOutputShader.end();

	float s = 0.15;
	videoSourceFbo.draw(0, 0, videoSource.getWidth() * s, videoSource.getHeight() * s);

	particlesFbo.clear();
	particlesFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

	videoFbo.clear();
	videoFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

	videoSourceFbo.clear();
	videoSourceFbo.allocate(videoSource.getWidth(), videoSource.getHeight(), GL_RGBA);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'm':
		++mode %= 2;
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
