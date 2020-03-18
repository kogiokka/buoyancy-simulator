#pragma once
#include <math.h>
#include <glm/glm.hpp>


struct Quaternion
{
	float x;
	float y;
	float z;
	float w;
	glm::vec4 initialValues;

	Quaternion() {}
	Quaternion(float x, float y, float z, float w)
	    : x(x), y(y), z(z), w(w), initialValues(x, y, z, w)
	{ }
	Quaternion(glm::vec4 vec)
	    : x(vec.x), y(vec.y), z(vec.z), w(vec.w), initialValues(vec)
	{ }

	Quaternion& operator += (const Quaternion& q)
	{
		x += q.x;
		y += q.y;
		z += q.z;
		w += q.w;
		return *this;
	}

	void normalize()
	{
		float len = sqrtf(x*x + y*y + z*z + w*w);
		if (len != 0.0f) {
			x /= len;
			y /= len;
			z /= len;
			w /= len;
		} else {
			x = 0;
			y = 0;
			z = 0;
			w = 1;
		}
	}

	Quaternion conjugate() const
	{
		return Quaternion(-x, -y, -z, w);
	}

	glm::vec3 rotate(const glm::vec3& v) const
	{
		glm::vec3 s(x, y, z);
		return v + 2.0f*cross(s, (cross(s,v)+w*v));
	}

	glm::mat3 Matrix() const
	{
		float x2 = x + x,  y2 = y + y,  z2 = z + z;
		float xx = x * x2, xy = x * y2, xz = x * z2;
		float yy = y * y2, yz = y * z2, zz = z * z2;
		float wx = w * x2, wy = w * y2, wz = w * z2;

		glm::mat3 R(0.0f);
		R[0][0] = 1 - (yy + zz);
		R[1][0] = xy - wz;
		R[2][0] = xz + wy;

		R[0][1] = xy + wz;
		R[1][1] = 1 - (xx + zz);
		R[2][1] = yz - wx;

		R[0][2] = xz - wy;
		R[1][2] = yz + wx;
		R[2][2] = 1 - (xx + yy);

		return R;
	}

	void setInitials(glm::vec4 vec4)
	{
		initialValues = vec4;
	}

	void reset()
	{
		x = initialValues.x;
		y = initialValues.y;
		z = initialValues.z;
		w = initialValues.w;
	}

	glm::vec4 initials() const
	{
		return initialValues;
	}

	glm::vec4 toVec4() const
	{
		return glm::vec4 { x, y, z, w };
	}
};

// Quaternion multiplication
inline Quaternion operator * (const Quaternion& a, const Quaternion& b)
{
	Quaternion result;

	float aW = a.w, aX = a.x, aY = a.y, aZ = a.z;
	float bW = b.w, bX = b.x, bY = b.y, bZ = b.z;

	result.x = aW * bX + bW * aX + aY * bZ - aZ * bY;
	result.y = aW * bY + bW * aY + aZ * bX - aX * bZ;
	result.z = aW * bZ + bW * aZ + aX * bY - aY * bX;
	result.w = aW * bW - (aX*bX + aY * bY + aZ * bZ);

	return result;
}

inline Quaternion operator * (float s, const Quaternion& q)
{
	return Quaternion(s*q.x, s*q.y, s*q.z, s*q.w);
}
