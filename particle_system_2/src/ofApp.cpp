#include "ofApp.h"
#include "glm/vec3.hpp"

#include <memory>

//--------------------------------------------------------------
void ofApp::setup() {

	//
	//  generators
	//

	box_generator pos{};
	pos.negavite_corner = glm::vec4(-800, -100, -100, 0);
	pos.positive_corner = glm::vec4(800, -100, 100, 0);

	//random_sphere_velocity spherical_velocity;
	random_upwards_velocity random_up_velocity;
	random_up_velocity.directional_sway = 0.5;
	random_up_velocity.min_upwords_velocity = 0.7;

	random_rgb_color random_color;

	time_generator time_gen;
	time_gen.initial_value = 0;



	box_generator firework_particles_position;
	firework_particles_position.negavite_corner = { -100, -100, -100, 0 };
	firework_particles_position.positive_corner = { 100, 100, 100, 0 };

	directional_random_velocity firework_particles_velocity;
	firework_particles_velocity.radius = 0.5f;
	firework_particles_velocity.direction = { 0, 0, 0, 0 };

	random_death_time_generator rand_dtg;
	rand_dtg.min_value = 70;
	rand_dtg.max_value = 130;

	
	//
	// emitters
	//

	particle_emitter emitter(jeden);
	emitter.add_generator(std::make_shared<box_generator>(pos));
	emitter.add_generator(std::make_shared<random_upwards_velocity>(random_up_velocity));
	emitter.add_generator(std::make_shared<random_rgb_color>(random_color));
	emitter.add_generator(std::make_shared<time_generator>(time_gen));

	emitter.emit_rate = 0.15;
	system.add_emitter(std::make_shared<particle_emitter>(emitter));



	firework_particles_emitter firework_particles(dwa);

	std::shared_ptr<directional_random_velocity> fire_part_vel = std::make_shared<directional_random_velocity>(firework_particles_velocity);
	firework_particles.add_generator(fire_part_vel);
	
	std::shared_ptr<box_generator> fire_part_posi = std::make_shared<box_generator>(firework_particles_position);
	firework_particles.add_generator(fire_part_posi);

	firework_particles.add_generator(std::make_shared<random_rgb_color>(random_color));
	firework_particles.add_generator(std::make_shared<time_generator>(time_gen));
	firework_particles.add_generator(std::make_shared<random_death_time_generator>(rand_dtg));

	firework_particles.emit_rate = 0;
	std::shared_ptr<firework_particles_emitter> fire_part = std::make_shared<firework_particles_emitter>(firework_particles);
	system.add_emitter(fire_part);



	//
	//  forces
	//

	gravity g_update(jeden);
	system.add_updater(std::make_shared<gravity>(g_update));
	g_update.type = dwa;
	system.add_updater(std::make_shared<gravity>(g_update));

	wind wiatr(jeden);
	wiatr_ptr = std::make_shared<wind>(wiatr);
	system.add_updater(wiatr_ptr);

	//
	//  movement
	//


	acceleration acc_updater(jeden);
	system.add_updater(std::make_shared<acceleration>(acc_updater));
	acc_updater.type = dwa;
	system.add_updater(std::make_shared<acceleration>(acc_updater));

	velocity vel_updater(jeden);
	system.add_updater(std::make_shared<velocity>(vel_updater));
	vel_updater.type = dwa;
	system.add_updater(std::make_shared<velocity>(vel_updater));

	position pos_update(jeden);
	system.add_updater(std::make_shared<position>(pos_update));
	pos_update.type = dwa;
	system.add_updater(std::make_shared<position>(pos_update));


	//
	//  collisions
	//

	/*
	axis_wall podloga(jeden);
	podloga.axis = &glm::vec4::y;
	podloga.position = -300;
	podloga.positive_direction = false;
	system.add_updater(std::make_unique<axis_wall>(podloga));

	axis_wall wallxp(jeden);
	wallxp.axis = &glm::vec4::x;
	wallxp.position = 300;
	wallxp.positive_direction = true;
	system.add_updater(std::make_shared<axis_wall>(wallxp));

	axis_wall wallxm(jeden);
	wallxm.axis = &glm::vec4::x;
	wallxm.position = -300;
	wallxm.positive_direction = false;
	system.add_updater(std::make_shared<axis_wall>(wallxm));

	axis_wall wallzp(jeden);
	wallzp.axis = &glm::vec4::z;
	wallzp.position = 300;
	wallzp.positive_direction = true;
	system.add_updater(std::make_shared<axis_wall>(wallzp));

	axis_wall wallzm(jeden);
	wallzm.axis = &glm::vec4::z;
	wallzm.position = -300;
	wallzm.positive_direction = false;
	system.add_updater(std::make_shared<axis_wall>(wallzm));

	//*/

	//
	// other
	//

	time_ticking time_tick(jeden);
	system.add_updater(std::make_shared<time_ticking>(time_tick));
	time_tick.type = dwa;
	system.add_updater(std::make_shared<time_ticking>(time_tick));

	time_killer time_kill(jeden);
	time_kill.death_value = 300;
	system.add_updater(std::make_shared<time_killer>(time_kill));
	//time_kill.type = dwa;
	//time_kill.death_value = 100;
	//system.add_updater(std::make_shared<time_killer>(time_kill));

	self_time_killer self_time_kill(dwa);
	system.add_updater(std::make_shared<self_time_killer>(self_time_kill));

	time_activation firework_explosion(jeden);
	firework_explosion.velocity_gen = fire_part_vel;
	firework_explosion.position_gen = fire_part_posi;
	firework_explosion.emi = fire_part;
	firework_explosion.activation_value = 299;
	system.add_updater(std::make_shared<time_activation>(firework_explosion));

	force_clearer clearer(jeden);
	system.add_updater(std::make_shared<force_clearer>(clearer));

	// background image
	background.load("city_background.png");
}

//--------------------------------------------------------------
void ofApp::update() {
	system.update(1);

}

//--------------------------------------------------------------
void ofApp::draw() {
	//ofSetColor(0);

	cam.begin();
	//ofNoFill();

	system.draw();

	cam.end();

	ofSetColor(255, 255, 255, 255);
	ofEnableAlphaBlending();
	background.draw(0, 0, ofGetWidth(), ofGetHeight());
	ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'w')
	{
		if (wiatr_ptr != nullptr)
		{
			wiatr_ptr->force += glm::vec4{ 1, 0, 0, 0 };
		}
		
	}
	if (key == 's')
	{
		if (wiatr_ptr != nullptr)
		{
			wiatr_ptr->force += glm::vec4{ -1, 0, 0, 0 };
		}
		
	}
	if (key == 'a')
	{
		if (wiatr_ptr != nullptr)
		{
			wiatr_ptr->force += glm::vec4{ 0, 0, 1, 0 };
		}
		
	}
	if (key == 'd')
	{
		if (wiatr_ptr != nullptr)
		{
			wiatr_ptr->force += glm::vec4{ 0, 0, -1, 0 };
		}
		
	}
	if (wiatr_ptr != nullptr)
	{
		std::cout << wiatr_ptr->force << "\n";
	}
	else
	{
		std::cout << "wiatr hasn't been initialized\n";
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}