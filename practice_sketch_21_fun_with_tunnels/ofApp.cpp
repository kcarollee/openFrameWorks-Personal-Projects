#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	gui.setup();
	gui.add(multiplePolygonMode.set("polygons", false));
	gui.add(multipleTubeMode.set("tubes", false));
	gui.add(singleTubeMode.set("single tube", true));
	gui.add(rotateMode.set("rotate", false));
	gui.add(tubeHeigtChangeMode.set("height change", false));
	gui.add(autoTwistMode.set("auto twist", false));
	gui.add(vertNum.set("vertices #", 5, 3, 15));
	gui.add(twist.set("twist by", 0, 0, PI));
	
	
	//setup(radius, vertexNum, startingDeg, zPos, meshHeight, layerNum);
	for (int i = 0; i < 100; i++) {
		Shape* s = new Shape();
		s->setup(50, 4, i, i * 25, 20, 4);
		shapeArr.push_back(s);
	}
	
	singleTube = new SingleTube();
	singleTube->setup(10, 8, 500, 0, 10, 1000);

	
	camera.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 500);
	camera.lookAt(ofVec3f(camera.getPosition().x, camera.getPosition().y, camera.getPosition().z - 1));

	camera2.setPosition(camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
	camera2.lookAt(ofVec3f(camera.getPosition().x, camera.getPosition().y, camera.getPosition().z - 1));

	rotateDeg = 0;	
}

//--------------------------------------------------------------
void ofApp::update(){
	
	rotateDeg += 0.1;
	for (auto s : shapeArr) {
		s->resetVertexNum(vertNum);
	}		
	singleTube->resetVertexNum(vertNum);
	if (rotateMode) singleTube->rotate(rotateDeg);
	if (tubeHeigtChangeMode) singleTube->resetTubeHeight(10 + 5 * sin(ofGetElapsedTimef() / 10));
	if (autoTwistMode) {
		twistf = 0.05 * sin(ofGetElapsedTimef() / 2);
		singleTube->twistTube(twistf);
	}
	else singleTube->twistTube(twist);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(75, 0, 130);
	if (easyCamMode) camera2.begin();
	else camera.begin();
	if (multipleTubeMode) {
		for (int i = 0; i < shapeArr.size(); i++) {
			shapeArr[i]->drawTubeMesh();
			if (rotateMode) shapeArr[i]->rotate(rotateDeg  * (i + 1) / 100);
			if (tubeHeigtChangeMode) shapeArr[i]->resetTubeHeight(50 * sin(ofGetElapsedTimef() * 2));
		}
	}

	else if (singleTubeMode) {
		singleTube->drawSingleTubeMesh();
		//singleTube->singleTubeCustomMovement();
		if (rotateMode) singleTube->rotate(rotateDeg);
		if (tubeHeigtChangeMode) singleTube->resetTubeHeight(10 + 5 * sin(ofGetElapsedTimef() / 10));
		if (autoTwistMode) singleTube->twistTube(twistf);
	}

	else if (multiplePolygonMode) {
		for (int i = 0; i < shapeArr.size(); i++) {
			shapeArr[i]->drawSingleShape();
			if (rotateMode) shapeArr[i]->rotate(rotateDeg  * (i + 1) / 100);
		}
	}
	
	if (easyCamMode) camera2.end();
	else camera.end();

	gui.draw();	
}

void ofApp::setCameraPos(float zPos) {
	camera.setPosition(camera.getPosition().x, camera.getPosition().y, zPos);
	camera.lookAt(ofVec3f(camera.getPosition().x, camera.getPosition().y, zPos - 1));

	camera2.setPosition(camera.getPosition().x, camera.getPosition().y, zPos);
	camera2.lookAt(ofVec3f(camera.getPosition().x, camera.getPosition().y, zPos - 1));
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'w':
		// if camera is below the last shape (the furthest one)
		if (camera.getPosition().z <= 0) {			
			if (multiplePolygonMode || multipleTubeMode) setCameraPos(shapeArr[shapeArr.size() - 1]->zPos + 100);			
			else if (singleTubeMode) setCameraPos(singleTube->totalHeight + 100);		
		}
		else setCameraPos(camera.getPosition().z - 5);			
		
		break;
	case 's':
		setCameraPos(camera.getPosition().z + 5);	
		break;
	case 'c':
		easyCamMode = !easyCamMode;
		camera2.setPosition(camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
		camera2.lookAt(ofVec3f(camera.getPosition().x, camera.getPosition().y, camera.getPosition().z - 1));
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
