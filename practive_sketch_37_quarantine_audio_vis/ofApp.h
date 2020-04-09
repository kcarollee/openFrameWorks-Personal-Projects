#pragma once

#include "ofMain.h"
#include "Camera.h"
class CShape {
public:
	CShape(int sideFaceNum, const glm::vec3& centerPos, float radius, float width, float height) : 
		sideFaceNum(sideFaceNum), centerPos(centerPos), radius(radius), width(width), height(height){
		degInc = TWO_PI / (float)sideFaceNum;
		for (int i = 0; i < sideFaceNum; i++){
			ofMesh* mesh = new ofMesh;
			buildQuad(*mesh, -i * degInc);
			quadArr.push_back(mesh);
		}
		initY = centerPos.y;
	}

	// deg: starting (left) degree
	// floor lies on the xz plane. 
	void buildQuad(ofMesh& mesh, float deg) {
		float uvcoords[8] = { 0, 1, 1, 1, 0, 0, 1, 0 };
		ofIndexType indices[6] = { 0, 1, 3, 3, 2, 0 };
		mesh.addVertex(glm::vec3(centerPos.x + radius * cos(deg), centerPos.y + height * 0.5, centerPos.z + radius * sin(deg)));
		mesh.addVertex(glm::vec3(centerPos.x + radius * cos(deg - degInc), centerPos.y + height * 0.5, centerPos.z + radius * sin(deg - degInc)));
		mesh.addVertex(glm::vec3(centerPos.x + radius * cos(deg), centerPos.y - height * 0.5, centerPos.z + radius * sin(deg)));
		mesh.addVertex(glm::vec3(centerPos.x + radius * cos(deg - degInc), centerPos.y - height * 0.5, centerPos.z + radius * sin(deg - degInc)));

		for (int i = 0; i < 4; i++) mesh.addTexCoord(glm::vec2(uvcoords[i * 2], uvcoords[i * 2 + 1]));
		mesh.addIndices(indices, 6);
	}
	
	

	void resetRadius(float newRadius) {
		for (int i = 0; i < sideFaceNum; i++) {
			quadArr[i]->setVertex(0, glm::vec3(centerPos.x + newRadius * cos(-i * degInc), centerPos.y + height * 0.5, centerPos.z + newRadius * sin(-i * degInc)));
			quadArr[i]->setVertex(1, glm::vec3(centerPos.x + newRadius * cos(-(i+1) * degInc), centerPos.y + height * 0.5, centerPos.z + newRadius * sin(-(i + 1) * degInc)));
			quadArr[i]->setVertex(2, glm::vec3(centerPos.x + newRadius * cos(-i * degInc), centerPos.y - height * 0.5, centerPos.z + newRadius * sin(-i * degInc)));
			quadArr[i]->setVertex(3, glm::vec3(centerPos.x + newRadius * cos(-(i + 1) * degInc), centerPos.y - height * 0.5, centerPos.z + newRadius * sin(-(i + 1) * degInc)));
		}
	}

	void resetQuadYpos(float newPos, int index) {
		quadArr[index]->setVertex(0, glm::vec3(quadArr[index]->getVertex(0).x, newPos + height * 0.5, quadArr[index]->getVertex(0).z));
		quadArr[index]->setVertex(1, glm::vec3(quadArr[index]->getVertex(1).x, newPos + height * 0.5, quadArr[index]->getVertex(1).z));
		quadArr[index]->setVertex(2, glm::vec3(quadArr[index]->getVertex(2).x, newPos - height * 0.5, quadArr[index]->getVertex(2).z));
		quadArr[index]->setVertex(3, glm::vec3(quadArr[index]->getVertex(3).x, newPos - height * 0.5, quadArr[index]->getVertex(3).z));
	}
	
	void draw() {
		for (auto q : quadArr) { q->draw(); }
	}

	void selectQuadToColor(ofShader& shader, int index) {
		for (int i = 0; i < sideFaceNum; i++) {
			if (i == index) shader.setUniform1i("isColored", true);
			else shader.setUniform1i("isColored", true);
		}
	}

	void drawWithTexture(const ofShader& shader, const vector<ofImage*>& textureArr, int shift, int mod, int colqindex) {
		int index;
		int rand = (int)ofRandom(0, 5);
		for (int i = 0; i < sideFaceNum; i++) {
			// selecting a quad that's to be of diff color
			if (i == colqindex || i == (colqindex + sideFaceNum / 4) % sideFaceNum ||
				i == (colqindex + sideFaceNum / 2) % sideFaceNum || 
				i == (colqindex + sideFaceNum * 3 / 4) % sideFaceNum) shader.setUniform1i("isColored", true);
			else shader.setUniform1i("isColored", false);
			index = (i + shift + mod * rand) % textureArr.size();
			shader.setUniformTexture("texture", textureArr[textureArr.size() - index - 1]->getTexture(), 0);
			quadArr[i]->draw();
		}

	}
public:
	int sideFaceNum;
	float degInc, radius, width, height, initY;
	glm::vec3 centerPos;
	vector<ofMesh*> quadArr;
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
	ofShader WallShader, FboShader;
	Camera camera;
	vector<CShape*> shapeArr;
	vector<ofImage*> textureImgArr;

	glm::mat4 sketchMvp, sketchModel, sketchView, sketchProj;

	int shapeNum, sideFaceNum;
	float initRadius;
	int moveMode;

	ofSoundPlayer track;
	int bandNum;
	float *fftSmooth;

	bool audioVisMode;

	ofFbo fbo;
	ofMesh fboMesh;

	string audioVisState, modeState;
};
