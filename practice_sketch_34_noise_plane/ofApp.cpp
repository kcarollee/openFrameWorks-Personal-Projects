#include "ofApp.h"


void ofApp::generateNoiseTexture(ofImage& noiseImg, float width, float height) {
	noiseImg.allocate(width, height, OF_IMAGE_GRAYSCALE);
	float noise;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			if (alterZOffset) noise = ofNoise(j * 0.1, i * 0.1 - ofGetElapsedTimef(), 0.5 + ofGetElapsedTimef() * 0.25) * 255;
			else noise = ofNoise(j * 0.1, i * 0.1 - ofGetElapsedTimef(), 0.5) * 255;

			noiseImg.getPixels()[i * width + j] = noise;
		}
	}
	noiseImg.update();
}
//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();
	ofEnableDepthTest();
	ofBackground(0);
	
	TestShader.load("TestShader");
	generateNoiseTexture(noiseImg, 50, 50);

	camera.setup(glm::vec3(0, 0, 1), glm::radians(90.0), 0.05);
	mvp = glm::mat4();
	view = glm::inverse(translate(camera.position));
	proj = glm::perspective(90.0f, (float)(ofGetWidth() / ofGetHeight()), 0.01f, 10.0f);
	
	plane.setup(6.0, 6.0, 50, 50, glm::vec3(0));
	plane.buildPlaneMesh();
	plane.addColor(noiseImg);
	plane.setMode(OF_PRIMITIVE_LINES);

	ceiling.setup(6.0, 6.0, 50, 50, glm::vec3(0));
	ceiling.buildPlaneMesh();
	ceiling.addColor(noiseImg);
	ceiling.setMode(OF_PRIMITIVE_LINES);

	greyScaleMode = 0;
	

	//track.load("track1.mp3");
	//track.play();

}

//--------------------------------------------------------------
void ofApp::update(){
	plane.setColor(noiseImg);
	ceiling.setColor(noiseImg);
	generateNoiseTexture(noiseImg, 50, 50);

	if (camera.cameraMoved) {
		camera.cameraUpdate(view);
		mvp = proj * view * model;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//noiseImg.draw(0, 0);

	TestShader.begin();
	
	TestShader.setUniform1f("time", ofGetElapsedTimef());
	TestShader.setUniformTexture("noiseTex", noiseImg.getTexture(), 0);
	TestShader.setUniform1i("greyScale", greyScaleMode);
	//quad.draw();

	glm::mat4 planeModel = glm::translate(glm::vec3(0, -0.5, 0)) *  glm::rotate(glm::radians(-90.0f), glm::vec3(1, 0, 0));
	mvp = proj * view * planeModel;
	TestShader.setUniformMatrix4f("model", planeModel);
	TestShader.setUniformMatrix4f("mvp", mvp);
	plane.draw();

	glm::mat4 ceilingModel = glm::translate(glm::vec3(0, 0.5, 0)) *  glm::rotate(glm::radians(270.0f), glm::vec3(1, 0, 0));
	mvp = proj * view * ceilingModel;
	TestShader.setUniformMatrix4f("model", ceilingModel);
	TestShader.setUniformMatrix4f("mvp", mvp);
	ceiling.draw();


	TestShader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	static int mPressedNum = 0;
	static int gPressedNum = 0;
	static int zPressedNum = 0;
	switch (key) {
	case 'm':
		switch (mPressedNum++ % 3) {
		case 0:
			plane.setMode(OF_PRIMITIVE_LINES);
			ceiling.setMode(OF_PRIMITIVE_LINES);
			break;
		case 1:
			plane.setMode(OF_PRIMITIVE_TRIANGLES);
			ceiling.setMode(OF_PRIMITIVE_TRIANGLES);
			break;
		case 2:
			plane.setMode(OF_PRIMITIVE_POINTS);
			ceiling.setMode(OF_PRIMITIVE_POINTS);
			break;
		}
		break;
	case 'g':
		switch (gPressedNum++ % 3) {
		case 0:
			greyScaleMode = 0;
			break;
		case 1:
			greyScaleMode = 1;
			break;
		case 2:
			greyScaleMode = 2;
			break;
		}
		break;
	case 'z':
		switch (zPressedNum++ % 2) {
		case 0:
			alterZOffset = false;
			break;
		case 1:
			alterZOffset = true;
			break;
		}
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
