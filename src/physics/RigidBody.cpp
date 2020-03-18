#include "physics/RigidBody.h"


RigidBody::RigidBody(glm::vec3 position, Quaternion quaternion)
    : m_Pos(position), m_Q(quaternion), m_PosBegin(position)
{ }

RigidBody::~RigidBody()
{ }
