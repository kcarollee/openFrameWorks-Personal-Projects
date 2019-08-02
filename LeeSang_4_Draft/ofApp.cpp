#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// initialize tileMatrix. images are not loaded in yet.
	float initx = 259;
	float inity = 42;
	for (int i = 0; i < 11; i++) {
		vector<Tile*> newRow;
		for (int j = 0; j < 11; j++) {
			Tile* newTile = new Tile;
			newTile->setPos(initx, inity);
			newRow.push_back(newTile);
			//cout << newTile->xpos << ", " << newTile->ypos << endl;
			initx += 46;
			
		}
		initx = 259;
		inity += 46;
		tileMatrix.push_back(newRow);
	}

	// load images directly into each Tile
	ofDirectory dir("C:\\Users\\kcaro\\OneDrive\\Documents\\of_v0.10.1_vs2017_release\\apps\\myApps\\Sketch_8\\bin\\data");
	background.load("background.png");
	dir.allowExt("png");
	dir.listDir();
	
	
	for (int i = 0; i < dir.size(); i++) {
		cout << dir.getName(i) << endl;	
		cout << getNumberID(dir.getName(i)) << endl;
		cout << getNumberName(dir.getName(i)) << endl;
	}
	
	cout << dir.size() << endl;
	cout << dir.path() << endl;
	
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
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	background.draw(0, 0);	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
