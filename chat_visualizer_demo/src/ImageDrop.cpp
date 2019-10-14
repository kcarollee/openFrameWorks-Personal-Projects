#include "ImageDrop.h"

ImageDrop::ImageDrop() {
	dropBoxColor = ofColor(222, 223, 222);
	dropMessageFontSize = 13;
	dropMessage.load("EXEPixelPerfect.ttf", dropMessageFontSize);
}
ImageDrop::~ImageDrop() {
	ofRemoveListener(ofEvents().mouseMoved, this, &ImageDrop::mouseMovedHandler);
	ofRemoveListener(ofEvents().mousePressed, this, &ImageDrop::mousePressedHandler);
}

void ImageDrop::setup(float width, float height, float xpos, float ypos) {
	this->width = width;
	this->height = height;
	this->xpos = xpos;
	this->ypos = ypos;
	dragDropAreaXpos = xpos + width / 10;
	dragDropAreaYpos = ypos + height / 8;
	dragDropAreaWidth = 0.8 * width;
	dragDropAreaHeight = 0.8 * height;

	ofAddListener(ofEvents().mouseMoved, this, &ImageDrop::mouseMovedHandler);
	ofAddListener(ofEvents().mousePressed, this, &ImageDrop::mousePressedHandler);
}

void ImageDrop::draw() {
	ofSetColor(255);
	ofDrawRectRounded(xpos, ypos, width, height, 10);
	ofSetColor(dropBoxColor);
	// drag and drop area
	ofDrawRectangle(dragDropAreaXpos, dragDropAreaYpos,
		dragDropAreaWidth, dragDropAreaHeight);
	ofSetColor(0);
	UIfont.drawString("Image", xpos + UIfontSize, ypos + UIfontSize);
	dropMessage.drawString("Drag and drop\nimages here\n's': default", xpos + width / 3, ypos + height / 2);
}

void ImageDrop::mouseMovedHandler(ofMouseEventArgs & mouse) {
	if (mouse.x > dragDropAreaXpos && mouse.x < dragDropAreaXpos + dragDropAreaWidth) {
		if (mouse.y > dragDropAreaYpos && mouse.y < dragDropAreaYpos + dragDropAreaHeight) {
			dropBoxColor = ofColor(100);
		}
	}
	else dropBoxColor = ofColor(222, 223, 222);
}

void ImageDrop::mousePressedHandler(ofMouseEventArgs & mouse) {
	
}
