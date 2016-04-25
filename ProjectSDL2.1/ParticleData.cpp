#include "ParticleData.h"



ParticleData::ParticleData(size_t maxCount)
{
}

void ParticleData::generate(size_t maxSize) {
	this->m_count = maxSize;
	m_countAlive = 0;

	m_pos.reset(new glm::vec4[maxSize]);
	m_col.reset(new glm::vec4[maxSize]);
	m_startCol.reset(new glm::vec4[maxSize]);
	m_endCol.reset(new glm::vec4[maxSize]);
	m_vel.reset(new glm::vec4[maxSize]);
	m_acc.reset(new glm::vec4[maxSize]);
	m_time.reset(new glm::vec4[maxSize]);
	m_alive.reset(new bool[maxSize]);
}

void ParticleData::kill(size_t id) {
	if (this->m_countAlive > 0) {
		m_alive[id] = false;
		swapData(id, m_countAlive - 1);
		m_countAlive--;
	}
}

void ParticleData::wake(size_t id) {
	if (m_countAlive < m_count) {
		m_alive[id] = true;
		swapData(id, m_countAlive);
		m_countAlive++;
	}
}

void ParticleData::swapData(size_t a, size_t b) {
	std::swap(m_pos[a], m_pos[b]);
	std::swap(m_col[a], m_col[b]);
	std::swap(m_startCol[a], m_startCol[b]);
	std::swap(m_endCol[a], m_endCol[b]);
	std::swap(m_vel[a], m_vel[b]);
	std::swap(m_acc[a], m_acc[b]);
	std::swap(m_time[a], m_time[b]);
	std::swap(m_alive[a], m_alive[b]);
}

ParticleData::~ParticleData()
{
}



void ParticleEmitter::emit(const float&dt, ParticleData *p) {
	const size_t maxNewParticles = static_cast<size_t>(dt*m_emiteRate);
	const size_t startId = p->m_countAlive;
	const size_t endId = std::min(startId + maxNewParticles, p->m_count);

	//for (auto &gen : m_generators)            // << gen loop
	//	gen->generate(dt, p, startId, endId);

	for (size_t i = startId; i < endId; ++i)
		p->wake(i);
}