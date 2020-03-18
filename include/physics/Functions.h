#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/intersect.hpp>
#include <QtGui/QVector3D>
#include <QtGui/QMatrix4x4>
#include <tuple>

#include "Quaternion.h"
#include "World.h"


class Func
{
public:
	typedef glm::vec3    Vertex;  // {float, float, float}
	typedef glm::ivec3    Face;  // {int, int, int}
	typedef glm::vec3    Position;

public:
	static glm::mat4 Translate(const glm::vec3& pos, const Quaternion& q);

	static float ClipTriangle(glm::vec3& c, glm::vec3 p, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3,
	                          float d1, float d2, float d3);

	static float TetrahedronVolume(glm::vec3& c, glm::vec3 p, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

	static float ComputeVolume(std::vector<Vertex>& vertices, std::vector<Face>& faces);

	static std::tuple<float, glm::vec3> SubmergedVolume(std::vector<Vertex>& vertices, std::vector<Face>& faces,
	                             Position& position, Quaternion& qnion);

	static glm::vec3 GlmVec3(QVector3D qvec3);
	static glm::vec4 GlmVec4(QVector4D qvec4);
	static QMatrix4x4 GlmMat4(glm::mat4 mat4);
	static QVector3D QtVector3(glm::vec3 vec3);
	static QVector4D QtVector4(glm::vec4 vec4);
	static glm::mat4 QtMatrix4(QMatrix4x4 qmat4);
};
