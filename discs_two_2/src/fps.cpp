// for real time animation
#include "fps.h"

void time_per_frame::update()
{
	previous_frame = current_frame;

	auto now = std::chrono::system_clock::now();

	auto duration = now.time_since_epoch();

	current_frame = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
}

uint64_t time_per_frame::frame_time_in_us()
{
	return current_frame - previous_frame;
}

float time_per_frame::frame_time_in_s()
{
	return (float)frame_time_in_us()/1000000;
}

void time_per_frame::set_frames_per_secound(float frames_per_secound)
{
	wanted_time_per_frame = 1/frames_per_secound;
}
/*
void time_per_frame::sleep()
{
	auto now = std::chrono::system_clock::now();

	auto duration = now.time_since_epoch();

}
//*/
void time_per_frame::sleep_till_next_frame()
{
	float frame_time = frame_time_in_s();
	if(frame_time < wanted_time_per_frame) // ahead of schedule so we can sleep
	{
		//Sleep((wanted_time_per_frame-frame_time)*1000); // Sleep wants milisecounds so we multiply our secounds by 1000. 1s = 1000ms
		// custom sleep function requires as windows one is inaccurate
		std::cout << "Sleept for: " << (wanted_time_per_frame-frame_time)*1000 << " s\n";
	}
}

void time_per_frame::display_fps()
{
	std::cout << 1/frame_time_in_s() << " FPS\n";
}
