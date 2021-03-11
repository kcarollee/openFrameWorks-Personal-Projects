#pragma once

#include "ofMain.h"
#include "ofxGui.h"
class Octree;
class BoidParticle {
public:
	BoidParticle(float x, float y, float z) {
		float vr = 10;
		float ar = 1;
		this->position = glm::vec3(x, y, z);
		this->velocity = glm::vec3(ofRandom(-vr, vr), ofRandom(-vr, vr), ofRandom(-vr, vr));
		//cout << this->velocity << endl;
		this->acceleration = glm::vec3( 0);
		this->maxForce = 0.2;
		this->maxSpeed = 3.0;

		this->alignRadius = 25;
		this->separationRadius = 24;
		this->cohesionRadius = 50;

		//this->treePtr = NULL;
	}

	void setCoefs(float a, float c, float s) {
		this->alignCoef = a;
		this->cohesionCoef = c;
		this->separateCoef = s;
	}

	void update() {
		this->position += this->velocity;
		this->velocity += this->acceleration;
		if (glm::length(this->velocity) > this->maxSpeed) this->velocity = glm::normalize(this->velocity) * this->maxSpeed;
		
		
		int dim = 598;
		
		
		if (this->position.x < - dim * 0.5) this->position.x = + dim * 0.5;
		if (this->position.x > + dim * 0.5) this->position.x = - dim * 0.5;
		if (this->position.y <  - dim * 0.5) this->position.y =  + dim * 0.5;
		if (this->position.y >  + dim * 0.5) this->position.y =  - dim * 0.5;
		if (this->position.z <  - dim * 0.5) this->position.z =  + dim * 0.5;
		if (this->position.z >  + dim * 0.5) this->position.z =  - dim * 0.5;

		
		
		// fountain-like pos update
		/*
		if (ofDist(this->position.x, this->position.y, this->position.z, 0, 0, 0) > 300) {
			this->velocity -= this->position;
		}
		
		this->acceleration *= 0;
		*/
	}

	void reset() {

	}

	void flock(vector<BoidParticle*>& particleArr) {
		glm::vec3 alignment = this->getAlignmentVec(particleArr);
		glm::vec3 cohesion = this->getCohesionVec(particleArr);
		glm::vec3 separation = this->getSeparationVec(particleArr);

		alignment *= this->alignCoef;
		cohesion *= this->cohesionCoef;
		separation *= this->separateCoef;

		this->acceleration += alignment + cohesion + separation;
	}

	glm::vec3 getAlignmentVec(vector<BoidParticle*>& particleArr) {
		// avgVel = steering force
		glm::vec3 avgVel = glm::vec3(.0);
		int boidCount = 0;
		bool flag = false;
		/*
		for (auto p : particleArr) {
			float d = ofDist(this->position.x, this->position.y, this->position.z,
				p->position.x, p->position.y, p->position.z);
			if (p != this &&  d < this->alignRadius) {
				avgVel += p->velocity;
				boidCount++;
			}
		}
		*/
		for (auto p : particleArr) {
			avgVel += p->velocity;
			boidCount++;
		}
		if (boidCount > 0) {
			avgVel /= (float)boidCount;
			avgVel = glm::normalize(avgVel) * this->maxSpeed;
			avgVel -= this->velocity;
			if (glm::length(avgVel) > this->maxForce) avgVel = glm::normalize(avgVel) * this->maxForce;
		}
		return avgVel;
	}

	glm::vec3 getCohesionVec(vector<BoidParticle*>& particleArr) {
		// avgVel = steering force
		glm::vec3 avgVel = glm::vec3(.0);

		int boidCount = 0;
		/*
		for (auto p : particleArr) {
			float d = ofDist(this->position.x, this->position.y, this->position.z,
				p->position.x, p->position.y, p->position.z);
			if (p != this && d < this->cohesionRadius) {
				avgVel += p->position;
				boidCount++;
			}
		}
		*/
		for (auto p : particleArr) {
			avgVel += p->position;
			boidCount++;
		}
		if (boidCount > 0) {
			avgVel /= (float)boidCount;
			avgVel -= this->position;
			avgVel = glm::normalize(avgVel) * this->maxSpeed;
			avgVel -= this->velocity;
			if (glm::length(avgVel) > this->maxForce) avgVel = glm::normalize(avgVel) * this->maxForce;
		}
		return avgVel;
	}

	glm::vec3 getSeparationVec(vector<BoidParticle*>& particleArr) {
		// avgVel = steering force
		glm::vec3 avgVel = glm::vec3(.0);

		int boidCount = 0;
		/*
		for (auto p : particleArr) {
			float d = ofDist(this->position.x, this->position.y, this->position.z,
				p->position.x, p->position.y, p->position.z);
			if (p != this && d < this->separationRadius) {
				boidCount++;
				glm::vec3 otherToThis = this->position - p->position;
				otherToThis /= d * d;
				avgVel += otherToThis;
			}
		}
		*/
		for (auto p : particleArr) {
			float d = ofDist(this->position.x, this->position.y, this->position.z,
				p->position.x, p->position.y, p->position.z);
			boidCount++;
			glm::vec3 otherToThis = this->position - p->position;
			otherToThis /= d * d;
			avgVel += otherToThis;
		}
		if (boidCount > 0) {
			avgVel /= (float)boidCount;
			avgVel = glm::normalize(avgVel) * this->maxSpeed;
			avgVel -= this->velocity;
			if (glm::length(avgVel) > this->maxForce) avgVel = glm::normalize(avgVel) * this->maxForce;
		}
		return avgVel;
	}

	void applyRandomForce(glm::vec3 randomForce) {
		this->velocity += randomForce;
	}
	void display() {

	}
	public:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	float maxForce;
	float maxSpeed;
	float alignRadius;
	float cohesionRadius;
	float separationRadius;
	float alignCoef, cohesionCoef, separateCoef;

	vector<BoidParticle*> nearestNeighbors;
	Octree* treePtr;
};



class Octree {
	public:
		Octree(glm::vec3 top0, glm::vec3 bottom3) {
			this->top0 = top0; // top back left
			this->bottom3 = bottom3; // bottom front right
			this->halfWidthPos = (this->top0.x + this->bottom3.x) * 0.5;
			this->halfHeightPos = (this->top0.y + this->bottom3.y) * 0.5;
			this->halfDepthPos = (this->top0.z + this->bottom3.z) * 0.5;

			this->halfWidth = abs(this->bottom3.x - this->top0.x) * 0.5;
			this->halfHeight = abs(this->bottom3.y - this->top0.y) * 0.5;
			this->halfDepth= abs(this->bottom3.z - this->top0.z) * 0.5;

			this->accuracy = 50;
			this->searchDepth = 2;
			this->drawMode = false;
			t0Tree = NULL;
			t1Tree = NULL;
			t2Tree = NULL;
			t3Tree = NULL;

			b0Tree = NULL;
			b1Tree = NULL;
			b2Tree = NULL;
			b3Tree = NULL;

			parent = NULL;

			
		}


		~Octree() {
			 
		}
		void resetAccuracy(float acc){this->accuracy = acc;}
		void reset(Octree* tree) {
			
			if (tree == NULL) return;
			reset(tree->t0Tree);
			reset(tree->t1Tree);
			reset(tree->t2Tree);
			reset(tree->t3Tree);

			reset(tree->b0Tree);
			reset(tree->b1Tree);
			reset(tree->b2Tree);
			reset(tree->b3Tree);
			
			delete tree;
			

			/*
			t0Tree = NULL;
			t1Tree = NULL;
			t2Tree = NULL;
			t3Tree = NULL;

			b0Tree = NULL;
			b1Tree = NULL;
			b2Tree = NULL;
			b3Tree = NULL;
			*/
		}

		// treePtr: Octree* obtained with getTreeByDepth. We just go down from here.
		void searchNeighbors(Octree* treePtr, vector<BoidParticle*>& neighbors, BoidParticle* startingNode) {
			if (treePtr == NULL) return;
			if (treePtr->n == NULL && treePtr->isLeafNode()) return;
			if (treePtr->n != NULL) {
				if (treePtr->n == startingNode) {
					//cout << "SAME" << endl;
					return;
				}
				neighbors.push_back(treePtr->n);
				return;
			}
			searchNeighbors(treePtr->b0Tree, neighbors, startingNode);
			searchNeighbors(treePtr->b1Tree, neighbors, startingNode);
			searchNeighbors(treePtr->b2Tree, neighbors, startingNode);
			searchNeighbors(treePtr->b3Tree, neighbors, startingNode);

			searchNeighbors(treePtr->t0Tree, neighbors, startingNode);
			searchNeighbors(treePtr->t1Tree, neighbors, startingNode);
			searchNeighbors(treePtr->t2Tree, neighbors, startingNode);
			searchNeighbors(treePtr->t3Tree, neighbors, startingNode);
		}

		Octree* getTreeByDepth(int searchDepth, Octree* treePtr) {
			if (searchDepth == 0) return treePtr;
			treePtr = treePtr->parent;
			getTreeByDepth(--searchDepth, treePtr);
		}

		void insert(BoidParticle* node) {
			
			if (node == NULL) {
				//cout << "RETURN TYPE 1" << endl;
				return;
			}
			/*
			if (!isWithinBounds(node)) {
				//cout << "RETURN TYPE 2" << endl;
				return;
			}
			*/
			// return if cannot subdivide further than this
			if (abs(this->top0.x - this->bottom3.x) <= this->accuracy &&
				abs(this->top0.y - this->bottom3.y) <= this->accuracy &&
				abs(this->top0.z - this->bottom3.z) <= this->accuracy) {
				// INSERTION HAPPENS HERE
				
				if (this->n == NULL) {
					//ofDrawBox(node->position, 10);
					this->n = node;
					this->n->nearestNeighbors.clear();
					Octree* tempTree = this->getTreeByDepth(this->searchDepth, this);
					
					this->searchNeighbors(tempTree, this->n->nearestNeighbors, this->n);
					//cout << this->n->nearestNeighbors.size() << endl;
					//this->n->treePtr = this;
				}
				return;
			}
			
			// if the node is in the left side of the given space
			if (this->halfWidthPos >= node->position.x) {
				
				// top left
				if (this->halfHeightPos >= node->position.y) {
					// back top left -> t0
					if (this->halfDepthPos >= node->position.z) {
						//cout << "t0" << endl;

						glm::vec3 t0 = this->top0;
						glm::vec3 b3 = glm::vec3(this->halfWidthPos, this->halfHeightPos, this->halfDepthPos);
						if (this->t0Tree == NULL) {
							this->t0Tree = new Octree(t0, b3);
							this->t0Tree->parent = this;
						}
						if (this->drawMode) ofDrawBox((t0 + b3) * 0.5, this->halfWidth, this->halfHeight, this->halfDepth);
						this->t0Tree->insert(node);

						
					}
					// front top left -> t2
					else {
						//cout << "t2" << endl;
						glm::vec3 t0 = glm::vec3(this->top0.x, this->top0.y, this->halfDepthPos);
						glm::vec3 b3 = glm::vec3(this->halfWidthPos, this->halfHeightPos, this->bottom3.z);
						if (this->t2Tree == NULL) {
							
							this->t2Tree = new Octree(t0, b3);
							this->t2Tree->parent = this;
						}	
						if (this->drawMode) ofDrawBox((t0 + b3) * 0.5, this->halfWidth, this->halfHeight, this->halfDepth);
						this->t2Tree->insert(node);
					}
				}
				// bottom left
				else {
					// back bottom left ->b0
					if (this->halfDepthPos >= node->position.z) {
						//cout << "b0" << endl;
						glm::vec3 t0 = glm::vec3(this->top0.x, this->halfHeightPos, this->top0.z);
						glm::vec3 b3 = glm::vec3(this->halfWidthPos, this->bottom3.y, this->halfDepthPos);
						if (this->b0Tree == NULL){
							
							this->b0Tree = new Octree(t0, b3);
							this->b0Tree->parent = this;
							
						}
						if (this->drawMode) ofDrawBox((t0 + b3) * 0.5, this->halfWidth, this->halfHeight, this->halfDepth);
						this->b0Tree->insert(node);
					}
					// front bottom left -> b2
					else {
						//cout << "b2" << endl;
						glm::vec3 t0 = glm::vec3(this->top0.x, this->halfHeightPos, this->halfDepthPos);
						glm::vec3 b3 = glm::vec3(this->halfWidthPos, this->bottom3.y, this->bottom3.z);
						if (this->b2Tree == NULL) {
							
							this->b2Tree = new Octree(t0, b3);
							this->b2Tree->parent = this;
						}
						if (this->drawMode) ofDrawBox((t0 + b3) * 0.5, this->halfWidth, this->halfHeight, this->halfDepth);
						this->b2Tree->insert(node);
					}
				}
			}

			// else when the node is in the right side of the given space
			else {
				// top right
				if (this->halfHeightPos >= node->position.y) {
					// back top right -> t1
					if (this->halfDepthPos >= node->position.z) {
						//cout << "t1" << endl;
						glm::vec3 t0 = glm::vec3(this->halfWidthPos, this->top0.y, this->top0.z);
						glm::vec3 b3 = glm::vec3(this->bottom3.x, this->halfHeightPos, this->halfDepthPos);
						if (this->t1Tree == NULL) {
							
							this->t1Tree = new Octree(t0, b3);
							this->t1Tree->parent = this;
						}
						if (this->drawMode) ofDrawBox((t0 + b3) * 0.5, this->halfWidth, this->halfHeight, this->halfDepth);
						this->t1Tree->insert(node);
					}
					// front top right ->t3
					else {
						//cout << "t3" << endl;
						glm::vec3 t0 = glm::vec3(this->halfWidthPos, this->top0.y, this->halfDepthPos);
						glm::vec3 b3 = glm::vec3(this->bottom3.x, this->halfHeightPos, this->bottom3.z);
						if (this->t3Tree == NULL) {
							
							this->t3Tree = new Octree(t0, b3);
							this->t3Tree->parent = this;
						}
						if (this->drawMode) ofDrawBox((t0 + b3) * 0.5, this->halfWidth, this->halfHeight, this->halfDepth);
						this->t3Tree->insert(node);
					}
				}
				// bottom right
				else {
					// back bottom right -> b1
					if (this->halfDepthPos >= node->position.z) {
						//cout << "b1" << endl;
						glm::vec3 t0 = glm::vec3(this->halfWidthPos, this->halfHeightPos, this->top0.z);
						glm::vec3 b3 = glm::vec3(this->bottom3.x, this->bottom3.y, this->halfDepthPos);
						if (this->b1Tree == NULL) {
							
							this->b1Tree = new Octree(t0, b3);
							this->b1Tree->parent = this;
						}
						if (this->drawMode) ofDrawBox((t0 + b3) * 0.5, this->halfWidth, this->halfHeight, this->halfDepth);
						this->b1Tree->insert(node);
					}
					// front bottom right -> b3
					else {
						//cout << "b3" << endl;
						glm::vec3 t0 = glm::vec3(this->halfWidthPos, this->halfHeightPos, this->halfDepthPos);
						glm::vec3 b3 = this->bottom3;
						if (this->b3Tree == NULL) {
							
							this->b3Tree = new Octree(t0, b3);
							this->b3Tree->parent = this;
						}
						if (this->drawMode) ofDrawBox((t0 + b3) * 0.5, this->halfWidth, this->halfHeight, this->halfDepth);
						this->b3Tree->insert(node);
					}
				}
			}

		}

		bool isWithinBounds(BoidParticle* node) {
			//cout << ofDist(node->position.x, node->position.y, node->position.z, 0, 0, 0) << endl;
			return (
				node->position.x >= this->top0.x &&
				node->position.x <= this->bottom3.x &&
				node->position.y >= this->top0.y &&
				node->position.y <= this->bottom3.y &&
				node->position.z >= this->top0.z &&
				node->position.z <= this->bottom3.z 
				);
		}

		bool isLeafNode() {
			return this->t0Tree == NULL && this->t1Tree == NULL && this->t2Tree == NULL && this->t3Tree == NULL &&
				this->b0Tree == NULL && this->b1Tree == NULL && this->b2Tree == NULL && this->b3Tree == NULL;
		}

		void display() {
			
			
		}
	public:
		glm::vec3 top0, bottom3;

		BoidParticle* n = NULL;

		Octree* t0Tree;
		Octree* t1Tree;
		Octree* t2Tree;
		Octree* t3Tree;

		Octree* b0Tree;
		Octree* b1Tree;
		Octree* b2Tree;
		Octree* b3Tree;

		Octree* parent;
		bool drawMode;
		vector<Octree*> octreePtrArr;
		vector<glm::vec3> posArr;
		float halfWidthPos, halfHeightPos, halfDepthPos;
		float halfWidth, halfHeight, halfDepth;
		float accuracy;
		int searchDepth;
};

class Flock {
	public:
		Flock(int boidNum) {
			this->boidNum = boidNum;
			this->flockMesh = new ofMesh;
			this->flockMesh->setMode(OF_PRIMITIVE_POINTS);
			int dim = 598;
			ofColor color = ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
			for (int i = 0; i < this->boidNum; i++) {
				BoidParticle* tp = new BoidParticle(ofRandom(ofGetWindowWidth() * 0.5 - dim * 0.5, + dim * 0.5),
					ofRandom( - dim * 0.5,  + dim * 0.5),
					ofRandom(- dim * 0.5,  dim * 0.5));
				particleArr.push_back(tp);
				this->flockMesh->addVertex(tp->position);
				this->flockMesh->addIndex(i);
				
				this->flockMesh->addColor(
					ofColor(
						
						ofMap(particleArr[i]->position.x, - dim * 0.5, + dim * 0.5, 255, 50),
						ofMap(particleArr[i]->position.y,  - dim * 0.5,  + dim * 0.5, 50, 255),
						ofMap(particleArr[i]->position.z, -dim * 0.5, dim * 0.5, 50, 255)
						
						/*
						50 + 25 * sin(particleArr[i]->position.x + ofGetElapsedTimef() * 10.0),
						200 + 30 * sin(particleArr[i]->position.y + ofGetElapsedTimef()),
						180 + 60 * cos(particleArr[i]->position.z + ofGetElapsedTimef())
						*/
					)
				);
				
				this->flockMesh->addColor(color);
			}
		}

		void update() {
			int dim = 598;
			for (int i = 0; i < this->flockMesh->getNumVertices(); i++) {
				particleArr[i]->update();
				//particleArr[i]->align(particleArr);
				//particleArr[i]->cohesion(particleArr);
				//particleArr[i]->getSeparationVec(particleArr);
				particleArr[i]->flock(particleArr[i]->nearestNeighbors);
				this->flockMesh->setVertex(i, particleArr[i]->position);
				
				
				this->flockMesh->setColor(
					i, ofColor(
						
						255 - ofMap((int) particleArr[i]->position.x, 0, dim, 100, 255),
						ofMap((int)particleArr[i]->position.y,  0,  dim, 100, 255),
						ofMap((int)particleArr[i]->position.z , 0, dim, 100, 255)
						
						
					)
				);
				
				
				
			}
		}

		
		void display() {
			this->flockMesh->draw();
		}
	
	public:
		vector<BoidParticle*> particleArr;
		ofMesh* flockMesh;
		int boidNum;
		
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
		ofMesh* pointCloud;
		ofPoint testPoint;
		
		Flock* testFlock;

		ofEasyCam cam;

		vector<Flock*> flockArr;

		ofxPanel gui;
		ofParameter<float> alignCoef;
		ofParameter<float> cohesionCoef;
		ofParameter<float> separationCoef;
		ofParameter<bool> rotateWithMouse;
		ofParameter<float> octreeAccuracy;
		ofParameter<float> boidSpeed;
		ofParameter<float> pointSize;
		Octree* testOctree;
		float zpos;
		int testIndex;

		ofFbo backBuffer;
		ofFbo currentBuffer;
		ofFbo midBuffer;
		ofShader shader;

		glm::vec2 mousePressedPoint;
		glm::vec2 mouseReleasedPoint;
		float rotateDegX, rotateDegXPrev;
		float rotateDegY, rotateDegYPrev;

};
