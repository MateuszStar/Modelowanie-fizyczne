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
	times.reset(new glm::vec4[max_size]);
	alive.reset(new bool[max_size]);
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
}

void particle_emitter::emit(double dt, particle_data* data)
{
	const size_t maxNewParticles = static_cast<size_t>(dt * emit_rate);
	const size_t startId = data->count_alive;
	const size_t endId = std::min(startId + maxNewParticles, data->count - 1);

	for (auto& gen : generators)            // << gen loop
		gen->generate(dt, data, startId, endId);

	for (size_t i = startId; i < endId; ++i)  // << wake loop
		data->wake(i);
}

particle_system::particle_system(size_t max_count)
{
	count = max_count;
	particles.generate(max_count);
	alive_particles.generate(max_count);

	for (size_t i = 0; i < max_count; i++)
	{
		particles.alive[i] = false;
	}
}
void particle_system::update(double dt)
{
	for (auto& emitter : emitters)
	{
		emitter->emit(dt, &particles);
	}

	for (auto& updater : updaters)
	{
		updater->update(dt, &particles);
	}
}

void particle_system::reset()
{
	particles.count_alive = 0;
}

void particle_system::draw()
{
	for (size_t i = 0; i < num_alive_particles(); i++)
	{
		ofDrawIcoSphere(particles.positions[i].x, particles.positions[i].y, particles.positions[i].z, 10);
	}
}
