#include "Cluster_2.h"

Cluster_2::Cluster_2()
{
	rotationDeg = 0;
}

Cluster_2::~Cluster_2()
{

}

void Cluster_2::setup(float width, float height, int depth)
{
	this->width = width;
	this->height = height;
	centerPosition = ofVec2f(ofRandom(width, ofGetWidth() - width), ofRandom(height, ofGetHeight() - height));
	this->depth = depth;
	velocity = ofVec2f(ofRandom(-10, 10), ofRandom(-10, 10));
}

void Cluster_2::spin()
{
	rotationDeg += 4;
}

void Cluster_2::draw()
{
	ofPushMatrix();
	// set rotation
	ofTranslate(centerPosition);
	spin();
	ofRotate(rotationDeg);

	// draw ellipses
	ofSetLineWidth(3);
	ofSetColor(204, 0, 0);
	ofNoFill();
	for (int i = 0; i < depth; i++) {
		ofDrawEllipse(0, 0, width - (2 * i + 1) *  ofRandom(-5, 5), height - (2 * i + 1) * ofRandom(-5, 5));
		
	}
	ofSetColor(0, 150, 0);
	ofFill();
	for (int i = 0; i < depth; i++) {
		ofDrawEllipse(0, 0, height - (2 * i + 1) * ofRandom(-5, 5), height - (2 * i + 1) * ofRandom(-5, 5));
	}
	ofPopMatrix();

}

void Cluster_2::move()
{
	centerPosition += velocity;
}

void Cluster_2::windowCollision()
{
	if (centerPosition.x - width < 0 || centerPosition.x + width > ofGetWidth())
		velocity.x *= -1;
	if (centerPosition.y - height < 0 || centerPosition.y + height > ofGetHeight())
		velocity.y *= -1;
}