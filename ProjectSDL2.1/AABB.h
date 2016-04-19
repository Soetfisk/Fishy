#pragma once
#include "GLUtil.h"
class AABB
{
public:
	AABB(glm::vec3 center, glm::vec3 halfDimensions) {
		this->center = center;
		this->halfDimension = halfDimensions;
	}
	~AABB() {}

	bool containsPoint(glm::vec3 pt) {
		if (pt.x >= center.x - halfDimension.x && pt.x <= center.x + halfDimension.x &&
			pt.y >= center.y - halfDimension.y && pt.y <= center.y + halfDimension.y &&
			pt.z >= center.z - halfDimension.z && pt.z <= center.z + halfDimension.z)
		{
			return true;
		}
		return false;
	}

	bool containsAABB(AABB other) {
		if (glm::abs(center.x - other.center.x) > (halfDimension.x + other.halfDimension.x)) return false;
		if (glm::abs(center.y - other.center.y) > (halfDimension.y + other.halfDimension.y)) return false;
		if (glm::abs(center.z - other.center.z) > (halfDimension.z + other.halfDimension.z)) return false;
		return true;
	}

private:
	glm::vec3 center;
	glm::vec3 halfDimension;
};
