#pragma once

#include <memory>
#include "particle_data.h"
#include <vector>
#include "emitters.h"
#include "updaters.h"
#include "particle_types.h"

class particle_system
{
protected:
	particle_data particles;
	particle_data other;

	particle_type type;

	size_t count_first_type;

	std::vector<std::shared_ptr<particle_emitter>> emitters;
	std::vector<std::shared_ptr<particle_updater>> updaters;

public:
	explicit particle_system(size_t max_count_first_type, size_t max_count_second_type);
	virtual ~particle_system() {};

	particle_system(const particle_system&) = delete;
	particle_system& operator=(const particle_system&) = delete;

	virtual void update(double dt);
	virtual void reset();

	virtual size_t num_all_particles() const
	{
		return particles.count;
	};
	virtual size_t num_alive_particles() const
	{
		return particles.count_alive;
	};

	void add_emitter(std::shared_ptr<particle_emitter> emitter)
	{
		emitters.push_back(emitter);
	};
	void add_updater(std::shared_ptr<particle_updater> updater)
	{
		updaters.push_back(updater);
	}

	particle_data* final_data()
	{
		return &particles;
	};

	void draw();
};
