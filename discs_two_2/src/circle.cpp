#include "circle.h"

circle::circle()
{
}

circle::circle(float radius_, sf::Vector2f position_, sf::Vector2f speed_, sf::Vector2f acceleration_, sf::Vector2f window_size)
{
	setRadius(radius_);
	set_mass(radius_ * radius_ * 3.1415926535);
	setOrigin(sf::Vector2f(radius_, radius_));
	setPosition(position_);
	set_speed(speed_);
	set_acceleration(acceleration_);
	set_bounds(window_size);
}

circle::circle(float radius_, float mass_, sf::Vector2f position_, sf::Vector2f speed_, sf::Vector2f acceleration_, sf::Vector2f window_size)
{
	setRadius(radius_);
	set_mass(mass_);
	setOrigin(sf::Vector2f(radius_, radius_));
	setPosition(position_);
	set_speed(speed_);
	set_acceleration(acceleration_);
	set_bounds(window_size);
}

void circle::set_speed(sf::Vector2f speed_)
{
	velocity = speed_;
}

void circle::set_speed(float x, float y)
{
	set_speed(sf::Vector2f(x, y));
}

void circle::set_acceleration(sf::Vector2f acceleration_)
{
	acceleration = acceleration_;
}

void circle::set_acceleretion(float x, float y)
{
	set_acceleration(sf::Vector2f(x, y));
}

void circle::set_mass(float mass_)
{
	mass = mass_;
}

float circle::get_mass()
{
	return mass;
}

void circle::set_bounds(sf::Vector2f window_size)
{
	sf::Vector2f circle_square_box = sf::Vector2f(getRadius(), getRadius());
	bounds_positive_direction = window_size - circle_square_box;
	bounds_negative_direction = circle_square_box;
}

void circle::set_bounds(float x, float y)
{
	set_bounds(sf::Vector2f(x, y));
}

void circle::set_radius(float radius_)
{
	setRadius(radius_);
	setOrigin(sf::Vector2f(radius_, radius_));
}

void circle::speed_limit(sf::Vector2f& vector, float limit)
{
	float abs_vector = absolute_value(vector);
	if (abs_vector > limit)
	{
		vector = vector * (limit / abs_vector);
	}
}

bool circle::is_outside(float sf::Vector2f::*axis)
{
	return is_outside_positive_direction(axis) || is_outside_negative_direction(axis);
}

bool circle::is_outside_positive_direction(float sf::Vector2f::*axis)
{
	return getPosition().*axis > bounds_positive_direction.*axis;
}

bool circle::is_outside_negative_direction(float sf::Vector2f::*axis)
{
	return getPosition().*axis < bounds_negative_direction.*axis;
}

void circle::handle_collision(float sf::Vector2f::*axis)
{
	if (is_outside_positive_direction(axis))
	{
		sf::Vector2f position = getPosition();
		position.*axis = 2 * bounds_positive_direction.*axis - position.*axis;
		setPosition(position);
		velocity.*axis = -velocity.*axis;
	}
	if (is_outside_negative_direction(axis))
	{
		sf::Vector2f position = getPosition();
		position.*axis = 2 * bounds_negative_direction.*axis - position.*axis;
		setPosition(position);
		velocity.*axis = -velocity.*axis;
	}
}

void circle::calculate_gravity_force_to_attractor(attractor& attractor_)
{
	sum_force += gravitational_force(getPosition(), mass, attractor_.position, attractor_.mass);
}

float circle::drag_coeff_function()
{
	sf::Vector2f screen_size = bounds_positive_direction + sf::Vector2f(getRadius(), getRadius());

	sf::Vector2f pos = getPosition() - screen_size / 2.f; // linear transformation. Now (0, 0) is in the middle of the screen

	float x = absolute_value(pos); // distance from the middle

	float max_x = absolute_value(screen_size / 2.f); // max distance aka from middle to corner

	float norm_x = x / max_x; // normalizing to from 0 to 1

	float coeff_max_value = 100;

	// function f(x) = -2mx^3 + 3mx^2 has values:
	// f (0) = 0
	// f'(0) = 0
	// f (1) = m
	// f'(1) = 0
	return -2 * coeff_max_value * norm_x * norm_x * norm_x + 3 * coeff_max_value * norm_x * norm_x;
}

void circle::calculate_drag()
{
	float drag_coefficient = drag_coeff_function();

	sf::Vector2f force = -drag_coefficient * getRadius() * velocity;

	sum_force += force;
}

void circle::update_acceleration()
{
	acceleration = sum_force / mass;
	sum_force = sf::Vector2f(0, 0); // resetting net force for the next frame
}

void circle::update(float dt, std::vector<attractor>& attractors)
{
	sf::Vector2f position = getPosition() + velocity * dt; // newton approximation
	setPosition(position);

	// calculate all forces acting on the object
	for (attractor& att : attractors)
	{
		calculate_gravity_force_to_attractor(att);
	}
	calculate_drag();

	//calculate acceleration base on the net force
	update_acceleration();

	velocity += acceleration * dt; // newton approximaiton

	handle_collision(&sf::Vector2f::x); // handle collisions with walls
	handle_collision(&sf::Vector2f::y); //
}
