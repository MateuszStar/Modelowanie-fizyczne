#pragma once

#include "particle_data.h"

class particle_generator
{
public:
	particle_generator() {};
	virtual ~particle_generator() {};
	virtual void generate(double dt, particle_data* data, size_t start_id, size_t end_id) = 0;
};

class box_generator : public particle_generator
{
public:
	glm::vec4 positive_corner = glm::vec4(0.0);
	glm::vec4 negavite_corner = glm::vec4(0.0);

	box_generator() {};
	~box_generator() {};

	box_generator(const box_generator&) = default;



	void generate(double dt, particle_data* data, size_t start_id, size_t end_id) override;
};

class random_sphere_velocity : public particle_generator
{
public:
	float radius = 1;

	random_sphere_velocity() {};
	~random_sphere_velocity() {};

	random_sphere_velocity(const random_sphere_velocity&) = default;

	void generate(double dt, particle_data* data, size_t start_id, size_t end_id) override;
};

class random_rgb_color : public particle_generator
{
public:
	random_rgb_color() {};
	~random_rgb_color() {};

	random_rgb_color(const random_rgb_color&) = default;

	void generate(double dt, particle_data* data, size_t start_id, size_t end_id) override;
};

class time_generator : public particle_generator
{
public:
	float initial_value = 0;

	time_generator() {};
	~time_generator() {};

	time_generator(const time_generator&) = default;

	void generate(double dt, particle_data* data, size_t start_id, size_t end_id) override;
};

class random_death_time_generator : public particle_generator
{
public:
	float min_value = 90;
	float max_value = 110;

	random_death_time_generator() {};
	~random_death_time_generator() {};

	random_death_time_generator(const random_death_time_generator&) = default;

	void generate(double dt, particle_data* data, size_t start_id, size_t end_id) override;
};

class directional_random_velocity : public particle_generator
{
public:
	glm::vec4 direction;
	float radius;

	directional_random_velocity() {};
	~directional_random_velocity() {};

	directional_random_velocity(const directional_random_velocity&) = default;

	void generate(double dt, particle_data* data, size_t start_id, size_t end_id) override;
};

class random_upwards_velocity : public particle_generator
{
public:
	float directional_sway = 0.2;
	float min_upwords_velocity = 1;
	float max_upwords_velocity = 2;

	random_upwards_velocity() {};
	~random_upwards_velocity() {};
	random_upwards_velocity(const random_upwards_velocity&) = default;

	void generate(double dt, particle_data* data, size_t start_id, size_t end_id) override;
};