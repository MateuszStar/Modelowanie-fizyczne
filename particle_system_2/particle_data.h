#pragma once

#include <memory>
#include "glm/vec4.hpp"
#include <vector>

class particle_data
{
public:
	std::unique_ptr<glm::vec4[]> positions;
	std::unique_ptr<glm::vec4[]> col;
	std::unique_ptr<glm::vec4[]> start_col;
	std::unique_ptr<glm::vec4[]> end_col;
	std::unique_ptr<glm::vec4[]> velocities;
	std::unique_ptr<glm::vec4[]> accelerations;
	std::unique_ptr<float[]> times;
	std::unique_ptr<bool[]> alive;
	std::unique_ptr <glm::vec4[]> forces;
	std::unique_ptr <float[]> masses;
	std::unique_ptr<glm::vec4[]> color;
	std::unique_ptr<float[]> death_times;

	size_t count = 0;
	size_t count_alive = 0;

	explicit particle_data(size_t max_count = 0);
	~particle_data();

	particle_data(const particle_data&) = delete;

	particle_data& operator=(const particle_data&) = delete;

	void generate(size_t max_size);
	void kill(size_t id);
	void wake(size_t id);
	void swap_data(size_t a, size_t b);

};






//*

//*/

