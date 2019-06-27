#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);

	this->font_size = 15;
	ofTrueTypeFontSettings font_settings("fonts/EmojiSymbols-Regular.ttf", this->font_size);
	font_settings.antialiased = true;
	font_settings.addRanges(ofAlphabet::Emoji);
	this->font.load(font_settings);

	this->words = {

		u8"🍶", u8"🍷", u8"🍸", u8"🍹" , u8"🍺",
		u8"🍻", u8"🍎", u8"🎃", u8"🍭", u8"👻",
		u8"😁", u8"😍", u8"😂", u8"😱", u8"😎",
		u8"🎵", u8"🎶",  
	};

	for (int x = 0; x < ofGetWidth(); x += this->font_size) {

		vector<string> line;
		for (int y = 0; y <= ofGetHeight(); y += this->font_size) {

			line.push_back(this->words[(int)(ofRandom(this->words.size()))]);
		}

		this->matrix.push_back(line);
		this->random_values.push_back(ofRandom(ofGetHeight() * 1.5));
	}

}
//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int row = 0; row < this->matrix.size(); row++) {

		int x = row * this->font_size;
		auto top = true;
		int random_value = this->random_values[row];
		for (int col = 0; col < this->matrix[row].size(); col++) {

			int y = col * this->font_size * 1.25;
			int alpha = (random_value + ofGetFrameNum() * 4 + y) % (int)(ofGetHeight() * 1.5);
			if (alpha <= 255) {

				if (top) {

					this->matrix[row][col] = this->words[(int)(ofRandom(this->words.size()))];
					top = false;
				}

				auto rb = ofMap(alpha, 0, 50, 239, 0);
				ofSetColor(rb, 239, rb, 255 - alpha);

				ofPushMatrix();
				ofTranslate(x, ofGetHeight() - y);

				this->font.drawString(this->matrix[row][col], 0, 0);

				ofPopMatrix();
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}