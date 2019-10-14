#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	fontSize = 15;
	ofTrueTypeFontSettings settings("UnBatang.ttf", fontSize);
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
	font.load(settings);
	shader.load("shadersGL3/shader");
	ofSetBackgroundColor(235, 74, 89);
	chatScreen.setup(0.4 * ofGetWidth(), 0.8 * ofGetHeight(),
		0.1 * ofGetWidth(), 0.1 * ofGetHeight());
	imageDrop.setup(0.3 * ofGetWidth(), 0.4 * ofGetHeight(),
		0.6 * ofGetWidth(), 0.1 * ofGetHeight());
	fontDrop.setup(0.3 * ofGetWidth(), 0.4 * ofGetHeight(),
		0.6 * ofGetWidth(), 0.6 * ofGetHeight());
	chatBoxNum = 8;
	firstChatBoxPos = chatScreen.getFirstChatBoxPos();

	firstChatBoxPos = chatScreen.getFirstChatBoxPos();
	
	stringBuffer = ofBufferFromFile("#zzamtiger0310.log");
	it = stringBuffer.getLines().begin(), end = stringBuffer.getLines().end();

	line = *it;
	isShaderMode = true;
	
}

//--------------------------------------------------------------
void ofApp::update(){
	//parseText("#vinesauce.log");
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	chatScreen.draw();
	imageDrop.draw();
	fontDrop.draw();
	for (int i = 0; i < chatBoxArr.size(); i++) {		
		if (isShaderMode) chatBoxArr[i]->draw(shader);
		else chatBoxArr[i]->draw(0);
		chatBoxArr[i]->displayText(0);	
	}
}

string ofApp::organizeText(string text) {
	string userID, message, formattedText, finalFormattedText;
	int index = 12;
	int lineCharLimit = 0;
	//cout << "CALLED" << endl;
	if (!text.empty()) {
		//cout << "CALLED" << endl;
		if (text.at(0) == '#' || text.at(11) != '<' || text.at(0) == '-') {
			//cout << "CALLED" << endl;
			return text;
		}
		else {
			//cout << "CALLED" << endl;
			for (; index < text.size() && text.at(index) != '>'; index++) {

				userID.push_back(text.at(index));

			}

			index++;
			for (; index < text.size() && text.at(index) != '\n'; index++) {
				message.push_back(text.at(index));
				
			}
		}

	}
	else {
		//cout << "CALLED" << endl;
		return "NO MORE TEXT TO DISPLAY";
	}
	
	formattedText = userID + ":" + message;
	return formattedText;
	//cout << formattedText << endl;
	
}

string ofApp::getFormattedTextLine(string formattedText) {
	string temp;
	int substringStartingIndex = 0;
	bool textDivided = false;
	if (font.getStringBoundingBox(formattedText, 0, 0).width > chatScreen.getChatBoxWidth()) {
		//cout << "TESTING " << font.getStringBoundingBox(formattedText, 0, 0).width << " " << chatScreen.getChatBoxWidth() << endl;
		for (int i = 0; i < formattedText.size(); i++) {
			/*
			if (font.getSize() * i * 1.8> chatScreen.getChatBoxWidth()) {
				lineCharLimit = i - 1;
				break;
			}
			*/

			if (font.getStringBoundingBox(formattedText.substr(substringStartingIndex, i - substringStartingIndex + 1), 0, 0).width > chatScreen.getChatBoxWidth()) {
				//cout <<"Limit: " <<  font.getStringBoundingBox(formattedText.substr(0, i), 0, 0).width << " i:" << i << endl;
				//lineCharLimit = i - 1;
				//break;
				temp.append(formattedText.substr(substringStartingIndex, i - substringStartingIndex + 1));
				temp.append("\n");
				substringStartingIndex = i - 1;
				textDivided = true;
				//cout << "TTTTTT" << endl;
			}
			else {
				if (textDivided) {
					temp.append(formattedText.substr(substringStartingIndex, formattedText.size() - substringStartingIndex));
					break;
				}
			}
		}
		int originalSize = formattedText.size();
		/*
		for (int i = lineCharLimit,  iterationNum = 0;iterationNum < (int) (originalSize / lineCharLimit); i *= 2, iterationNum++) {
			formattedText.insert( i + iterationNum, "\n");/////////////////////////////////////////////try putting it in the if statement above
		}
		*/
		return temp;

	}
	else return formattedText;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 's':
		isShaderMode = true;
		break;
	case 'i': // insert a new text box for testing purposes
		if (chatBoxArr.size() >= chatBoxNum) {
			chatBoxArr.pop_front();
			
			ChatBox* chatBox = new ChatBox();
			chatBox->setup(chatScreen.getChatBoxWidth(), chatScreen.getChatBoxHeight(chatBoxNum),
				firstChatBoxPos.x, firstChatBoxPos.y + chatBoxNum * chatScreen.getChatBoxHeight(chatBoxNum));
			chatBox->setFont(font);
			chatBoxArr.push_back(chatBox);
			if (!isShaderMode) {
				chatBox->setImage(draggedImage);
			}
			
			if (line.empty() == false) {
				if (textArr.size() >= 10) {
					textArr.pop_front();
					textArr.push_back(getFormattedTextLine(organizeText(line)));
					++it;
					
				}
				else {
					
					textArr.push_back(getFormattedTextLine(organizeText(line)));
					++it;
				}
				line = *it;

			}
			if (textArr.size() > 0) {
				chatBox->setText(textArr[textArr.size() - 1]);
				//cout << textArr[textArr.size() - 1] << endl;
			}
			for (auto box : chatBoxArr) {
				box->move();
			}
		}
		else {
			ChatBox* chatBox = new ChatBox();
			chatBox->setup(chatScreen.getChatBoxWidth(), chatScreen.getChatBoxHeight(chatBoxNum),
				firstChatBoxPos.x, firstChatBoxPos.y + chatBoxArr.size() * chatScreen.getChatBoxHeight(chatBoxNum));
			chatBoxArr.push_back(chatBox);
			chatBox->setFont(font);
			if (!isShaderMode) {
				chatBox->setImage(draggedImage);
			}
			
			if (line.empty() == false) {
				if (textArr.size() >= 10) {
					textArr.pop_front();
					textArr.push_back(getFormattedTextLine(organizeText(line)));
					++it;
				}
				else {
					textArr.push_back(getFormattedTextLine(organizeText(line)));
					++it;
				}
				line = *it;
			}
			if (textArr.size() > 0) {
				chatBox->setText(textArr[textArr.size() - 1]);
				
			}
		}
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

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	chatScreen.setup(0.65 * w, 0.95 * h,
		0.025 * w, 0.025 * h);
	imageDrop.setup(0.275 * w, 0.4625 * h,
		0.7 * w, 0.025 * h);
	fontDrop.setup(0.275 * w, 0.4625 * h,
		0.7 * w, 0.5125 * h);
	firstChatBoxPos = chatScreen.getFirstChatBoxPos();
	for (auto chatBox : chatBoxArr) {
		chatBox->setup(chatScreen.getChatBoxWidth(), chatScreen.getChatBoxHeight(chatBoxNum),
			firstChatBoxPos.x, firstChatBoxPos.y);
		firstChatBoxPos.y += chatScreen.getChatBoxHeight(chatBoxNum);
		

	}
	for (auto chatBox : chatBoxArr) {
		
		chatBox->setText(getFormattedTextLine(chatBox->originalText));
		//cout << "ORGANIZED TEXT: " << organizeText(chatBox->text) << endl;

	}
	firstChatBoxPos = chatScreen.getFirstChatBoxPos();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	if (dragInfo.files.size() > 0) {
		dragPt = dragInfo.position;
		if (dragPt.x > imageDrop.xpos && dragPt.x < imageDrop.xpos + imageDrop.width &&
			dragPt.y > imageDrop.ypos && dragPt.y < imageDrop.ypos + imageDrop.height) {
			isShaderMode = false;
			draggedImages.assign(dragInfo.files.size(), ofImage());
			draggedImage.load(dragInfo.files[0]);
			
			for (auto chatBox : chatBoxArr) {
				chatBox->setImage(draggedImage);
				
			}
		}
		else if (dragPt.x > fontDrop.xpos && dragPt.x < fontDrop.xpos + fontDrop.width &&
			dragPt.y > fontDrop.ypos && dragPt.y < fontDrop.ypos + fontDrop.height) {
			ofTrueTypeFontSettings settings(dragInfo.files[0], fontSize);
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
			font.load(settings);
		
			for (auto chatBox : chatBoxArr) {
				chatBox->setFont(font);
			}
		}
	}
}
