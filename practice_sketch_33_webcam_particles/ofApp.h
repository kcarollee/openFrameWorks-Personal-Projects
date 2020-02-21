#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

class Tile {
public:
	Tile (glm::vec2& pos, float width, float height, float radius) :
		pos(pos), width(width), height(height), radius(radius){
		particleSpeed = ofRandom(0.1, 1.5);
		float angle = ofRandom(0, 2 * PI);
		particleDirection = glm::vec2(cos(angle), sin(angle));
		particlePos = glm::vec2(pos.x + width / 2.0, pos.y + height / 2.0);
		toggleParticle = false;
		toggleRect = true;
		toggleBoundary = true;
		alpha = 255;
	}

	void resetRadius(float r) { radius = r; }
	void updateParticle() {
		if (toggleParticle) {		
			if(toggleBoundary) checkBoundary();
			else alpha -= 5.0;
			particlePos += particleSpeed * particleDirection;
		}
	}

	void setColor(ofColor* color) {
		particleColor.set(*color);
	}
	void checkBoundary() {
		if (particlePos.x - radius <= pos.x || particlePos.x + radius >= pos.x + width) {
			particleDirection.x = -particleDirection.x;
		}
		if (particlePos.y - radius <= pos.y || particlePos.y + radius >= pos.y + height) {
			particleDirection.y = -particleDirection.y;
		}
	}
	// a more accurate, but more cpu consuming color check
	void checkColorByPixels(ofxCvGrayscaleImage& image, int inc) {
		for (int i = pos.x; i < pos.x + width; i += inc) {
			for (int j = pos.y; j < pos.t + height; j += inc) {	
				if (image.getPixels().getColor(i, j).r  > 200) {
					toggleParticle = true;
					break;
				}		
			}
		}	
	}

	// checking only the center
	bool checkCenterColor(ofxCvGrayscaleImage& image) {
		if (image.getPixels().getColor(pos.x + width / 2.0, pos.y + height / 2.0).r > 200) return true;
		else return false;
	}
	void draw() {
		if (toggleRect) {
			ofNoFill();
			ofDrawRectangle(pos, width, height);		
		}
		if (toggleParticle) {
			ofFill();
			ofSetColor(particleColor, alpha);		
			ofDrawCircle(particlePos, radius);
			if (alpha <= 0) {
				alpha = 255;
				particlePos = glm::vec2(pos.x + width / 2.0, pos.y + height / 2.0);
				toggleParticle = false;
			}		
		}
	}
public:
	glm::vec2 pos;
	glm::vec2 particlePos, particleDirection;
	ofColor particleColor;
	float width, height;
	float radius;
	float particleSpeed;
	int alpha;
	bool toggleParticle, toggleRect, toggleBoundary;
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
	vector<Tile*> TileArr;
	int tileRowNum, tileColNum;
	ofVideoGrabber webcam;
	ofxCvColorImage webcamCapture;
	ofxCvGrayscaleImage webcamGray, webcamGrayPrev, webcamGrayDiff;
	float threshold;
	bool snapshot, webcamFeed, contMode;
};
