#include "physics/Functions.h"


/**
 * @brief Return the rotation matrix calculated from unit quaterion.
 *
 * @param  Position
 * @param  Quaternion
 * @return  Rotation matrix
 */
glm::mat4 Func::Translate(const glm::vec3& pos, const Quaternion& q)
{
	glm::mat3 scaleMat = q.Matrix();
	glm::mat4 rotateMat;

	rotateMat[0][0] = scaleMat[0][0]; rotateMat[0][1] = scaleMat[0][1]; rotateMat[0][2] = scaleMat[0][2]; rotateMat[0][3] = 0;
	rotateMat[1][0] = scaleMat[1][0]; rotateMat[1][1] = scaleMat[1][1]; rotateMat[1][2] = scaleMat[1][2]; rotateMat[1][3] = 0;
	rotateMat[2][0] = scaleMat[2][0]; rotateMat[2][1] = scaleMat[2][1]; rotateMat[2][2] = scaleMat[2][2]; rotateMat[2][3] = 0;
	rotateMat[3][0] = pos.x;          rotateMat[3][1] = pos.y;          rotateMat[3][2] = pos.z;          rotateMat[3][3] = 1;

	return rotateMat;
}

/**
 * @brief Return the volume of tetrahedron from the object
 *
 * @param  Centroid
 * @param
 * @param  Vertex position
 * @param  Vertex position
 * @param  Vertex position
 * @return  Volume of a tetrahedron
 */
float Func::TetrahedronVolume(glm::vec3& centroid, glm::vec3 p, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
{
	glm::vec3 a = v2 - v1;
	glm::vec3 b = v3 - v1;
	glm::vec3 r = p - v1;
	float volume = (1.0f / 6.0f) * glm::dot(glm::cross(b, a), r);

	//update the centroid accumulator
	centroid += 0.25f * volume * (v1 + v2 + v3 + p);
	return volume;
}

float Func::ComputeVolume(std::vector<Vertex>& vertices, std::vector<Face>& faces)
{
	float volume = 0;
	glm::vec3 c(0.0f), zero(0.0f);

	// Compute the contribution of each triangle
	for (unsigned int i = 0; i < faces.size(); ++i)
	{
		unsigned int i1 = faces[i].x;
		unsigned int i2 = faces[i].y;
		unsigned int i3 = faces[i].z;

		glm::vec3 v1 = vertices[i1];
		glm::vec3 v2 = vertices[i2];
		glm::vec3 v3 = vertices[i3];

		volume += TetrahedronVolume(c, zero, v1, v2, v3);
	}
	return volume;
}

std::tuple<float, glm::vec3> Func::SubmergedVolume(std::vector<Vertex>& vertices, std::vector<Face>& faces,
                            Position& position, Quaternion& qnion)
{
	// Transform the plane into the polyhedron frame.
	glm::vec3 normal = qnion.conjugate().rotate(Water::Plane::normal);
	float offset = Water::Plane::offset - glm::dot(Water::Plane::normal, position);

	// Compute the vertex heights relative to the surface.
	float TINY_DEPTH = -1e-6f;
	float* ds = new float[vertices.size()];

	// Compute the depth of each vertex.
	int numSubmerged = 0;
	unsigned int sampleVert = 0;
	for (unsigned int i = 0; i < vertices.size(); ++i)
	{
		ds[i] = glm::dot(normal, vertices[i]) - offset;
		if (ds[i] < TINY_DEPTH)
		{
			++numSubmerged;
			sampleVert = i;
		}
	}

	// Return early if no vertices are submerged
	if (numSubmerged == 0)
	{
		delete[] ds;
		return { 0.0f, glm::vec3{0.0f} };  // --- return <volume, centroid>
	}

	glm::vec3 p = vertices[sampleVert] - ds[sampleVert] * normal;

	// Initialize volume and centroid accumulators.
	float volume = 0.0f;
	glm::vec3 C { 0.0f };

	// Compute the contribution of each triangle.
	for (unsigned int i = 0; i < faces.size(); ++i)
	{
		int i1 = faces[i].x;
		int i2 = faces[i].y;
		int i3 = faces[i].z;

		glm::vec3 v1 = vertices[i1];
		float d1 = ds[i1];

		glm::vec3 v2 = vertices[i2];
		float d2 = ds[i2];

		glm::vec3 v3 = vertices[i3];
		float d3 = ds[i3];

		if (d1 * d2 < 0)
		{
			// v1-v2 crosses the plane
			volume += Func::ClipTriangle(C, p, v1, v2, v3, d1, d2, d3);
		}
		else if (d1 * d3 < 0)
		{
			// v1-v3 crosses the plane
			volume += Func::ClipTriangle(C, p, v3, v1, v2, d3, d1, d2);
		}
		else if (d2 * d3 < 0)
		{
			// v2-v3 crosses the plane
			volume += Func::ClipTriangle(C, p, v2, v3, v1, d2, d3, d1);
		}
		else if (d1 < 0 || d2 < 0 || d3 < 0)
		{
			// fully submerged
			volume += TetrahedronVolume(C, p, v1, v2, v3);
		}
	}

	// Small submerged slivers may have roundoff error leading to a zero or negative volume.
	// If so, then return a result of zero.
	float TINY_VOLUME = 1e-6f;
	if (volume <= TINY_VOLUME)
	{
		delete[] ds;
		return { 0.0f, glm::vec3{0.0f} };  // --- return <volume, centroid>
	}

	// Normalize the centroid by the total volume.
	C *= 1.0f / volume;

	// Transform the centroid into world coordinates.
	C = position + qnion.rotate(C);

	delete[] ds;
	return { volume, C };  // --- return <volume, centroid>
}

float Func::ClipTriangle(glm::vec3& c, glm::vec3 p, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3,
                         float d1, float d2, float d3)
{
	assert(d1*d2 < 0);
	glm::vec3 vc1 = v1 + (d1 / (d1 - d2))*(v2 - v1);
	float volume = 0;

	if (d1 < 0)
	{
		if (d3 < 0)
		{
			// Case B - two triangles.
			glm::vec3 vc2 = v2 + (d2 / (d2 - d3))*(v3 - v2);
			volume += TetrahedronVolume(c, p, vc1, vc2, v1);
			volume += TetrahedronVolume(c, p, vc2, v3, v1);
		}
		else
		{
			// Case A - a single triangle.
			glm::vec3 vc2 = v1 + (d1 / (d1 - d3))*(v3 - v1);
			volume += TetrahedronVolume(c, p, vc1, vc2, v1);
		}
	}
	else
	{
		if (d3 < 0)
		{
			// Case B
			glm::vec3 vc2 = v1 + (d1 / (d1 - d3))*(v3 - v1);
			volume += TetrahedronVolume(c, p, vc1, v2, v3);
			volume += TetrahedronVolume(c, p, vc1, v3, vc2);
		}
		else
		{
			// Case A
			glm::vec3 vc2 = v2 + (d2 / (d2 - d3))*(v3 - v2);
			volume += TetrahedronVolume(c, p, vc1, v2, vc2);
		}
	}
	return volume;
}

glm::vec3 Func::GlmVec3(QVector3D qvec3)
{
	return glm::vec3 { qvec3.x(), qvec3.y(), qvec3.z() };
}

glm::vec4 Func::GlmVec4(QVector4D qvec4)
{
	return  glm::vec4 {qvec4.x(), qvec4.y(), qvec4.z(), qvec4.w() };
}

QMatrix4x4 Func::GlmMat4(glm::mat4 mat4)
{
	QMatrix4x4 qmat4;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			 qmat4.data()[4*i + j] = mat4[i][j];
	return qmat4;
}

QVector3D Func::QtVector3(glm::vec3 vec3)
{
	return QVector3D { vec3.x, vec3.y, vec3.z };
}

QVector4D Func::QtVector4(glm::vec4 vec4)
{
	return QVector4D(vec4.x, vec4.y, vec4.z, vec4.w);
}

glm::mat4 Func::QtMatrix4(QMatrix4x4 qmat4)
{
	glm::mat4 glmMat4;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			glmMat4[i][j] = qmat4.data()[4*i + j];
	return glmMat4;
}
