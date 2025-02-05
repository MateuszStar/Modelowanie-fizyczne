#include "emitters.h"

void particle_emitter::emit(double dt, particle_data* data)
{
	inbeetween_emit_rate += dt * emit_rate;
	const size_t maxNewParticles = static_cast<size_t>(inbeetween_emit_rate);

	if (inbeetween_emit_rate > 1)
	{
		float whole_number = static_cast<float>(static_cast<size_t>(inbeetween_emit_rate));
		inbeetween_emit_rate = inbeetween_emit_rate - whole_number;
	}

	const size_t startId = data->count_alive;
	const size_t endId = std::min(startId + maxNewParticles, data->count - 1);

	for (auto& gen : generators)            // << gen loop
		gen->generate(dt, data, startId, endId);

	for (size_t i = startId; i < endId; ++i)  // << wake loop
		data->wake(i);
}

void firework_particles_emitter::emit(double dt, particle_data* data)
{
	inbeetween_emit_rate += dt * emit_rate;
	const size_t maxNewParticles = static_cast<size_t>(inbeetween_emit_rate);

	if (inbeetween_emit_rate > 1)
	{
		float whole_number = static_cast<float>(static_cast<size_t>(inbeetween_emit_rate));
		inbeetween_emit_rate = inbeetween_emit_rate - whole_number;
	}
	const size_t startId = data->count_alive;
	const size_t endId = std::min(startId + maxNewParticles, data->count - 1);

	for (auto& gen : generators)            // << gen loop
		gen->generate(dt, data, startId, endId);

	for (size_t i = startId; i < endId; ++i)  // << wake loop
		data->wake(i);

	emit_rate = 0;
}
