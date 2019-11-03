#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	cellNumPerRow = 100;
	allowedNumberOfNeighbors = 3;
	cellWidth = ofGetWindowWidth() / cellNumPerRow;
	cellHeight = ofGetWindowHeight() / cellNumPerRow;
	deg = 45;
	clickMode = "single cell";
	ofSetBackgroundColor(255);

	for (int i = 0; i < cellNumPerRow; i++) {
		vector<Cell*> cellRow;
		for (int j = 0; j < cellNumPerRow; j++) {
			Cell* cell = new Cell;
			cell->xpos = j * cellWidth;
			cell->ypos = i * cellHeight;
			cell->alive = (int) ofRandom(0, 2);
			if (cell->alive) cell->aliveCount = 0;
			else cell->aliveCount = 1;
			cell->ncount = 0;
			cellRow.push_back(cell);
		}
		cellArr.push_back(cellRow);	
	}
	
	light.setAmbientColor(ofColor(255, 0, 0));
	light.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 0);
	//light.setAreaLight(1000, 1000);
	ofEnableLighting();
}

void ofApp::countNeighbors() {
	// init ncount
	for (int i = 0; i < cellNumPerRow; i++) {
		for (int j = 0; j < cellNumPerRow; j++) {
			// top left corner check
			
			int neighbors = 0;
			if (i == 0 && j == 0) {
				if (cellArr[0][1]->alive) neighbors++;
				if (cellArr[0][cellNumPerRow - 1]->alive) neighbors++;
				if (cellArr[1][0]->alive) neighbors++;
				if (cellArr[1][1]->alive) neighbors++;
				if (cellArr[1][cellNumPerRow - 1]->alive) neighbors++;
				if (cellArr[cellNumPerRow - 2][0]->alive) neighbors++;
				if (cellArr[cellNumPerRow - 1][0]->alive) neighbors++;
				if (cellArr[cellNumPerRow - 1][cellNumPerRow - 1]->alive) neighbors++;
				cellArr[i][j]->ncount = neighbors;
			}
			// top right corner check
			else if (i == 0 && j == cellNumPerRow - 1) {
				if (cellArr[0][cellNumPerRow - 2]->alive) neighbors++;
				if (cellArr[0][0]->alive) neighbors++;
				if (cellArr[1][cellNumPerRow - 1]->alive) neighbors++;
				if (cellArr[1][cellNumPerRow - 2]->alive) neighbors++;
				if (cellArr[1][0]->alive) neighbors++;
				if (cellArr[cellNumPerRow - 2][cellNumPerRow - 1]->alive) neighbors++;
				if (cellArr[cellNumPerRow - 1][cellNumPerRow - 1]->alive) neighbors++;
				if (cellArr[cellNumPerRow - 1][0]->alive) neighbors++;
				cellArr[i][j]->ncount = neighbors;
			}
			// bottom left corner check 
			else if (i == cellNumPerRow - 1 && j == 0) {
				if (cellArr[cellNumPerRow - 1][1]->alive) neighbors++;
				if (cellArr[cellNumPerRow - 1][cellNumPerRow - 1]->alive) neighbors++;
				if (cellArr[cellNumPerRow - 2][0]->alive) neighbors++;
				if (cellArr[cellNumPerRow - 2][1]->alive) neighbors++;
				if (cellArr[cellNumPerRow - 2][cellNumPerRow - 1]->alive) neighbors++;
				if (cellArr[1][0]->alive) neighbors++;
				if (cellArr[0][0]->alive) neighbors++;
				if (cellArr[0][cellNumPerRow - 1]->alive) neighbors++;
				cellArr[i][j]->ncount = neighbors;
			}
			// bottom right corner check
			else if (i == cellNumPerRow - 1 && j == cellNumPerRow - 1) {
				if (cellArr[cellNumPerRow - 1][cellNumPerRow - 2]->alive) neighbors++;
				if (cellArr[cellNumPerRow - 1][0]->alive) neighbors++;
				if (cellArr[cellNumPerRow - 2][cellNumPerRow - 1]->alive) neighbors++;
				if (cellArr[cellNumPerRow - 2][cellNumPerRow - 2]->alive) neighbors++;
				if (cellArr[cellNumPerRow - 2][0]->alive) neighbors++;
				if (cellArr[1][cellNumPerRow - 1]->alive) neighbors++;
				if (cellArr[0][cellNumPerRow - 1]->alive) neighbors++;
				if (cellArr[0][0]->alive) neighbors++;
				cellArr[i][j]->ncount = neighbors;
			}
			// top side check
			else if (i == 0) {
				if (cellArr[cellNumPerRow - 1][j - 1]->alive) neighbors++;
				if (cellArr[cellNumPerRow - 1][j]->alive) neighbors++;
				if (cellArr[cellNumPerRow - 1][j + 1]->alive) neighbors++;
				if (cellArr[0][j - 1]->alive) neighbors++;
				if (cellArr[0][j + 1]->alive) neighbors++;
				if (cellArr[1][j - 1]->alive) neighbors++;
				if (cellArr[1][j]->alive) neighbors++;
				if (cellArr[1][j + 1]->alive) neighbors++;
				cellArr[i][j]->ncount = neighbors;
			}
			// bottom side check
			else if (i == cellNumPerRow - 1) {
				if (cellArr[i - 1][j - 1]->alive) neighbors++;
				if (cellArr[i - 1][j]->alive) neighbors++;
				if (cellArr[i - 1][j + 1]->alive) neighbors++;
				if (cellArr[i][j - 1]->alive) neighbors++;
				if (cellArr[i][j + 1]->alive) neighbors++;
				if (cellArr[0][j - 1]->alive) neighbors++;
				if (cellArr[0][j]->alive) neighbors++;
				if (cellArr[0][j + 1]->alive) neighbors++;
				cellArr[i][j]->ncount = neighbors;
			}
			// left side check
			else if (j == 0) {
				if (cellArr[i - 1][cellNumPerRow - 1]->alive) neighbors++;
				if (cellArr[i][cellNumPerRow - 1]->alive) neighbors++;
				if (cellArr[i + 1][cellNumPerRow - 1]->alive) neighbors++;
				if (cellArr[i - 1][0]->alive) neighbors++;
				if (cellArr[i + 1][0]->alive) neighbors++;
				if (cellArr[i - 1][1]->alive) neighbors++;
				if (cellArr[i][1]->alive) neighbors++;
				if (cellArr[i + 1][1]->alive) neighbors++;
				cellArr[i][j]->ncount = neighbors;
			}
			// right side check
			else if (j == cellNumPerRow - 1) {
				if (cellArr[i - 1][cellNumPerRow - 2]->alive) neighbors++;
				if (cellArr[i][cellNumPerRow - 2]->alive) neighbors++;
				if (cellArr[i + 1][cellNumPerRow - 2]->alive) neighbors++;
				if (cellArr[i - 1][cellNumPerRow - 1]->alive) neighbors++;
				if (cellArr[i + 1][cellNumPerRow - 1]->alive) neighbors++;
				if (cellArr[i - 1][0]->alive) neighbors++;
				if (cellArr[i][0]->alive) neighbors++;
				if (cellArr[i + 1][0]->alive) neighbors++;
				cellArr[i][j]->ncount = neighbors;
			}
			else {
				if (cellArr[i - 1][j - 1]->alive) neighbors++;
				if (cellArr[i - 1][j]->alive) neighbors++;
				if (cellArr[i - 1][j + 1]->alive) neighbors++;
				if (cellArr[i][j - 1]->alive) neighbors++;
				if (cellArr[i][j + 1]->alive) neighbors++;
				if (cellArr[i + 1][j - 1]->alive) neighbors++;
				if (cellArr[i + 1][j]->alive) neighbors++;
				if (cellArr[i + 1][j + 1]->alive) neighbors++;
				cellArr[i][j]->ncount = neighbors;
			}
		}
	}
}

void ofApp::updateStatus() {
	for (auto row : cellArr) {
		for (auto cell : row) {			 
			if (cell->ncount == allowedNumberOfNeighbors) {
				cell->alive = true;
				cell->aliveCount++;
				if (cell->aliveCount > 50) cell->aliveCount = 1;
			}
			else if (cell->ncount == allowedNumberOfNeighbors - 1) {}
			else {
				cell->alive = false;
				cell->aliveCount = 0;
			}
			cell->ncount = 0;
		}
	}
	ofEnableDepthTest();
	
}

//--------------------------------------------------------------
void ofApp::update(){
	countNeighbors();
	updateStatus();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(0);
	ofDrawBitmapString("'r' to reset", 20, 20);
	ofDrawBitmapString("'m' to switch mouse mode", 20, 30);
	ofDrawBitmapString("on click: " + clickMode, 20, 40);
	light.enable();
	ofTranslate(0, ofGetHeight() / 4);
	ofRotate(deg, 1, 0, 0);
	ofTranslate(0, -ofGetHeight() / 4);
	ofPushMatrix();
	for (int i = 0; i < cellNumPerRow; i++) {
		for (int j = 0; j < cellNumPerRow; j++) {
			if (cellArr[i][j]->alive) {
				ofSetColor(0);
				ofDrawRectangle(cellArr[i][j]->xpos, cellArr[i][j]->ypos, cellWidth, cellHeight);
				ofSetColor(255);
				ofDrawBox(cellArr[i][j]->xpos, cellArr[i][j]->ypos, 50, cellWidth, cellHeight, cellWidth);
				ofSetColor(60, 50);
				for (int k = 1; k <= cellArr[i][j]->aliveCount; k++) {
					ofDrawBox(cellArr[i][j]->xpos, cellArr[i][j]->ypos, -cellWidth * k, cellWidth, cellHeight, cellWidth);
				}
				
			}
		}
	}
	ofPopMatrix();

	light.disable();
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'm': mouseMode++;
		mouseMode %= 2;
		if (mouseMode == 0) clickMode = "single cell";
		else clickMode = "glider";
		break;
	case 'r':
		for (auto row : cellArr) {
			for (auto cell : row) {
				cell->alive = (int)ofRandom(0, 2);
				if (cell->alive) cell->aliveCount = 1;
				else cell->aliveCount = 0;
			}
		}
		break;
	case 't':
		deg += 3;
		break;
	case 'y':
		deg -= 3;
		break;
	}



}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

	for (int i = 0; i < cellNumPerRow; i++) {
		for (int j = 0; j < cellNumPerRow; j++) {
			if (x >= cellArr[i][j]->xpos && x <= cellArr[i][j]->xpos + cellWidth &&
				y >= cellArr[i][j]->ypos && y <= cellArr[i][j]->ypos + cellHeight) {
				if (mouseMode == 1) {
					cellArr[i][j - 1]->alive = true;
					cellArr[i][j + 1]->alive = true;
					cellArr[i + 1][j]->alive = true;
					cellArr[i + 1][j + 1]->alive = true;
					cellArr[i - 1][j + 1]->alive = true;
				}
				else if (mouseMode == 0) {
					cellArr[i][j]->alive = true;
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
