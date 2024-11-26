#include "gravity.h"

float absolute_value(sf::Vector2f vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f gravitational_force(sf::Vector2f position_1, float mass_1, sf::Vector2f position_2, float mass_2) // technically not gravity because it pushes them apart
{
	float gravity_constant = -300; // random value that works
	sf::Vector2f r = position_2 - position_1;
	float r_abs = absolute_value(r);

	if (r_abs < 5) // limiting the r which in turn limits the force from reaching infinity
	{
		r_abs = 5;
	}

	return gravity_constant * mass_1 * mass_2 * r / (r_abs * r_abs * r_abs);
}

sf::Vector2f one_over_r_force(sf::Vector2f position_1, float mass_1, sf::Vector2f position_2, float mass_2)
{
	float force_constant = 300*0.005; // random value that works
	sf::Vector2f r = position_2 - position_1;
	float r_abs = absolute_value(r);

	if (r_abs < 5) // limiting the r which in turn limits the force from reaching infinity
	{
		r_abs = 5;
	}

	return force_constant * mass_1 * mass_2 * r / (r_abs * r_abs);
}