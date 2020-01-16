#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class MappedCube {
public:
	void setup(glm::vec3 centerPos, double w, double h, double d) {
		this->centerPos = centerPos;
		this->w = w; this->h = h; this->d = d;
		// ceiling vertices
		for (int i = 0; i < 6; i++) {
			ofMesh* mesh = new ofMesh();
			meshArr.push_back(mesh);
		}
		v1 = {
			centerPos.x + w / 2.0, centerPos.y + h / 2.0, centerPos.z + d / 2.0,
			centerPos.x - w / 2.0, centerPos.y + h / 2.0, centerPos.z + d / 2.0,
			centerPos.x - w / 2.0, centerPos.y - h / 2.0, centerPos.z + d / 2.0,
			centerPos.x + w / 2.0, centerPos.y - h / 2.0, centerPos.z + d / 2.0
		};
		buildMesh(*meshArr[0], v1);
		// side vertices
		v2 = {
			centerPos.x + w / 2.0, centerPos.y + h / 2.0, centerPos.z + d / 2.0,
			centerPos.x - w / 2.0, centerPos.y + h / 2.0, centerPos.z + d / 2.0,
			centerPos.x - w / 2.0, centerPos.y + h / 2.0, centerPos.z - d / 2.0,
			centerPos.x + w / 2.0, centerPos.y + h / 2.0, centerPos.z - d / 2.0
		};
		buildMesh(*meshArr[1], v2);
		v3 = {
			centerPos.x + w / 2.0, centerPos.y + h / 2.0, centerPos.z + d / 2.0,
			centerPos.x + w / 2.0, centerPos.y - h / 2.0, centerPos.z + d / 2.0,
			centerPos.x + w / 2.0, centerPos.y - h / 2.0, centerPos.z - d / 2.0,
			centerPos.x + w / 2.0, centerPos.y + h / 2.0, centerPos.z - d / 2.0
		};
		buildMesh(*meshArr[2], v3);
		v4 = {
			centerPos.x + w / 2.0, centerPos.y - h / 2.0, centerPos.z + d / 2.0,
			centerPos.x - w / 2.0, centerPos.y - h / 2.0, centerPos.z + d / 2.0,
			centerPos.x - w / 2.0, centerPos.y - h / 2.0, centerPos.z - d / 2.0,
			centerPos.x + w / 2.0, centerPos.y - h / 2.0, centerPos.z - d / 2.0
		};
		buildMesh(*meshArr[3], v4);
		v5 = {
			centerPos.x - w / 2.0, centerPos.y + h / 2.0, centerPos.z + d / 2.0,
			centerPos.x - w / 2.0, centerPos.y - h / 2.0, centerPos.z + d / 2.0,
			centerPos.x - w / 2.0, centerPos.y - h / 2.0, centerPos.z - d / 2.0,
			centerPos.x - w / 2.0, centerPos.y + h / 2.0, centerPos.z - d / 2.0
		};
		buildMesh(*meshArr[4], v5);
		// floor vertices
		v6 = {
			centerPos.x + w / 2.0, centerPos.y + h / 2.0, centerPos.z - d / 2.0,
			centerPos.x - w / 2.0, centerPos.y + h / 2.0, centerPos.z - d / 2.0,
			centerPos.x - w / 2.0, centerPos.y - h / 2.0, centerPos.z - d / 2.0,
			centerPos.x + w / 2.0, centerPos.y - h / 2.0, centerPos.z - d / 2.0
		};
		buildMesh(*meshArr[5], v6);
	}

	void buildMesh(ofMesh &mesh, vector<double> &vertArr) {
		for (int i = 0; i < 4; i++) {
			mesh.addVertex(glm::vec3(vertArr[i * 3], vertArr[i * 3 + 1], vertArr[i * 3 + 2]));
			mesh.addTexCoord(glm::vec2(uvcoords[i*2], uvcoords[i*2+1]));
		}	
		mesh.addIndices(indices, 6);
	}

	void draw() {
		for (auto mesh : meshArr) mesh->draw();
	}
private:
	vector<ofMesh*> meshArr;
	vector<double> uvcoords = { 0, 0, 1, 0, 1, 1, 0, 1 };
	vector<double> v1, v2, v3, v4, v5, v6;
	ofIndexType indices[6] = { 0, 1, 2, 2, 3, 0 };
	glm::vec3 centerPos;
	float w, h, d;
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
	ofMesh mesh;
	ofShader shader;
	MappedCube cube;
	
	ofxPanel gui;
	ofParameter<bool> enableDepthTest;
	ofParameter<float> rcThreshold;
	
};
