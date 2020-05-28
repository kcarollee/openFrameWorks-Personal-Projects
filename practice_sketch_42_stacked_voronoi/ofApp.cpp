#include "ofApp.h"

// things to setup: seedArr's array size, colorArr's array size, and num
// also set seeds and colors uniform arrays' sizes to half of seedArr's size

void printSeeds(float* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << *(arr + i) << endl;
	}
}
void buildQuadMesh(ofMesh& mesh, glm::vec3 pos, float width, float height) {
	float uvcoords[8] = { 0, 1, 1, 1, 0, 0, 1, 0 };
	ofIndexType indices[6] = { 0, 1, 3, 3, 2, 0 };
	mesh.addVertex(glm::vec3(pos.x - width * 0.5, pos.y + height * 0.5, pos.z));
	mesh.addVertex(glm::vec3(pos.x + width * 0.5, pos.y + height * 0.5, pos.z));
	mesh.addVertex(glm::vec3(pos.x - width * 0.5, pos.y - height * 0.5, pos.z));
	mesh.addVertex(glm::vec3(pos.x + width * 0.5, pos.y - height * 0.5, pos.z));
	for (int i = 0; i < 4; i++) {
		mesh.addTexCoord(glm::vec2(uvcoords[i * 2], uvcoords[i * 2 + 1]));
	}
	mesh.addIndices(indices, 6);
}

void ofApp::manageShader(glm::mat4 mvp, int sourceNum,
	int textureIndex, float* seedArr, ofTexture& tex, int translateMode, ofMesh* mesh) {
	shader.begin();
	shader.setUniformMatrix4f("mvp", mvp);
	shader.setUniform1i("seedNum", seedNum);
	shader.setUniform1i("sourceNum", sourceNum);
	shader.setUniform1i("discardMode", discardMode);
	shader.setUniform1i("greyScaleMode", greyScaleMode);
	shader.setUniform1i("textureIndex", textureIndex);
	shader.setUniform1fv("greyScaleVal", colorArr, seedNum);
	shader.setUniform1f("time", ofGetElapsedTimef() * 0.5);
	shader.setUniform2fv("seeds", seedArr, seedNum);
	shader.setUniform3f("shapeCenter", shapeCenter);
	shader.setUniformTexture("tex", tex, 0);
	shader.setUniform1i("translateMode", translateMode);
	mesh->draw();
	shader.end();
}

void ofApp::updateSeeds() {
	float time = ofGetElapsedTimef() * 0.25;
	float piDiv = TWO_PI / (float) seedNum;
	float radius = 0.75;
	for (int i = 0; i < seedNum; i++) {
		if (i == 0) {
			// front layer seeds
			*(seedArrArr[0] + 2 * i) = 2.0f * (float)ofGetMouseX() / (float)ofGetWindowWidth() - 1.0f;
			*(seedArrArr[0] + 2 * i + 1) = (float)ofGetMouseY() / (float)ofGetWindowHeight();
		}
		else {
			// front layer seeds
			*(seedArrArr[0] + 2 * i) = 0.5 + radius * ofNoise(time * velXFront[i] + i % 2) * cos(piDiv * i + time);
			*(seedArrArr[0] + 2 * i + 1) = 0.5 + radius * ofNoise(time * velYFront[i] + i % 2) * sin(piDiv * i + time);
		}
		// back layer seeds
		*(seedArrArr[layerNum - 1] + 2 * i) = 0.5 + radius * ofNoise(time  * velYBack[i] + i) * sin(piDiv * i + time);
		*(seedArrArr[layerNum - 1] + 2 * i + 1) = 0.5 + radius * ofNoise(time * velXBack[i] + i) * cos(piDiv * i + time);
	}
	// layers between front & back layers
	float zFront = quadMeshArr[0]->getVertex(0).z;
	float zBack = quadMeshArr[quadMeshArr.size() - 1]->getVertex(0).z;
	for (int i = 1; i < layerNum - 1; i++) {
		float zCurrent = quadMeshArr[i]->getVertex(0).z;
		for (int j = 0; j < seedNum; j++) {
			// x = (x2 - x1) (z - z1) / (z2 - z1) + x1
			*(seedArrArr[i] + 2 * j) = (zCurrent - zFront) *
				(*(seedArrArr[layerNum - 1] + 2 * j) - *(seedArrArr[0] + 2 * j)) / (zBack - zFront) + *(seedArrArr[0] + 2 * j);
			// y = (y2 - y1) (z - z1) / (z2 - z1) + y1
			*(seedArrArr[i] + 2 * j + 1) = (zCurrent - zFront) *
				(*(seedArrArr[layerNum - 1] + 2 * j + 1) - *(seedArrArr[0] + 2 * j + 1)) / (zBack - zFront) + *(seedArrArr[0] + 2 * j + 1);
			// cout << i << ": " << *(seedArrArr[i] + 2 * j) << " " << *(seedArrArr[i] + 2 * j + 1) << endl;
		}
	}
}
//--------------------------------------------------------------
void ofApp::setup(){
	ofDisableArbTex();
	// load shaders
	shader.load("TestShader.vert", "TestShader.frag");

	seedNum = 15; // half of seedArr's size. keep it less than 15 for now
	layerNum = 40;

	// load images
	for (int i = 0; i < seedNum; i++) {
		ofImage* img = new ofImage;
		img->load("./images/test" + to_string(i) + ".png");
		//img->resize(ofGetWindowWidth(), ofGetWindowHeight());
		imgArr.push_back(img);
	}

	// load videos
	for (int i = 0; i < seedNum; i++) {
		string videoName;
		videoName = "./videoclips/video" + to_string(i) + ".mov";
		ofxHapPlayer* v = new ofxHapPlayer;
		v->load(videoName);
		videoArr.push_back(v);
		videoArr[i]->play();
	}

	// init random seeds(points)
	greyDiv = 1.0 / (float)seedNum;
	for (int i = 0; i < seedNum; i++) {	
		*(seedArr + 2 * i) = ofRandom(0, 1);
		*(seedArr + 2 * i + 1) = ofRandom(0, 1);
		*(colorArr + i) = greyDiv * i;
	}

	// init velocity
	for (int i = 0; i < seedNum; i++) {
		velXFront.push_back(ofRandom(0.1, 0.9));
		velXBack.push_back(ofRandom(0.1, 0.9));
		velYFront.push_back(ofRandom(0.1, 0.9));
		velYBack.push_back(ofRandom(0.1, 0.9));
	}

	// init layers
	float gap = 2.0 / (float)layerNum;
	for (int i = 0; i < layerNum; i++) {
		ofMesh* m = new ofMesh;
		buildQuadMesh(*m, glm::vec3(0, 0, 1.0 - gap * i), 2.0, 2.0);
		quadMeshArr.push_back(m);
	}
	shapeCenter = glm::vec3(0, 0, (quadMeshArr[0]->getVertex(0).z + quadMeshArr[quadMeshArr.size() - 1]->getVertex(0).z) * 0.5);

	// seeds must be updated after meshes are initialized
	updateSeeds();

	// 0: system default 1: different source
	webcam.setDeviceID(0);
	//printSeeds(seedArr, seedNum * 2);
	webcam.setup(ofGetWindowWidth(), ofGetWindowHeight());
	webcam.setVerbose(true);
	
	// cam
	camera.setup(glm::vec3(0, 0, 4.0), 95.0f, 0.06);
	//sketchProj = glm::perspective(camera.fov, (float)ofGetWindowWidth() / (float)ofGetWindowHeight(), 0.01f, 20.0f);
	sketchProj = glm::ortho(-1.33f, 1.33f, -1.0f, 1.0f, 0.0f, 10.0f);
	sketchModel = glm::mat4();
	sketchView = glm::inverse(glm::translate(camera.position));
	sketchMvp = sketchProj * sketchModel * sketchView;

	ofSetBackgroundColor(0);

	// modes
	discardMode = false;
	imageMode = true;
	webcamMode = false;
	greyScaleMode = false;
	showCubeOnly = false;
	mode = "images";

	// visible texture numbers
	visibleTextureNum = 1;
}

//--------------------------------------------------------------
void ofApp::update(){
	
	/*
	// load images
	if ((int)ofGetElapsedTimef() % 10 == 0) {
		for (int i = 0; i < seedNum; i++) {
			imgArr[i]->load("./img/test" + to_string(i) + ".jpg");
		}
	}
	*/
	// update video
	if (videoMode) {
		for (auto v : videoArr) v->update();
	}
	// update webcam frames
	if (webcamMode) {
		webcam.update();
		if (webcamFrameDeque.size() < visibleTextureNum) {
			ofImage* temp = new ofImage;
			temp->setFromPixels(webcam.getPixels());
			webcamFrameDeque.push_back(temp);
		}
		else {
			webcamFrameDeque.front()->clear();
			webcamFrameDeque.pop_front();
			ofImage* temp = new ofImage;
			temp->setFromPixels(webcam.getPixels());
			webcamFrameDeque.push_back(temp);
		}
	}

	if (camera.cameraMoved) {
		camera.cameraUpdate(sketchView);
		sketchMvp = sketchProj * sketchModel * sketchView;
	}

	updateSeeds();
}


//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();
	// image mode
	int translateMode;
	showCubeOnly ? translateMode = 2 : translateMode = 0;
	if (imageMode) {
		for (int h = 0; h < layerNum; h++) {
			for (int i = 0; i < visibleTextureNum; i++) {
				manageShader(sketchMvp, imgArr.size(), i, seedArrArr[h], imgArr[visibleTextureNum - 1 - i]->getTexture(), translateMode, quadMeshArr[h]);
			}
		}
		if (!showCubeOnly) {
			// mouse interaction -> front layer, not affected by camera
			for (int i = 0; i < visibleTextureNum; i++) {
				manageShader(glm::mat4(), imgArr.size(), i, seedArrArr[0], imgArr[visibleTextureNum - 1 - i]->getTexture(), 1, quadMeshArr[0]);
			}
		}
	}
	else if (videoMode) {
		for (int h = 0; h < layerNum; h++) {
			for (int i = 0; i < visibleTextureNum; i++) {
				manageShader(sketchMvp, videoArr.size(), i, seedArrArr[h], *videoArr[visibleTextureNum - 1 - i]->getTexture(), translateMode, quadMeshArr[h]);
			}
		}
		if (!showCubeOnly) {
			// mouse interaction -> front layer, not affected by camera
			for (int i = 0; i < visibleTextureNum; i++) {
				manageShader(glm::mat4(), imgArr.size(), i, seedArrArr[0], *videoArr[visibleTextureNum - 1 - i]->getTexture(), 1, quadMeshArr[0]);
			}
		}
	}
	// webcamMode
	else if (webcamMode) {
		int index;
		if (!webcamFrameDeque.empty()) {
			webcamFrameDeque.size() < visibleTextureNum ? index = webcamFrameDeque.size() : index = visibleTextureNum;
			for (int h = 0; h < layerNum; h++) {
				for (int i = 0; i < index; i++) {
					manageShader(sketchMvp, webcamFrameDeque.size(), i, seedArrArr[h], webcamFrameDeque[i]->getTexture(), translateMode, quadMeshArr[h]);
				}
			}
			if (!showCubeOnly) {
				// mouse interaction -> front layer, not affected by camera
				for (int i = 0; i < index; i++) {
					manageShader(glm::mat4(), webcamFrameDeque.size(), i, seedArrArr[0], webcamFrameDeque[i]->getTexture(), 1, quadMeshArr[0]);
				}
			}
		}
	}
	ofDisableDepthTest();
	ofDrawBitmapString("x: discard", glm::vec2(10, 15));
	ofDrawBitmapString("i: images", glm::vec2(10, 25));
	ofDrawBitmapString("v: videos", glm::vec2(10, 35));
	ofDrawBitmapString("c: webcam", glm::vec2(10, 45));
	ofDrawBitmapString("texture mode: " + mode, glm::vec2(10, 55));
	ofDrawBitmapString("# of pieces visible: "  + to_string(visibleTextureNum), glm::vec2(10, 65));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'x':
		discardMode = !discardMode;
		break;
	case 'i':
		imageMode = true;
		videoMode = false;
		webcamMode = false;
		mode = "images";
		break;
	case 'c':
		imageMode = false;
		videoMode = false;
		webcamMode = true;
		mode = "webcam";
		break;
	case 'v':
		imageMode = false;
		videoMode = true;
		webcamMode = false;
		mode = "video";
		break;
	case 'g':
		greyScaleMode = !greyScaleMode;
		if (greyScaleMode) mode = "greyscale";
		else {
			if (imageMode) mode = "images";
			else if (webcamMode) mode = "webcam";
		}
		break;
	case 'q':
		showCubeOnly = !showCubeOnly;
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

	switch (button) {
	case 0:
		if (visibleTextureNum < imgArr.size()) visibleTextureNum++;
		break;
	case 2:
		if (visibleTextureNum > 0) visibleTextureNum--;
		break;
	}
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
	sketchProj = glm::perspective(camera.fov, (float)ofGetWindowWidth() / (float)ofGetWindowHeight(), 0.01f, 20.0f);
	sketchModel = glm::mat4();
	sketchView = glm::inverse(glm::translate(camera.position));
	sketchMvp = sketchProj * sketchModel * sketchView;
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
