#include "simulation.h"

#include <cmath> // sqrt function

// not uniformly random distribution because circle
sf::Vector2f simulation::random_vector(float min_magnitude, float max_magnitude)
{
	float angle = random_float(0, 2 * 3.1415926535);
	float magnitude = random_float(min_magnitude, max_magnitude);

	return magnitude * sf::Vector2f(cos(angle), sin(angle));
}

float simulation::random_float(float min, float max)
{
	std::uniform_real_distribution<float> distrubution(min, max);
	return distrubution(gen);
}

uint8_t simulation::random_uint8_t()
{
	std::uniform_int_distribution<sf::Uint8> distrubution(0, 255);
	return distrubution(gen);
}

sf::Color simulation::random_colour()
{
	return sf::Color(
		random_uint8_t(),
		random_uint8_t(),
		random_uint8_t(),
		128);
}

simulation::simulation(int amount, sf::Vector2f window_size)
{
	gen = std::default_random_engine(time(NULL));

	balls.resize(amount);

	for (circle& kolko : balls)
	{
		kolko.set_radius(random_float(10, 20));
		kolko.set_mass(3.1415926 * kolko.getRadius() * kolko.getRadius());
		kolko.set_bounds(window_size);
		kolko.set_speed(random_vector(50, 200));
		float x = random_float(kolko.getRadius(), window_size.x - kolko.getRadius());
		float y = random_float(kolko.getRadius(), window_size.y - kolko.getRadius());
		kolko.setPosition(sf::Vector2f(x, y));
		kolko.setFillColor(random_colour());
	}
}

void simulation::add_attractor(sf::Vector2f position, float mass)
{
	attractor att(position, mass);

	attractors.push_back(att);
}

void simulation::remove_most_recent_attractor()
{
	if(attractors.size() != 0)
	{
		attractors.pop_back();
	}
}

void simulation::calculate_gravity_between_balls()
{
	for(size_t i = 0; i<balls.size(); i++) // for all balls
	{
		for(size_t j = i+1; j<balls.size(); j++) // for all from i'th but i'th cannot react with itself so from i+1
		{
			sf::Vector2f force = gravitational_force(balls[i].getPosition(), balls[i].get_mass(), balls[j].getPosition(), balls[j].get_mass());
			force += one_over_r_force(balls[i].getPosition(), balls[i].get_mass(), balls[j].getPosition(), balls[j].get_mass());

			balls[i].sum_force += force;
			balls[j].sum_force -= force;
		}
	}
}

void simulation::update(float dt)
{
	calculate_gravity_between_balls();
	for (circle& kolko : balls)
	{
		kolko.update(dt, attractors);
	}
}

void simulation::draw(sf::RenderWindow& window)
{
	for (circle& kolko : balls)
	{
		window.draw(kolko);
		//std::cout << kolko.getPosition().x << " " << kolko.getPosition().y << "\n";
	}
}
