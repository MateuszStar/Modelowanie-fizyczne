#pragma once

#include "ofMain.h"

#include "../../generators.h"
#include "../../emitters.h"
#include "../../updaters.h"
#include "../../particle_system.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofEasyCam cam;

	glm::vec3 pos = { 0, 0, 0 };
	float radius = 10;

	particle_system system{ 100, 1000 };

	std::shared_ptr<wind> wiatr_ptr = nullptr;

	ofImage background;



};
