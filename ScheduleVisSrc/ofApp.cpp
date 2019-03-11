#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	font.load("verdana.ttf", 16);
	smallFont.load("verdana.ttf", 8);
	blockID = 1;
	setupInitial();

	registerColor = ofColor(255, 0, 255);
	resultsColor = ofColor(100, 100, 100);
	clearColor = ofColor(50, 24, 34);


	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 5; j++) {
			Block *rect;
			rect = new Block();
			rect->setup(j * (ofGetWidth() - 200) / 5 + 80, i * (ofGetHeight() - 200)/ 9 + 80, 
				((ofGetWidth()- 200)/ 5) - 10, ((ofGetHeight() - 200)/ 9) - 10);
			if (blockID <= 45) {
				rect->blockID = blockID;
				blockID++;
			}
			rectArr.push_back(rect);			
		}
	}

	//initializing register button
	registerButton.set(120, ofGetHeight() - 100, 200, 50);
	resultsButton.set(400, ofGetHeight() - 100, 200, 50);
	allClearButton.set(680, ofGetHeight() - 100, 200, 50);
}

//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < 9; i++) {
		font.drawString(period[i], 10, i * (ofGetHeight() - 200) / 9 + 120);
	}

	for (int j = 0; j < 5; j++) {
		font.drawString(days[j], j *(ofGetWidth() - 200) / 5 + 80, 60);
	}
	
	for (auto r : rectArr) {
		r->draw();
	}


	ofSetColor(0, 0, 0);
	smallFont.drawString(recordStatus, ofGetWidth() - 100, 40);

	

	ofSetColor(registerColor);
	ofDrawRectangle(registerButton);

	ofSetColor(resultsColor);
	ofDrawRectangle(resultsButton);

	ofSetColor(clearColor);
	ofDrawRectangle(allClearButton);

	ofSetColor(0, 0, 0);
	font.drawString("REGISTER", 140, ofGetHeight() - 70);

	ofSetColor(0, 0, 0);
	font.drawString("SEE RESULTS", 420, ofGetHeight() - 70);

	ofSetColor(0, 0, 0);
	font.drawString("CLEAR RECORD", 700, ofGetHeight() - 70);
}

void ofApp::setupInitial()
{
	initialAvail.clear();
	for (int i = 1; i <= 45; i++) {
		initialAvail.push_back(i);
	}
}

void ofApp::Compare()
{
	for (int i = 0; i < Block::scheduleArr.size(); i++) {
		for (int j = 0; j < Block::scheduleArr[i].size(); j++) {
			for (int k = 0; k < initialAvail.size(); k++) {
				if (initialAvail[k] == Block::scheduleArr[i][j]) {
					initialAvail.erase(initialAvail.begin() + k);
					break;
				}
			}
		}
	}
	cout << "available spaces: ";
	for (auto i : initialAvail) {
		cout << i << " ";
	}
	cout << endl;

	for (int i = 0; i < initialAvail.size(); i++) {
		rectArr[initialAvail[i] - 1]->color = ofColor(0, 0, 0);
	}
}
void ofApp::Clear()
{
	for (auto r : rectArr) {
		r->reset();
	}
	Block::scheduleArr.push_back(Block::schedule);
	cout << "Number of records: " << Block::scheduleArr.size() << endl;
	Block::schedule.clear();
}

bool ofApp::isInsideButton(int x, int y, ofRectangle rect)
{
	if ((x > rect.x) && (x < rect.x + rect.getWidth())) {
		if ((y > rect.y) && (y < rect.y + rect.getHeight())) {

			return true;
		}
	}

	return false;
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	if (isInsideButton(x, y, registerButton)) {
		registerColor = ofColor(20, 34, 45);
	}
	else if (isInsideButton(x, y, resultsButton)) {
		resultsColor = ofColor(40, 100, 231);
	}
	else if (isInsideButton(x, y, allClearButton)) {
		clearColor = ofColor(23, 34, 201);
	}
	else {
		registerColor = ofColor(255, 0, 255);
		resultsColor = ofColor(100, 100, 100);
		clearColor = ofColor(50, 24, 34);
	}

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (isInsideButton(x, y, registerButton)) {
	
		Clear();
		recordStatus = "Student " + to_string(Block::scheduleArr.size()) + " added.";
	}
	else if (isInsideButton(x, y, resultsButton)) {
		Compare();
	}
	else if (isInsideButton(x, y, allClearButton)) {
		Block::scheduleArr.clear();
		setupInitial();
	}
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
