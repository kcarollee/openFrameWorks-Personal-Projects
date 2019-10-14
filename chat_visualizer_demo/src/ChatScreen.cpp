#include "ChatScreen.h"

ChatScreen::ChatScreen()
{
	UIfontSize = 30;
	UIfont.load("EXEPixelPerfect.ttf", UIfontSize);
	chatBoxNum = 0;
}

ChatScreen::~ChatScreen()
{
	ofRemoveListener(ofEvents().mouseMoved, this, &ChatScreen::mouseMovedHandler);
	ofRemoveListener(ofEvents().mousePressed, this, &ChatScreen::mousePressedHandler);
}

void ChatScreen::setup(float width, float height, float xpos, float ypos) {
	this->width = width;
	this->height = height;
	this->xpos = xpos;
	this->ypos = ypos;
}

void ChatScreen::draw() {
	ofSetColor(255);
	ofDrawRectRounded(xpos, ypos, width, height, 10);
	// need to draw boundary of the chat boxes
	ofSetColor(222, 223, 222);
	ofNoFill();
	ofSetLineWidth(2);
	ofDrawRectangle(xpos + width / 10, ypos + height / 15,
		width * 0.8, height * 0.9);
	ofFill();
	ofSetLineWidth(0);
	ofSetColor(0);
	UIfont.drawString("Chat Log", xpos + UIfontSize, ypos + UIfontSize);
}

float ChatScreen::getChatBoxBoundaryHeight() {
	return height * 0.9;
}

float ChatScreen::getChatBoxWidth() {
	return width * 0.8 - 4;
}

float ChatScreen::getChatBoxHeight(int chatBoxNum) {
	return (height * 0.9 - 4) / chatBoxNum;
}

ofVec2f ChatScreen::getFirstChatBoxPos() {
	// 2 is the thickness of boundary
	return ofVec2f(xpos + 2 + width / 10, ypos + 2 + height / 15);
}



void ChatScreen::mouseMovedHandler(ofMouseEventArgs & mouse) {

}

void ChatScreen::mousePressedHandler(ofMouseEventArgs & mouse) {

}