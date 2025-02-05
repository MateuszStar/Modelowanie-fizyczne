#include "particle_system.h"

#include "src/ofApp.h"

particle_system::particle_system(size_t max_count_first_type, size_t max_count_second_type)
{
	count_first_type = max_count_first_type;
	particles.generate(max_count_first_type);
	other.generate(max_count_second_type);

	for (size_t i = 0; i < max_count_first_type; i++)
	{
		particles.alive[i] = false;
	}

	for (size_t i = 0; i < max_count_second_type; i++)
	{
		other.alive[i] = false;
	}
}
void particle_system::update(double dt)
{
	for (auto& emitter : emitters)
	{
		//emitter->emit(dt, &particles);
		switch (emitter->type) {
		case jeden:
		{
			emitter->emit(dt, &particles);
			break;
		}
		case dwa: 
		{
			emitter->emit(dt, &other);
			break;
		}
		}
	}

	for (auto& updater : updaters)
	{
		//updater->update(dt, &particles);
		switch (updater->type) {
		case jeden:
		{
			updater->update(dt, &particles);
			break;
		}
		case dwa: 
		{
			updater->update(dt, &other);
			break;
		}
		}
	}
}

void particle_system::reset()
{
	particles.count_alive = 0;
}

void particle_system::draw()
{
	for (size_t i = 0; i < particles.count_alive; i++)
	{
		ofEnableAlphaBlending();

		uint8_t red = particles.color[i].x;
		uint8_t green = particles.color[i].y;
		uint8_t blue = particles.color[i].z;

		ofSetColor(red, green, blue, 255);
		ofDrawSphere(particles.positions[i].x, particles.positions[i].y, particles.positions[i].z, 4);

		ofDisableAlphaBlending();
	}
	for (size_t i = 0; i < other.count_alive; i++)
	{
		ofEnableAlphaBlending();

		uint8_t red = other.color[i].x;
		uint8_t green = other.color[i].y;
		uint8_t blue = other.color[i].z;

		ofSetColor(red, green, blue, 255);
		ofDrawSphere(other.positions[i].x, other.positions[i].y, other.positions[i].z, 1);

		ofDisableAlphaBlending();
	}
}