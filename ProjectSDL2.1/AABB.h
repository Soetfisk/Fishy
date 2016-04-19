#pragma once
#include "GLUtil.h"
#include "SphereBS.h"
class AABB
{
public:
	glm::vec3 center;
	glm::vec3 halfDimension;

	AABB(glm::vec3 center, glm::vec3 halfDimensions) {
		this->center = center;
		this->halfDimension = halfDimensions;
	}
	~AABB() {}

	bool containsPoint(glm::vec3& pt) const {
		if (pt.x >= center.x - halfDimension.x && pt.x <= center.x + halfDimension.x &&
			pt.y >= center.y - halfDimension.y && pt.y <= center.y + halfDimension.y &&
			pt.z >= center.z - halfDimension.z && pt.z <= center.z + halfDimension.z)
		{
			return true;
		}
		return false;
	}

	bool containsAABB(AABB& other) const {
		if (glm::abs(center.x - other.center.x) > (halfDimension.x + other.halfDimension.x)) return false;
		if (glm::abs(center.y - other.center.y) > (halfDimension.y + other.halfDimension.y)) return false;
		if (glm::abs(center.z - other.center.z) > (halfDimension.z + other.halfDimension.z)) return false;
		return true;
	}

	bool containsSphere(SphereBS& other) const {
		if (glm::abs(center.x - other.m_center.x) > (halfDimension.x + other.m_radius)) return false;
		if (glm::abs(center.y - other.m_center.y) > (halfDimension.y + other.m_radius)) return false;
		if (glm::abs(center.z - other.m_center.z) > (halfDimension.z + other.m_radius)) return false;
		return true;
	}
};