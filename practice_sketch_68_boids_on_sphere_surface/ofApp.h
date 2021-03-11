#pragma once

#include "ofMain.h"
#define PLANE_DOMAIN_MAX 180.0
class BoidParticle2D {
	public:
		BoidParticle2D(float x, float y) {
			float vr = 1;
			this->position = glm::vec2(x, y);
			this->velocity = glm::vec2(ofRandom(-vr, vr), ofRandom(-vr, vr));
			this->acceleration = glm::vec2(0);
			this->maxForce = 0.5;
			this->maxSpeed = 1.0;
		}

		void setCoefs(float a, float c, float s) {
			this->alignCoef = a;
			this->cohesionCoef = c;
			this->separateCoef = s;
		}


		glm::vec2 getAlignmentVec(vector<BoidParticle2D*>& particleArr) {
			glm::vec2 steerVec = glm::vec2(0);
			int boidCount = 0;
			for (auto p : particleArr) {
				steerVec += p->velocity;
				boidCount++;
			}
			if (boidCount > 0) {
				steerVec /= (float)boidCount;
				steerVec = glm::normalize(steerVec) * this->maxSpeed;
				steerVec -= this->velocity;
				if (glm::length(steerVec) > this->maxForce) steerVec = glm::normalize(steerVec) * this->maxForce;
			}
			return steerVec;
		}

		glm::vec2 getCohesionVec(vector<BoidParticle2D*>& particleArr) {
			glm::vec2 steerVec = glm::vec2(0);
			int boidCount = 0;
			for (auto p : particleArr) {
				steerVec += p->position;
				boidCount++;
			}
			if (boidCount > 0) {
				steerVec /= (float)boidCount;
				steerVec -= this->position;
				steerVec = glm::normalize(steerVec) * this->maxSpeed;
				steerVec -= this->velocity;
				if (glm::length(steerVec) > this->maxForce) steerVec = glm::normalize(steerVec) * this->maxForce;
			}
			return steerVec;
		}

		glm::vec2 getSeparationVec(vector<BoidParticle2D*>& particleArr) {
			glm::vec2 steerVec = glm::vec2(0);
			int boidCount = 0;
			for (auto p : particleArr) {
				float d = ofDist(this->position.x, this->position.y,
					p->position.x, p->position.y);
				glm::vec2 otherToThis = this->position - p->position;
				otherToThis /= d * d;
				steerVec += otherToThis;
				boidCount++;
			}
			if (boidCount > 0) {
				steerVec /= (float)boidCount;
				steerVec = glm::normalize(steerVec) * this->maxSpeed;
				steerVec -= this->velocity;
				if (glm::length(steerVec) > this->maxForce) steerVec = glm::normalize(steerVec) * this->maxForce;
			}
			return steerVec;
		}

		void flock(vector<BoidParticle2D*>& particleArr) {
			glm::vec2 alignment = this->getAlignmentVec(particleArr);
			glm::vec2 cohesion = this->getCohesionVec(particleArr);
			glm::vec2 separation = this->getSeparationVec(particleArr);

			alignment *= this->alignCoef;
			cohesion *= this->cohesionCoef;
			separation *= this->separateCoef;

			this->acceleration += alignment + cohesion + separation;
		}

		void update() {
			this->position += this->velocity;
			this->velocity += this->acceleration;
			if (glm::length(this->velocity) > this->maxSpeed) this->velocity = glm::normalize(this->velocity) * this->maxSpeed;

			if (this->position.x > PLANE_DOMAIN_MAX) this->position.x = -PLANE_DOMAIN_MAX;
			if (this->position.x < -PLANE_DOMAIN_MAX) this->position.x = PLANE_DOMAIN_MAX;
			if (this->position.y > PLANE_DOMAIN_MAX) this->position.y = -PLANE_DOMAIN_MAX;
			if (this->position.y < -PLANE_DOMAIN_MAX) this->position.y = PLANE_DOMAIN_MAX;

			this->acceleration *= 0;
		}
	public:
		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec2 acceleration;
		float maxForce, maxSpeed;
		float alignCoef, cohesionCoef, separateCoef;

		vector<BoidParticle2D*> nearestNeighbors;
};

class QuadTree {
	public:
		QuadTree(glm::vec2 topLeft, glm::vec2 bottomRight) {
			this->topLeft = topLeft;
			this->bottomRight = bottomRight;
			this->halfWidthPos = (this->topLeft.x + this->bottomRight.x) * 0.5;
			this->halfHeightPos = (this->topLeft.y + this->bottomRight.y) * 0.5;
			this->halfWidth = abs(this->bottomRight.x - this->topLeft.x) * 0.5;
			this->halfHeight = abs(this->bottomRight.y - this->topLeft.y) * 0.5;

			this->accuracy = 10;
			this->searchDepth = 2;

			this->topLeftTree = NULL;
			this->topRightTree = NULL;
			this->bottomLeftTree = NULL;
			this->bottomRightTree = NULL;

			this->parent = NULL;
			this->n = NULL;
		}

		void searchNeighbors(QuadTree* treePtr, vector<BoidParticle2D*>& neighbors, BoidParticle2D* startingNode) {
			if (treePtr == NULL) return;
			if (treePtr->n == NULL && treePtr->isLeafNode()) return;
			if (treePtr->n != NULL) {
				if (treePtr->n == startingNode) return;
				neighbors.push_back(treePtr->n);
				return;
			}
			searchNeighbors(treePtr->topLeftTree, neighbors, startingNode);
			searchNeighbors(treePtr->topRightTree, neighbors, startingNode);
			searchNeighbors(treePtr->bottomLeftTree, neighbors, startingNode);
			searchNeighbors(treePtr->bottomRightTree, neighbors, startingNode);
		}

		QuadTree* getTreeByDepth(int searchDepth, QuadTree* treePtr) {
			if (searchDepth == 0) return treePtr;
			if (treePtr != NULL) {
				treePtr = treePtr->parent;
				getTreeByDepth(--searchDepth, treePtr);
			}
		}

		void insert(BoidParticle2D* node) {
			if (node == NULL) return;
			if (abs(this->topLeft.x - this->bottomRight.x) <= this->accuracy &&
				abs(this->topLeft.y - this->bottomRight.y) <= this->accuracy) {
				if (this->n == NULL) {
					this->n = node;
					this->n->nearestNeighbors.clear();
					QuadTree* tempTree = this->getTreeByDepth(this->searchDepth, this);
					this->searchNeighbors(tempTree, this->n->nearestNeighbors, this->n);
				}
				return;
			}

			// if the node is in the left side of the given space
			if (this->halfWidthPos >= node->position.x) {
				// top left
				if (this->halfHeightPos >= node->position.y) {
					glm::vec2 tl = this->topLeft;
					glm::vec2 br = glm::vec2(this->halfWidthPos, this->halfHeightPos);
					if (this->topLeftTree == NULL) {
						this->topLeftTree = new QuadTree(tl, br);
						ofNoFill();
						ofDrawRectangle(tl, 0.5 * (br.x - tl.x), 0.5 * (br.x - tl.x));
						ofFill();
						this->topLeftTree->parent = this;
					}
					this->topLeftTree->insert(node);
				}
				// bottom left
				else {
					glm::vec2 tl = glm::vec2(this->topLeft.x, this->halfHeightPos);
					glm::vec2 br = glm::vec2(this->halfWidthPos, this->bottomRight.y);
					if (this->bottomLeftTree == NULL) {
						this->bottomLeftTree = new QuadTree(tl, br);
						ofNoFill();
						ofDrawRectangle(tl, (br.x - tl.x), (br.x - tl.x));
						ofFill();
						this->bottomLeftTree->parent = this;
					}
					this->bottomLeftTree->insert(node);
				}
			}
			// if the node is in the right side of the given space
			else {
				// top right
				if (this->halfHeightPos >= node->position.y) {
					glm::vec2 tl = glm::vec2(this->halfWidthPos, this->topLeft.y);
					glm::vec2 br = glm::vec2(this->bottomRight.x, this->halfHeightPos);
					if (this->topRightTree == NULL) {
						this->topRightTree = new QuadTree(tl, br);
						ofNoFill();
						ofDrawRectangle(tl, (br.x - tl.x), (br.x - tl.x));
						ofFill();
						this->topRightTree->parent = this;
					}
					this->topRightTree->insert(node);
				}
				// bottom right
				else {
					glm::vec2 tl = glm::vec2(this->halfWidthPos, this->halfHeightPos);
					glm::vec2 br = this->bottomRight;
					if (this->bottomRightTree == NULL) {
						this->bottomRightTree = new QuadTree(tl, br);
						ofNoFill();
						ofDrawRectangle(tl, (br.x - tl.x), (br.x - tl.x));
						ofFill();
						this->bottomRightTree->parent = this;
					}
					this->bottomRightTree->insert(node);
				}
			}
		}

		void drawTree(int mode, glm::vec2 pos, float w) {
			ofNoFill();
			ofDrawRectangle(pos, w, w);
			ofFill();
		}
		bool isLeafNode() {
			return this->topLeftTree == NULL && this->topRightTree == NULL &&
				this->bottomLeftTree == NULL && this->bottomRightTree == NULL;
		}

		void reset(QuadTree* tree) {
			if (tree == NULL) return;
			reset(tree->topLeftTree);
			reset(tree->topRightTree);
			reset(tree->bottomLeftTree);
			reset(tree->bottomRightTree);
			delete tree;
		}

		
	public:

		glm::vec2 topLeft, bottomRight;
		QuadTree* parent;
		QuadTree* topLeftTree;
		QuadTree* topRightTree;
		QuadTree* bottomLeftTree;
		QuadTree* bottomRightTree;

		float halfWidthPos, halfHeightPos;
		float halfWidth, halfHeight;
		float accuracy;
		int searchDepth;

		BoidParticle2D* n;

		
};

class FishBoid {
public:
	FishBoid(float x, float y, float z) {
		this->posNum = 10;
		this->randX = ofRandom(-10, 10);
		this->randY = ofRandom(-10, 10);
		this->randZ = ofRandom(-10, 10);
		this->gapDist = 20;
		this->bodyLine = new ofMesh;
		this->bodyLine->setMode(OF_PRIMITIVE_LINE_STRIP);
		this->headPos = glm::vec3(x, y, z);
		this->noiseCoef = 0.025;
		this->vel = 0.2;

		this->timeInterval = 1;

		this->t1 = ofRandom(0, 360);
		this->t2 = ofRandom(0, 360);

		this->bodyLine->addVertex(this->headPos);
		this->bodyLine->addIndex(0);
		
	}

	void pushNewVertex(glm::vec3 pos) {
		this->bodyLine->addVertex(pos);
		this->bodyLine->addIndex(this->bodyLine->getVertices().size() - 1);
		if (this->bodyLine->getVertices().size() > this->posNum) {
			this->bodyLine->getVertices().erase(this->bodyLine->getVertices().begin());	
		}
	}

	void display(ofMaterial& mat) {
		mat.end();
		//this->bodyLine->draw();
		glm::vec3 prevPos = this->headPos;
		if (this->bodyLine->getVertices().size() > 1) {
			for (int i = 1; i < this->bodyLine->getVertices().size(); i++) {
				if (i == this->bodyLine->getVertices().size() - 1) {
					//ofDrawBox(this->bodyLine->getVertices()[i], 5);
					mat.begin();
					glm::vec3 curPos = glm::vec3(this->bodyLine->getVertex(i).x, this->bodyLine->getVertex(i).y, this->bodyLine->getVertex(i).z);
					glm::vec3 halfVec = glm::normalize(prevPos + curPos);

					//ofDrawBox(this->bodyLine->getVertex(i), 30);
					//ofSetColor(100, 60);
					ofPushMatrix();
					ofTranslate(this->bodyLine->getVertex(i));
					ofRotateDeg(180, halfVec.x, halfVec.y, halfVec.z);
					ofDrawBox(glm::vec3(0), 2);
					ofPopMatrix();
					mat.end();
					
				}
				else {
					glm::vec3 curPos = glm::vec3(this->bodyLine->getVertex(i).x, this->bodyLine->getVertex(i).y, this->bodyLine->getVertex(i).z);
					glm::vec3 halfVec = glm::normalize(prevPos + curPos);

					ofPushMatrix();

					ofTranslate(this->bodyLine->getVertex(i));
					//ofRotateX(ofGetElapsedTimef() * 2.0 + i);
					ofRotateDeg(180, halfVec.x, halfVec.y, halfVec.z);
					ofRotateX((ofGetElapsedTimef() + i) * 10);
					float s = 0.5;
					float d = 10;
					ofDrawBox(glm::vec3(0), s, d * sin(ofGetElapsedTimef() * 2.0 + i * 0.5), s);
					ofPopMatrix();

					prevPos = curPos;
				}
			}
		}
	}
public:
	int posNum;
	float randX, randY, randZ;
	float gapDist; // distance between each vertices
	float noiseCoef; // lesser the coef, lesser the noise
	float vel;
	float t1, t2; // angles
	int timeInterval;
	glm::vec3 headPos;
	vector<glm::vec3> posArr;
	ofMesh* bodyLine;
};


class Flock {
	public:
		Flock(int boidNum, float radius) {
			this->boidNum = boidNum;
			this->flatFlockMesh = new ofMesh;
			this->flatFlockMesh->setMode(OF_PRIMITIVE_POINTS);
			this->radius = radius;
			this->mode = 0;
			for (int i = 0; i < this->boidNum; i++) {
				BoidParticle2D* tp = new BoidParticle2D(ofRandom(-PLANE_DOMAIN_MAX, PLANE_DOMAIN_MAX), ofRandom(-PLANE_DOMAIN_MAX, PLANE_DOMAIN_MAX));
				particleArr.push_back(tp);
				this->flatFlockMesh->addVertex(glm::vec3(tp->position.x, tp->position.y, 0));
				this->flatFlockMesh->addIndex(i);

				glm::vec3 fPos = this->getPosFromAngles(this->flatFlockMesh->getVertex(i).x, (this->flatFlockMesh->getVertex(i).y), this->radius);
				FishBoid* tf = new FishBoid(fPos.x, fPos.y, fPos.z);
				this->fishBoidArr.push_back(tf);
			}


			
			this->neighborSearchTree = new QuadTree(glm::vec2(-PLANE_DOMAIN_MAX, -PLANE_DOMAIN_MAX),
				glm::vec2(PLANE_DOMAIN_MAX, PLANE_DOMAIN_MAX));
			for (int i = 0; i < this->boidNum; i++) {
				this->neighborSearchTree->insert(particleArr[i]);
			}

			this->color.set(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
			this->mat.setAmbientColor(this->color);
			this->mat.setDiffuseColor(this->color);
		}

		void update() {


			for (int i = 0; i < this->boidNum; i++) {
				particleArr[i]->update();
				// inefficient circular search
				/*
				vector<BoidParticle2D*> nearestNeighbors;
				for (int j = 0; j < this->boidNum; j++) {
					if (j != i && ofDist(particleArr[i]->position.x, particleArr[i]->position.y,
						particleArr[j]->position.x, particleArr[j]->position.y) < PLANE_DOMAIN_MAX * 0.5) {
						nearestNeighbors.push_back(particleArr[j]);
					}
				}
				*/
				particleArr[i]->flock(particleArr[i]->nearestNeighbors);
				switch (mode % 3) {
					case 0:
						this->flatFlockMesh->setVertex(i, 
							glm::vec3(ofMap(particleArr[i]->position.x, -PLANE_DOMAIN_MAX, PLANE_DOMAIN_MAX, -180, 180),
								ofMap(particleArr[i]->position.y, -PLANE_DOMAIN_MAX, PLANE_DOMAIN_MAX, -180, 180), 0));

						break;
					case 1:
						this->flatFlockMesh->setVertex(i, glm::vec3(this->getPosFromAngles(particleArr[i]->position.x, particleArr[i]->position.y, this->radius)));
						break;
					case 2:
						this->flatFlockMesh->setVertex(i, glm::vec3(this->getPosFromAngles(particleArr[i]->position.x, particleArr[i]->position.y, this->radius)));
						break;
				}
				
				
				//nearestNeighbors.clear();
			}


			
		

			
		}

		glm::vec3 getPosFromAngles(float t1, float t2, float r) {
			/*
			t1 *= 18.0 / PLANE_DOMAIN_MAX * 0.1;
			t2 *= 18.0 / PLANE_DOMAIN_MAX * 0.1;
			*/
			t1 = ofMap(t1, -PLANE_DOMAIN_MAX, PLANE_DOMAIN_MAX, -PI, PI);
			t2 = ofMap(t2, -PLANE_DOMAIN_MAX, PLANE_DOMAIN_MAX, -PI, PI);
			float x = r * cos(t1) * cos(t2);
			float y = r * sin(t1) * cos(t2);
			float z = r * sin(t2);
			return glm::vec3(x, y, z);
		}

		void setCoefs(float a, float c, float s) {
			for (auto p : particleArr) {
				p->setCoefs(a, c, s);
			}
		}

		void display() {
			this->neighborSearchTree->reset(this->neighborSearchTree);
			this->neighborSearchTree = new QuadTree(glm::vec2(-PLANE_DOMAIN_MAX, -PLANE_DOMAIN_MAX),
				glm::vec2(PLANE_DOMAIN_MAX, PLANE_DOMAIN_MAX));
			for (int i = 0; i < this->boidNum; i++) {
				this->neighborSearchTree->insert(particleArr[i]);
			}
			if (this->mode % 3 == 2) {
				this->mat.begin();
				
			}
			else ofSetColor(this->color);
			//ofSetColor(this->color);
			switch (this->mode % 3) {
				case 0:
					this->flatFlockMesh->draw();
					break;
				case 1:
					this->flatFlockMesh->draw();
					break;
				case 2:
					ofSetColor(this->color, 100);
					for (int i = 0; i < this->flatFlockMesh->getVertices().size(); i++) {
						this->fishBoidArr[i]->pushNewVertex(this->flatFlockMesh->getVertex(i));
						this->fishBoidArr[i]->display(this->mat);
					}
					break;
			}
			if (this->mode % 3 == 2) {
				this->mat.end();
				
			}
		}
	public:
		vector<BoidParticle2D*> particleArr;
		vector<FishBoid*> fishBoidArr;
		ofMesh* flatFlockMesh;
		ofMesh* sphericalFlockMesh;
		int boidNum;
		int mode;
		float radius;
		QuadTree* neighborSearchTree;
		ofColor color;
		ofMaterial mat;
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
		Flock* testFlock;
		vector<Flock*> flockArr;
		ofEasyCam cam;
		ofShader sketchShader;
		ofLight light;

		ofFbo* frameBuffer;
		vector<ofTexture> textureArr;
		int textureNum;

		float cubeDiv;

		ofPlanePrimitive sketchPlane;
};
