#include "ChatBox.h"

ChatBox::ChatBox() {
	random = (int)ofRandom(10, 100);
	setTextCallNum = 0;
}
ChatBox::~ChatBox() {
}

void ChatBox::setup(float width, float height, float xpos, float ypos) {
	this->width = width;
	this->height = height;
	this->xpos = xpos;
	this->ypos = ypos;
}
void ChatBox::setImage(ofImage image) {
	this->image = image;
}

void ChatBox::setText(string text) {
	this->text = text;
	if (setTextCallNum == 0) {
		originalText = this->text;
	}
	setTextCallNum++;
	
}
void ChatBox::setFont(ofTrueTypeFont font) {
	this->font = font;
}
void ChatBox::displayText(int mode) {
	ofSetColor(255);
	//ofDrawBitmapString(text, xpos, ypos + 10);
	//font.load(fontFileName, fontSize, true, true);
	font.drawString(text, xpos, ypos + font.getSize());
}

void ChatBox::displayText() {
	ofSetColor(0);
	ofDrawBitmapString(text, xpos, ypos + 10);
	
}
void ChatBox::move() {
	ypos -= height;
}
void ChatBox::draw(int mode) {
	ofSetColor(255);
	image.resize(width, height);
	image.draw(xpos, ypos);
}
void ChatBox::draw(ofShader shader) {
	
	shader.begin();
	shader.setUniform1f("time", ofGetElapsedTimef());
	shader.setUniform1f("random", random);
	shader.setUniform1f("rectXpos", xpos);
	shader.setUniform1f("rectYpos", ypos);
	shader.setUniform1f("rectWidth", width);
	shader.setUniform1f("rectHeight", height);
	//ofSetColor(ofRandom(10, 50));
	ofDrawRectangle(xpos, ypos, width, height);
	shader.end();
}