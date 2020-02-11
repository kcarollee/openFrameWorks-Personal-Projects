#pragma once

#include "ofMain.h"
using namespace glm;

typedef struct Camera {
	glm::vec3 position;
	float fov, rotateDeg, rotateDegHori, rotateDegVert;
	bool forward, backward, rotateLeft, rotateRight, rotateUp, rotateDown;
};

class CustomPoly {
public:
	void setup(int res, float width, float gapLength, vec3 startPoint) {
		this->resolution = res; this->startPoint = startPoint; this->width = width; this->gapLength = gapLength;
		height = 0;
		mesh.addVertex(startPoint);
		mesh.addTexCoord(vec2(uvcoords[0], uvcoords[1]));
		for (int i = 1; i < res + 1; i++) {
			mesh.addVertex(vec3(startPoint.x + width * cos(2.0f * PI / res * i),
				startPoint.y - gapLength,
				startPoint.z + width * sin(2.0f * PI / res * i)));
			if (i % 2 == 0) mesh.addTexCoord(vec2(uvcoords[2], uvcoords[3]));
			else if (i % 2 == 1) mesh.addTexCoord(vec2(uvcoords[4], uvcoords[5]));
		}
		for (int i = 0; i < res / 2; i++) {
			ofIndexType indices[6] = { 0, i * 2 + 1, i * 2 + 2, i * 2 + 2, (i * 2 + 3) % res, 0 };
			vec3 normal1 = normalize(cross(mesh.getVertex(indices[1]) - mesh.getVertex(indices[0]), 
				mesh.getVertex(indices[2]) - mesh.getVertex(indices[0])));

			vec3 normal2 = normalize(cross(mesh.getVertex(indices[4]) - mesh.getVertex(indices[3]),
				mesh.getVertex(indices[5]) - mesh.getVertex(indices[3])));
			for (int j = 0; j < 3; j++) { mesh.addNormal(normal1); }
			for (int j = 0; j < 3; j++) { mesh.addNormal(normal2); }
			mesh.addIndices(indices, 6);
		}
		grow = true;
		viewNormals = false;
		layerNum = 1;
		lifeSpan = ofRandom(6, 12);
		creationTime = ofGetElapsedTimef();
		colorOffset = vec4(ofRandom(0, 1), ofRandom(0, 1), ofRandom(0, 1), 1.0);
	}

	void addVertices(float movementWidthx, float movementWidthz) {
		float centerx = startPoint.x + movementWidthx * cos(ofGetElapsedTimef());
		float centerz = startPoint.z + movementWidthz * sin(ofGetElapsedTimef());
		if (layerNum % 2 == 1) {
			for (int i = 1; i < resolution + 1; i++) {
				float vertx = (centerx)+width * cos(2.0f * PI / resolution * i),
					verty = startPoint.y - gapLength * layerNum,
					vertz = centerz + width * sin(2.0f * PI / resolution * i);
				mesh.addVertex(vec3(vertx, verty, vertz));

				if (i % 2 == 0) mesh.addTexCoord(vec2(uvcoords[0], uvcoords[1]));
				else if (i % 2 == 1) mesh.addTexCoord(vec2(uvcoords[6], uvcoords[7]));
			}
		}
		else {
			for (int i = 1; i < resolution + 1; i++) {
				float vertx = (centerx)+width * cos(2.0f * PI / resolution * i),
					verty = startPoint.y - gapLength * layerNum,
					vertz = centerz + width * sin(2.0f * PI / resolution * i);
				mesh.addVertex(vec3(vertx, verty, vertz));	
				if (i % 2 == 0) mesh.addTexCoord(vec2(uvcoords[2], uvcoords[3]));
				else if (i % 2 == 1) mesh.addTexCoord(vec2(uvcoords[4], uvcoords[5]));
			}
		}
		int start = (layerNum - 1) * resolution + 1;
		for (int i = 0; i < resolution; i++) {
			ofIndexType indices[6] = { start + i, i == resolution - 1 ? start : start + i + 1,i == resolution - 1 ? start + resolution : start + i + 1 + resolution,
				i == resolution - 1 ? start + resolution : start + i + 1 + resolution, start + i + resolution, start + i };
			
			// this is all so messed up wtf
			vec3 normal1 = normalize(cross(mesh.getVertex(indices[2]) - mesh.getVertex(indices[0]),
				mesh.getVertex(indices[1]) - mesh.getVertex(indices[0])));
			vec3 normal2 = normalize(cross(mesh.getVertex(indices[3]) - mesh.getVertex(indices[5]),
				mesh.getVertex(indices[4]) - mesh.getVertex(indices[5])));
			for (int j = 0; j < 3; j++) { mesh.addNormal(normal1); }
			for (int k = 0; k < 3; k++) { mesh.addNormal(normal2); }
			
			mesh.addIndices(indices, 6);
		}
		layerNum++;
	}

	void setMode(ofPrimitiveMode mode) {mesh.setMode(mode);}
	ofPrimitiveMode getMode() {return mesh.getMode();}
	void draw() {
		if (viewNormals) {
			for (int i = 0; i < mesh.getNumVertices(); i++) {
				ofMesh normLine;
				normLine.addVertex(mesh.getVertex(i));
				normLine.addVertex((mesh.getVertex(i) + mesh.getNormal(i) / 30.0f));
				normLine.setMode(OF_PRIMITIVE_LINES);
				normLine.draw();
			}
		}
		mesh.draw();
	}


public:
	int resolution, height, layerNum;
	float width, gapLength;
	vec3 startPoint;
	ofMesh mesh;
	bool grow, stop, viewNormals;
	float uvcoords[8] = { 0, 0, 0, 1, 1, 1, 1, 0 };
	float lifeSpan, creationTime;
	vec4 colorOffset;
	int positionInDeque;
};
class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

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
public:
	int resDivFour;
	CustomPoly customPoly;
	ofShader polyShader;
	deque<CustomPoly*> customPolyArr;

	Camera camera;
	mat4 model, view, proj, mvp;
};
