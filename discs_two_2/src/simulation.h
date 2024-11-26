#pragma once

#include "Platform/Platform.hpp" // sfml
#include "circle.h" // circles
#include "attractor.h"
#include "gravity.h"

#include <random> // for generating random values

class simulation
{
private:
	std::vector<circle> balls;

	// randomness for random balls
	std::default_random_engine gen;
	sf::Vector2f random_vector(float min_magnitude, float max_magnitude);
	float random_float(float min, float max);
	uint8_t random_uint8_t();
	sf::Color random_colour();

	std::vector<attractor> attractors;

public:
	simulation(int amount, sf::Vector2f window_size);

	void add_attractor(sf::Vector2f position, float mass);
	void remove_most_recent_attractor();
	void calculate_gravity_between_balls();

	void update(float dt);
	void draw(sf::RenderWindow& window);
};