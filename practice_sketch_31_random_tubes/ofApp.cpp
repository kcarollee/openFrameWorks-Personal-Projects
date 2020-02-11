#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	using namespace glm;
	ofDisableArbTex();
	ofEnableDepthTest();
	polyShader.load("shader.vert", "shader.frag");	
	camera.position = vec3(0, 0, 4.0);
	camera.fov = radians(90.0);
	camera.rotateDeg = 0.0f;
	camera.rotateDeg = camera.rotateDegVert = camera.rotateDegHori = 0.0f;
	camera.forward = camera.backward = camera.rotateDown = camera.rotateUp = camera.rotateRight = camera.rotateLeft = false;
	model = translate(vec3(0.0f)) *
		rotate(radians(0.0f), vec3(0, 1, 0)) *
		scale(vec3(1.0));
	view = inverse(translate(camera.position));
	proj = perspective(camera.fov,((float)ofGetWidth() / (float)ofGetHeight()), 0.01f, 10.0f);
	mvp = proj * view * model;
	glPointSize(4);
	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){
	if (camera.forward) {
		camera.position.z -= 0.01;
		view = inverse(translate(camera.position));
	}
	else if (camera.backward) {
		camera.position.z += 0.01;
		view = inverse(translate(camera.position));
	}
	if (camera.rotateLeft) camera.rotateDegHori += 0.02;
	else if (camera.rotateRight) camera.rotateDegHori -= 0.02;
	if (camera.rotateUp) camera.rotateDegVert += 0.02;
	else if (camera.rotateDown) camera.rotateDegVert -= 0.02;
	view = inverse(rotate(camera.rotateDegHori, vec3(0, 1, 0)) *
		rotate(camera.rotateDegVert, vec3(1, 0, 0)) *
		translate(camera.position));
	mvp = proj * view * model;
}

//--------------------------------------------------------------
void ofApp::draw(){
	polyShader.begin();
	model = translate(vec3(0.0f)) *
		rotate(radians(0.0f), vec3(0, 1, 0)) *
		scale(vec3(1.0));

	polyShader.setUniformMatrix4f("mvp", mvp);
	polyShader.setUniform3f("campos", camera.position);
	polyShader.setUniform1f("time", ofGetElapsedTimef());
	if (!customPolyArr.empty()) {
		for (auto c : customPolyArr) {
			polyShader.setUniform4f("colorOffset", c->colorOffset);
			c->draw();
			if (c->lifeSpan > ofGetElapsedTimef() - c->creationTime) {
				c->addVertices(0.7 + 0.1 *  cos(ofGetElapsedTimef()), 0.7 + 0.1 * sin(ofGetElapsedTimef()));
			}
			else c->grow = false;
			if (!c->grow) {
				c->colorOffset.a -= 0.0025;
				if (c->colorOffset.a < 0) {
					for (auto t : customPolyArr) {
						if (t->positionInDeque > c->positionInDeque) t->positionInDeque--;
					}
					customPolyArr.erase(customPolyArr.begin() + c->positionInDeque);					
				}
			}
		}
	}
	polyShader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	static int modeCount = 0;
	switch (key) {
	case 'm':
		modeCount++;
		for (auto c : customPolyArr) {
			if (modeCount % 3 == 0) c->setMode(OF_PRIMITIVE_TRIANGLES);
			else if (modeCount % 3 == 1) c->setMode(OF_PRIMITIVE_POINTS);
			else if (modeCount % 3 == 2) c->setMode(OF_PRIMITIVE_LINES);
		}
		break;	
	case 'w':
		camera.forward = true;
		break;
	case 's':
		camera.backward = true;
		break;
	case 'a':
		camera.rotateLeft = true;
		break;
	case 'd':
		camera.rotateRight = true;
		break;
	case'v':
		for (auto c : customPolyArr) c->viewNormals = !c->viewNormals;
		break;
	case 'n':
		CustomPoly* newPoly = new CustomPoly();
		newPoly->setup(16, ofRandom(0.05, 0.2), ofRandom(0.005, 0.015), 
			glm::vec3(ofRandom(-2.0, 2.0), 4.0, ofRandom(-2.0, 2.0)));
		newPoly->positionInDeque = customPolyArr.size();
		if (customPolyArr.empty()) newPoly->setMode(OF_PRIMITIVE_TRIANGLES);
		else newPoly->setMode(customPolyArr[customPolyArr.size() - 1]->getMode());
		customPolyArr.push_back(newPoly);	
		break;
	
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key) {
	case 'w':
		camera.forward = false;
		break;
	case 's':
		camera.backward = false;
		break;
	case 'a':
		camera.rotateLeft = false;
		break;
	case 'd':
		camera.rotateRight = false;
		break;
	}
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
