#pragma once

#include "particle_data.h"
#include "particle_types.h"
#include "generators.h"
#include "emitters.h"

class particle_updater
{
public:
	particle_type type = jeden;
	particle_updater() {};
	particle_updater(particle_type _type)
	{
		type = _type;
	};
	virtual ~particle_updater() {};

	virtual void update(double dt, particle_data* particles) = 0;
};

class gravity : public particle_updater
{
public:
	glm::vec4 force = { 0, -0.00001, 0, 0 };

	gravity() {};
	using particle_updater::particle_updater;
	~gravity() {};

	//gravity(const gravity&) = default;

	void update(double dt, particle_data* particles) override;
};

class force_clearer : public particle_updater
{
	glm::vec4 zero = { 0, 0, 0, 0 };
public:
	force_clearer() {};
	using particle_updater::particle_updater;
	~force_clearer() {};

	void update(double dt, particle_data* particles) override;
};

class acceleration : public particle_updater
{
public:
	acceleration() {};
	using particle_updater::particle_updater;
	~acceleration() {};

	void update(double dt, particle_data* particles) override;
};

class velocity : public particle_updater
{
public:
	velocity() {};
	using particle_updater::particle_updater;
	~velocity() {};

	void update(double dt, particle_data* particles) override;
};

class position : public particle_updater
{
public:
	position() {};
	using particle_updater::particle_updater;
	~position() {};

	//position(const position&) = default;

	void update(double dt, particle_data* particles) override;
};

class bottom_floor : public particle_updater
{
public:
	float floor_level = -200.f;

	bottom_floor() {};
	using particle_updater::particle_updater;
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
	using particle_updater::particle_updater;
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
	using particle_updater::particle_updater;
	~wind() {};

	void set_force(glm::vec4& vec);

	float magnitude(glm::vec4& vec);

	void update(double dt, particle_data* particles) override;
};

class time_ticking : public particle_updater
{
public:
	time_ticking() {};
	using particle_updater::particle_updater;
	~time_ticking() {};

	void update(double dt, particle_data* particles) override;
};

class time_killer : public particle_updater
{
public:
	float death_value;
	time_killer() {};
	using particle_updater::particle_updater;
	~time_killer() {};

	void update(double dt, particle_data* particles) override;
};

class self_time_killer : public particle_updater
{
public:
	self_time_killer() {};
	using particle_updater::particle_updater;
	~self_time_killer() {};

	void update(double dt, particle_data* particles) override;
};

class time_activation : public particle_updater
{
public:
	std::shared_ptr<directional_random_velocity> velocity_gen = nullptr;
	std::shared_ptr<box_generator> position_gen = nullptr;
	std::shared_ptr<firework_particles_emitter> emi = nullptr;

	float activation_value;
	time_activation() {};
	using particle_updater::particle_updater;
	~time_activation() {};

	void update(double dt, particle_data* particles) override;
};