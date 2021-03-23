#include "ofApp.h"

//--------------------------------------------------------------
Walker::Walker(glm::vec2 location, ofColor color) {

	this->log.push_back(location);
	this->change_rotate();

	this->color = color;
}

//--------------------------------------------------------------
void Walker::update() {

	if (glm::length(this->log.back()) > 720) {

		this->log.clear();
		auto location = glm::vec2(ofRandom(-300, 300), ofRandom(-300, 300));
		this->log.push_back(location);
		this->change_rotate();
	}

	auto location = this->rotate_location + glm::vec2(this->rotate_radius * cos(this->rotate_deg * DEG_TO_RAD), this->rotate_radius * sin(this->rotate_deg * DEG_TO_RAD));
	this->rotate_deg += this->rotate_direction * 10;
	this->rotate_radius -= 0.25;

	this->log.push_back(location);

	if (this->rotate_radius < 0 || ofRandom(100) < 0.5) {

		this->change_rotate();
	}

	while (this->log.size() > 150) { this->log.erase(this->log.begin()); }
}

//--------------------------------------------------------------
void Walker::change_rotate() {

	auto tmp_radius = ofRandom(30, 80);
	auto tmp_deg = this->rotate_deg + ofRandom(-90, 90);
	this->rotate_location = this->log.back() + glm::vec2(tmp_radius * cos(tmp_deg * DEG_TO_RAD), tmp_radius * sin(tmp_deg * DEG_TO_RAD));
	this->rotate_deg = 180 + tmp_deg;
	this->rotate_radius = tmp_radius;

	this->rotate_direction = ofRandom(100) < 50 ? 1 : -1;
}

//--------------------------------------------------------------
void Walker::draw() {

	ofMesh mesh, frame;
	frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	for (int i = 0; i < this->log.size(); i++) {

		auto right = glm::vec3(this->log[i], -15);
		auto left = glm::vec3(this->log[i], 15);

		mesh.addVertex(right);
		mesh.addVertex(left);
		
		frame.addVertex(right);
		frame.addVertex(left);

		if (i > 0) {

			mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 2); mesh.addIndex(mesh.getNumVertices() - 4);
			mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 3); mesh.addIndex(mesh.getNumVertices() - 4);

			frame.addIndex(frame.getNumVertices() - 1); frame.addIndex(frame.getNumVertices() - 3);
			frame.addIndex(frame.getNumVertices() - 2); frame.addIndex(frame.getNumVertices() - 4);
		}

		mesh.addColor(color);
		mesh.addColor(color);

		frame.addColor(ofColor(239));
		frame.addColor(ofColor(239));
	}

	frame.addIndex(0); frame.addIndex(1);
	frame.addIndex(frame.getNumVertices() - 1);	frame.addIndex(frame.getNumVertices() - 2);

	mesh.draw();
	frame.drawWireframe();
}

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();
	ofSetLineWidth(2);

	vector<ofColor> base_color_list;
	ofColor color;
	vector<int> hex_list = { 0x247BA0, 0x70C1B3, 0xB2DBBF, 0xF3FFBD, 0xFF1654 };
	for (auto hex : hex_list) {

		color.setHex(hex);
		base_color_list.push_back(color);
	}

	for (int i = 0; i < 20; i++) {

		this->walker_list.push_back(Walker(glm::vec2(ofRandom(-300, 300), ofRandom(-300, 300)), base_color_list[ofRandom(base_color_list.size())]));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	for (auto& walker : this->walker_list) {

		walker.update();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (auto& walker : this->walker_list) {

		walker.draw();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}