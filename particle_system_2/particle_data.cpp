#include "particle_data.h"
#include "src/ofApp.h"

particle_data::particle_data(size_t max_count)
{
	generate(max_count);
}

particle_data::~particle_data()
{
}

void particle_data::generate(size_t max_size)
{
	count = max_size;
	count_alive = 0;
	positions.reset(new glm::vec4[max_size]);
	col.reset(new glm::vec4[max_size]);
	start_col.reset(new glm::vec4[max_size]);
	end_col.reset(new glm::vec4[max_size]);
	velocities.reset(new glm::vec4[max_size]);
	accelerations.reset(new glm::vec4[max_size]);
	times.reset(new float[max_size]);
	alive.reset(new bool[max_size]);
	forces.reset(new glm::vec4[max_size]);
	masses.reset(new float[max_size]);
	color.reset(new glm::vec4[max_size]);
	death_times.reset(new float[max_size]);
}

void particle_data::kill(size_t id)
{
	if (count_alive > 0)
	{
		alive[id] = false;
		swap_data(id, count_alive - 1);
		count_alive--;
	}
}

void particle_data::wake(size_t id)
{
	if (count_alive < count)
	{
		alive[id] = true;
		swap_data(id, count_alive);
		count_alive++;
	}
}

void particle_data::swap_data(size_t a, size_t b)
{
	std::swap(positions[a], positions[b]);
	std::swap(col[a], col[b]);
	std::swap(start_col[a], start_col[b]);
	std::swap(end_col[a], end_col[b]);
	std::swap(velocities[a], velocities[b]);
	std::swap(accelerations[a], accelerations[b]);
	std::swap(times[a], times[b]);
	std::swap(alive[a], alive[b]);
	std::swap(forces[a], forces[b]);
	std::swap(masses[a], masses[b]);
	std::swap(color[a], color[b]);
	std::swap(death_times[a], death_times[b]);
}




