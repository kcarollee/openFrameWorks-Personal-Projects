
#pragma once

#include "ofMain.h"
#include "ChatScreen.h"
#include "ChatBox.h"
#include "FontDrop.h"
#include "ImageDrop.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	string organizeText(string text);
	string getFormattedTextLine(string text);

public:
	ChatScreen chatScreen;
	ImageDrop imageDrop;
	FontDrop fontDrop;

	int chatBoxNum;

	ofVec2f firstChatBoxPos;
	ofShader shader;

	deque<ChatBox*> chatBoxArr;
	deque<string> textArr;
	//ofBuffer::Line it, end;
	ofBuffer stringBuffer;
	ofBuffer::Line it = stringBuffer.getLines().begin(), end = stringBuffer.getLines().end();
	string line;

	ofTrueTypeFont font;


	vector <ofImage> draggedImages;
	ofImage draggedImage;
	ofPoint dragPt;
	int fontSize;


	

	bool isShaderMode;
};