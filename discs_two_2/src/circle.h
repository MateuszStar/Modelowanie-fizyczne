#pragma once

#include "Platform/Platform.hpp" // sfml

#include "attractor.h"
#include "gravity.h"

#include <vector>


class circle : public sf::CircleShape
{
private:
	// circle properties
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float mass;

	// for bouncing off of the sides
	sf::Vector2f bounds_positive_direction;
	sf::Vector2f bounds_negative_direction;

public:
	sf::Vector2f sum_force;

	circle();
	circle(float radius_, sf::Vector2f position_, sf::Vector2f velocity_, sf::Vector2f acceleration_, sf::Vector2f window_size);
	circle(float radius_, float mass_, sf::Vector2f position_, sf::Vector2f velocity_, sf::Vector2f acceleration_, sf::Vector2f window_size);

	void set_speed(sf::Vector2f velocity_);
	void set_speed(float x, float y);

	void set_acceleration(sf::Vector2f acceleration_);
	void set_acceleretion(float x, float y);

	void set_mass(float mass_);
	float get_mass();

	void set_bounds(sf::Vector2f window_size);
	void set_bounds(float x, float y);

	void set_radius(float radius_);

	void speed_limit(sf::Vector2f& vector, float limit);

private:
	bool is_outside(float sf::Vector2f::*axis);
	bool is_outside_positive_direction(float sf::Vector2f::*axis);
	bool is_outside_negative_direction(float sf::Vector2f::*axis);
	void handle_collision(float sf::Vector2f::*axis);

	void calculate_gravity_force_to_attractor(attractor& attractor_);
	float drag_coeff_function();
	void calculate_drag();

	void update_acceleration();
public:
	void update(float dt, std::vector<attractor>& attractors);
};