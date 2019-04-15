#include "Tree.h"
Tree::Tree(ofVec2f rtp)
{
	root = NULL;
	rootPos = rtp;
	elemNum = 0;
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
			p->pos = ofVec2f(ofRandom(root->pos.x - getHeight() * 20,
				root->pos.x + getHeight() * 20), root->pos.y + getHeight() * 60);
		}
		else {
			parent->right = p;
			p->par = parent;
			p->pos = ofVec2f(ofRandom(root->pos.x- getHeight() * 20,
				root->pos.x + getHeight() * 20), root->pos.y + getHeight() * 60);
		}
	}
}

void Tree::viewData(node *ptr)
{
	if (ptr != NULL) {

		viewData(ptr->left);

		ofDrawBitmapString(to_string(ptr->data), ptr->pos - ofVec2f(3, 3));

		viewData(ptr->right);

	}

		
}
void Tree::drawInOrder(node *ptr)
{
	if (ptr != NULL) {

		drawInOrder(ptr->left);
		ofSetColor(0);
		ofDrawCircle(ptr->pos, 3);
		if (ptr != root) {
			ofDrawLine(ptr->par->pos, ptr->pos);
		}
		else {
			ofDrawBitmapString("root" + to_string(ptr->data), ptr->pos - ofVec2f(3, 3));
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
			ptr->pos = ofVec2f(ofGetMouseX(), ofGetMouseY());
		}
		dragNode(ptr->right);

	}
}

void Tree::wiggle(node *ptr)
{
	if (ptr != NULL) {

		wiggle(ptr->left);
		
		ptr->pos += ofVec2f(ofRandom(-10, 10), ofRandom(-10, 10));
		
		wiggle(ptr->right);
		//ofDrawLine(ptr->pos, ptr->right->pos);
	}
}