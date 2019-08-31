#pragma once

#include "ofMain.h"
class Rect {
public:
	void setBoundary(float boundxleft, float boundxright, float boundytop, float boundybottom) {
		this->boundxleft = boundxleft;
		this->boundxright = boundxright;
		this->boundytop = boundytop;
		this->boundybottom = boundybottom;
	}
	void boundaryCheck() {
		if (x < boundxleft || x + width > boundxright) {
			velocity.x *= -1;
		}
		if (y < boundytop || y + height > boundybottom) {
			velocity.y *= -1;
		}
	}
	void move() {
		boundaryCheck();
		x += velocity.x;
		y += velocity.y;
	}
	void draw() {
		ofDrawRectangle(x, y, width, height);
	}
public:
	float x, y, width, height;
	float boundxleft, boundxright, boundytop, boundybottom;
	ofVec2f velocity;
};


class DoubleCircle {
public:
	void setup(ofVec2f position, float radius) {
		this->position = position;
		this->radius = radius;
		this->velocity.x = ofRandom(-10, 10);
		this->velocity.y = ofRandom(-10, 10);
	}
	void setBoundary(float boundxleft, float boundxright, float boundytop, float boundybottom) {
		this->boundxleft = boundxleft;
		this->boundxright = boundxright;
		this->boundytop = boundytop;
		this->boundybottom = boundybottom;
	}
	void draw() {	
		ofDrawCircle(position, radius);
	}	
	void boundaryCheck() {
		if (position.x - radius < boundxleft || position.x + radius > boundxright) {
			velocity.x *= -1;
		}
		if (position.y - radius < boundytop || position.y + radius > boundybottom) {
			velocity.y *= -1;
		}
	}
	void move() {
		boundaryCheck();
		position += velocity;
	}
public:
	ofVec2f position;
	ofVec2f velocity;
	float radius;
	float boundxleft, boundxright, boundytop, boundybottom;
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
		void drawDiagonalRect(int rectNum);

public:
	
	ofShader shader, shader2, shader3, shader4;

	vector<Rect*> rectArr;
	vector<Rect*> rectArr2;
	vector<DoubleCircle*> circleArr;
	bool rectDrawn;
	int rectNum;
};
