#include "ofApp.h"

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

void ofApp::videoShaderSetupAndDraw(int frameIndex, int mode, glm::vec2 pos, float radius, float divWidth, float divHeight) {
	VideoShader.begin();
	VideoShader.setUniformMatrix4f("mvp", glm::mat4());
	VideoShader.setUniform1i("webcamMode", webcamMode);
	VideoShader.setUniform1i("mode", mode);
	if (webcamMode) VideoShader.setUniformTexture("videoTex", webcamFrameDeque[frameIndex]->getTexture(), 0);
	else if (videoMode) VideoShader.setUniformTexture("videoTex", videoFboDeque[frameIndex]->getTexture(), 0);
	VideoShader.setUniform1f("divh", divHeight);
	VideoShader.setUniform1f("divw", divWidth);
	VideoShader.setUniform2f("rectPos", pos);
	VideoShader.setUniform1f("radius", radius);
	videoMesh.draw();
	VideoShader.end();
}
//--------------------------------------------------------------
void ofApp::setup() {
	ofDisableArbTex();
	webcam.setDeviceID(0); // 0: webcam, 2: droidcam
	webcam.setVerbose(true);
	webcam.setup(ofGetWidth(), ofGetHeight());

	dequeSize = 100;
	smallFrameSize = 50;

	viewMode = 0;
	dispMode = 0;
	randomMode = 0;
	webcamMode = true;
	videoMode = !webcamMode;

	buildQuadMesh(sketchMesh, glm::vec3(0), 2.0, 2.0);

	SketchShader.load("SketchShader");
	sketchFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
	sketchFbo.begin();
	ofClear(0, 0, 0, 0);
	sketchFbo.end();

	loadingString = "loading......";
	modeString = "current mode(m): time displacement";
	dispModeString = "displacement mode(d): linear (horizontal)";
	randomSelectionRange = 0.75;
	randString = "random frame selection(r): off (range: " + to_string(1.0 - randomSelectionRange) + ")";
	loadingFrames = true;
	
	buildQuadMesh(videoMesh, glm::vec3(0), 2.0, 2.0);
	VideoShader.load("VideoShader");

	automateModes = false;

	movie.load("movie.mov");
	movie.play();
	track.load("track.mp3");

}

//--------------------------------------------------------------
void ofApp::update() {
	if (webcamMode) {
		webcam.update();
		if (webcamFrameDeque.size() <= dequeSize) {
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

	else if (videoMode) {
		if (videoFboDeque.size() <= dequeSize) {
			ofFbo* temp = new ofFbo;
			temp->allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
			temp->begin();
			ofClear(0, 0, 0, 0);
			temp->end();
			videoFboDeque.push_back(temp);
		}
		else {
			videoFboDeque.front()->clear();
			videoFboDeque.pop_front();
			ofFbo* temp = new ofFbo;
			temp->allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
			temp->begin();
			ofClear(0, 0, 0, 0);
			temp->end();
			videoFboDeque.push_back(temp);
		}
	}

	if (automateModes) {
		dispMode = (int)ofGetElapsedTimef() % 4;
		if ((dispMode == 0 || dispMode == 1) && ((int)ofGetElapsedTimef() % 8 == 0) || (int)ofGetElapsedTimef() % 8 == 1) {
			randomMode = 1;
		}
		else randomMode = 0;

		switch (randomMode) {
		case 0:
			randString = "random frame selection(r): off (range: " + to_string(1.0 - randomSelectionRange) + ")";
			break;
		case 1:
			randString = "random frame selection(r): on (range: " + to_string(1.0 - randomSelectionRange) + ")";
			break;
		}

		switch (dispMode) {
		case 0:
			dispModeString = "displacement mode(d): linear (horizontal)";
			break;
		case 1:
			dispModeString = "displacement mode(d): linear (vertical)";
			break;
		case 2:
			dispModeString = "displacement mode(d): rectangular";
			break;
		case 3:
			dispModeString = "displacement mode(d): circular";
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {	
	ofDisableArbTex();
	// store sketch in an fbo
	sketchFbo.begin();
	switch (viewMode) {
	// sliced view
	case 0:
		if (!webcamFrameDeque.empty()) {
			if (webcamFrameDeque.size() < dequeSize) {
				webcamFrameDeque[webcamFrameDeque.size() - 1]->draw(0, 0);
			}
			else {
				loadingFrames = false;
				int divw = ofGetWidth() / dequeSize;
				int divh = ofGetHeight() / dequeSize;
				if (!randomMode) {
					//(webcamMode ? webcamFrameDeque.size() : videoFboDeque.size());
					// starting from the most recent frame
					for (int t = (webcamMode ? webcamFrameDeque.size() : videoFboDeque.size()) - 1; t >= 0; t--) {
						switch (dispMode) {
						// linear (horizontal) cross sections
						case 0:
							videoShaderSetupAndDraw(t, 0, glm::vec2(0, 1.0 - t * 1.0 / (float)(dequeSize)),
								NULL, NULL, 1.0 / (float)dequeSize);
							break;
						// linear (vertical) cross sections
						case 1:							
							videoShaderSetupAndDraw(t, 1, glm::vec2((t + 1) * 1.0 / (float)(dequeSize)),
								NULL, 1.0 / (float)dequeSize, NULL);
							break;
						// rectangular cross sections
						case 2:
							videoShaderSetupAndDraw(t, 2, glm::vec2(0.5),
								NULL, 1.0 / (float)dequeSize * (t + 1), 1.0 / (float)dequeSize * (t + 1));
							break;
						// circular cross sections
						case 3:
							videoShaderSetupAndDraw(t, 3, glm::vec2(),
								1.0 / (float)(dequeSize)* t, NULL, NULL);
							break;
						}
					}
				}
				// random frame selection(r)  mode
				else {
					int iter = 0;
					switch (dispMode) {
					// linear (horizontal) cross sections
					case 0:						
						for (int hPos = 0; hPos < webcam.getHeight(); hPos += divh) {		
							int index = (int)ofRandom((dequeSize - 1) * randomSelectionRange, dequeSize - 1);
							videoShaderSetupAndDraw(index, 0, glm::vec2(0, 1.0 - (iter++) * 1.0 / (float)(dequeSize)),
								NULL, NULL, 1.0 / (float)dequeSize);
						}
						break;
					// linear (vertical) cross sections
					case 1:					
						for (int wPos = 0; wPos < webcam.getWidth(); wPos += divw) {
							int index = (int)ofRandom((dequeSize - 1) * randomSelectionRange, dequeSize - 1);
							videoShaderSetupAndDraw(index, 1, glm::vec2(((iter++) + 1) * 1.0 / (float)(dequeSize)),
								NULL, 1.0 / (float)dequeSize, NULL);
						}
						break;
					}
				}
			}
		}
		break;
	// view all frames
	case 1:
		int index = 0;
		for (int j = 0; j < ofGetHeight(); j += smallFrameSize) {
			for (int i = 0; i < ofGetWidth(); i += smallFrameSize) {
				if (index < webcamFrameDeque.size()) {
					webcamFrameDeque[index]->resize(smallFrameSize, smallFrameSize);
					webcamFrameDeque[index]->draw(i, j);
					index++;
				}
			}
		}
		break;
	}
	sketchFbo.end();

	// flip fbo since ofVideograbber can't flip a video prior to processing
	SketchShader.begin();
	SketchShader.setUniformTexture("sketchTex", sketchFbo.getTexture(), 0);
	SketchShader.setUniformMatrix4f("mvp", glm::mat4());
	sketchMesh.draw();
	SketchShader.end();

	if (loadingFrames) ofDrawBitmapString(loadingString, ofGetWidth() / 2 - 50, ofGetHeight() * 0.5);
	ofDrawBitmapString(modeString, 10, 15);
	ofDrawBitmapString(dispModeString, 10, 25);
	ofDrawBitmapString(randString, 10, 35);

	sketchFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
	sketchFbo.begin();
	ofClear(0, 0, 0, 0);
	sketchFbo.end();

	
	//update video frames
	if (!videoFboDeque.empty()) {
		videoFboDeque[videoFboDeque.size() - 1]->begin();
		movie.draw(0, 0);
		videoFboDeque[videoFboDeque.size() - 1]->end();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case 'r':
		randomMode = (++randomMode) % 2;
		switch (randomMode) {
		case 0:
			randString = "random frame selection(r): off (range: " + to_string(1.0 - randomSelectionRange) + ")";
			break;
		case 1:
			randString = "random frame selection(r): on (range: " + to_string(1.0 - randomSelectionRange) + ")";
			break;
		}
		break;
	case 'm':
		viewMode = (++viewMode) % 2;
		switch (viewMode) {
		case 0:
			modeString = "current mode(m): time displacement";
			break;
		case 1:
			modeString = "current mode(m): view all frames in deque";
			break;
		}
		break;
	case 'd':
		dispMode = (++dispMode) % 4;
		switch (dispMode) {
		case 0:
			dispModeString = "displacement mode(d): linear (horizontal)";
			break;
		case 1:
			dispModeString = "displacement mode(d): linear (vertical)";
			break;
		case 2:
			dispModeString = "displacement mode(d): rectangular";
			break;
		case 3:
			dispModeString = "displacement mode(d): circular";
			break;
		}
		break;
	case OF_KEY_DOWN:
		randomSelectionRange = ofClamp(randomSelectionRange += 0.0125, .0, 1.0);
		if (randomMode) randString = "random frame selection(r): on (range: " + to_string(1.0 - randomSelectionRange) + ")";
		else randString = "random frame selection(r): off (range: " + to_string(1.0 - randomSelectionRange) + ")";
		break;
	case OF_KEY_UP:
		randomSelectionRange = ofClamp(randomSelectionRange -= 0.0125, .0, 1.0);
		if (randomMode) randString = "random frame selection(r): on (range: " + to_string(1.0 - randomSelectionRange) + ")";
		else randString = "random frame selection(r): off (range: " + to_string(1.0 - randomSelectionRange) + ")";
		break;
	case 'a':
		automateModes = !automateModes;
		break;
	case 'w':
		webcamMode = !webcamMode;
		videoMode = !webcamMode;
	case 'p':
		movie.setPosition(0);
		movie.play();
		break;
	case 'o':
		track.setPosition(0);
		track.play();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
