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
	std::unique_ptr<glm::vec4[]> times;
	std::unique_ptr<bool[]> alive;
	std::unique_ptr <glm::vec4[]> forces;
	std::unique_ptr <float[]> masses;
	std::unique_ptr<glm::vec4[]> color;

	size_t count = 0;
	size_t count_alive = 0;

	explicit particle_data(size_t max_count=0);
	~particle_data();

	particle_data(const particle_data&) = delete;

	particle_data& operator=(const particle_data&) = delete;

	void generate(size_t max_size);
	void kill(size_t id);
	void wake(size_t id);
	void swap_data(size_t a, size_t b);

};

class particle_generator
{
public:
	particle_generator() {};
	virtual ~particle_generator() {};
	virtual void generate(double dt, particle_data* data, size_t start_id, size_t end_id) = 0;
};

class particle_emitter
{
protected:
	std::vector<std::shared_ptr<particle_generator>> generators;
public:
	float emit_rate = 0.0;
	particle_emitter() {};
	virtual ~particle_emitter() {};
	virtual void emit(double dt, particle_data* data);
	void add_generator(std::shared_ptr<particle_generator> generator)
	{
		generators.push_back(generator);
	}
};

class particle_updater
{
public:
	particle_updater() {};
	virtual ~particle_updater() {};

	virtual void update(double dt, particle_data* particles) = 0;
};

class particle_system
{
protected:
	particle_data particles;
	//particle_data alive_particles;

	size_t count;

	std::vector<std::shared_ptr<particle_emitter>> emitters;
	std::vector<std::shared_ptr<particle_updater>> updaters;

public:
	explicit particle_system(size_t max_count);
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

