#pragma once

#include "ofMain.h"
#include "ofxGui.h"
typedef struct Shape
{
	void setup(float radius, int vertexNum, float startingDeg, float zPos, float meshHeight, int layerNum) {
		this->radius = radius;
		this->vertexNum = vertexNum; // number of vertices per layer
		this->startingDeg = startingDeg;
		this->degIncrement = 2 * PI / vertexNum;
		this->zPos = zPos;
		this->meshHeight = meshHeight;
		this->layerNum = layerNum;
		
		// initializing polygon for polygone mode
		p.begin();	
		for (int i = 0; i < vertexNum; i++) {
			p.addVertex(radius * cos(i * degIncrement + startingDeg), 
				radius * sin(i * degIncrement + startingDeg));
		}
		p.end();
		p.close();
		
		// initializing tube for tube mode
		// for each layer
		for (int layer = 0; layer < this->layerNum; layer++) {
			// complete rotation
			for (int i = 0; i < vertexNum; i++) {
				m.addVertex(ofVec3f(radius * cos(i * degIncrement + startingDeg),
					radius * sin(i * degIncrement + startingDeg), zPos + meshHeight * layer));
			}
		}
		
		for (int layer = 0; layer < this->layerNum - 1; layer++) {
			for (int i = 0; i < this->vertexNum; i++) {
				if (i == this->vertexNum - 1) {
					m.addIndex(this->vertexNum * layer + i);
					m.addIndex(this->vertexNum * layer);
					m.addIndex(this->vertexNum * (layer + 1) + i);

					m.addIndex(this->vertexNum * layer);
					m.addIndex(this->vertexNum * (layer + 1));
					m.addIndex(this->vertexNum * (layer + 1) + i);
				}
				else {
					m.addIndex(this->vertexNum * layer + i);
					m.addIndex(this->vertexNum * layer + i + 1);
					m.addIndex(this->vertexNum * (layer + 1) + i);

					m.addIndex(this->vertexNum * layer + i + 1);
					m.addIndex(this->vertexNum * (layer + 1) + i + 1);
					m.addIndex(this->vertexNum * (layer + 1) + i);
				}
			}
		}
		this->totalHeight = (this->layerNum - 1) * this->meshHeight;
	}

	void drawSingleShape() {
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, zPos);
		ofSetColor(200 + 100 * sin(ofGetElapsedTimef() * 2 + zPos), 
			100 + 50 * cos(ofGetElapsedTimef() / 2 + zPos), 20);
		p.draw();		
		ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2, -zPos);
	}

	void drawTubeMesh() {
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, zPos);
		ofSetColor(200 + 100 * sin(ofGetElapsedTimef() * 2 + zPos),
			100 + 50 * cos(ofGetElapsedTimef() / 2 + zPos), 20);	
		m.drawFaces();
		ofSetColor(100, 200, 20);
		m.drawWireframe();
		ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2, -zPos);
	}

	void resetTubeHeight(float newHeight) {
		// for each layer
		for (int layer = 0; layer < this->layerNum; layer++) {
			// complete rotation
			for (int i = 0; i < vertexNum; i++) {
				m.setVertex(layer * vertexNum + i, ofVec3f(m.getVertex(layer * vertexNum + i).x,
					m.getVertex(layer * vertexNum + i).y, zPos + newHeight * layer));
			}
		}
	}

	void resetTubeRadius(float newRadius) {
		// for each layer
		for (int layer = 0; layer < this->layerNum; layer++) {
			// complete rotation
			for (int i = 0; i < vertexNum; i++) {
				m.setVertex(layer * vertexNum + i ,ofVec3f(newRadius * cos(i * degIncrement + startingDeg),
					newRadius * sin(i * degIncrement + startingDeg), m.getVertex(layer * vertexNum + i).z));
			}
		}
	}

	void moveTubeMesh(float index) {
		for (int i = 0; i < vertexNum * 2; i++) {
			m.setVertex(i, ofVec3f(m.getVertex(i).x * index,
				m.getVertex(i).y * index,
				m.getVertex(i).z));
		}
	}

	void rotate(float deg) {
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, zPos);
		ofRotateZ(deg);
		ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2, -zPos);
	}

	void resetVertexNum(int newVertexNum) {
		p.clear();
		m.clear();
		setup(radius, newVertexNum, startingDeg, zPos, meshHeight, layerNum);
	}

	int vertexNum, layerNum;
	float startingDeg, radius, degIncrement, zPos, meshHeight, totalHeight;
	ofPolyline p;
	ofMesh m;

} Shape;

typedef struct SingleTube : public Shape {
	void setup(float radius, int vertexNum, float startingDeg, float zPos, float meshHeight, int layerNum) {
		this->radius = radius;
		this->vertexNum = vertexNum; // number of vertices per layer
		this->startingDeg = startingDeg;
		this->degIncrement = 2 * PI / vertexNum;
		this->zPos = zPos;
		this->meshHeight = meshHeight;
		this->layerNum = layerNum;
	
		// initializing tube 
		// for each layer
		for (int layer = 0; layer < this->layerNum; layer++) {
			// complete rotation
			for (int i = 0; i < vertexNum; i++) {
				m.addVertex(ofVec3f(radius * cos(i * degIncrement + startingDeg),
					radius * sin(i * degIncrement + startingDeg), zPos + meshHeight * layer));
				m.addColor(ofColor(75 * sin(layer + i), 2 * sin(layer + i), 130 * sin(layer + i)));
			}
		}

		for (int layer = 0; layer < this->layerNum - 1; layer++) {
			for (int i = 0; i < this->vertexNum; i++) {
				if (i == this->vertexNum - 1) {
					m.addIndex(this->vertexNum * layer + i);
					m.addIndex(this->vertexNum * layer);
					m.addIndex(this->vertexNum * (layer + 1) + i);

					m.addIndex(this->vertexNum * layer);
					m.addIndex(this->vertexNum * (layer + 1));
					m.addIndex(this->vertexNum * (layer + 1) + i);
					
				}
				else {
					m.addIndex(this->vertexNum * layer + i);
					m.addIndex(this->vertexNum * layer + i + 1);
					m.addIndex(this->vertexNum * (layer + 1) + i);

					m.addIndex(this->vertexNum * layer + i + 1);
					m.addIndex(this->vertexNum * (layer + 1) + i + 1);
					m.addIndex(this->vertexNum * (layer + 1) + i);					
				}
			}
		}
		this->totalHeight = (this->layerNum - 1) * this->meshHeight;
	}
	void singleTubeCustomMovement() {
		// for each layer
		for (int layer = 0; layer < this->layerNum; layer++) {
			// complete rotation
			for (int i = 0; i < vertexNum; i++) {
				m.setVertex(layer * vertexNum + i, 
					ofVec3f(radius * cos(i * degIncrement + startingDeg + layer * sin(ofGetElapsedTimef())),
					radius * sin(i * degIncrement + startingDeg  + layer * sin(ofGetElapsedTimef())), 
						zPos + meshHeight * layer));
			}
		}
	}

	// n is a value between 0 and PI
	void twistTube(float n) {
		for (int layer = 0; layer < this->layerNum; layer++) {
			// complete rotation
			for (int i = 0; i < vertexNum; i++) {
				m.setVertex(layer * vertexNum + i, 
					ofVec3f(radius * cos(i * degIncrement + startingDeg + layer * n),
						radius * sin(i * degIncrement + startingDeg + layer * n), zPos + meshHeight * layer));
			}
		}
	}

	void resetVertexNum(int newVertexNum) {
		m.clear();
		setup(radius, newVertexNum, startingDeg, zPos, meshHeight, layerNum);
	}

	void drawSingleTubeMesh() {
		ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, zPos);
		m.drawFaces();
		//m.drawWireframe();
		ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2, -zPos);
	}
}SingleTube;

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
		void setCameraPos(float zpos);
public:
	vector<Shape*> shapeArr;
	ofCamera camera;
	ofEasyCam camera2;
	bool easyCamMode;
	float rotateDeg, twistf;
	SingleTube* singleTube;

	ofxPanel gui;
	ofParameter<bool> rotateMode, tubeHeigtChangeMode;
	ofParameter<bool> multipleTubeMode, multiplePolygonMode, singleTubeMode, autoTwistMode;
	ofParameter<int> vertNum;
	ofParameter<float> twist;
	
};
