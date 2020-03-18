#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <tuple>

#include "physics/Functions.h"
#include "physics/RigidBody.h"
#include "render/Render.h"

#ifndef NDEBUG
#include <DebugFunctions.h>
#endif


class Polyhedron : public RigidBody
{
	typedef glm::vec3     Vertex;
	typedef glm::ivec3    Face;  // {int, int, int}
	typedef glm::vec3     Normal;

	std::vector<Vertex> m_Verts;
	std::vector<Face> m_Faces;
	std::vector<Normal> m_Normals;

	int m_NumVerts;
	int m_NumFaces;
	std::vector<float> m_AttribArray;

	std::string m_Name;
	glm::vec3 m_Dimen;
	float m_Length;
	float m_Volume;
	float m_Density;

public:
	Polyhedron(
	  std::string name,
	  glm::vec3 position = glm::vec3{0.0f, 10.0f, 0.0f},
	  glm::vec3 dimension = glm::vec3{1.0f, 0.3f, 1.0f},
	  Quaternion quaternion = Quaternion(1.0f, 2.0f, 3.0f, 4.0f),
	  float density = 500.0f
	);
	virtual ~Polyhedron();
	void updateVertexData() const;
	void setPosition(glm::vec3 pos);
	void setDimension(glm::vec3 dimen);
	void setDensity(float density);
	void setQuaternion(QVector4D quaternion);
	glm::vec3 position() const;
	glm::vec3 dimension() const;
	float density() const;
	glm::vec4 quaternion() const;

	void init();
	void initBody();
	void initPhysicalProperties();
	void update();
	void restart(bool rebuildBody);
	void updateVertexAttrs();
private:
	void computeBuoyancy();
};
