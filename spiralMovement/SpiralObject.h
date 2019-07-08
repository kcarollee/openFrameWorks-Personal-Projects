#include "ofMain.h"

class SpiralObject
{
public:
	SpiralObject();
	~SpiralObject();
	void setup(float diameter, ofVec2f centerPos);
	void move();
	void draw(ofFbo fbo);
	void draw();
	void drawLineMode(ofFbo fbo);
	

public:
	float diameter;
	float incLength;
	float velocity;
	float angle;
	ofVec2f centerPos;
	ofVec2f pos;
	ofVec2f prevPos;

	int rValue;
	int bValue;
	int gValue;
};