#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
	using namespace glm;
	ofBackground(0);
	ofDisableArbTex();
	
	planeMeshBox.setup(0.8, 0.8, 0.8, 90, 90, 90, vec3(0.0));
	planeMeshBox.buildMeshes();
	planeMeshBox.setMode(OF_PRIMITIVE_POINTS);

	webcamShader.load("webcam.vert", "webcam.frag");

	webcam.setVerbose(true);
	webcam.setup(ofGetHeight(), ofGetWidth());

	webcamFeed = webcam.getPixels();

	camera.position = vec3(0, 0, 1.25);
	camera.fov = radians(90.0);
	camera.rotateDeg = 0.0f;
	camera.rotateDeg = camera.rotateDegVert = camera.rotateDegHori = 0.0f;
	cameraMoveBackward = cameraMoveForward = cameraLookUp = 
	cameraLookDown = cameraLookLeft = cameraLookRight =  false;
	cameraMoved = false;

	model = translate(vec3(0.0f)) *
		rotate(radians(0.0f), vec3(0, 1, 0)) *
		scale(vec3(1.0));
	view = inverse(translate(camera.position));
	proj = perspective(camera.fov, (float)(ofGetWidth() / ofGetHeight()), 0.01f, 10.0f);
	mvp = proj * view * model;

	firstIter = true;

	toggleColor = 1;
	primitiveMode = 0;

	glPointSize(2);

	gui.setup();
	gui.add(popOut.set("vertex popout", 0.0, -3.0, 3.0));
	gui.add(singlePlaneMode.set("single plane", false));
}

//--------------------------------------------------------------
void ofApp::update(){
	webcam.update();
	webcamFeed = webcam.getPixels();
	webcamFeed.resize(planeMeshBox.wnum, planeMeshBox.hnum);

	if (firstIter) {
		planeMeshBox.addColor(webcamFeed);
		firstIter = false;
	}
	planeMeshBox.setColor(webcamFeed);

	if (singlePlaneMode) planeMeshBox.singlePlaneMode = true;
	else planeMeshBox.singlePlaneMode = false;

	// camera control
	if (cameraMoved) {
		if (cameraMoveForward) camera.position.z -= 0.03;
		else if (cameraMoveBackward) camera.position.z += 0.03;
		if (cameraLookUp) camera.rotateDegVert += 0.02;
		else if (cameraLookDown) camera.rotateDegVert -= 0.02;
		if (cameraLookRight) camera.rotateDegHori -= 0.02;
		else if (cameraLookLeft) camera.rotateDegHori += 0.02;	
	}
	using namespace glm;
	view = inverse(rotate(camera.rotateDegHori, vec3(0, 1, 0)) *
		rotate(camera.rotateDegVert, vec3(1, 0, 0)) *
		translate(camera.position));
}

//--------------------------------------------------------------
void ofApp::draw(){
	using namespace glm;
	ofEnableDepthTest();

	webcamShader.begin();
	webcamShader.setUniformTexture("webcamFeed", webcamFeed, 0);
	webcamShader.setUniform1f("time", ofGetElapsedTimef());
	webcamShader.setUniformMatrix4f("model", model);
	webcamShader.setUniform1i("toggleColor", toggleColor);
	webcamShader.setUniform1f("popOut", popOut);
	webcamShader.setUniformMatrix4f("mvp", mvp);

	planeMeshBox.draw(webcamShader, model, view, proj, mvp);
	webcamShader.end();

	ofDisableDepthTest();
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'o':
		toggleColor = (++toggleColor) % 2;
		break;
	case 'm':
		primitiveMode = (++primitiveMode) % 2;
		switch (primitiveMode) {
		case 0:
			planeMeshBox.setMode(OF_PRIMITIVE_POINTS);
			break;
		case 1:
			planeMeshBox.setMode(OF_PRIMITIVE_LINES);
			break;
		}
		break;
	case OF_KEY_UP:
		cameraLookUp = true;
		cameraMoved = true;
		break;
	case OF_KEY_DOWN:
		cameraLookDown = true;
		cameraMoved = true;
		break;
	case 'a':
		cameraLookLeft = true;
		cameraMoved = true;
		break;
	case 'd':
		cameraLookRight = true;
		cameraMoved = true;
		break;
	case 'w':
		cameraMoveForward = true;
		cameraMoved = true;
		break;
	case 's':
		cameraMoveBackward = true;
		cameraMoved = true;
		break;
	}
	
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key) {
	case OF_KEY_UP:
		cameraLookUp = false;
		cameraMoved = false;
		break;
	case OF_KEY_DOWN:
		cameraLookDown = false;
		cameraMoved = false;
		break;
	case 'a':
		cameraLookLeft = false;
		cameraMoved = false;
		break;
	case 'd':
		cameraLookRight = false;
		cameraMoved = false;
		break;
	case 'w':
		cameraMoveForward = false;
		cameraMoved = false;
		break;
	case 's':
		cameraMoveBackward = false;
		cameraMoved = false;
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
