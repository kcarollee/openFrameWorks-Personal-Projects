#include "ofApp.h"

void buildQuadMesh(ofMesh& mesh, glm::vec3 pos, float width, float height) {
	float uvcoords[8] = { 0, 1, 1, 1, 0, 0, 1, 0 };
	ofIndexType indices[6] = { 0, 1, 3, 3, 2, 0 };
	mesh.addVertex(glm::vec3(pos.x - width * 0.5, pos.y + height * 0.5, pos.z));
	mesh.addVertex(glm::vec3(pos.x + width * 0.5, pos.y + height * 0.5, pos.z));
	mesh.addVertex(glm::vec3(pos.x - width * 0.5, pos.y - height * 0.5, pos.z));
	mesh.addVertex(glm::vec3(pos.x + width * 0.5, pos.y - height * 0.5, pos.z));
	for (int i = 0; i < 4; i++) {
		mesh.addTexCoord(glm::vec2(uvcoords[i * 2], uvcoords[i * 2 + 1]));
	}
	mesh.addIndices(indices, 6);
}
//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableDepthTest();
	ofDisableArbTex();
	
	CubeShader.load("CubeShader.vert", "CubeShader.frag");
	SketchShader.load("SketchShader.vert", "SketchShader.frag");
	BackgroundShader.load("BackgroundShader.vert", "BackgroundShader.frag");
	ofBackground(0);

	walkerNum = 50;
	for (int i = 0; i < walkerNum; i++) {
		Walker* w = new Walker(30, 0.1,0.1, vec3(0));
		w->setBoundary(vec3(1.0));
		walkerArr.push_back(w);
	}
	camera.setup(glm::vec3(0, 0, 1), 90.0f, 0.1);
	proj = perspective(camera.fov, (float)(ofGetWidth() / (float)ofGetHeight()), 0.01f, 10.0f);
	model = mat4();
	view = inverse(translate(camera.position));
	mvp = proj * model * view;

	buildQuadMesh(sketchQuadMesh, vec3(0), 2.0, 2.0);
	buildQuadMesh(backgroundMesh, vec3(0), 2.0, 2.0);
	sketchFbo.allocate(ofGetWidth(), ofGetHeight());
	sketchFbo.begin();
	ofClear(0, 0, 0, 0);
	sketchFbo.end();
	
	sizeChangeFlag = false;
	newSize = 0.2;

	track.load("track.mp3");
	track.play(); 
	track.setPosition(0.65);
	bandNum = 10;
	fftSmooth = new float[bandNum];
	for (int i = 0; i < bandNum; i++) {
		fftSmooth[i] = 0;
	}

	bgSoundVal = 3.0;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (track.isPlaying()) {
		float * value = ofSoundGetSpectrum(bandNum);
		for (int i = 0; i < bandNum; i++) {
			fftSmooth[i] *= 0.97f;
			if (fftSmooth[i] < value[i]) {
				fftSmooth[i] = value[i];
			}
		}
	}
	
	if (fftSmooth[0] > 0.95) sizeChangeFlag = true;
	if (sizeChangeFlag) {
		for (auto w : walkerArr) {
			w->changeCubeSize(newSize);
		}
		bgSoundVal -= 0.5;
		newSize -= 0.015;
		if (newSize < 0.1) {
			newSize = 0.2;
			bgSoundVal = 3.0;
			sizeChangeFlag = false;
		}
	}
	//else newSize = 0.075;
	for (auto w : walkerArr) w->update();
	if (camera.cameraMoved) {
		camera.cameraUpdate(view);
		mvp = proj * model * view;
	}

	
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	sketchFbo.begin();

	ofDisableDepthTest();
	BackgroundShader.begin();
	BackgroundShader.setUniformMatrix4f("mvp", mat4());
	BackgroundShader.setUniform1f("time", ofGetElapsedTimef());
	BackgroundShader.setUniform1f("bgSoundVal", bgSoundVal);
	backgroundMesh.draw();
	BackgroundShader.end();

	ofEnableDepthTest();
	CubeShader.begin();
	CubeShader.setUniformMatrix4f("mvp", mvp);
	CubeShader.setUniform1f("time", ofGetElapsedTimef());
	for (auto w : walkerArr) w->draw(CubeShader);
	CubeShader.end();
	sketchFbo.end();

	SketchShader.begin();
	SketchShader.setUniformMatrix4f("mvp", mat4());
	SketchShader.setUniformTexture("tex", sketchFbo.getTexture(), 0);
	sketchQuadMesh.draw();
	SketchShader.end();

	sketchFbo.allocate(ofGetWidth(), ofGetHeight());
	sketchFbo.begin();
	ofClear(0, 0, 0, 0);
	sketchFbo.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'm':
		for (auto w : walkerArr) {
			w->mode = ++w->mode % 4;
		}
		break;
	case 'n':
		sizeChangeFlag = false;
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
