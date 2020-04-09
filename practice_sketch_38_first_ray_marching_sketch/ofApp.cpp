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
	
	dispMode = 0;

	coef.setName("disp. coefs");
	coef.add(xcof.set("x coef", 3.0, -7.0, 7.0));
	coef.add(ycof.set("y coef", 3.0, -7.0, 7.0));
	coef.add(zcof.set("z coef", 3.0, -7.0, 7.0));

	misc.setName("misc.");
	misc.add(smoothUnion.set("smooth union", 0.5, 0.0, 2.0));
	gui.setup(coef);
	gui.add(smoothUnion);
}

//--------------------------------------------------------------
void ofApp::update(){

	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();
	QuadShader.begin();
	QuadShader.setUniformMatrix4f("mvp", glm::mat4());
	QuadShader.setUniform1f("time", ofGetElapsedTimef());
	QuadShader.setUniform1f("cx", xcof);
	QuadShader.setUniform1f("cy", ycof);
	QuadShader.setUniform1f("cz", zcof);
	QuadShader.setUniform1f("smoothUnion", smoothUnion);
	QuadShader.setUniform1i("dispMode", dispMode);
	
	quad.draw();
	QuadShader.end();
	
	ofDisableDepthTest();
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'm':
		dispMode = (++dispMode) % 2;
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
