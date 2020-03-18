#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <glm/glm.hpp>
#include <QtGui/QVector3D>
#include <QtGui/QMatrix4x4>


class Debug
{
public:
	static void Vec3(glm::vec3 vec, std::string name = "Vector 3", std::string dilimiter = ", ")
	{
		std::cout.setf(std::ios::scientific);
		std::cout << " - " << name << ":\n"
		          << vec.x << dilimiter << vec.y << dilimiter << vec.z << "\n"
		          << std::endl;
		std::cout.unsetf(std::ios::scientific);
	}

	static void Vec4(glm::vec4 vec, std::string name = "Vector 4", std::string dilimiter = ", ")
	{
		std::cout.setf(std::ios::scientific);
		std::cout << " - " << name << ":\n"
		          << vec.x << dilimiter << vec.y << dilimiter << vec.z << dilimiter << vec.w << "\n"
		          << std::endl;
		std::cout.unsetf(std::ios::scientific);
	}

	static void Mat4(glm::mat4 mat, std::string name = "Matrix 4x4", std::string dilimiter = ", ")
	{
		std::cout.setf(std::ios::scientific);
		std::cout << " - " << name << ":\n"
		          << mat[0][0] << dilimiter << mat[0][1] << dilimiter << mat[0][2] << dilimiter << mat[0][3] << "\n"
		          << mat[1][0] << dilimiter << mat[1][1] << dilimiter << mat[1][2] << dilimiter << mat[1][3] << "\n"
		          << mat[2][0] << dilimiter << mat[2][1] << dilimiter << mat[2][2] << dilimiter << mat[2][3] << "\n"
		          << mat[3][0] << dilimiter << mat[3][1] << dilimiter << mat[3][2] << dilimiter << mat[3][3] << "\n"
		          << std::endl;
		std::cout.unsetf(std::ios::scientific);
	}
	static void QVec3(QVector3D vec, std::string name = "QVector3D", std::string dilimiter = ", ")
	{
		std::cout.setf(std::ios::scientific);
		std::cout << " - " << name << ":\n"
		          << vec.x() << dilimiter << vec.y() << dilimiter << vec.z() << "\n"
		          << std::endl;
		std::cout.unsetf(std::ios::scientific);
	}
	static void QVec4(QVector4D vec, std::string name = "QVector4D", std::string dilimiter = ", ")
	{
		std::cout.setf(std::ios::scientific);
		std::cout << " - " << name << ":\n"
		          << vec.x() << dilimiter << vec.y() << dilimiter << vec.z() << dilimiter << vec.w() << "\n"
		          << std::endl;
		std::cout.unsetf(std::ios::scientific);
	}
	static void QMat4(QMatrix4x4 mat, std::string name = "QMatrix4x4", std::string dilimiter = ", ")
	{
		std::cout.setf(std::ios::scientific);
		std::cout << " - " << name << ":\n";
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 3; j++) {
				std::cout << mat.data()[4*i + j] << dilimiter;
			}
			std::cout << mat.data()[4*i + 3] << "\n";
		}
		std::cout << std::endl;
		std::cout.unsetf(std::ios::scientific);
	}
};
