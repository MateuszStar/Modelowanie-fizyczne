#pragma once

float absolute_value(sf::Vector2f vector);
sf::Vector2f gravitational_force(sf::Vector2f position_1, float mass_1, sf::Vector2f position_2, float mass_2);
sf::Vector2f one_over_r_force(sf::Vector2f position_1, float mass_1, sf::Vector2f position_2, float mass_2);