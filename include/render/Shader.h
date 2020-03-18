#pragma once

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <unordered_map>
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QString>


class Shader
{
	unsigned int m_ID;  //Shader Program ID

	// Store uniform locations to avoid asking the shader program object every time.
	std::unordered_map<std::string, int> m_UniformLocations;

public:
	Shader(const QString& vertexPath, const QString& fragmentPath);
	~Shader();
	Shader(const Shader&) = delete;
	void use();
	void disable();
	/*uinform setter*/
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setVec4(const std::string& name, float x, float y, float z, float w);
	void setVec3(const std::string& name, float x, float y, float z);
	void setMat4(const std::string& name, const glm::mat4 &mat);
private:
	int uniform(const std::string& name);  // Get the uniform location
	void checkCompileErrors(unsigned int ID, std::string type);
};

