#pragma once

#include "ofMain.h"
class PlaneMesh {
public:
	void setup(float width, float height, int widthQuadNum, int heightQuadNum, glm::vec3 centerPos) {
		this->w = width; this->h = height;
		this->wnum = widthQuadNum; this->hnum = heightQuadNum;
		this->centerPos = centerPos;
	}
	void buildPlaneMesh() {
		float qw = w / wnum; float qh = h / hnum;
		float quvw = 1.0 / wnum; float quvh = 1.0 / hnum;

		for (int i = 0; i <= hnum; i++) {
			for (int j = 0; j <= wnum; j++) {
				mesh.addVertex(glm::vec3(qw * j - w / 2.0, qh * i - h / 2.0, 0));
				mesh.addTexCoord(glm::vec2(quvw * j, quvh * i));
			}
		}

		for (int i = 0; i < hnum; i++) {
			for (int j = 0; j < wnum; j++) {
				int start = i * (wnum + 1) + j;
				ofIndexType indices[6] = { start, start + 1, start + wnum + 2,
									start + wnum + 2, start + wnum + 1, start };
				mesh.addIndices(indices, 6);
			}
		}

	}
	void setMode(ofPrimitiveMode mode) {
		mesh.setMode(mode);
	}
	
	void draw() {
		mesh.draw();
	}
public:
	float w, h;
	int wnum, hnum;
	glm::vec3 centerPos;
	ofMesh mesh;
};


class Point {
public:
	Point(glm::vec2 pos, float branchoutAngle, ofColor color) : pos(pos), branchoutAngle(branchoutAngle), color(color) {
		initPos = pos;
	}
	
public:
	glm::vec2 pos;
	glm::vec2 initPos;
	float branchoutAngle;
	ofColor color;
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
		void reset();
		
public:
	ofFbo fbo1, fbo2;
	ofShader FboShader1;
	PlaneMesh fboMesh1;

	glm::mat4 sModel, sProj, sView, sMvp;
	glm::mat4 fboModel, fboProj, fboView, fboMvp;

	float initAngle, branchoutAngle, prevBranchoutAngle;
	float moveSpeed;
	vector<Point*> movingPoints;
	Point* initPoint;
	bool branchout;
};
