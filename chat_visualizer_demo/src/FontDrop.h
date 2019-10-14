#include "ofMain.h"
#include "ofEvents.h"
#include "ChatScreen.h"

class FontDrop : public ChatScreen {
public:
	FontDrop();
	~FontDrop();
	void setup(float width, float height, float xpos, float ypos);
	void mouseMovedHandler(ofMouseEventArgs & mouse);
	void mousePressedHandler(ofMouseEventArgs & mouse);
	void draw();
public:
	ofTrueTypeFont dropMessage;
	int dropMessageFontSize;
	ofColor dropBoxColor;
	float dragDropAreaXpos, dragDropAreaYpos;
	float dragDropAreaWidth, dragDropAreaHeight;
};