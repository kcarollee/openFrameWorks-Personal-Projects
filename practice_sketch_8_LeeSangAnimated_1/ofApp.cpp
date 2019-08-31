#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){
	// initialize tileMatrix. 
	float initx = 259;
	float inity = 42;
	int tileFileNameIndex = 0;
	for (int i = 0; i < 11; i++) {
		vector<Tile*> newRow;
		for (int j = 0; j < 11; j++) {
			Tile* newTile = new Tile;
			newTile->setPos(initx, inity);
			newTile->setImage(tileFileNames[tileFileNameIndex]);
			newRow.push_back(newTile);
			//cout << newTile->name << ", " << newTile->xpos << ", " << newTile->ypos << endl;
			initx += 46;
			tileFileNameIndex++;
		}
		initx = 259;
		inity += 46;
		tileMatrix.push_back(newRow);
	}

	// load images directly into each Tile
	ofDirectory dir("C:\\Users\\kcaro\\OneDrive\\Documents\\of_v0.10.1_vs2017_release\\apps\\myApps\\Sketch_8\\bin\\data");
	background.load("background.png");
	date.load("date.png");
	title.load("title.png");
	//date.resize(date.getWidth() * 0.9, date.getHeight() * 0.9);
	//title.resize(date.getWidth() * 0.9, date.getHeight() * 0.9);
	dir.allowExt("png");
	dir.listDir();
	
	/*
	for (int i = 0; i < dir.size(); i++) {
		cout << dir.getName(i) << endl;	
		cout << getNumberID(dir.getName(i)) << endl;
		cout << getNumberName(dir.getName(i)) << endl;
	}
	
	cout << dir.size() << endl;
	cout << dir.path() << endl;
	*/

	randomHighlight = upHighlight = leftHighlight =
	downHighlight = rightHighlight = resetHighlight = ofColor(20);
}

void ofApp::moveColUp(int colNum) {
	int lastPosx = tileMatrix[10][colNum]->xpos;
	int lastPosy = tileMatrix[10][colNum]->ypos;
	for (int i = 10; i >= 0; i--) {
		if (i == 0) {
			tileMatrix[i][colNum]->xpos = lastPosx;
			tileMatrix[i][colNum]->ypos = lastPosy;
		}
		else {
			tileMatrix[i][colNum]->xpos = tileMatrix[i - 1][colNum]->xpos;
			tileMatrix[i][colNum]->ypos = tileMatrix[i - 1][colNum]->ypos;
		}
	}
}

void ofApp::moveColDown(int colNum) {
	int firstPosx = tileMatrix[0][colNum]->xpos;
	int firstPosy = tileMatrix[0][colNum]->ypos;
	for (int i = 0; i < 11; i++) {
		if (i == 10) {
			tileMatrix[i][colNum]->xpos = firstPosx;
			tileMatrix[i][colNum]->ypos = firstPosy;
		}
		else {
			tileMatrix[i][colNum]->xpos = tileMatrix[i + 1][colNum]->xpos;
			tileMatrix[i][colNum]->ypos = tileMatrix[i + 1][colNum]->ypos;
		}
	}
}

void ofApp::moveRowLeft(int rowNum) {
	int lastPosx = tileMatrix[rowNum][10]->xpos;
	int lastPosy = tileMatrix[rowNum][10]->ypos;
	for (int i = 10; i >= 0; i--) {
		if (i == 0) {
			tileMatrix[rowNum][i]->xpos = lastPosx;
			tileMatrix[rowNum][i]->ypos = lastPosy;
		}
		else {
			tileMatrix[rowNum][i]->xpos = tileMatrix[rowNum][i - 1]->xpos;
			tileMatrix[rowNum][i]->ypos = tileMatrix[rowNum][i - 1]->ypos;
		}
	}
}

void ofApp::moveRowRight(int rowNum) {
	int firstPosx = tileMatrix[rowNum][0]->xpos;
	int firstPosy = tileMatrix[rowNum][0]->ypos;
	for (int i = 0; i < 11; i++) {
		if (i == 10) {
			tileMatrix[rowNum][i]->xpos = firstPosx;
			tileMatrix[rowNum][i]->ypos = firstPosy;
		}
		else {
			tileMatrix[rowNum][i]->xpos = tileMatrix[rowNum][i + 1]->xpos;
			tileMatrix[rowNum][i]->ypos = tileMatrix[rowNum][i + 1]->ypos;
		}
	}

}
void ofApp::switchTilePos() {
	int x1 = (int)ofRandom(0, 11);
	int y1 = (int)ofRandom(0, 11);
	int x2 = (int)ofRandom(0, 11);
	int y2 = (int)ofRandom(0, 11);

	int originalx = tileMatrix[y1][x1]->xpos;
	int originaly = tileMatrix[y1][x1]->ypos;

	tileMatrix[y1][x1]->xpos = tileMatrix[y2][x2]->xpos;
	tileMatrix[y1][x1]->ypos = tileMatrix[y2][x2]->ypos;

	tileMatrix[y2][x2]->xpos = originalx;
	tileMatrix[y2][x2]->ypos = originaly;
}

void ofApp::reset() {
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			tileMatrix[i][j]->reset();
		}
	}
	isSwitchMode = isRightMode = isLeftMode = 
	isUpMode = isDownMode = false;
}
string ofApp::getNumberID(string fileName) {
	string idString;	
	if (48 <= fileName.at(fileName.size() - 5) && fileName.at(fileName.size() - 5) <= 57 &&
		48 <= fileName.at(fileName.size() - 6) && fileName.at(fileName.size() - 6) <= 57) {
		idString = fileName.substr(fileName.size() - 6, 2);
		return idString;
	}
	else
		return "NOT A TILE";
}

string ofApp::getNumberName(string fileName) {
	string idString;
	if (48 <= fileName.at(fileName.size() - 5) && fileName.at(fileName.size() - 5) <= 57 &&
		48 <= fileName.at(fileName.size() - 6) && fileName.at(fileName.size() - 6) <= 57) {
		idString = fileName.substr(0, 2);
		return idString;
	}
	return "NOT A TILE";
}

//--------------------------------------------------------------
void ofApp::update(){
	
	if (isSwitchMode) switchTilePos();
	if (isRightMode) {
		for (int i = 0; i < 11; i++) {
			moveRowRight(i);
			ofSleepMillis(10);
		}
	}
	if (isLeftMode) {
		for (int i = 0; i < 11; i++) {
			moveRowLeft(i);
			ofSleepMillis(10);
		}
	}
	if (isUpMode) {
		for (int i = 0; i < 11; i++) {
			moveColUp(i);
			ofSleepMillis(10);
		}
	}
	if (isDownMode) {
		for (int i = 0; i < 11; i++) {
			moveColDown(i);
			ofSleepMillis(10);
		}
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	background.draw(0, 0);
	date.draw(120, 12);
	title.draw(815, 12);
	for (auto row : tileMatrix) {
		for (auto tile : row) {
			tile->draw();
		}
	}
	
	ofDrawBitmapStringHighlight("'r' : random", 20, 300, randomHighlight);
	ofDrawBitmapStringHighlight("'w' : up", 20, 330, upHighlight);
	ofDrawBitmapStringHighlight("'a' : left", 20, 360, leftHighlight);
	ofDrawBitmapStringHighlight("'s' : down", 20, 390, downHighlight);
	ofDrawBitmapStringHighlight("'d' : right", 20, 420, rightHighlight);
	ofDrawBitmapStringHighlight("'z' : reset", 20, 450, resetHighlight);
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'r': isSwitchMode = !isSwitchMode;
		if (isSwitchMode) randomHighlight = ofColor(150);
		else randomHighlight = ofColor(20);
		break;
	case 'w': isUpMode = !isUpMode;
		if (isUpMode) upHighlight = ofColor(150);
		else upHighlight = ofColor(20);
		break;
	case 's': isDownMode = !isDownMode;
		if (isDownMode) downHighlight = ofColor(150);
		else downHighlight = ofColor(20);
		break;
	case 'a': isLeftMode = !isLeftMode;
		if (isLeftMode) leftHighlight = ofColor(150);
		else leftHighlight = ofColor(20);
		break;
	case 'd': isRightMode = !isRightMode; 
		if (isRightMode) rightHighlight = ofColor(150);
		else rightHighlight = ofColor(20);
		break;
	case 'z': reset(); 
		resetHighlight = ofColor(150);
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == 'z') {
		resetHighlight = ofColor(20);
	}
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
