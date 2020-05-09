#pragma once

#include "ofMain.h"
#include "Camera.h"
using namespace glm;
typedef struct CubeMesh {
	CubeMesh(vec3& center, float size) : center(center), size(size){
		/*
			0--1
	 		|\  \
			| 2--3
			4-|5 |
			 \|  |
			  6--7
		*/
		vertArr.push_back(vec3(center.x - size / 2.0, center.y + size / 2.0, center.z - size / 2.0));
		vertArr.push_back(vec3(center.x + size / 2.0, center.y + size / 2.0, center.z - size / 2.0));
		vertArr.push_back(vec3(center.x - size / 2.0, center.y + size / 2.0, center.z + size / 2.0));
		vertArr.push_back(vec3(center.x + size / 2.0, center.y + size / 2.0, center.z + size / 2.0));
		vertArr.push_back(vec3(center.x - size / 2.0, center.y - size / 2.0, center.z - size / 2.0));
		vertArr.push_back(vec3(center.x + size / 2.0, center.y - size / 2.0, center.z - size / 2.0));
		vertArr.push_back(vec3(center.x - size / 2.0, center.y - size / 2.0, center.z + size / 2.0));
		vertArr.push_back(vec3(center.x + size / 2.0, center.y - size / 2.0, center.z + size / 2.0));
		//setQuadTexCoords();
		buildQuads();
		
	}
	void addQuadTexCoords() {
		float tex[8] = { 0, 1, 1, 1, 0, 0, 1, 0 };
		for (int i = 0; i < 4; i++) {
			mesh.addTexCoord(vec2(tex[2 * i], tex[2 * i + 1]));
		}
	}

	void setQuadTexCoords(const float* texCoords) {
		this->texCoords = texCoords;
	}
	void setQuadTexCoords() {
		float tex[8] = { 0, 1, 1, 1, 0, 0, 1, 0 };
		cout << tex[3] << endl;
		this->texCoords = tex;
		cout << texCoords[3] << endl;
	}
	void buildQuads() {
		// 0 1 2 3 4 5 8 9 12 13 16 17
		// celiing indices: 0 1 2 3, verts: 0 1 2 3 
		mesh.addVertex(vertArr[0]);
		mesh.addVertex(vertArr[1]);
		mesh.addVertex(vertArr[2]);
		mesh.addVertex(vertArr[3]);
		ofIndexType ci[6] = { 0, 1, 3, 3, 2, 0 };
		mesh.addIndices(ci, 6);
		addQuadTexCoords();
		
		// left indices: 4 5 6 7, verts: 0 2 4 6 
		mesh.addVertex(vertArr[0]);
		mesh.addVertex(vertArr[2]);
		mesh.addVertex(vertArr[4]);
		mesh.addVertex(vertArr[6]);
		ofIndexType li[6] = { 4, 5, 7, 7, 6, 4 };
		mesh.addIndices(li, 6);
		addQuadTexCoords();
		
		// right indices: 8 9 10 11, verts: 3 1 7 5
		mesh.addVertex(vertArr[3]);
		mesh.addVertex(vertArr[1]);
		mesh.addVertex(vertArr[7]);
		mesh.addVertex(vertArr[5]);
		ofIndexType ri[6] = { 8, 9, 11, 11, 10, 8 };
		mesh.addIndices(ri, 6);
		addQuadTexCoords();
		
		// front indices: 12 13 14 15, verts: 2 3 6 7 
		mesh.addVertex(vertArr[2]);
		mesh.addVertex(vertArr[3]);
		mesh.addVertex(vertArr[6]);
		mesh.addVertex(vertArr[7]);
		ofIndexType fi[6] = { 12, 13, 15, 15, 14, 12 };
		mesh.addIndices(fi, 6);
		addQuadTexCoords();
		
		// back indices: 16 17 18 19, verts: 1 0 5 4
		mesh.addVertex(vertArr[1]);
		mesh.addVertex(vertArr[0]);
		mesh.addVertex(vertArr[5]);
		mesh.addVertex(vertArr[4]);
		ofIndexType bi[6] = { 16, 17, 19, 19, 18, 16 };
		mesh.addIndices(bi, 6);
		addQuadTexCoords();

		// bottom indices: 20 21 22 23, verts: 4 5 6 7
		mesh.addVertex(vertArr[4]);
		mesh.addVertex(vertArr[5]);
		mesh.addVertex(vertArr[6]);
		mesh.addVertex(vertArr[7]);
		ofIndexType bti[6] = { 20, 21, 23, 23, 22, 20 };
		mesh.addIndices(bti, 6);
		addQuadTexCoords();
	}

	void changeCenterPos(vec3& newPos) {
		vec3 diff = newPos - this->center;
		this->center = newPos;
		for (int i = 0; i < 24; i++) {
			mesh.setVertex(i, mesh.getVertex(i) + diff);
		}
	}

	void changeSize(float newSize) {
		for (int i = 0; i < 24; i++) {
			vec3 u = normalize(mesh.getVertex(i) - this->center);
			mesh.setVertex(i, this->center + u * sqrt(3.0) * 0.5 * newSize);
		}
	}
	void draw() { mesh.draw(); }
	const float* texCoords;
	vec3 center;
	vector<vec3> vertArr;
	float size;
	ofMesh mesh;
};

class Walker {
public:
	Walker(int size, float vel, float cubeSize, vec3& headPos) : size(size), vel(vel), cubeSize(cubeSize), headPos(headPos){
		positionArr.push_back(headPos);
		for (int i = 0; i < this->size - 1; i++) {
			addRandomPos();
		}
		for (int i = 0; i < this->size; i++) {
			CubeMesh* cube = new CubeMesh(positionArr[i], cubeSize);
			cubeArr.push_back(cube);
		}
		boundaryEnabled = false;
		colorVal = vec3(ofRandom(0, 1), ofRandom(0, 1), ofRandom(0, 1));
		mode = 0;
	}
	void setBoundary(vec3& boundary) { boundaryEnabled = true; this->boundary = boundary; }
	void addRandomPos() {
		int random = (int) ofRandom(0, 6);
		switch (random) {
		case 0:
			headPos += vel * vec3(-1, 0, 0);
			break;
		case 1:
			headPos += vel * vec3(1, 0, 0);
			break;
		case 2:
			headPos += vel * vec3(0, -1, 0);
			break;
		case 3:
			headPos += vel * vec3(0, 1, 0);
			break;
		case 4:
			headPos += vel * vec3(0, 0, -1);
			break;
		case 5:
			headPos += vel * vec3(0, 0, 1);
			break;
		}
		if (boundaryEnabled) {
			if (headPos.x < -boundary.x) headPos += vel * vec3(1, 0, 0);
			else if (headPos.x > boundary.x) headPos += vel * vec3(-1, 0, 0);

			if (headPos.y < -boundary.y) headPos += vel * vec3(0, 1, 0);
			else if (headPos.y > boundary.y) headPos += vel * vec3(0, -1, 0);

			if (headPos.z < -boundary.z) headPos += vel * vec3(0, 0, 1);
			else if (headPos.z > boundary.z) headPos += vel * vec3(0, 0, -1);
			
		}
		vec3 newPos = headPos;
		positionArr.push_back(newPos);
	}
	void addRandomPosTunnel() {
		int random = (int)ofRandom(0, 6);
		switch (random) {
		case 0:
			headPos += vel * vec3(-1, 0, 0);
			break;
		case 1:
			headPos += vel * vec3(1, 0, 0);
			break;
		case 2:
			headPos += vel * vec3(0, -1, 0);
			break;
		case 3:
			headPos += vel * vec3(0, 1, 0);
			break;
		case 4:
			headPos += vel * vec3(0, 0, -1);
			break;
		case 5:
			headPos += vel * vec3(0, 0, 1);
			break;
		}
		if (boundaryEnabled) {
			if (headPos.x < -boundary.x || (headPos.x < 0.5 * boundary.x && headPos.x > 0)) {
				if (headPos.y > -0.5 * boundary.y && headPos.y < 0.5 * boundary.y) {
					headPos += vel * vec3(1, 0, 0);
				}
			}
			else if (headPos.x > boundary.x || (headPos.x > -0.5 * boundary.x && headPos.x < 0)) {
				
				if (headPos.y > -0.5 * boundary.y && headPos.y < 0.5 * boundary.y) {
					headPos += vel * vec3(-1, 0, 0);
				}
			}
			
			if (headPos.y < -boundary.y) headPos += vel * vec3(0, 1, 0);
			if (headPos.y > boundary.y) headPos += vel * vec3(0, -1, 0);
			
			if (headPos.z < -boundary.z) headPos += vel * vec3(0, 0, 1);
			else if (headPos.z > boundary.z) headPos += vel * vec3(0, 0, -1);

		}
		vec3 newPos = headPos;
		positionArr.push_back(newPos);
	}
	void addRandomPosMoveForward() {
		int random = (int)ofRandom(0, 4);
		switch (random) {
		case 0:
			headPos += vel * vec3(-1, 0, 0);
			break;
		case 1:
			headPos += vel * vec3(1, 0, 0);
			break;
		case 2:
			headPos += vel * vec3(0, -1, 0);
			break;
		case 3:
			headPos += vel * vec3(0, 1, 0);
			break;
		
		}
		headPos += vel * vec3(0, 0, -1);
		if (boundaryEnabled) {
			if (headPos.x < -boundary.x) headPos += vel * vec3(1, 0, 0);
			else if (headPos.x > boundary.x) headPos += vel * vec3(-1, 0, 0);

			if (headPos.y < -boundary.y) headPos += vel * vec3(0, 1, 0);
			else if (headPos.y > boundary.y) headPos += vel * vec3(0, -1, 0);

		}
		vec3 newPos = headPos;
		positionArr.push_back(newPos);
	}
	void addRandomPosTunnelMoveForward() {
		int random = (int)ofRandom(0, 4);
		switch (random) {
		case 0:
			headPos += vel * vec3(-1, 0, 0);
			break;
		case 1:
			headPos += vel * vec3(1, 0, 0);
			break;
		case 2:
			headPos += vel * vec3(0, -1, 0);
			break;
		case 3:
			headPos += vel * vec3(0, 1, 0);
			break;
		
		}
		headPos += vel * vec3(0, 0, -1);
		if (boundaryEnabled) {
			if (headPos.x < -boundary.x || (headPos.x < 0.5 * boundary.x && headPos.x > 0)) {
				if (headPos.y > -0.5 * boundary.y && headPos.y < 0.5 * boundary.y) {
					headPos += vel * vec3(1, 0, 0);
				}
			}
			else if (headPos.x > boundary.x || (headPos.x > -0.5 * boundary.x && headPos.x < 0)) {

				if (headPos.y > -0.5 * boundary.y && headPos.y < 0.5 * boundary.y) {
					headPos += vel * vec3(-1, 0, 0);
				}
			}

			if (headPos.y < -boundary.y) headPos += vel * vec3(0, 1, 0);
			if (headPos.y > boundary.y) headPos += vel * vec3(0, -1, 0);


		}
		vec3 newPos = headPos;
		positionArr.push_back(newPos);
	}
	void update() {
		switch (mode) {
		case 0: 
			if (positionArr.size() == size) addRandomPos();
			break;
		case 1: 
			if (positionArr.size() == size) addRandomPosTunnel(); 
			break;
		case 2:
			if (positionArr.size() == size) addRandomPosMoveForward();
			break;
		case 3:
			if (positionArr.size() == size) addRandomPosTunnelMoveForward();
			break;
		}
		positionArr.pop_front();
		//cout << cubeArr.size() << " " << positionArr.size() << endl;
		float div = PI / this->size;
		for (int i = 0; i < this->size; i++) {
			cubeArr[i]->changeCenterPos(positionArr[i]);
			cubeArr[i]->changeSize(this->cubeSize * sin(div * i));
			
		}
	}
	void changeCubeSize(float newVal) {
		this->cubeSize = newVal;
	}
	void draw(ofShader& shader) {
		shader.setUniform3f("colorVal", colorVal);
		for (auto c : cubeArr) {
			c->draw();
		}
	}

public:
	int size, mode;
	float vel, cubeSize;
	bool boundaryEnabled;
	vec3 headPos;
	vec3 boundary;
	vec3 colorVal;
	deque<vec3> positionArr;
	vector<CubeMesh*> cubeArr;
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
	CubeMesh* test;
	Walker* walkerTest;
	ofShader CubeShader, SketchShader, BackgroundShader;
	Camera camera;
	mat4 model, view, proj, mvp;
	vector<Walker*> walkerArr;
	int walkerNum;
	ofMesh sketchQuadMesh, backgroundMesh;
	ofFbo sketchFbo;
	bool sizeChangeFlag;
	float newSize;

	ofSoundPlayer track;
	int bandNum;
	float *fftSmooth;

	float bgSoundVal;
};
