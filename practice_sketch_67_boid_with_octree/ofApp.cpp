#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();
	ofEnableDepthTest();
	testPoint.set(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.5, 0);
	pointCloud = new ofMesh;
	pointCloud->addVertex(testPoint);
	pointCloud->addColor(ofColor(255, 0, 0));
	pointCloud->addIndex(0);
	pointCloud->setMode(ofPrimitiveMode::OF_PRIMITIVE_POINTS);
	
	
	

	cam.setPosition(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.5, 1000);
	
	//ofSetBackgroundColor(0);


	gui.setup();
	gui.add(alignCoef.set("alignCoef", 1.0, 0, 100.0));
	gui.add(cohesionCoef.set("cohesionCoef", 1.0, 0, 100));
	gui.add(separationCoef.set("separationCoef", 1.0, 0.0, 100.0));
	gui.add(boidSpeed.set("boidSpeed", 5.0, 0.0, 10.0));
	gui.add(pointSize.set("pointSize", 1.0, 0.0, 4.0));
	testOctree = new Octree(glm::vec3(-300, -300, -300), glm::vec3(300, 300, 300));
	testOctree->accuracy = octreeAccuracy;
	for (int i = 0; i < 1; i++) {
		Flock* tf = new Flock(15000);
		for (auto p : tf->particleArr) {
			testOctree->insert(p);
			p->setCoefs(alignCoef, cohesionCoef, separationCoef);
		}
		flockArr.push_back(tf);
	}

	ofEnableSmoothing();

	zpos = -300;

	backBuffer.allocate(ofGetWindowWidth(), ofGetWindowHeight());
	backBuffer.begin();
	ofClear(0, 0, 0, 0);
	backBuffer.end();

	currentBuffer.allocate(ofGetWindowWidth(), ofGetWindowHeight());
	currentBuffer.begin();
	ofClear(0, 0, 0, 0);
	currentBuffer.end();

	midBuffer.allocate(ofGetWindowWidth(), ofGetWindowHeight());
	midBuffer.begin();
	ofClear(0, 0, 0, 0);
	midBuffer.end();

	shader.load("shader1");

	

	testOctree->drawMode = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	for (auto f : flockArr) {
		f->update();
		for (auto p : f->particleArr) p->maxSpeed = boidSpeed;
	}
	
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	glPointSize(pointSize);
	
	//cam.begin();
	//currentBuffer.clear();
	currentBuffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	currentBuffer.begin();
	//ofEnableDepthTest();
	ofPushMatrix();
	ofTranslate(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.5, zpos);
	ofRotateX(rotateDegX);
	ofRotateY(rotateDegY);

	testOctree->reset(testOctree);
	
	testOctree = new Octree(glm::vec3(-300, -300, -300), glm::vec3(300, 300, 300));
	
	ofNoFill();
	ofSetColor(255, 50);
	for (int i = 0; i < 1; i++) {
		for (auto p : flockArr[i]->particleArr) testOctree->insert(p);
	}
	

	testOctree->display();
	

	for (auto f : flockArr) {
		f->display();
		
		for (auto p : f->particleArr) {
			p->setCoefs(alignCoef, cohesionCoef, separationCoef);
		}
		
	}
	
	
	float dim = 600;
	ofNoFill();
	ofSetColor(255, 60);
	ofDrawBox(0, 0, 0, dim, dim, dim);
	ofPopMatrix();
	//ofDrawSphere(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.5, dim * 0.5);
	//cam.end();

	ofDisableDepthTest();
	currentBuffer.end();

	midBuffer.clear();
	midBuffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	midBuffer.begin();
	shader.begin();
	shader.setUniform2f("resolution", glm::vec2(ofGetWidth(), ofGetHeight()));
	shader.setUniformTexture("currentBuffer", currentBuffer.getTexture(), 0);
	shader.setUniformTexture("backBuffer", backBuffer.getTexture(), 1);
	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	shader.end();
	midBuffer.end();

	backBuffer.clear();
	backBuffer.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	backBuffer.begin();
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5, 0);
	ofRotateX(180);
	midBuffer.draw(ofGetWidth() * -0.5, ofGetHeight() * -0.5);
	backBuffer.end();

	midBuffer.draw(0, 0);
	
	gui.draw();
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case ' ':
		for (auto f : flockArr) {
			for (auto p : f->particleArr) {
				int d = 50;
				glm::vec3 randomForce = glm::vec3(ofRandom(-d, d), ofRandom(-d, d), ofRandom(-d, d));
				p->applyRandomForce(randomForce);
			}
		}
		break;
	case 'w': 
		zpos += 50;
		break;
	case 's':
		zpos -= 50;
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
	rotateDegX = rotateDegXPrev + ofGetMouseY() - mousePressedPoint.y;
	rotateDegY = rotateDegYPrev + ofGetMouseX() - mousePressedPoint.x;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	mousePressedPoint = glm::vec2(ofGetMouseX(), ofGetMouseY());
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	mouseReleasedPoint = glm::vec2(ofGetMouseX(), ofGetMouseY());
	rotateDegXPrev = rotateDegX;
	rotateDegYPrev = rotateDegY;
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
