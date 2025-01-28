#include "ofApp.h"
#include "glm/vec3.hpp"

#include <memory>

//--------------------------------------------------------------
void ofApp::setup(){

	//
	//  generators
	//

	box_generator pos{};
	pos.negavite_corner = glm::vec4(-100, -100, -100, 0);
	pos.positive_corner = glm::vec4(100, 100, 100, 0);

	particle_emitter emitter;
	emitter.add_generator(std::make_shared<box_generator>(pos));
	emitter.emit_rate = 1;
	system.add_emitter(std::make_shared<particle_emitter>(emitter));

	//
	//  forces
	//

	gravity g_update;
	system.add_updater(std::make_shared<gravity>(g_update));

	//wind wiatr;
	//std::shared_ptr<wind> wiatr_ptr = std::make_shared<wind>(wiatr);
	system.add_updater(wiatr_ptr);

	//
	//  movement
	//

	acceleration acc_updater;
	system.add_updater(std::make_shared<acceleration>(acc_updater));

	velocity vel_updater;
	system.add_updater(std::make_shared<velocity>(vel_updater));

	position pos_update;
	system.add_updater(std::make_shared<position>(pos_update));

	//
	//  collisions
	//

	axis_wall podloga;
	podloga.axis = &glm::vec4::y;
	podloga.position = -300;
	podloga.positive_direction = false;
	system.add_updater(std::make_unique<axis_wall>(podloga));

	axis_wall wallxp;
	wallxp.axis = &glm::vec4::x;
	wallxp.position = 300;
	wallxp.positive_direction = true;
	system.add_updater(std::make_shared<axis_wall>(wallxp));

	axis_wall wallxm;
	wallxm.axis = &glm::vec4::x;
	wallxm.position = -300;
	wallxm.positive_direction = false;
	system.add_updater(std::make_shared<axis_wall>(wallxm));

	axis_wall wallzp;
	wallzp.axis = &glm::vec4::z;
	wallzp.position = 300;
	wallzp.positive_direction = true;
	system.add_updater(std::make_shared<axis_wall>(wallzp));

	axis_wall wallzm;
	wallzm.axis = &glm::vec4::z;
	wallzm.position = -300;
	wallzm.positive_direction = false;
	system.add_updater(std::make_shared<axis_wall>(wallzm));


	force_clearer clearer;
	system.add_updater(std::make_shared<force_clearer>(clearer));
	
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
	if (key == 'w')
	{
		wiatr_ptr->force += glm::vec4{1, 0, 0, 0};
	}
	if (key == 's')
	{
		wiatr_ptr->force += glm::vec4{ -1, 0, 0, 0 };
	}
	if (key == 'a')
	{
		wiatr_ptr->force += glm::vec4{ 0, 0, 1, 0 };
	}
	if (key == 'd')
	{
		wiatr_ptr->force += glm::vec4{ 0, 0, -1, 0 };
	}
	std::cout << wiatr_ptr->force << "\n";
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
