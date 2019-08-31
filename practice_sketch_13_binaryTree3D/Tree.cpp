#include "Tree.h"
Tree::Tree(ofVec3f rtp)
{
	root = NULL;
	rootPos = rtp;
	elemNum = 0;
	radius = 10;
	depthGap = 30;

	red = 150;
	blue = 200;
	green = 160;
}

int Tree::isEmpty() {
	return (root == NULL);
}

int Tree::getHeight() {
	if (elemNum == 1) {
		return 0;
	}
	else {
		return (int)sqrt((double)elemNum);
	}
}

void Tree::spinNode(node *ptr) 
{
	
	
		if (ptr != NULL) {

			spinNode(ptr->left);
			if (ptr == root) {}
			else {
				ptr->currentDeg += ptr->degInc;
				ptr->pos.x = radius * ptr->height * cos(ptr->currentDeg);
				ptr->pos.y = radius * ptr->height * sin(ptr->currentDeg);
			}
			spinNode(ptr->right);

		}
	
}

void Tree::spinTree(node *ptr, float deg) {
	if (ptr != NULL) {

		spinTree(ptr->left, deg);
		if (ptr == root) {}
		else {
			ptr->currentDeg += deg;
			ptr->pos.x = radius * ptr->height * cos(ptr->currentDeg);
			ptr->pos.y = radius * ptr->height * sin(ptr->currentDeg);
		}
		spinTree(ptr->right, deg);

	}
}



void Tree::insert(int item)
{

	elemNum++;
	node *p = new node;
	node *parent;
	p->left = NULL;
	p->right = NULL;
	p->data = item;
	p->par = NULL;
	parent = NULL;

	if (isEmpty()) {
		root = p;
		root->pos = rootPos;
		root->currentDeg = 0;
		root->degInc = 0;
		root->color = ofColor(red, blue, green);
	}
	else {
		node *ptr;
		ptr = root;
		while (ptr != NULL) {
			parent = ptr;

			if (item > ptr->data)
				ptr = ptr->right;
			else
				ptr = ptr->left;
		}

		if (item < parent->data) {
			parent->left = p;
			p->par = parent;
			p->pos = ofVec3f(radius * getHeight() * cos(ofRandom(0, 2 * PI)),
				radius * getHeight() * sin(ofRandom(0, 2 * PI)),
				root->pos.z - getHeight() * depthGap);
			p->height = getHeight();
			p->currentDeg = acos(p->pos.x / (radius * getHeight()));
			p->degInc = ofRandom(-0.3, 0.3);
			p->color = ofColor(red + p->height * 4, blue - p->height * 3, green - p->height);
		}
		else {
			parent->right = p;
			p->par = parent;
			p->pos = ofVec3f(radius * getHeight() * cos(ofRandom(0, 2 * PI)),
				radius * getHeight() * sin(ofRandom(0, 2 * PI)),
					root->pos.z - getHeight() * depthGap);
			p->height = getHeight();
			p->currentDeg = acos(p->pos.x / (radius * getHeight()));
			p->degInc = ofRandom(-0.3, 0.3);
			p->color = ofColor(red + p->height * 4, blue - p->height * 3, green - p->height);
		}
	}
}

void Tree::viewData(node *ptr)
{
	if (ptr != NULL) {

		viewData(ptr->left);
		ofSetColor(0);

		ofDrawBitmapString(to_string(ptr->data), ptr->pos - ofVec2f(3, 3));

		viewData(ptr->right);

	}


}
void Tree::drawInOrder(node *ptr)
{
	static int red = 100;
	static int blue = 100;
	if (ptr != NULL) {

		drawInOrder(ptr->left);
		ofSetColor(ptr->color);
		ofDrawSphere(ptr->pos, 3);
		if (ptr != root) {		
			ofDrawLine(ptr->par->pos, ptr->pos);
			//pseudo shadow
			ofSetColor(30, 30, 30, 100);
			ofDrawCircle(ptr->pos.x, ptr->pos.y, -300, 3);
		}
		else {
			ofSetColor(30, 30, 30, 100);
			ofDrawCircle(ptr->pos.x, ptr->pos.y, -300, 3);
			ofSetColor(0);
			ofDrawBitmapString("root" + to_string(ptr->data), ptr->pos - ofVec3f(3, 3));
		}
		drawInOrder(ptr->right);
		//ofDrawLine(ptr->pos, ptr->right->pos);
	}
}

void Tree::moveTowardsMouse(node *ptr)
{
	if (ptr != NULL) {

		moveTowardsMouse(ptr->left);
		ptr->pos += ofVec2f((ofGetMouseX() - ptr->pos.x) / 100, (ofGetMouseY() - ptr->pos.y) / 100);
		moveTowardsMouse(ptr->right);

	}
}

bool Tree::mouseInNode(node *ptr) {
	if (ofGetMousePressed()) {
		if (ofDist(ofGetMouseX(), ofGetMouseY(), ptr->pos.x, ptr->pos.y) <= 8) {
			return true;
		}
	}
	return false;
}
void Tree::dragNode(node *ptr) {
	if (ptr != NULL) {

		dragNode(ptr->left);
		if (mouseInNode(ptr)) {
			ptr->pos = ofVec3f(ofGetMouseX(), ofGetMouseY());
		}
		dragNode(ptr->right);

	}
}

void Tree::wiggle(node *ptr)
{
	if (ptr != NULL) {

		wiggle(ptr->left);

		ptr->pos += ofVec3f(ofRandom(-10, 10), ofRandom(-10, 10));

		wiggle(ptr->right);
		//ofDrawLine(ptr->pos, ptr->right->pos);
	}
}