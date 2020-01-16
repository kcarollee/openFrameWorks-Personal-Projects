#include "ofApp.h"

void buildQuadCube(ofMesh& mesh, float w, float h, float d, glm::vec3 pos) {
	float vertices[] = {
		pos.x + w / 2.0, pos.y + h / 2.0, pos.z + d / 2.0,
		pos.x - w / 2.0, pos.y + h / 2.0, pos.z + d / 2.0,
		pos.x - w / 2.0, pos.y - h / 2.0, pos.z + d / 2.0,
		pos.x + w / 2.0, pos.y - h / 2.0, pos.z + d / 2.0,

		pos.x + w / 2.0, pos.y + h / 2.0, pos.z - d / 2.0,
		pos.x - w / 2.0, pos.y + h / 2.0, pos.z - d / 2.0,
		pos.x - w / 2.0, pos.y - h / 2.0, pos.z - d / 2.0,
		pos.x + w / 2.0, pos.y - h / 2.0, pos.z - d / 2.0		
	};
	float uvcoords[] = { 0, 0, 1, 0, 1, 1, 0, 1 };
	for (int i = 0; i < 8; i++) {
		mesh.addVertex(glm::vec3(vertices[i*3], vertices[i*3+1], vertices[i*3+2]));
		mesh.addTexCoord(glm::vec2(uvcoords[i*2], uvcoords[i*2+1]));
	}
	
	ofIndexType indices[36] = {
		0,1,2,2,3,0,
		1,2,6,6,5,1,
		5,6,7,7,4,5,
		3,7,4,4,0,3,
		2,6,7,7,3,2,
		0,4,5,5,1,0
	};
	mesh.addIndices(indices, 36);
}

//--------------------------------------------------------------
void ofApp::setup(){
	gui.setup();
	gui.add(enableDepthTest.set("depth test", false));
	gui.add(rcThreshold.set("rc threshold", 1.0, 0.0, 1.0));
	
	ofDisableArbTex();
	ofDisableAlphaBlending();
	ofEnableDepthTest();
	shader.load("shader1.vert", "shader1.frag");
	

	cube.setup(glm::vec3(0, 0, 0), 0.6, 0.6, 0.6);
	buildQuadCube(mesh, 0.6, 0.6, 0.6, glm::vec3(0, 0, 0));
}

//--------------------------------------------------------------
void ofApp::update(){
	if (!enableDepthTest) ofDisableDepthTest();
	else ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(255);
	
	
	shader.begin();
	shader.setUniform1f("time", ofGetElapsedTimef());
	shader.setUniform1f("rcThreshold", rcThreshold);
	shader.setUniform3f("translate", glm::vec3(0.5, 0, 0));
	
	mesh.draw();
	
	shader.setUniform3f("translate", glm::vec3(-0.5, 0, 0));
	cube.draw();
	
	shader.end();


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
