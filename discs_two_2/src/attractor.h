#pragma once

#include "Platform/Platform.hpp" // sfml

class attractor
{
public:
	sf::Vector2f position;
	float mass;

	attractor();
	attractor(sf::Vector2f position_, float mass_);
};