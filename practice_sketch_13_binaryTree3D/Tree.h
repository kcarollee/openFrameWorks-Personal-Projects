#pragma once
#include "ofMain.h"
#include "windows.h"
struct node {
	node *left;
	node *right;
	node *par;
	int data;
	ofVec3f pos;
	int height;
	float currentDeg;
	float degInc;
	ofColor color;
};

class Tree {


public:
	Tree(ofVec3f rtp);
	int isEmpty();
	void insert(int item);
	void drawInOrder(node *ptr);
	int getHeight();
	
	void wiggle(node *ptr);
	void viewData(node *ptr);
	void dragNode(node *ptr);
	bool mouseInNode(node *ptr);
	void moveTowardsMouse(node *ptr);
	void spinNode(node *ptr);
	void spinTree(node *ptr, float deg);

public:
	node *root;
	int elemNum;
	ofVec3f rootPos;
	float radius;
	float depthGap;

	int red, blue, green;

};