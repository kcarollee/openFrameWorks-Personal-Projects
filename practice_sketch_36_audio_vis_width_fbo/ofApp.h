#pragma once

#include "ofMain.h"
#include "Camera.h"
using namespace glm;
class RectBox {
public:
	RectBox(const vec3& pos, float width, float height, float depth):
		pos(pos), width(width), height(height), depth(depth){
		vertArr.push_back(pos);
		vertArr.push_back(vec3(pos.x + width, pos.y, pos.z));
		vertArr.push_back(vec3(pos.x, pos.y - height, pos.z));
		vertArr.push_back(vec3(pos.x + width, pos.y - height, pos.z));
		vertArr.push_back(vec3(pos.x, pos.y, pos.z - depth));
		vertArr.push_back(vec3(pos.x + width, pos.y, pos.z - depth));
		vertArr.push_back(vec3(pos.x, pos.y - height, pos.z - depth));
		vertArr.push_back(vec3(pos.x + width, pos.y - height, pos.z - depth));

		floorCenter = vec2(pos.x + width * 0.5, pos.y - height * 0.5);
		floorCenterDist = glm::distance(floorCenter, vec2(0.0));
	}
	
	
	void setQuadTexCoords(const float* texCoords) {
		this->texCoords = texCoords;
	}

	void addQuadTexCoords() {
		for (int i = 0; i < 4; i++) {
			mesh.addTexCoord(vec2(*(texCoords + i * 2), *(texCoords + i * 2 + 1)));
		}
	}
	void addNormals(int mode) {
		float normArr[15] = {
			0, 0, 1, // ceiling
			-1, 0, 0, // left
			1, 0, 0, // right
			0, -1, 0, // front
			0, 1, 0 // back
		};
		vec3 normal = vec3(normArr[mode * 3], normArr[mode * 3 + 1], normArr[mode * 3 + 2]);
		for (int i = 0; i < 4; i++){
			mesh.addNormal(normal); // left
		}
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
		addNormals(0);
		// left indices: 4 5 6 7, verts: 0 2 4 6 
		mesh.addVertex(vertArr[0]);
		mesh.addVertex(vertArr[2]);
		mesh.addVertex(vertArr[4]);
		mesh.addVertex(vertArr[6]);
		ofIndexType li[6] = { 4, 5, 7, 7, 6, 4 };
		mesh.addIndices(li, 6);
		addQuadTexCoords();
		addNormals(1);
		// right indices: 8 9 10 11, verts: 3 1 7 5
		mesh.addVertex(vertArr[3]);
		mesh.addVertex(vertArr[1]);
		mesh.addVertex(vertArr[7]);
		mesh.addVertex(vertArr[5]);
		ofIndexType ri[6] = { 8, 9, 11, 11, 10, 8 };
		mesh.addIndices(ri, 6);
		addQuadTexCoords();
		addNormals(2);
		// front indices: 12 13 14 15, verts: 2 3 6 7 
		mesh.addVertex(vertArr[2]);
		mesh.addVertex(vertArr[3]);
		mesh.addVertex(vertArr[6]);
		mesh.addVertex(vertArr[7]);
		ofIndexType fi[6] = { 12, 13, 15, 15, 14, 12 };
		mesh.addIndices(fi, 6);
		addQuadTexCoords();
		addNormals(3);
		// back indices: 16 17 18 19, verts: 1 0 5 4
		mesh.addVertex(vertArr[1]);
		mesh.addVertex(vertArr[0]);
		mesh.addVertex(vertArr[5]);
		mesh.addVertex(vertArr[4]);
		ofIndexType bi[6] = { 16, 17, 19, 19, 18, 16 };
		mesh.addIndices(bi, 6);
		addQuadTexCoords();
		addNormals(4);
	}

	void changeHeight(float d) {
		for (int i = 0; i < 12; i++) {
			int vi = ceilingvertices[i];
			mesh.setVertex(vi,
				vec3(mesh.getVertex(vi).x, mesh.getVertex(vi).y, d));
		}
	}

	const vec2 &getFloorCenter() { return floorCenter; }
	const float &getFloorCenterDist() { return floorCenterDist; }

	void draw() { mesh.draw(); }
private:
	vec3 pos; // ceiling top left
	vec2 floorCenter;
	float floorCenterDist; // distance from origin to floor center
	float width, height, depth;
	ofMesh mesh;
	vector<vec3> vertArr;
	const float* texCoords;
	const int ceilingvertices[12] = { 0, 1, 2, 3, 4 ,5, 8, 9, 12, 13, 16, 17 };
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
		int rowBoxNum, widthBoxNum;
		float rectBoxw, rectBoxh, rectBoxd;
		mat4 sketchModel, sketchProj, sketchView, sketchMvp;
		
		ofShader SketchShader1, SketchShader2;
		vector<RectBox*> rectBoxArr;

		ofFbo fbo1, fbo2;
		
		bool allocateFbo;
		bool manualFbo;
		int passNum;
		Camera camera;

		ofTexture texBuffer;

		// background
		ofMesh backgroundMesh;
		ofImage noiseTex;
		// sound
		ofSoundPlayer track;
		int bandNum;
		float *fftSmooth;
		glm::vec2 center;
};
