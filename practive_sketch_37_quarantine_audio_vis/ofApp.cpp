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
void ofApp::setup(){
	ofEnableDepthTest();
	ofDisableArbTex();

	WallShader.load("WallShader");
	ofSetBackgroundColor(0);
	int imgNum = 30;
	for (int i = 0; i < imgNum; i++) {
		ofImage* img = new ofImage;
		img->load("charImages/q" + to_string(i + 1) + ".png");
		textureImgArr.push_back(img);
	}

	shapeNum = 20;
	sideFaceNum = 20;
	initRadius = 0.03;
	moveMode = 0;
	modeState = "movement: STOP";
	for (int i = 0; i < shapeNum; i++) {
		CShape* c = new CShape(sideFaceNum, glm::vec3(0, 0.1 - i * 0.01, 0), initRadius, 0.01, 0.01);
		shapeArr.push_back(c);
	}
	// cam
	camera.setup(glm::vec3(0, 0, 0), 90.0f, 0.0075);
	sketchProj = glm::perspective(camera.fov, (float)(ofGetWidth() / ofGetHeight()), 0.01f, 20.0f);
	sketchModel = glm::mat4();
	sketchView = glm::inverse(glm::translate(camera.position));
	sketchMvp = sketchProj * sketchModel * sketchView;

	// audio
	track.load("track.mp3");
	bandNum = shapeNum;
	fftSmooth = new float[bandNum];
	for (int i = 0; i < bandNum; i++) {
		fftSmooth[i] = 0;
	}
	audioVisMode = false;
	audioVisState = "audio-vis: OFF";
	// fbo
	FboShader.load("FboShader");
	buildQuadMesh(fboMesh, glm::vec3(-1.0, 1.0, 0), 2.0, 2.0);
	fbo.allocate(ofGetWidth(), ofGetHeight());
	fbo.begin();
	ofClear(0, 0, 0, 0);
	fbo.end();

}

//--------------------------------------------------------------
void ofApp::update(){
	// sound
	if (track.isPlaying()) {
		float * value = ofSoundGetSpectrum(bandNum);
		for (int i = 0; i < bandNum; i++) {
			fftSmooth[i] *= 0.97f;

			if (fftSmooth[i] < value[i]) {
				fftSmooth[i] = value[i];
			}
		}
	}

	if (camera.cameraMoved) {
		camera.cameraUpdate(sketchView);
		sketchMvp = sketchProj * sketchModel * sketchView;
	}

	if (audioVisMode) {
		if (moveMode == 1) {
			float div = TWO_PI / shapeNum;
			for (int i = 0; i < shapeNum; i++) {
				shapeArr[i]->resetRadius(initRadius + fftSmooth[i % 4] * 0.025 + 0.01 * sin(ofGetElapsedTimef() * 4 + div * i));
			}
		}
		else if (moveMode == 2) {
			float div = TWO_PI / shapeNum;
			for (int i = 0; i < sideFaceNum; i++) {
				for (int j = 0; j < shapeNum; j++) {
					shapeArr[j]->resetQuadYpos(shapeArr[j]->initY + fftSmooth[i % 4] * 0.1 + 0.01 * sin(ofGetElapsedTimef() * 4 + div * i), i);
				}
			}
		}
		else if (moveMode == 3) {
			float div = TWO_PI / shapeNum;
			for (int i = 0; i < shapeNum; i++) {
				shapeArr[i]->resetRadius(initRadius + fftSmooth[i % 4] * 0.025 + 0.01 * sin(ofGetElapsedTimef() * 4 + div * i));
			}
			for (int i = 0; i < sideFaceNum; i++) {
				for (int j = 0; j < shapeNum; j++) {
					shapeArr[j]->resetQuadYpos(shapeArr[j]->initY + fftSmooth[i % 4] * 0.1 + 0.01 * sin(ofGetElapsedTimef() * 4 + div * i), i);
				}
			}
		}
		
	}
	else {
		if (moveMode == 1) {
			float div = TWO_PI / shapeNum;
			for (int i = 0; i < shapeNum; i++) {
				shapeArr[i]->resetRadius(0.05 + 0.01 * sin(ofGetElapsedTimef() * 4 + div * i));
			}
		}
		else if (moveMode == 2) {
			for (int i = 0; i < sideFaceNum; i++) {
				for (int j = 0; j < shapeNum; j++) {
					shapeArr[j]->resetQuadYpos(shapeArr[j]->initY + 0.05 * sin(ofGetElapsedTimef() + i), i);
				}
			}
		}
		else if (moveMode == 3) {
			float div = TWO_PI / shapeNum;
			for (int i = 0; i < shapeNum; i++) {
				shapeArr[i]->resetRadius(0.05 + 0.01 * sin(ofGetElapsedTimef() * 4 + div * i));
			}
			for (int i = 0; i < sideFaceNum; i++) {
				for (int j = 0; j < shapeNum; j++) {
					shapeArr[j]->resetQuadYpos(shapeArr[j]->initY + 0.05 * sin(ofGetElapsedTimef() + i), i);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	fbo.begin();
	WallShader.begin();
	WallShader.setUniformMatrix4f("mvp",  (sketchMvp));
	WallShader.setUniformMatrix4f("model", glm::rotate(ofGetElapsedTimef() * 0.5f, glm::vec3(0, 1, 0)));
	WallShader.setUniform1f("time", ofGetElapsedTimef());
	WallShader.setUniform1i("intTime", (int) ofGetElapsedTimef());
	WallShader.setUniform1i("moveMode", moveMode);

	int shift = (int) (ofGetElapsedTimef() * 2);
	int colqindex = 0;
	for (auto s : shapeArr) s->drawWithTexture(WallShader, textureImgArr, shift++, 10, 
		( (int)(ofGetElapsedTimef() * 10 + (colqindex++)) % sideFaceNum)); // mod = length of string
	WallShader.end();
	fbo.end();
	
	FboShader.begin();
	FboShader.setUniform1f("time", ofGetElapsedTimef());
	FboShader.setUniformMatrix4f("mvp", glm::mat4());
	FboShader.setUniformTexture("fboTex", fbo.getTexture(), 0);
	fboMesh.draw();
	FboShader.end();
	
	fbo.allocate(ofGetHeight(), ofGetWidth());
	fbo.begin();
	ofClear(0, 0, 0, 0);
	fbo.end();

	ofDisableDepthTest();
	ofSetColor(255);
	ofDrawBitmapString(modeState, 5, 15);
	ofDrawBitmapString(audioVisState, 5, 25);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'm':
		++moveMode %= 4;
		switch (moveMode) {
		case 0:
			modeState = "movement: STOP";
			break;
		case 1:
			modeState = "movement: HORI";
			break;
		case 2:
			modeState = "movement: VERT";
			break;
		case 3:
			modeState = "movement: HORI+VERT";
			break;
		}
		break;
	case 'n':
		audioVisMode = !audioVisMode;
		if (audioVisMode) audioVisState = "audio-vis: ON";
		else audioVisState = "audio-vis: OFF";
		break;
	case 'p':
		track.play();
		audioVisState = "audio-vis: ON";
		audioVisMode = true;
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
