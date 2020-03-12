#include "ofApp.h"
void ofApp::reset() {
	for (auto p : movingPoints) delete p;
	movingPoints.clear();
	initAngle = 0;
	branchoutAngle = prevBranchoutAngle + PI * 0.5 + ofRandom(-PI / 6, PI / 6);
	prevBranchoutAngle = branchoutAngle;
	initPoint = new Point(glm::vec2(ofGetWidth() / 2, ofGetHeight() / 2), branchoutAngle,
		ofColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255)));
	movingPoints.push_back(initPoint);
	branchout = false;
}
//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();
	ofEnableDepthTest();
	
	ofBackground(0);
	fbo1.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
	fbo1.begin();
	ofClear(0,0, 0, 0);
	fbo1.end();

	fbo2.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
	fbo2.begin();
	ofClear(0, 0, 0, 0);
	fbo2.end();
	FboShader1.load("FboShader1");

	fboMesh1.setup(2.0, 2.0, 50, 50, glm::vec3(0.0));
	fboMesh1.buildPlaneMesh();
	fboProj = glm::perspective(90.0f, (float)(ofGetWidth() / ofGetHeight()), 0.01f, 10.0f);
	fboModel = glm::mat4();
	fboView =glm::inverse(glm::translate(glm::vec3(0, 0, 0.75)));
	fboMvp = fboProj * fboModel * fboView;

	initAngle = 0;
	prevBranchoutAngle = branchoutAngle = PI / 2;
	initPoint = new Point(glm::vec2(ofGetWidth() / 2, ofGetHeight() / 2), branchoutAngle,
		ofColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255)));
	movingPoints.push_back(initPoint);
	branchout = false;
	moveSpeed = 0.8;
	
}

//--------------------------------------------------------------
void ofApp::update(){
	if (branchout) {
		int curVecSize = movingPoints.size();
		ofColor randc = ofColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255));
		for (int i = 0; i < curVecSize; i++) {
			Point* newPointLeft; Point* newPointRight;
			float randf = ofRandom(4, 12);
			if (i > 2) {if ((int)randf % 4 == 0) continue;}
			newPointLeft = new Point(movingPoints[i]->pos, movingPoints[i]->branchoutAngle + PI / randf, randc );
			newPointRight = new Point(movingPoints[i]->pos, movingPoints[i]->branchoutAngle - PI / randf, randc);
			movingPoints.push_back(newPointLeft);
			movingPoints.push_back(newPointRight);		
		}
		movingPoints.erase(movingPoints.begin(), movingPoints.begin() + curVecSize);
		branchout = false;
	}

	for (auto point : movingPoints) {
		point->pos.x  +=  moveSpeed * cos(point->branchoutAngle);
		point->pos.y +=  moveSpeed * sin(point->branchoutAngle);
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(60);
	fbo1.begin(); 
	if (!movingPoints.empty()) {
		ofSetColor(movingPoints[0]->color);
		for (auto point : movingPoints) {
			ofDrawLine(point->initPos, point->pos);

		}
	}
	fbo1.end();
	/*
	FboShader1.begin();
	FboShader1.setUniformTexture("fboTex", fbo1.getTextureReference(0), 0);
	FboShader1.setUniformMatrix4f("mvp", fboMvp);
	fboMesh1.draw();
	FboShader1.end();
	

	fbo1.clear();
	
	fbo1.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
	fbo1.begin();
	ofClear(0, 0, 0, 0);
	fbo1.end();
	*/
	fbo2.begin();
	fbo1.draw(0, 0);
	fbo2.end();

	

	FboShader1.begin();
	FboShader1.setUniformTexture("fboTex", fbo2.getTextureReference(0), 0);
	FboShader1.setUniformMatrix4f("mvp", fboMvp);
	FboShader1.setUniform1f("time", ofGetElapsedTimef());
	FboShader1.setUniform1i("mode", (int) (ofGetElapsedTimef() * 2));
	fboMesh1.draw();
	FboShader1.end();


	fbo2.clear();
	fbo2.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
	fbo2.begin();
	ofClear(0, 0, 0, 0);
	fbo2.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'b':
		branchout = true;
		
		break;
	case 's':
		reset();
		break;
	case 'r':
		fbo1.clear();
		fbo1.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
		fbo1.begin();
		ofClear(0, 0, 0, 0);
		fbo1.end();
		reset();
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
