#include "Cluster_1.h"

Cluster_1::Cluster_1()
{
	radius = 0;
	centerPosition = ofVec2f(0, 0);
	velocity = ofVec2f(0, 0);
	rotationDeg = 0;
	widthAngle = 0;
}

Cluster_1::~Cluster_1()
{

}

void Cluster_1::setup(float radius)
{
	this->radius = radius;
	centerPosition = ofVec2f(ofRandom(5 * radius, ofGetWidth() - 5 * radius), ofRandom(5 * radius, ofGetHeight() - 5 * radius));
	velocity = ofVec2f(ofRandom(1, 4), ofRandom(1, 4));
	widthAngle = 9;
}

void Cluster_1::move()
{
	centerPosition += velocity;
}

void Cluster_1::windowCollision()
{
	if (centerPosition.x - 5 * radius < 0 || centerPosition.x + 5 * radius > ofGetWidth())
		velocity.x *= -1;
	if (centerPosition.y - 5 * radius < 0 || centerPosition.y + 5 * radius > ofGetHeight())
		velocity.y *= -1;
}

void Cluster_1::spin()
{
	rotationDeg += 0.5;
}
void Cluster_1::draw()
{
	ofPushMatrix();
	// set rotation
	ofTranslate(centerPosition);
	ofRotate(rotationDeg);
	spin();
	
	// set center circle
	ofNoFill();
	ofSetLineWidth(3);
	ofSetColor(233, 98, 233);
	ofSetCircleResolution(60);
	ofDrawCircle(0, 0, radius);
	
	// set inner circles
	for (int i = 0; i < 3; i++) {
		for (int j = 1; j <= 6; j++) {
			ofDrawCircle(ofVec2f((((2 * i + 1) * 2 / 6) * radius * cos(j * (PI / 3))) * ofRandom(0, 1),
				(((2 * i + 1) * 2 / 6) * radius * sin(j * (PI / 3)))) *  ofRandom(0, 1), radius / 6);
		}
	}

	// set triangles
	ofSetColor(0, 102, 104);
	for (int i = 1; i <= 6; i++) {
		ofFill();
		ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
		ofDrawTriangle(ofVec2f(2 * radius * cos(widthAngle) * cos(i * (PI / 3) - widthAngle),
			2 * radius * cos(widthAngle) * sin(i * (PI / 3) - widthAngle)),
			ofVec2f(2 * radius * cos(widthAngle) * cos(i * (PI / 3) + widthAngle),
				2 * radius * cos(widthAngle) * sin(i * (PI / 3) + widthAngle)),
			ofVec2f(5 * radius * cos(i * (PI /3)), 5 * radius * sin(i * (PI / 3))));
	}
	ofPopMatrix();
}