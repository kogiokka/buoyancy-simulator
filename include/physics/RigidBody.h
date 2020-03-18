#pragma once

#include <glm/glm.hpp>
#include "physics/Quaternion.h"
#include "physics/Functions.h"


class RigidBody
{
	friend class Func;

protected:
	glm::vec3 m_Pos;    // world position of center of mass
	Quaternion m_Q;     // rotation
	glm::vec3 m_V;      // velocity of center of mass
	glm::vec3 m_W;      // angular velocity
	glm::vec3 m_F;      // force at center of mass
	glm::vec3 m_Torque; // torque
	glm::vec3 m_I;      // rotational inertia
	float m_Mass;

	glm::vec3 m_PosBegin;

	RigidBody(glm::vec3 position, Quaternion quaternion);
	virtual ~RigidBody();
};
