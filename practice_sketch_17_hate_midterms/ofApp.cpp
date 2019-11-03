#include "ofApp.h"
ofTrueTypeFont globalFont;
//--------------------------------------------------------------
void ofApp::setup(){
	fontSize = 30;
	ofTrueTypeFontSettings settings("UnBatang.ttf", 11);
	settings.antialiased = true;
	settings.addRanges({
	ofUnicode::Latin1Supplement,
	ofUnicode::Hiragana,
	ofUnicode::Katakana,
	ofUnicode::CJKUnified,
	ofUnicode::HangulJamo,
	ofUnicode::HangulExtendedA,
	ofUnicode::HangulExtendedB,
	ofUnicode::HangulSyllables,
	ofUnicode::HangulCompatJamo,
		});
	ofTrueTypeFont::setGlobalDpi(72);
	globalFont.load(settings);
	//globalFont.loadFont("UnBatang.ttf", 30);
	testfont.load(settings);
	rowNum = 20;
	colNum = 20;
	int iter = 0;

	for (int i = 0; i < rowNum; i++) {
		for (int j = 0; j < colNum; j++) {
			if (iter % 2 == 0) {
				Tile* tile = new Tile();
				tile->setup(ofVec2f(i * ofGetWidth() / rowNum, j * ofGetHeight() / colNum), 
					ofGetWidth() / rowNum, ofGetHeight() / colNum, "A");
				tileArr.push_back(tile);
				cout << "PUSH" << endl;
				cout << tile->text << endl;
				iter++;
			}
			else {
				Tile* tile = new Tile();
				tile->setup(ofVec2f(i * ofGetWidth() / rowNum, j * ofGetHeight() / colNum),
					ofGetWidth() / rowNum, ofGetHeight() / colNum, "제B");
				tileArr.push_back(tile);
				cout << "PUSH" << endl;
				cout << tile->text << endl;
				iter++;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(0);
	testfont.drawString("하하하", 10, 20);
	for (auto tile : tileArr) {
		tile->draw();
	}
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
