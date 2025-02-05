#pragma once

#include "particle_data.h"
#include "generators.h"
#include "particle_types.h"

class particle_emitter
{
protected:
	std::vector<std::shared_ptr<particle_generator>> generators;

public:
	particle_type type;
	float emit_rate = 0.0;
	float inbeetween_emit_rate = 0.0;
	particle_emitter() {};
	particle_emitter(particle_type _type)
	{
		type = _type;
	};
	virtual ~particle_emitter() {};
	virtual void emit(double dt, particle_data* data);
	void add_generator(std::shared_ptr<particle_generator> generator)
	{
		generators.push_back(generator);
	}
};

class firework_particles_emitter : public particle_emitter
{
public:
	firework_particles_emitter() {};
	using particle_emitter::particle_emitter;
	~firework_particles_emitter() {};
	void emit(double dt, particle_data* data) override;
};
