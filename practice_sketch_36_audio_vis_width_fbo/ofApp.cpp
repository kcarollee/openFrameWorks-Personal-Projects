#include "ofApp.h"

void buildQuadMesh(ofMesh& mesh, glm::vec3 pos, float width, float height) {
	float uvcoords[8] = { 0, 1, 1, 1, 0, 0, 1, 0 };
	ofIndexType indices[6] = { 0, 1, 3, 3, 2, 0 };
	mesh.addVertex(pos);
	mesh.addVertex(vec3(pos.x + width, pos.y, pos.z));
	mesh.addVertex(vec3(pos.x, pos.y - height, pos.z));
	mesh.addVertex(vec3(pos.x + width, pos.y - height, pos.z));
	for (int i = 0; i < 4; i++) {
		mesh.addTexCoord(vec2(uvcoords[i * 2], uvcoords[i * 2 + 1]));
	}
	mesh.addIndices(indices, 6);
}
//--------------------------------------------------------------
void ofApp::setup() {
	ofDisableArbTex();
	ofEnableDepthTest();
	rectBoxw = rectBoxh = rectBoxd = 0.1;
	rowBoxNum = widthBoxNum = 2 / rectBoxw;
	float texDivx = 1.0 / (float)widthBoxNum;
	float texDivy = 1.0 / (float)rowBoxNum;
	for (int j = 0; j < rowBoxNum; j++) {
		for (int i = 0; i < widthBoxNum; i++) {
			RectBox* temp = new RectBox(vec3(-1.0 + rectBoxw * i, 1.0 - rectBoxh * j, rectBoxd),
				rectBoxw, rectBoxh, rectBoxd);
			float texCoords[8] = { i * texDivx, 1.0 - j * texDivy, 
									(i + 1) * texDivx, 1.0 - j * texDivy,
									i * texDivx, 1.0 - (j + 1) * texDivy,
									(i + 1) * texDivx, 1.0 - (j + 1) * texDivy};
			temp->setQuadTexCoords(texCoords);
			temp->buildQuads();
			rectBoxArr.push_back(temp);
		}
	}

	camera.setup(vec3(0, 0, 0.5), 90.0f, 0.06f);

	sketchProj = glm::perspective(90.0f, (float)(ofGetWidth() / ofGetHeight()), 0.01f, 10.0f);
	sketchModel = glm::mat4();
	sketchView = glm::inverse(glm::translate(camera.position));
	sketchMvp = sketchProj * sketchModel * sketchView;
	
	SketchShader1.load("SketchShader1");

	fbo1.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	fbo1.begin();
	ofClear(0, 0, 0, 0);
	fbo1.end();

	allocateFbo = false;
	manualFbo = false;
	passNum = 0;
	// background
	buildQuadMesh(backgroundMesh, glm::vec3(-1, 1, 0), 2.0, 2.0);
	SketchShader2.load("SketchShader2");
	noiseTex.load("noise.png");
	texBuffer = noiseTex.getTexture();
	
	// sound
	track.load("track.mp3");
	bandNum = 30;
	fftSmooth = new float[bandNum];
	for (int i = 0; i < bandNum; i++) {
		fftSmooth[i] = 0;
	}
	center = glm::vec2(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
}

//--------------------------------------------------------------
void ofApp::update() {
	if (manualFbo) {
		if (++passNum == 1) allocateFbo = true;
		manualFbo = false;
	}
	else passNum = 0;

	for (int j = 0; j < rowBoxNum; j++) {
		for (int i = 0; i < widthBoxNum; i++) {
			int index = j * widthBoxNum + i;
			rectBoxArr[index]->changeHeight(ofClamp(fftSmooth[1], 0, 0.5) * 0.3 * sin(rectBoxArr[index]->getFloorCenterDist() * 30 + ofGetElapsedTimef() * 10));
		}
	}
	
	if (camera.cameraMoved) {camera.cameraUpdate(sketchView);}
	sketchMvp = sketchProj * sketchModel * sketchView;
	// sound
	float * value = ofSoundGetSpectrum(bandNum);
	for (int i = 0; i < bandNum; i++) {
		fftSmooth[i] *= 0.97f;
		if (fftSmooth[i] < value[i]) {
			fftSmooth[i] = value[i];
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	float t = ofGetElapsedTimef();
	
	if (allocateFbo) {
		texBuffer = fbo1.getTexture();
		fbo1.clear();
		fbo1.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
		camera.position.z = 0.5;
		camera.setup(vec3(0, 0, 0.5), 90.0f, 0.06f);
		camera.viewDir  = vec3(glm::cos(PI * 1.5), 0.0, glm::sin(PI  * 1.5));
		camera.cameraUpdate(sketchView);
		//camera.cameraMoved = true;
		sketchMvp = sketchProj * sketchModel * sketchView;
		allocateFbo = false;
	}
	else {
		fbo1.clear();
		fbo1.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	}
	
	fbo1.begin();
	
	ofBackground(0);
	// background
	SketchShader2.begin();
	SketchShader2.setUniformMatrix4f("mvp", glm::mat4());
	SketchShader2.setUniform1f("time", t);
	SketchShader2.setUniform1f("soundVal", fftSmooth[1]);
	SketchShader2.setUniform1f("randf", ofRandom(0, 1));
	backgroundMesh.draw();
	SketchShader2.end();

	ofEnableDepthTest();
	SketchShader1.begin();
	SketchShader1.setUniform1f("time", t);
	SketchShader1.setUniformTexture("fboTex", texBuffer, 0);
	SketchShader1.setUniformMatrix4f("model", sketchModel);
	SketchShader1.setUniformMatrix4f("mvp", sketchMvp);
	SketchShader1.setUniform3f("camData.position", camera.position);
	SketchShader1.setUniform3f("camData.dir", camera.viewDir);
	for (auto s : rectBoxArr) {
		s->draw();
		
	}
	SketchShader1.end();

	
	char randChars[11];
	
	for (int i = 0; i < bandNum; i++) {
		float len1 = fftSmooth[1] * 100;
		float len2 = fftSmooth[2] * 200;
		ofSetColor(0);
		for (int j = 0; j < 11; j++) { 
			if (j == 3 || j == 7) randChars[j] = '\n';
			else randChars[j] = ofRandom(0, 255);
		}
		ofDrawBitmapString( randChars,
			ofRandom(center.x - len2, center.x + len2), ofRandom(center.y - len2, center.y + len2));
		ofSetColor(157, 45, 198);
		ofDrawBitmapString( randChars,
			ofRandom(center.x - len1, center.x + len1), ofRandom(center.y - len1, center.y + len1));
	}
	
	fbo1.end();
	fbo1.draw(0, 0);
	
	ofDisableDepthTest();
	texBuffer.draw(0, 0, 100, 100);
	ofDrawBitmapString("current fbo", 5, 15);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case 'm':
		manualFbo = true;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
	case 'm':
		manualFbo = false;
		break;
	case 'p':
		track.play();
		break;
	}
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
