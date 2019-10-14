#include "FontDrop.h"

FontDrop::FontDrop() {
	dropBoxColor = ofColor(222, 223, 222);
	dropMessageFontSize = 13;
	dropMessage.load("EXEPixelPerfect.ttf", dropMessageFontSize);
}
FontDrop::~FontDrop() {
	ofRemoveListener(ofEvents().mouseMoved, this, &FontDrop::mouseMovedHandler);
	ofRemoveListener(ofEvents().mousePressed, this, &FontDrop::mousePressedHandler);
}

void FontDrop::setup(float width, float height, float xpos, float ypos) {
	this->width = width;
	this->height = height;
	this->xpos = xpos;
	this->ypos = ypos;
	dragDropAreaXpos = xpos + width / 10;
	dragDropAreaYpos = ypos + height / 7;
	dragDropAreaWidth = 0.8 * width;
	dragDropAreaHeight = 0.8 * height;

	ofAddListener(ofEvents().mouseMoved, this, &FontDrop::mouseMovedHandler);
	ofAddListener(ofEvents().mousePressed, this, &FontDrop::mousePressedHandler);
}

void FontDrop::draw() {
	ofSetColor(255);
	ofDrawRectRounded(xpos, ypos, width, height, 10);
	ofSetColor(dropBoxColor);
	// drag and drop area
	ofDrawRectangle(dragDropAreaXpos, dragDropAreaYpos,
		dragDropAreaWidth, dragDropAreaHeight);
	ofSetColor(0);
	dropMessage.drawString("Drag and drop\n.ttf file here", xpos + width / 3, ypos + height / 2);
	UIfont.drawString("Font", xpos + UIfontSize, ypos + UIfontSize);
}

void FontDrop::mouseMovedHandler(ofMouseEventArgs & mouse) {
	if (mouse.x > dragDropAreaXpos && mouse.x < dragDropAreaXpos + dragDropAreaWidth) {
		if (mouse.y > dragDropAreaYpos && mouse.y < dragDropAreaYpos + dragDropAreaHeight) {
			dropBoxColor = ofColor(100);

		}
	}
	else dropBoxColor = ofColor(222, 223, 222);
}

void FontDrop::mousePressedHandler(ofMouseEventArgs & mouse) {

}