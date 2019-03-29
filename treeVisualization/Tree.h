#pragma once
#include "ofMain.h"
#include "windows.h"
struct node {
	node *left;
	node *right;
	node *par;
	int data;
	ofVec2f pos;
};

class Tree {


public:
	Tree(ofVec2f rtp);
	int isEmpty();
	void insert(int item);
	void drawInOrder(node *ptr);
	int getHeight();
	void wiggle(node *ptr);
	void viewData(node *ptr);
	void dragNode(node *ptr);
	bool mouseInNode(node *ptr);

public:
	node *root;
	int elemNum;
	ofVec2f rootPos;

};