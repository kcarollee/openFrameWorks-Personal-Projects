#pragma once

#include "ofMain.h"
#include "Camera.h"


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
	void addColor(ofImage& image) {
		for (int i = 0; i < hnum + 1; i++) {
			for (int j = 0; j < wnum + 1; j++) {
				mesh.addColor(image.getColor(j, hnum - i));
			}
		}
	}

	void setColor(ofImage& image) {
		for (int i = 0; i < hnum + 1; i++) {
			for (int j = 0; j < wnum + 1; j++) {
				mesh.setColor(i * (wnum + 1) + j, image.getColor(j, hnum - i));
			}
		}
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
		void generateNoiseTexture(ofImage& noiseImg, float width, float height);
public:
	glm::mat4 model, view, proj, mvp;
	ofMesh quad;
	ofShader TestShader;
	ofTexture noiseTexture;
	ofImage noiseImg;
	PlaneMesh plane, ceiling;
	int greyScaleMode;

	Camera camera;
	bool alterZOffset;

	ofSoundPlayer track;
};
