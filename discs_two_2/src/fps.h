// for real time animation
#pragma once

#include <chrono> // for measuring real time

class time_per_frame
{
private:
	uint64_t previous_frame = 0;
	uint64_t current_frame = 0;

	float wanted_time_per_frame;

public:
	void update();
	uint64_t frame_time_in_us();
	float frame_time_in_s();

	// need custom sleep function
	void set_frames_per_secound(float frames_per_secound);
	//void sleep();
	void sleep_till_next_frame();

	void display_fps();
};