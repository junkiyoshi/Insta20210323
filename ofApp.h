#pragma once
#include "ofMain.h"

class Walker {

public:
	Walker(glm::vec2 location, ofColor color);
	void update();
	void change_rotate();
	void draw();
private:

	glm::vec2 rotate_location;
	float rotate_radius;
	float rotate_deg;
	int rotate_direction;

	vector<glm::vec2> log;
	ofColor color;
};

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void mouseEntered(int x, int y) {};
	void mouseExited(int x, int y) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	ofEasyCam cam;
	vector<Walker> walker_list;
};