#pragma once

#include "ofMain.h"
#include "ofxGui.h"

typedef struct Camera {
	glm::vec3 position;
	float fov, rotateDeg, rotateDegHori, rotateDegVert;
};

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
				mesh.addVertex(glm::vec3(qw * j, qh * i, 0));
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

class PlaneMeshBox {
public:
	void setup(float width, float height, float depth,
		int widthQuadNum, int heightQuadNum, int depthQuadNum, glm::vec3 centerPos) {
		this->w = width; this->h = height; this->d = depth;
		this->wnum = widthQuadNum; this->hnum = heightQuadNum; this->dnum = depthQuadNum;
		this->centerPos = centerPos;
		rotateDeg = 0;
		singlePlaneMode = false;
	}

	void buildMeshes() {
		ff.setup(w, h, wnum, hnum, glm::vec3(centerPos.x, centerPos.y, centerPos.z - d / 2.0));
		fc.setup(w, h, wnum, hnum, glm::vec3(centerPos.x, centerPos.y, centerPos.z + d / 2.0));
		fl.setup(d, h, dnum, hnum, glm::vec3(centerPos.x - w / 2.0, centerPos.y, centerPos.z));
		fr.setup(d, h, dnum, hnum, glm::vec3(centerPos.x + w / 2.0, centerPos.y, centerPos.z));
		ft.setup(w, d, wnum, dnum, glm::vec3(centerPos.x, centerPos.y + h / 2.0, centerPos.z));
		fb.setup(w, d, wnum, dnum, glm::vec3(centerPos.x, centerPos.y - h / 2.0, centerPos.z));
		ff.buildPlaneMesh();
		fc.buildPlaneMesh();
		fl.buildPlaneMesh();
		fr.buildPlaneMesh();
		ft.buildPlaneMesh();
		fb.buildPlaneMesh();
	}

	void addColor(ofImage& image) {
		ff.addColor(image);
		fc.addColor(image);
		fl.addColor(image);
		fr.addColor(image);
		ft.addColor(image);
		fb.addColor(image);
	}

	void setColor(ofImage& image) {
		ff.setColor(image);
		fc.setColor(image);
		fl.setColor(image);
		fr.setColor(image);
		ft.setColor(image);
		fb.setColor(image);
	}

	void setMode(ofPrimitiveMode mode) {
		ff.setMode(mode);
		fc.setMode(mode);
		fl.setMode(mode);
		fr.setMode(mode);
		ft.setMode(mode);
		fb.setMode(mode);
	}

	void draw(ofShader& shader, glm::mat4& model, glm::mat4& view, glm::mat4& proj, glm::mat4& mvp) {
		using namespace glm;

		model = translate(vec3(fc.centerPos.x + w / 2.0, fc.centerPos.y - h / 2.0, fc.centerPos.z)) *
			rotate(radians(-180.0f), vec3(0, 1, 0)) *
			scale(vec3(1.0));
		mvp = proj * view * model;
		shader.setUniformMatrix4f("mvp", mvp);
		fc.draw();
		
		if (!singlePlaneMode) {
			model = translate(vec3(ff.centerPos.x - w / 2.0, ff.centerPos.y - h / 2.0, ff.centerPos.z)) *
				rotate(radians(0.0f), vec3(1, 0, 0)) *
				scale(vec3(1.0));
			mvp = proj * view * model;
			shader.setUniformMatrix4f("mvp", mvp);
			ff.draw();

			model = translate(vec3(fl.centerPos.x, fl.centerPos.y - d / 2.0, fl.centerPos.z + h / 2.0)) *
				rotate(radians(90.0f), vec3(0, 1, 0)) *
				scale(vec3(1.0));
			mvp = proj * view * model;
			shader.setUniformMatrix4f("mvp", mvp);
			fl.draw();

			model = translate(vec3(fr.centerPos.x, fr.centerPos.y - d / 2.0, fr.centerPos.z - h / 2.0)) *
				rotate(radians(-90.0f), vec3(0, 1, 0)) *
				scale(vec3(1.0));
			mvp = proj * view * model;
			shader.setUniformMatrix4f("mvp", mvp);
			fr.draw();

			model = translate(vec3(ft.centerPos.x - w / 2.0, ft.centerPos.y, ft.centerPos.z - d / 2.0)) *
				rotate(radians(90.0f), vec3(1, 0, 0)) *
				scale(vec3(1.0));
			mvp = proj * view * model;
			shader.setUniformMatrix4f("mvp", mvp);
			ft.draw();

			model = translate(vec3(fb.centerPos.x - w / 2.0, fb.centerPos.y, fb.centerPos.z + d / 2.0)) *
				rotate(radians(-90.0f), vec3(1, 0, 0)) *
				scale(vec3(1.0));
			mvp = proj * view * model;
			shader.setUniformMatrix4f("mvp", mvp);
			fb.draw();
		}
	}

	
public:
	PlaneMesh ff, fc, fl, fr, ft, fb;
	float w, h, d;
	int wnum, hnum, dnum;
	glm::vec3 centerPos;
	float rotateDeg;
	bool singlePlaneMode;
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
	Camera camera;

	PlaneMeshBox planeMeshBox;
	
	ofVideoGrabber webcam;
	glm::mat4 model, view, proj, mvp;
	ofShader webcamShader;
	ofImage webcamFeed;

	bool firstIter;
	bool cameraMoved, cameraMoveForward, cameraMoveBackward, cameraLookUp, 
		cameraLookDown, cameraLookLeft, cameraLookRight;

	int toggleColor, primitiveMode;

	ofxPanel gui;
	ofParameter<float> popOut;
	ofParameter<bool> singlePlaneMode;
};
