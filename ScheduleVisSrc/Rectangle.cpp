#include "Rectangle.h"
vector<int> Block::schedule;
vector<vector<int>> Block::scheduleArr;
Block::Block()
{
	
	
}
Block::~Block()
{
	ofRemoveListener(ofEvents().mouseMoved, this, &Block::mouseMovedHandler);
	ofRemoveListener(ofEvents().mousePressed, this, &Block::mousePressedHandler);
}

void Block::setup(int x, int y, int w, int h)
{
	posX = x;
	posY = y;
	width = w;
	height = h;

	blockID = 0;

	color = ofColor(255, 255, 255);

	rect.set(posX, posY, width, height);

	pressedFlag = false;

	ofAddListener(ofEvents().mouseMoved, this, &Block::mouseMovedHandler);
	ofAddListener(ofEvents().mousePressed, this, &Block::mousePressedHandler);

}
void Block::reset()
{
	color = ofColor(255, 255, 255);
	pressedFlag = false;
}
void Block::draw()
{
	ofSetColor(color);
	ofDrawRectangle(rect);

}

bool Block::isInside(int x, int y)
{
	if ((x > rect.x) && (x < rect.x + rect.getWidth())) {
		if ((y > rect.y) && (y < rect.y + rect.getHeight())) {
			
			return true;
		}
	}
	
	return false;
}
void Block::mouseMovedHandler(ofMouseEventArgs & mouse)
{
	if (isInside(mouse.x, mouse.y)) {
		//cout << "in block number " << blockID << endl;
		color = ofColor(255, 0, 0);
	}

	else {
		if (!pressedFlag) {
			color = ofColor(255, 255, 255);
		}
		else
			color = ofColor(80, 80, 80);
	}

		
}
void Block::mousePressedHandler(ofMouseEventArgs & mouse)
{
	if (isInside(mouse.x, mouse.y)) {
		if (!pressedFlag) {
			pressedFlag = true;
			schedule.push_back(blockID);
			for (auto i : schedule) {
				cout << i << " " << endl;
			}
		}
		else {

			pressedFlag = false;
			for (int i = 0; i < schedule.size(); i++) {
				if (schedule[i] == blockID) {
					schedule.erase(schedule.begin() + i);
				}
			}
		}
	}
	
	
}