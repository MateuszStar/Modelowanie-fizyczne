#include "generators.h"

#include <glm/gtc/random.hpp>
#include <iostream>

void box_generator::generate(double dt, particle_data* data, size_t start_id, size_t end_id)
{

	for (size_t i = start_id; i < end_id; i++)
	{
		data->positions[i] = glm::linearRand(negavite_corner, positive_corner);
		data->accelerations[i] = glm::vec4(0.0f);
		data->forces[i] = glm::vec4(0.0f);
		data->masses[i] = 10;
	}
}

void random_sphere_velocity::generate(double dt, particle_data* data, size_t start_id, size_t end_id)
{
	for (size_t i = start_id; i < end_id; i++)
	{
		glm::tvec3<float> three_d = glm::sphericalRand(radius);

		data->velocities[i].x = three_d.x;
		data->velocities[i].y = three_d.y;
		data->velocities[i].z = three_d.z;
		data->velocities[i].w = 0;
	}
}

void random_rgb_color::generate(double dt, particle_data* data, size_t start_id, size_t end_id)
{
	for (size_t i = start_id; i < end_id; i++)
	{
		data->color[i] = glm::linearRand(glm::vec4(0, 0, 0, 255), glm::vec4(255, 255, 255, 255));
	}
}

void time_generator::generate(double dt, particle_data* data, size_t start_id, size_t end_id)
{
	for (size_t i = start_id; i < end_id; i++)
	{
		data->times[i] = initial_value;
	}
}

void random_death_time_generator::generate(double dt, particle_data* data, size_t start_id, size_t end_id)
{
	for (size_t i = start_id; i < end_id; i++)
	{
		data->death_times[i] = glm::linearRand(glm::vec4(min_value, 0, 0, 0), glm::vec4(max_value, 0, 0, 0)).x;
	}
}

void directional_random_velocity::generate(double dt, particle_data* data, size_t start_id, size_t end_id)
{
	for (size_t i = start_id; i < end_id; i++)
	{
		data->velocities[i] = direction;

		glm::tvec3<float> three_d = glm::sphericalRand(radius);

		data->velocities[i].x += three_d.x;
		data->velocities[i].y += three_d.y;
		data->velocities[i].z += three_d.z;
		data->velocities[i].w += 0;
	}
}

void random_upwards_velocity::generate(double dt, particle_data* data, size_t start_id, size_t end_id)
{
	for (size_t i = start_id; i < end_id; i++)
	{
		//data->velocities[i] = direction;

		glm::tvec2<float> two_d = glm::circularRand(directional_sway);

		glm::vec4 upwards = glm::linearRand(glm::vec4(min_upwords_velocity, 0, 0, 0), glm::vec4(max_upwords_velocity, 0, 0, 0));

		data->velocities[i].x = two_d.x;
		data->velocities[i].y = upwards.x;
		data->velocities[i].z = two_d.y;
		data->velocities[i].w = 0;
	}
}
