#pragma once
#include "GLUtil.h"
#include <vector>
#include <memory>
#include <glm/vec4.hpp>
#include <algorithm>

class ParticleData
{
public:
	std::unique_ptr<glm::vec4[]> m_pos;
	std::unique_ptr<glm::vec4[]> m_col;
	std::unique_ptr<glm::vec4[]> m_startCol;
	std::unique_ptr<glm::vec4[]> m_endCol;
	std::unique_ptr<glm::vec4[]> m_vel;
	std::unique_ptr<glm::vec4[]> m_acc;
	std::unique_ptr<glm::vec4[]> m_time;
	std::unique_ptr<bool[]>      m_alive;

	size_t m_count{ 0 };
	size_t m_countAlive{ 0 };
public:
	explicit ParticleData(size_t maxCount) { generate(maxCount); }
	~ParticleData();

	void generate(size_t maxSize);
	void kill(size_t id);
	void wake(size_t id);
	void swapData(size_t a, size_t b);
};

class ParticleEmitter {
protected:
	
public:
	float m_emiteRate{ 0.0 };
public:
	void emit(const float&dt, ParticleData *p);
};