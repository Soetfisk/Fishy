#pragma once
#include "GLUtil.h"
class SphereBS
{
public:
	glm::vec3 m_center;
	float m_radius;

	SphereBS(glm::vec3& center, float radius) {
		this->m_center = center;
		this->m_radius = radius;
	}
	~SphereBS() {}
	bool containsPoint(const glm::vec3& point) const {
		glm::vec3 vecDist = this->m_center - point;

		float distance = glm::dot(vecDist, vecDist);

		if (distance < (this->m_radius * this->m_radius))
		{
			return true;
		}
		return false;
	}

	bool containsSphere(const SphereBS& other) const {
		glm::vec3 vecDist = other.m_center - this->m_center;
		float distance = glm::dot(vecDist, vecDist);

		float radiusLength = other.m_radius + this->m_radius;
		radiusLength *= radiusLength;

		if (distance <= radiusLength)
		{
			return true;
		}
		return false;
	}
};