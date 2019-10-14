#pragma once
#include "ofMain.h"
#include "ofEvents.h"

class ChatBox {
public:
	ChatBox();
	~ChatBox();

	void setup(float width, float height, float xpos, float ypos);
	void setImage(ofImage image);
	void setText(string text);
	void setFont(ofTrueTypeFont font);
	
	void displayText(int mode);
	void displayText();
	void draw(ofShader shader);
	void draw(int mode); // image as background mode
	void move();
public:
	float width, height, xpos, ypos;
	ofImage image;
	string text;
	string originalText;
	int setTextCallNum;
	int random;
	ofTrueTypeFont font;
};