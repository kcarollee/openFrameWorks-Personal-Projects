#pragma once
#include "ofMain.h"

class Cluster_1
{
public:
	Cluster_1();
	~Cluster_1();
	void setup(float radius);
	void draw();
	void spin();
	void move();
	void windowCollision();

public:
	ofVec2f centerPosition;
	ofVec2f velocity;
	float radius;
	float widthAngle; // angle that determines the length of the triangles' base
	float rotationDeg;
};