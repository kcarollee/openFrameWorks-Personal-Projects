#pragma once
#include "ofMain.h"


class Cluster_2
{
public:
	Cluster_2();
	~Cluster_2();
	void setup(float width, float height, int depth); // depth = number of ellipses
	void draw();
	void move();
	void windowCollision();
	void spin();
public:
	ofVec2f centerPosition;
	ofVec2f velocity;
	
	float width;
	float height;
	float rotationDeg;
	
	int depth;
};