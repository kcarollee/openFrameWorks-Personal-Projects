#pragma once

#include "ofMain.h"
#include "ofxHapPlayer.h"
#include "ofxOpenCv.h"
class Particle {
	public:
		Particle(float x, float y, float vCoef, ofColor color) {
			this->lifeCount = 0;
			this->lifeSpan = 10;
			this->posx = x; this->posy = y;
			this->alive = true;
			this->vMax = 0.1;
			this->vCoef = vCoef;
			this->velx = ofRandom(-this->vMax, this->vMax) * vCoef;
			this->vely = ofRandom(-this->vMax, this->vMax) * vCoef;
			this->color = color;
			this->pointMesh.setMode(OF_PRIMITIVE_POINTS);
			this->pointMesh.addVertex(glm::vec3(0));
			this->size = ofRandom(1, 5);
		}

		void display() {
			if (this->alive) {
				ofSetColor(this->color, 255);
				//ofDrawRectangle(this->posx, this->posy, this->size, this->size);
				//ofDrawCircle(this->posx, this->posy, this->size);
				glPointSize(this->size);
				this->pointMesh.setVertex(0, glm::vec3(this->posx, this->posy, 0));
				this->pointMesh.draw();
			}
		}

		void update() {
			if (this->lifeCount++ > this->lifeSpan) this->alive = false;
			else {
				float noiseDeg = 0.01;
				glm::vec2 noise = glm::vec2(ofMap(ofNoise(this->posx * noiseDeg + ofGetElapsedTimef() * 0.2, this->posy * noiseDeg), 0, 1, -this->vMax, this->vMax), 
					ofMap(ofNoise(this->posx * noiseDeg, this->posy * noiseDeg + ofGetElapsedTimef() * 0.2), 0, 1, -this->vMax, this->vMax));
				noise = glm::normalize(noise) * this->vCoef;
				this->posx += noise.x;
				this->posy += noise.y;
			}
		}
	
	public:
		float lifeSpan, lifeCount;
		float posx, posy;
		float velx, vely;
		bool alive;
		float vMax, vCoef;
		ofColor color;
		ofMesh pointMesh;
		float size;
};
class ParticleCell {
	public:
		ParticleCell(float x, float y, float w, float h) {
			this->posx = x; this->posy = y;
			this->width = w; this->height = h;
			this->diffThreshold = 30;
			this->particleNum = 1;
		}

		void setGreyscaleColor(ofColor color) {
			this->prevColor = this->currentColor;
			this->currentColor = color;
		}

		void setDisplayColor(ofColor color) {
			this->displayColor = color;
		}

		void createParticles() {
			if (abs(currentColor.r - prevColor.r) > this->diffThreshold && this->particleArr.size() < 10) {
				float vCoef = pow(ofMap(abs(currentColor.r - prevColor.r), this->diffThreshold, 255, 1, 3), 3);
				for (int i = 0; i < this->particleNum; i++) {
					Particle* tp = new Particle(ofRandom(this->posx, this->posx + this->width),
						ofRandom(this->posy, this->posy + this->height), vCoef, this->displayColor);
					this->particleArr.push_back(tp);
				}
			}
		}

		void update() {
			for (auto p : particleArr) {
				if (!p->alive) {
					vector<Particle*>::iterator it = find(particleArr.begin(), particleArr.end(), p);
					if (it < particleArr.end()) particleArr.erase(it);
					//cout << "GONE" << endl;
				}
				else {
					p->update();
				}
			}

		}

		void display() {
			//ofSetColor(this->currentColor);
			//ofDrawRectangle(this->posx, this->posy, this->width, this->height);
			for (auto p : particleArr) p->display();
		}
	public:
		ofColor prevColor, currentColor, displayColor; // prev and currentColors are greyscales. displayColor is the source's color
		float diffThreshold;
		float width, height;
		float posx, posy;
		vector<Particle*> particleArr;
		int particleNum;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
	public:
		ofxHapPlayer videoSource;
		ofShader videoSourceShader, backbufferShader, finalOutputShader;
		float windowDiv;
		float cellWidth, cellHeight;
		ofFbo videoFbo, particlesFbo, videoSourceFbo, backbuffer, midbuffer, finalOutputFbo;
		ofFloatPixels videoPixels, videoSourcePixels;
		ofImage videoImage;

		vector<ParticleCell*> particleCellArr;

		ofVideoGrabber webcam;
		int mode;

		ofTexture prevVideoTexture;

		ofxCvColorImage videoCapture;
		ofxCvGrayscaleImage videoGray, videoGrayPrev, videoGrayDiff;
};
