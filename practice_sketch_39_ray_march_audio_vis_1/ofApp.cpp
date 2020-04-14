#include "ofApp.h"


void buildQuad(ofMesh& mesh, glm::vec3 center, float w, float h) {
	ofIndexType indices[6] = { 0, 1, 3, 3, 2, 0 };
	float texCoords[8] = { 0, 1, 1, 1, 0, 0, 1, 0 };
	mesh.addVertex(glm::vec3(center.x - w * 0.5, center.y + h * 0.5, center.z));
	mesh.addVertex(glm::vec3(center.x + w * 0.5, center.y + h * 0.5, center.z));
	mesh.addVertex(glm::vec3(center.x - w * 0.5, center.y - h * 0.5, center.z));
	mesh.addVertex(glm::vec3(center.x + w * 0.5, center.y - h * 0.5, center.z));
	for (int i = 0; i < 4; i++) {
		mesh.addTexCoord(glm::vec2(texCoords[2 * i], texCoords[2 * i + 1]));
	}
	mesh.addIndices(indices, 6);
}
//--------------------------------------------------------------
void ofApp::setup(){
	ofEnableDepthTest();
	ofDisableArbTex();
	
	buildQuad(quad, glm::vec3(0), 2.0, 2.0);
	QuadShader.load("QuadShader");
	
	gui.setup();
	gui.add(smoothUnion.set("smooth union", 0.0, 0.0, 0.5));
	gui.add(gap.set("gap", 0.5, 0.0, 1.0));
	gui.add(width.set("width", 0.05, 0.0, 0.1));

	track.load("track.mp3");
	track.play();
	bandNum = 5;
	fftSmooth = new float[bandNum];
	for (int i = 0; i < bandNum; i++) {
		fftSmooth[i] = 0;
	}
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
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();
	QuadShader.begin();
	QuadShader.setUniformMatrix4f("mvp", glm::mat4());
	QuadShader.setUniform1f("time", ofGetElapsedTimef());
	QuadShader.setUniform1f("gap", gap);
	QuadShader.setUniform1f("width", width);
	QuadShader.setUniform1f("smoothUnion", smoothUnion);
	QuadShader.setUniform1f("soundVal", fftSmooth[0]);
	quad.draw();
	QuadShader.end();
	
	ofDisableDepthTest();
	gui.draw();
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
