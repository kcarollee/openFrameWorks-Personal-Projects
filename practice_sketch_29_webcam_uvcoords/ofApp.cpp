#include "ofApp.h"


void buildQuadMesh(ofMesh& mesh, float w, float h, glm::vec3 pos)
{
	float verts[] = { -w + pos.x, -h + pos.y,  pos.z,
		-w + pos.x,  h + pos.y,  pos.z,
		w + pos.x,  h + pos.y,  pos.z,
		w + pos.x, -h + pos.y,  pos.z };

	float uvs[] = { 0,0, 0,1, 1,1, 1,0 };

	for (int i = 0; i < 4; ++i) {
		int idx = i * 3;
		int uvIdx = i * 2;

		mesh.addVertex(glm::vec3(verts[idx], verts[idx + 1], verts[idx + 2]));
		mesh.addTexCoord(glm::vec2(uvs[uvIdx], uvs[uvIdx + 1]));
	}

	ofIndexType indices[6] = { 0,1,2,2,3,0 };
	mesh.addIndices(indices, 6);
}
//--------------------------------------------------------------
void ofApp::setup(){
	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	ofDisableArbTex();
	ofEnableDepthTest();

	planeMesh.setup(0.8, 0.8, 100, 100, glm::vec3(0));
	planeMesh.buildPlaneMesh();

	webcamShader.load("webcam.vert", "webcam.frag");
	webcam.setVerbose(true);
	webcam.setup(ofGetHeight(), ofGetWidth());
	
	webcamFeed = webcam.getPixels();
	webcamFeed.resize(planeMesh.wnum, planeMesh.hnum);
	
	testImage.load("test.jpg");
	
	buildQuadMesh(webcamQuadMesh, 1.0, 1.0, glm::vec3(0.0));
	
	
	//planeMesh.addColor(webcamFeed);
	planeMesh.setMode(OF_PRIMITIVE_POINTS);
	
	glLineWidth(3);
	glPointSize(1.2);
	
	ofBackground(0);
	
	cameraMoveForward = cameraMoveBackward = false;
	cameraRotateCCW = cameraRotateCW = false;
	cameraRotateLeft = cameraRotateRight = false;
	cameraRotateUp = cameraRotateDown = false;

	fboMode = false;

	using namespace glm;
	camera.position = vec3(0, 0, 1.0);
	camera.fov = radians(90.0);
	camera.rotateDeg = 0.0f;
	camera.rotateDegHori = 0.0f;
	view = inverse(translate(camera.position));
	float aspect = ofGetWidth() / ofGetHeight();
	proj = perspective(camera.fov, aspect, 0.01f, 4.5f);
	mvp = proj * view * model;

	visibleWallNum = 4;
}

//--------------------------------------------------------------
void ofApp::update(){
	webcam.update();
	
	webcamFeed = webcam.getPixels();
	webcamFeed.resize(planeMesh.wnum, planeMesh.hnum);
	
	//planeMesh.setColor(webcamFeed);

	using namespace glm;
	if (cameraMoveForward) camera.position.z -= 0.025;
	else if (cameraMoveBackward) camera.position.z += 0.025;
	
	if (cameraRotateLeft) camera.rotateDegHori += 0.02;
	else if (cameraRotateRight) camera.rotateDegHori -= 0.02;


	if (cameraRotateCW) camera.rotateDeg += 0.01;
	else if (cameraRotateCCW) camera.rotateDeg -= 0.01;

	if (cameraRotateUp) camera.rotateDegVert += 0.02;
	else if (cameraRotateDown) camera.rotateDegVert -= 0.02;
	
	view = inverse(translate(camera.position) * 
		rotate(camera.rotateDegHori, vec3(0, 1, 0)) * 
		rotate(camera.rotateDeg, vec3(0, 0, 1)) * 
		rotate(camera.rotateDegVert, vec3(1, 0, 0)));
	
	mvp = proj * view * model;
	switch ((int) (camera.position.z / 2.0) % 3) {
	case -2: planeMesh.setMode(OF_PRIMITIVE_LINES);
		break;
	case -1: planeMesh.setMode(OF_PRIMITIVE_POINTS);
		break;
	case 0: planeMesh.setMode(OF_PRIMITIVE_TRIANGLES);
		break;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	fbo.begin();
	using namespace glm;
	webcamShader.begin();
	webcamShader.setUniformTexture("webcamFeed", webcamFeed, 0);
	webcamShader.setUniform1f("time", ofGetElapsedTimef());
	
	webcamShader.setUniformMatrix4f("model", model);

	
	for (int i = 0; i < 3; i++) {
		model = translate(vec3(-planeMesh.w / 2.0, -planeMesh.h / 2.0, 4.0 * ceil((camera.position.z / 4.0 - i)))) *
			rotate(0.0f, vec3(1, 1, 0)) *
			scale(vec3(1.0));
		mvp = proj * view * model;
		webcamShader.setUniformMatrix4f("mvp", mvp);
		webcamShader.setUniform1i("fragMode", 0);
		planeMesh.draw();
	}
	//float floorn = 6.0 * (ofGetElapsedTimef() / 8.0 - floor(ofGetElapsedTimef() / 8.0)) - 3.0;
	float time = ofGetElapsedTimef() / 2.0f;
	for (int i = 0; i < visibleWallNum; i++) {
		// left side
		model = translate(vec3(-0.7, sin(time + i), ceil(camera.position.z - i - 1.0))) *
			rotate(radians(90.0f), vec3(0, 1, 0)) *
			scale(vec3(0.5));
		mvp = proj * view * model;
		webcamShader.setUniform1i("fragMode", 1);
		webcamShader.setUniformMatrix4f("mvp", mvp);
		webcamQuadMesh.draw();
		// right side
		model = translate(vec3(0.7, -sin(time + i), ceil(camera.position.z - i - 1.0))) *
			rotate(radians(-90.0f), vec3(0, 1, 0)) *
			scale(vec3(0.5));
		mvp = proj * view * model;
		webcamShader.setUniform1i("fragMode", 1);
		webcamShader.setUniformMatrix4f("mvp", mvp);
		webcamQuadMesh.draw();
		// floor
		model = translate(vec3(-sin(time + i), -0.7, ceil(camera.position.z - i - 1.0))) *
			rotate(radians(90.0f), vec3(1, 0, 0)) *
			scale(vec3(0.5));
		mvp = proj * view * model;
		webcamShader.setUniform1i("fragMode", 2);
		webcamShader.setUniformMatrix4f("mvp", mvp);
		webcamQuadMesh.draw();
		//ceiling
		model = translate(vec3(sin(time + i), 0.7, ceil(camera.position.z - i - 1.0))) *
			rotate(radians(-90.0f), vec3(1, 0, 0)) *
			scale(vec3(0.5));
		mvp = proj * view * model;
		webcamShader.setUniform1i("fragMode", 2);
		webcamShader.setUniformMatrix4f("mvp", mvp);
		webcamQuadMesh.draw();
	}
	webcamShader.end();
	fbo.end();
	fbo.draw(0, 0);
	fbo.clear();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case OF_KEY_UP:
		cameraMoveForward = true;
		//cout << camera.position.z << endl;
		break;
	case OF_KEY_DOWN:
		cameraMoveBackward = true;
		break;
	case OF_KEY_RIGHT:
		cameraRotateCW = true;
		//cout << camera.rotateDeg << endl;
		break;
	case OF_KEY_LEFT:
		cameraRotateCCW = true;
		break;
	case 'a':
		cameraRotateLeft = true;
		break;
	case 'd':
		cameraRotateRight = true;
		break;
	case 'w':
		cameraRotateUp = true;
		break;
	case's':
		cameraRotateDown = true;
		break;
	case 'f':
		fboMode = !fboMode;
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key) {
	case OF_KEY_UP:
		cameraMoveForward = false;
		break;
	case OF_KEY_DOWN:
		cameraMoveBackward = false;
		break;
	case OF_KEY_RIGHT:
		cameraRotateCW = false;
		break;
	case OF_KEY_LEFT:
		cameraRotateCCW = false;
		break;
	case 'a':
		cameraRotateLeft = false;
		break;
	case 'd':
		cameraRotateRight = false;
		break;
	case 'w':
		cameraRotateUp = false;
		break;
	case's':
		cameraRotateDown = false;
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
