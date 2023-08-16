#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	sender1.init("OF_SPOUT_1");
	sender2.init("OF_SPOUT_2");

	textureOut1.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA);
	textureOut2.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA);
	ofEnableDepthTest();
	ofDisableArbTex();
	//cout << "TESTING MIDI" << endl;
	midi.listInPorts();

	midi.openPort(1);
	midi.addListener(this);

	camera.lookAt(glm::vec3(0, 0, 0));
}

//--------------------------------------------------------------
void ofApp::update() {
	for (auto randomLine : randomLines) {
		randomLine->choosePointsFromMidiBox();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	updateCamera();
	
	// draw cubes on textureOut1
	textureOut1.begin();
	camera.begin();
	ofBackground(0, 0);
	if (midiBoxes.size() > 0) {
		for (auto midiBox : midiBoxes) {
			midiBox->displayBox();
			midiBox->updateBox();
		}
	}
	camera.end();
	textureOut1.end();
	sender1.send(textureOut1.getTexture());


	// draw lines on textureOut2
	textureOut2.begin();
	camera.begin();
	ofBackground(0, 0);
	if (randomLines.size() > 0 &&  ofGetFrameNum() % 5 == 0) {
		for (auto randomLine : randomLines) {
			randomLine->displayLine();
		}
	}
	camera.end();
	textureOut2.end();
	sender2.send(textureOut2.getTexture());

	
	ofBackground(0, 0);
	textureOut1.draw(0, 0);
	textureOut2.draw(0, 0);
}

void ofApp::exit() {
	midi.closePort();
	midi.removeListener(this);
}

void ofApp::newMidiMessage(ofxMidiMessage& message) {
	messages.push_back(message);
	cout << "VALUE: " << message.value << " VEL: " << message.velocity << endl;
	if (messages.size() > 32) {
		messages.erase(messages.begin());
	}


	if (message.velocity > 0) {
		glm::vec3 size = glm::vec3(
			message.velocity,
			message.velocity,
			message.velocity
		);

		float gap = 100;

		float spawnSphereRadius = min(ofGetWindowHeight(), ofGetWindowWidth());
		spawnSphereRadius *= 0.75;
		glm::vec3 spawnSphereCenterPos = glm::vec3(ofGetWindowWidth() * 0.5, ofGetWindowHeight() * 0.5, 0);
		float randomTheta = ofRandom(0, 360);
		float randomTheta2 = ofRandom(0, 360);
		float randomX = spawnSphereRadius * sin(randomTheta) * cos(randomTheta2);
		float randomY = spawnSphereRadius * sin(randomTheta) * sin(randomTheta2);
		float randomZ = spawnSphereRadius * cos(randomTheta);
		glm::vec3 randPos = glm::vec3(
			randomX + spawnSphereCenterPos.x, randomY + spawnSphereCenterPos.y, randomZ
		);
		MidiBox* tempMidiBox = new MidiBox(size, randPos);
		midiBoxes.push_back(tempMidiBox);

		if (midiBoxes.size() > 1) {
			RandomLine* randomLine = new RandomLine(10);
			//randomLine->chooseMidiBox(midiBoxes);
			//randomLines.push_back(randomLine);
		}
	}

}

void ofApp::updateCamera() {
	float radius = ofGetWidth();
	float cameraVel = ofGetElapsedTimef();
	cameraPos.x = ofGetWindowWidth() * 0.5 + radius * sin(cameraVel);
	cameraPos.z = radius * cos(cameraVel);
	cameraPos.y = ofGetWindowHeight() * 0.5;
	camera.setPosition(cameraPos);
	camera.lookAt(glm::vec3(ofGetWidth() * 0.5, ofGetHeight() * 0.5, 0));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

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
