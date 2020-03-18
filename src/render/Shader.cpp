#include "render/Shader.h"


Shader::Shader(const QString& vertexPath, const QString& fragmentPath)
{
	QFile vertexShaderFile(vertexPath);
	QFile fragmentShaderFile(fragmentPath);

	// open files
	if (!vertexShaderFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Opening Vertex Shader file failed!";
	}

	if (!fragmentShaderFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Opening Fragment Shader file failed!";
	}

	std::string vSrc = vertexShaderFile.readAll().toStdString();
	std::string fSrc = fragmentShaderFile.readAll().toStdString();

	const GLchar* vertexShaderSource = vSrc.c_str();
	const GLchar* fragmentShaderSource = fSrc.c_str();

	// std::cout << "Shader content: " << vertexShaderSource << std::endl;
	// std::cout << "Shader content: " << fragmentShaderSource << std::endl;

	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");

	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	glLinkProgram(m_ID);
	checkCompileErrors(m_ID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	// GLint shaderNum;
	// glGetProgramiv(m_ID, GL_ATTACHED_SHADERS, &shaderNum);
	// std::cout << "There are " << shaderNum << " shaders attached to the program object.\n";
}

Shader::~Shader()
{
	glDeleteShader(m_ID);
}

void Shader::use()
{
	glUseProgram(m_ID);
}

void Shader::disable()
{
	glUseProgram(0);
}

/*uniform setter function*/
void Shader::setBool(const std::string &name, bool value)
{
	glUniform1i(uniform(name), (int)value);
}

void Shader::setInt(const std::string &name, int value)
{
	glUniform1i(uniform(name), value);
}

void Shader::setFloat(const std::string &name, float value)
{
	glUniform1f(uniform(name), value);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w)
{
	glUniform4f(uniform(name), x, y, z, w);
}

void Shader::setVec3(const std::string &name, float x, float y, float z)
{
	glUniform3f(uniform(name), x, y, z);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat)
{
	glUniformMatrix4fv(uniform(name), 1, GL_FALSE, glm::value_ptr(mat));
}

int Shader::uniform(const std::string &name)
{
	if (m_UniformLocations.find(name) != m_UniformLocations.end())
		return m_UniformLocations[name];

	int location = glGetUniformLocation(m_ID, name.c_str());
	if (location == -1) {
		std::cerr << "Uniform " << name << " does not exist!" << std::endl;
	}

	m_UniformLocations[name] = location;
	return location;
}

void Shader::checkCompileErrors(unsigned int m_ID, std::string type) {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(m_ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(m_ID, 1024, nullptr, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
			          << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	} else
	{
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_ID, 1024, nullptr, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
			          << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
