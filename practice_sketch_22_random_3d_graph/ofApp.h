#pragma once

#include "ofMain.h"
#define INF 1000000

typedef struct GraphNode {
	int vertex;
	struct GraphNode *link;
	
}GraphNode;

typedef struct VertSphere {
	float initRadius;
	float radius;
	ofVec3f pos;
	ofVec3f initLinePos;
	ofColor color = ofColor(255);
}VertSphere;

typedef struct GraphType {
	int n; // number of vertices
	int radiusDiv; // number of layers in the sphere; must be odd
	vector<GraphNode*> adjList;
	vector<VertSphere*> verticesArr;
	vector<float> distancesFromStartingPoint;
	vector<bool> vertexVisited;
	vector<vector<float>> weightsArr; // weights represent the distance between two vertices
	float radius, heightIncrement;
	int drawIndex, drawIndex2, dijkstraIter;
	bool allVerticesDrawn;
	bool firstIteration;
	bool dijkstraMode;
	bool toggleNumbers;
	
	float inc, inc2;
	void setup(float radius) {
		this->radius = radius;
		drawIndex = 0;
		drawIndex2 = 0;
		dijkstraIter = 0;
		allVerticesDrawn = false;
		firstIteration = true;
		dijkstraMode = false;
		toggleNumbers = false;
		inc = 0;
		inc2 = 0;
	}
	
	void insertVertices(int n) {
		this->n = n;
		// initialize weights array
		vector<float> tempRow;
		for (int i = 0; i < n; i++) {	
			for (int j = 0; j < n; j++) {
				if (i == j) tempRow.push_back(0);
				else tempRow.push_back(INF);
			}
			weightsArr.push_back(tempRow);
			tempRow.clear();
		}
		for (int i = 0; i < n; i++) {
			// random positions
			VertSphere *temp = new VertSphere();
			temp->initRadius = 6;
			temp->radius = 2;
			temp->pos = ofVec3f(ofRandom(-radius, radius), ofRandom(-radius, radius), ofRandom(-radius, radius));
			temp->initLinePos = temp->pos;
			verticesArr.push_back(temp);
		}
		// initialize adjacency list
		for (int i = 0; i < n; i++) {
			adjList.push_back(NULL);
		}
	}

	void insertEdge(int u, int v) {
		GraphNode *node = new GraphNode();
		node->vertex = v;
		node->link = adjList[u];
		adjList[u] = node;
		// update weights array
		float weight = ofDist(verticesArr[node->vertex]->pos.x, verticesArr[node->vertex]->pos.y,
			verticesArr[u]->pos.x, verticesArr[u]->pos.y);

		weightsArr[node->vertex][u] = weight;
		weightsArr[u][node->vertex] = weight;
	}

	

	// max edgNum = n * (n - 1) / 2
	void insertRandomEdges(int edgeNum) {
		int tempu, tempv;
		tempu = (int)ofRandom(0, this->n);
		tempv = (int)ofRandom(0, this->n);
		for (int i = 0; i < edgeNum; i++) {
			while (isConnected(tempu, tempv) || tempu == tempv) {
				tempu = (int)ofRandom(0, this->n);
				tempv = (int)ofRandom(0, this->n);
				//cout << "connected" << endl;
			}
			insertEdge(tempu, tempv);
			tempu = (int)ofRandom(0, this->n);
			tempv = (int)ofRandom(0, this->n);
		}
		// setup dijkstra after filling in the edges
		dijkstraSetup(0);
	}

	bool isConnected(int u, int v) {
		GraphNode *temp = adjList[u], *temp2 = adjList[v];	
		while (temp != NULL) {
			if (temp->vertex == v) return true;
			temp = temp->link;
		}
		while (temp2 != NULL) {
			if (temp2->vertex == u) return true;
			temp2 = temp2->link;
		}
		return false;
	}

	void updateDrawIndex() {
		if (drawIndex < verticesArr.size() - 1) drawIndex++;
		else allVerticesDrawn = true;
		if (allVerticesDrawn) {
			if (drawIndex2 < adjList.size() - 1) drawIndex2++;
		}
	}

	int getMinimumIndex() {
		int i, min, minIndex;
		min = INT_MAX;
		minIndex = -1;
		for (i = 0; i < this->n; i++) {
			if (distancesFromStartingPoint[i] < min && !vertexVisited[i]) {
				min = distancesFromStartingPoint[i];
				minIndex = i;
			}
		}
		//cout << minIndex << " " << distancesFromStartingPoint[minIndex] <<  " " << weightsArr[0][minIndex]<<endl;
		return minIndex;
	}

	void dijkstraSetup(int startingVert) {
		int i;
		for (int i = 0; i < this->n; i++) {
			distancesFromStartingPoint.push_back(weightsArr[startingVert][i]);
			vertexVisited.push_back(false);
		}

		vertexVisited[startingVert] = true;
	}

	int dijkstraShortestPath() {
		int u, w;
		u = getMinimumIndex();
		//cout << u << endl;
		vertexVisited[u] = true;
		verticesArr[u]->color = ofColor(50, 100, 200, 70);
		verticesArr[u]->initRadius = 15;
		for (w = 0; w < this->n; w++) {
			if (!vertexVisited[w]) {
				if (distancesFromStartingPoint[u] + weightsArr[u][w] < distancesFromStartingPoint[w])
					distancesFromStartingPoint[w] = distancesFromStartingPoint[u] + weightsArr[u][w];
			}
		}
		return u;
	}

	void draw() {
		ofSetColor(255);
		int minIndex;
		if (dijkstraMode) {	
			minIndex = dijkstraShortestPath();
			if (dijkstraIter < this->n - 2)	dijkstraIter++;
			//cout << dijkstraIter << "t" << endl;
			else {
				dijkstraMode = false;
				dijkstraIter = 0;
				vertexVisited.clear();
				distancesFromStartingPoint.clear();
				dijkstraSetup(0);
			}
		}
		for (int i = 0; i <= drawIndex; i++) {	
			if (verticesArr[i]->initRadius >= 2) {
				ofSetColor(verticesArr[i]->color);
				ofDrawSphere(verticesArr[i]->pos, verticesArr[i]->initRadius);
				if (toggleNumbers) {
					ofSetColor(255);
					if (i == 0) ofDrawBitmapString("start", verticesArr[i]->pos);
					else ofDrawBitmapString(to_string(i), verticesArr[i]->pos);
				}
				verticesArr[i]->initRadius -= 0.2;
			}
			else{
				ofSetColor(verticesArr[i]->color);
				ofDrawSphere(verticesArr[i]->pos, verticesArr[i]->radius);
				if (toggleNumbers) {
					ofSetColor(255);
					if (i == 0) ofDrawBitmapString("start", verticesArr[i]->pos);
					else ofDrawBitmapString(to_string(i), verticesArr[i]->pos);
				}
			}
			
		}
		if (allVerticesDrawn) {
			/*
			if (dijkstraMode) {
				for (int j = 0; j < vertexVisited.size(); j++) {
					if (vertexVisited[j]) {
						if (isConnected(minIndex, j)) {
							ofSetLineWidth(3);
							ofSetColor(255, 0, 0);
							
							ofDrawLine(verticesArr[minIndex]->pos, verticesArr[j]->pos);
							
						}
					}
				}
			}
			*/
			for (int i = 0; i <= drawIndex2; i++) {
				GraphNode *temp = adjList[i];
				ofSetColor(255, 20);
				while (temp != NULL) {											
					ofSetLineWidth(1);
					
					if (dijkstraMode) {
						if (vertexVisited[temp->vertex] && vertexVisited[i]) {
							ofSetColor(200, 100, 150, 30);
							ofDrawLine(verticesArr[temp->vertex]->pos,
								verticesArr[temp->vertex]->pos + (verticesArr[i]->pos - verticesArr[temp->vertex]->pos) / 2000 * inc);							
						}
						temp = temp->link;
					}
					else {
						ofSetLineWidth(1);
						ofDrawLine(verticesArr[temp->vertex]->pos,
							verticesArr[temp->vertex]->pos + (verticesArr[i]->pos - verticesArr[temp->vertex]->pos) / 2000 * inc);
						temp = temp->link;
					}
				}
				if (inc < 2000) {
					//cout << inc;
					inc += 0.1;
				}
			}
			if (firstIteration) {
				//printWeights();
				//printAdjList();
			}
			firstIteration = false;
		}
	}

	void printAdjList() {
		for (int i = 0; i < adjList.size(); i++){
			GraphNode *temp = adjList[i];
			cout << "CONNECTED TO VERTEX " << i << " ";
			while (temp != NULL) {
				cout << temp->vertex << "->";
				temp = temp->link;
			}
			cout << endl;
			
		}
		cout << endl;
	}
	void printWeights() {
		for (int i = 0; i < this->n; i++) {
			for (int j = 0; j < this->n; j++) {
				cout << weightsArr[i][j] << " ";
			}
			cout << endl;
			
		}
		cout << endl;
		cout << endl;
	}

	
	void reset() {
		adjList.clear();
		verticesArr.clear();
		distancesFromStartingPoint.clear();
		vertexVisited.clear();
		drawIndex = 0;
		drawIndex2 = 0;
		allVerticesDrawn = false;
		firstIteration = true;
		dijkstraMode = false;
		toggleNumbers = false;
		inc = 0;
	}
	

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
	GraphType* graph;
	float deg;
	int vertNum, edgeNum;
};
