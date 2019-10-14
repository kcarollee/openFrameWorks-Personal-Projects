#pragma once
#include "ofMain.h"
#include "ofEvents.h"

class ChatScreen {
public:
	ChatScreen();
	~ChatScreen();
	void setup(float width, float height, float xpos, float ypos);
	void draw();
	void mouseMovedHandler(ofMouseEventArgs & mouse);
	void mousePressedHandler(ofMouseEventArgs & mouse);
	float getChatBoxBoundaryHeight();
	float getChatBoxWidth();
	float getChatBoxHeight(int chatBoxNum);
	ofVec2f getFirstChatBoxPos();

public:
	float width, height, xpos, ypos;
	ofTrueTypeFont UIfont;
	int UIfontSize;
	int chatBoxNum;
};