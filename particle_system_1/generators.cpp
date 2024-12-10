#include "generators.h"

#include <glm/gtc/random.hpp>
#include <iostream>

void box_generator::generate(double dt, particle_data* data, size_t start_id, size_t end_id)
{

	for (size_t i = start_id; i < end_id; i++)
	{
		data->positions[i] = glm::linearRand(negavite_corner, positive_corner);
		data->accelerations[i] = glm::vec4(0.0f);
		data->velocities[i] = glm::vec4(0.0f);
	}
	std::cout << "A";
}

void gravity::update(double dt, particle_data* particles)
{
	glm::vec4 dt_force = (float)dt * force;

	size_t end_id = particles->count_alive;

	for (size_t i = 0; i < end_id; i++)
	{
		particles->velocities[i] += dt_force;
	}
}

void position::update(double dt, particle_data* particles)
{
	size_t end_id = particles->count_alive;

	float dt_f = (float)dt;

	for (size_t i = 0; i < end_id; i++)
	{
		particles->positions[i] += dt_f * particles->velocities[i];
	}
}

void bottom_floor::update(double dt, particle_data* particles)
{
	size_t end_id = particles->count_alive;

	float ball_radius = 10.f;

	for (size_t i = 0; i < end_id; i++)
	{
		if (particles->positions[i].y < floor_level + ball_radius)
		{
			particles->velocities[i].y *= -1;
		}
	}
}
