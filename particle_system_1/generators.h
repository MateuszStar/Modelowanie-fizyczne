#pragma once

#include "particle_data.h"

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

class gravity : public particle_updater
{
public:
	glm::vec4 force = { 0, -0.00001, 0, 0 };

	gravity() {};
	~gravity() {};

	//gravity(const gravity&) = default;

	void update(double dt, particle_data* particles) override;
};

class force_clearer : public particle_updater
{
	glm::vec4 zero = { 0, 0, 0, 0 };
public:
	force_clearer() {};
	~force_clearer() {};

	void update(double dt, particle_data* particles) override;
};

class acceleration : public particle_updater
{
public:
	acceleration() {};
	~acceleration() {};

	void update(double dt, particle_data* particles) override;
};

class velocity : public particle_updater
{
public:
	velocity() {};
	~velocity() {};

	void update(double dt, particle_data* particles) override;
};

class position : public particle_updater
{
public:
	position() {};
	~position() {};

	//position(const position&) = default;

	void update(double dt, particle_data* particles) override;
};

class bottom_floor : public particle_updater
{
public:
	float floor_level = -200.f;

	bottom_floor() {};
	~bottom_floor() {};

	void update(double dt, particle_data* particles) override;
};

class axis_wall : public particle_updater
{
public:

	float glm::vec4::* axis;
	bool positive_direction;
	float position;

	axis_wall() {};
	~axis_wall() {};

	void update(double dt, particle_data* particles) override;
};

class wind : public particle_updater
{
public:
	glm::vec4 force = { 0, 0, 0, 0 };
	float air_density = 1.225f;
	float sphere_drag_coefficient = 0.47f;
	float sphere_cross_section_area = 3.1415926535 * 10 * 10;
	float constant = 0.000001;

	wind() {};
	~wind() {};

	void set_force(glm::vec4& vec);

	float magnitude(glm::vec4& vec);

	void update(double dt, particle_data* particles) override;
};
