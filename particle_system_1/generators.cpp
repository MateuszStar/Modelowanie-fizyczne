#include "generators.h"

#include <glm/gtc/random.hpp>
#include <iostream>

void box_generator::generate(double dt, particle_data* data, size_t start_id, size_t end_id)
{
	//glm::vec4 velocity_

	for (size_t i = start_id; i < end_id; i++)
	{
		data->positions[i] = glm::linearRand(negavite_corner, positive_corner);
		data->accelerations[i] = glm::vec4(0.0f);
		data->forces[i] = glm::vec4(0.0f);
		data->masses[i] = 10;
		//data->velocities[i] = glm::vec4(0.0f);

		glm::tvec3<float> three_d = glm::sphericalRand(1.0f);

		data->velocities[i].x = three_d.x;
		data->velocities[i].y = three_d.y;
		data->velocities[i].z = three_d.z;
		data->velocities[i].w = 0;

		data->color[i] = glm::linearRand(glm::vec4(0, 0, 0, 255), glm::vec4(255, 255, 255, 255));
	}
}

void gravity::update(double dt, particle_data* particles)
{
	size_t end_id = particles->count_alive;

	for (size_t i = 0; i < end_id; i++)
	{
		particles->accelerations[i] += force;
	}
}

void force_clearer::update(double dt, particle_data* particles)
{
	size_t end_id = particles->count_alive;

	//std::cout << particles->forces[0].y;

	for (size_t i = 0; i < end_id; i++)
	{
		particles->forces[i] = zero;
	}
}

void acceleration::update(double dt, particle_data* particles)
{
	size_t end_id = particles->count_alive;

	for (size_t i = 0; i < end_id; i++)
	{
		particles->accelerations[i] += particles->forces[i] / particles->masses[i];
	}
}


void velocity::update(double dt, particle_data* particles)
{
	size_t end_id = particles->count_alive;

	float dt_f = (float)dt;
	//std::cout << dt_f << " * " << particles->forces[0].y << "\n";

	for (size_t i = 0; i < end_id; i++)
	{
		particles->velocities[i] += dt_f * particles->accelerations[i];
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

void axis_wall::update(double dt, particle_data* particles)
{
	size_t end_id = particles->count_alive;

	for (size_t i = 0; i < end_id; i++)
	{
		if (positive_direction)
		{
			if (particles->positions[i].*axis > position)
			{
				particles->positions[i].*axis = 2 * position - particles->positions[i].*axis;
				particles->velocities[i].*axis = -particles->velocities[i].*axis;
			}
		}
		else
		{
			if (particles->positions[i].*axis < position)
			{
				particles->positions[i].*axis = 2 * position - particles->positions[i].*axis;
				particles->velocities[i].*axis = -particles->velocities[i].*axis;
			}
		}
	}
}

void wind::set_force(glm::vec4& vec)
{
	force = vec;
}

float wind::magnitude(glm::vec4& vec)
{
	return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

void wind::update(double dt, particle_data* particles)
{
	size_t end_id = particles->count_alive;

	//std::cout << force.x << " " << force.y << " " << force.z << "\n";

	for (size_t i = 0; i < end_id; i++)
	{
		glm::vec4 relative_velocity = particles->velocities[i] - force;

		float relative_speed = magnitude(relative_velocity);

		glm::vec4 relative_velocity_normalized = relative_velocity / relative_speed;

		float constants = -0.5f * air_density * sphere_drag_coefficient * sphere_cross_section_area * relative_speed * relative_speed * constant;

		//std::cout << constants << " ";

		particles->forces[i] += constants * relative_velocity_normalized;

		//std::cout << particles->forces[i].x << "\n";
	}
}