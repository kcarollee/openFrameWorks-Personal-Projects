#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(200, 200, 200);
	carr.clear();
	collided = false;
	circleID = 0;
	fnt.load("verdana.ttf", 24);
	message = "";
	
}

//--------------------------------------------------------------
void ofApp::update(){
	collisionCheck(carr);
	windowCollision(carr);
	for (auto circ : carr) {
		circ->move();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(0, 200, 0);
	fnt.drawString(message, 30, 60);
	for (auto circ : carr) {
		circ->draw();
	}
}
void ofApp::windowCollision(vector <Circle*> carr)
{
		for (int i = 0; i < carr.size(); i++) {
			if (((carr[i]->position.x) - (carr[i]->radius) <= 0) ||
				((carr[i]->position.x) + (carr[i]->radius)) >= ofGetWidth()) {
				carr[i]->velocity.x *= -1;
			}
			if (((carr[i]->position.y) - (carr[i]->radius) <= 0) ||
				((carr[i]->position.y) + (carr[i]->radius)) >= ofGetHeight()) {
				carr[i]->velocity.y *= -1;
			}
		}
	
}
void ofApp::collisionCheck(vector<Circle*> carr)
{
	for (int i = 0; i < carr.size(); i++) {
		for (int j = 0; j < carr.size(); j++)
			if (i == j) {
				continue;
			}
			else {
				if (ofDist(carr[i]->position.x, carr[i]->position.y,
					carr[j]->position.x, carr[j]->position.y) <=
					(carr[i]->showRadius() + carr[j]->showRadius())) {
					carr[i]->velocity.x *= 0.9;
					carr[i]->velocity.y *= 0.9;
					carr[j]->velocity.x *= 0.9;
					carr[j]->velocity.y *= 0.9;
					//carr.erase(carr.begin() + i);
					//carr.erase(carr.begin() + j);
					//cout <<i + 1<<" and "<<j + 1<<" collided"<< endl;
					//cout << i + 1 << "'s x velocity: " << carr[i]->velocity.x << "  "
					//	<< j + 1 << "'s x velocity: " << carr[j]->velocity.x << endl;
				}
			}
	}
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (carr.size() == 0) {

	}
	else if (key == 'd') {

		carr.pop_back();
		circleID -= 1;
		message = "Ball #" + to_string(circleID) + " deleted";
	}
	
	if (key == 'a') {
		vel.x = ofRandom(-10, 10);
		vel.y = ofRandom(-10, 10);

		varrx.push_back(vel.x);
		varry.push_back(vel.y);

		Circle *c;
		c = new Circle();
		c->setup(pos, vel, ofRandom(20, 40));
		c->id_num = circleID;
		carr.push_back(c);
		
		message = "Ball #" + to_string(circleID) + " created";

		circleID += 1;

	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	pos.x = x;
	pos.y = y;

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
	//pos.x = x;
	//pos.y = y;

	//vel.x = ofRandom(-10, 10);
	//vel.y = ofRandom(-10, 10);

	//varrx.push_back(vel.x);
	//varry.push_back(vel.y);

	//Circle *c;
	//c = new Circle();
	//c->setup(pos, vel, ofRandom(20, 40));
	//carr.push_back(c);
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
