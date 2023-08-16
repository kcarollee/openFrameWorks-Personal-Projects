#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxSpout.h"

class MidiBox {
public:
	MidiBox(glm::vec3 dimension, glm::vec3 position) {
		this->dimension = dimension;
		this->sizeX = dimension.x;
		this->sizeY = dimension.y;
		this->sizeZ = dimension.z;

		this->lifeSpan = min(min(this->sizeX, this->sizeY), this->sizeZ);

		this->initPos = position;

		this->boxPrimitive.set(this->sizeX, this->sizeY, this->sizeZ);
		this->spherePrimitive.set(this->sizeX, 10);
		this->boxMesh = this->spherePrimitive.getMesh();

		for (int i = 0; i < this->boxMesh.getNumVertices(); i++) {
			glm::vec3 vert = this->boxMesh.getVertex(i);
			vert += this->initPos;
			this->boxMesh.setVertex(i, vert);
		}
	}

	void displayBox() {
		ofSetLineWidth(0.5);
		this->boxMesh.draw();
		//cout << this->boxMesh.getNumVertices() << endl;
	}

	void updateBox() {
		//if (this->boxMesh.getNumVertices() == NULL) return;
		// for some reason, this->boxMesh.getNumVertices() causes the app to crash
		int vertNum = this->boxMesh.getVertices().size();
		
		for (int i = 0; i < vertNum; i++) {
			
			glm::vec3 vert = this->boxMesh.getVertex(i);

			/*
			float noiseDensity = 0.1;
			float noiseAmp = 1.0;
			float noise1 = ofNoise(glm::vec4(
				vert.x * noiseDensity,
				vert.y * noiseDensity,
				vert.z * noiseDensity,
				ofGetElapsedTimef())
			);
			float noise2 = ofNoise(glm::vec4(
				vert.x * noiseDensity,
				vert.z * noiseDensity,
				vert.y * noiseDensity,
				ofGetElapsedTimef())
			);
			float noise3 = ofNoise(glm::vec4(
				vert.z * noiseDensity,
				vert.y * noiseDensity,
				vert.x * noiseDensity,
				ofGetElapsedTimef())
			);

			noise1 = ofMap(noise1, 0, 1, -noiseAmp, noiseAmp, true);
			noise2 = ofMap(noise2, 0, 1, -noiseAmp, noiseAmp, true);
			noise3 = ofMap(noise3, 0, 1, -noiseAmp, noiseAmp, true);

			vert += glm::vec3(noise1, noise2, noise3);
			this->boxMesh.setVertex(i, vert);
			*/
		}
		
	}

	public:
		glm::vec3 dimension;
		glm::vec3 initPos;
		float sizeX, sizeY, sizeZ;
		float lifeSpan; // the minimum of sizeX, sizeY, sizeZ
		ofBoxPrimitive boxPrimitive;
		ofSpherePrimitive spherePrimitive;
		ofMesh boxMesh;
};

class RandomLine {

	public:
		RandomLine(float lifeSpan) {
			this->lifeSpan = lifeSpan;
		}

		// choose 2 midiboxes 
		void chooseMidiBox(vector<MidiBox*> &midiBoxes) {
			vector<int> indexArr;
			int midiBoxSize = midiBoxes.size();
			for (int i = 0; i < midiBoxSize; i++) indexArr.push_back(i);

			int randElemIndex = ofRandom(midiBoxSize);

			int randIndex1 = indexArr[randElemIndex];

			indexArr.erase(indexArr.begin() + randElemIndex);

			randElemIndex = ofRandom(midiBoxSize - 1);

			int randIndex2 = indexArr[randElemIndex];

			cout << randIndex1 << " " << randIndex2 << endl;


			this->midiBox1 = midiBoxes[randIndex1];
			this->midiBox2 = midiBoxes[randIndex2];
		}

		// choose another MidiBox if the current one isn't alive 
		
		// get random points from each midiBox
		void choosePointsFromMidiBox() {
			/*
			int pointsNum1, pointsNum2;

			pointsNum1 = this->midiBox1->boxMesh.getNumVertices();
			pointsNum2 = this->midiBox2->boxMesh.getNumVertices();

			int randomPointIndex1 = ofRandom(0, pointsNum1);
			int randomPointIndex2 = ofRandom(0, pointsNum2);

			point1 = this->midiBox1->boxMesh.getVertex(randomPointIndex1);
			point2 = this->midiBox2->boxMesh.getVertex(randomPointIndex2);

			cout << point1.x << endl;
			*/
		}

		void displayLine() {
			ofSetLineWidth(10);
			ofSetColor(255, 0, 0);
			ofDrawBox(point1, 5);
			ofDrawBox(point2, 5);
			ofDrawLine(point1, point2);
		}

		

	public:
		float lifeSpan;
		MidiBox* midiBox1;
		MidiBox* midiBox2;

		glm::vec3 point1, point2;
};


class ofApp : public ofBaseApp, public ofxMidiListener {

public:
	void setup();
	void update();
	void draw();

	void exit();
	void newMidiMessage(ofxMidiMessage& message);

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void updateCamera();

	ofxMidiIn midi;
	vector<ofxMidiMessage> messages;
	vector<MidiBox*> midiBoxes;
	vector<RandomLine*> randomLines;

	// texture to send out via spout
	ofFbo textureOut1, textureOut2;

	ofxSpout::Sender sender1, sender2;

	//camera

	ofCamera camera;
	glm::vec3 cameraPos;

};
