#include "ofApp.h"
#include "glm/vec3.hpp"

#include <memory>

//--------------------------------------------------------------
void ofApp::setup(){

	box_generator pos{};
	pos.negavite_corner = glm::vec4(-100, -100, -100, 0);
	pos.positive_corner = glm::vec4(100, 100, 100, 0);

	particle_emitter emitter;
	emitter.add_generator(std::make_shared<box_generator>(pos));
	emitter.emit_rate = 1;
	system.add_emitter(std::make_shared<particle_emitter>(emitter));

	gravity g_update;
	system.add_updater(std::make_shared<gravity>(g_update));

	position pos_update;
	system.add_updater(std::make_shared<position>(pos_update));

	bottom_floor podloga;
	system.add_updater(std::make_shared<bottom_floor>(podloga));
	
}

//--------------------------------------------------------------
void ofApp::update(){
	system.update(1);
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
	ofNoFill();
	
	//ofDrawIcoSphere
	system.draw();



	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'x')
	{
		pos.x++;
	}
	if (key == 'y')
	{
		pos.y++;
	}
	if (key == 'z')
	{
		pos.z++;
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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
