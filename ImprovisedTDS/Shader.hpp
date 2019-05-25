#pragma once
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


// TODO: Shader class should compile itself and provide any shader data (uniforms etc)
class Shader
{
public:
	Shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
	~Shader();
	
	static Shader* ReadFromFile(const std::string& shadersFilePath);

	void Use();
	static void Unuse();
	//GLuint GetProgram() const;
	//GLint GetUniformLocation(const std::string& name) const;

	void SetUniform(const std::string& name, glm::vec2 value) const;
	void SetUniform(const std::string& name, glm::vec3 value) const;
	void SetUniform(const std::string& name, glm::vec4 value) const;
	void SetUniform(const std::string& name, glm::mat4 value) const;
	void SetUniform(const std::string& name, GLfloat value) const;
	void SetUniform(const std::string& name, GLuint value) const;
	void SetUniform(const std::string& name, GLint value) const;

private:
	GLint GetUniformLocation(const std::string& name) const;
	GLuint GetProgram() const;
	GLuint program_;

	bool isUsed_ = false;
};

inline Shader::Shader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
{
	const GLchar* vertexCode = vertexShaderCode.c_str();
	const GLchar* fragmentCode = fragmentShaderCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexCode, nullptr);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		throw std::runtime_error(infoLog);
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentCode, nullptr);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		throw std::runtime_error(infoLog);
	}

	this->program_ = glCreateProgram();
	glAttachShader(this->program_, vertex);
	glAttachShader(this->program_, fragment);
	glLinkProgram(this->program_);

	glGetProgramiv(this->program_, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->program_, 512, nullptr, infoLog);
		throw std::runtime_error(infoLog);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


inline Shader::~Shader()
{
	glDeleteProgram(GetProgram());
}

inline Shader* Shader::ReadFromFile(const std::string& shadersFilePath)
{
	std::cout << "> Reading Shader " << shadersFilePath << "..." << std::endl;
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;

	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);

	try
	{
		vShaderFile.open(shadersFilePath + ".vert");
		fShaderFile.open(shadersFilePath + ".frag");

		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(std::ifstream::failure e)
	{
		throw std::runtime_error("ERROR: Couldn't read the shader files");
	}
	std::cout << "> End reading Shader " << shadersFilePath << "..." << std::endl;
	return new Shader(vertexCode, fragmentCode);
}

inline void Shader::Use()
{
	if (!isUsed_)
	{
		std::cout << "> Using Program " << GetProgram() << "..." << std::endl;
		glUseProgram(GetProgram());
		isUsed_ = true;
	}
}

inline void Shader::Unuse()
{
	glUseProgram(0);
}

inline GLuint Shader::GetProgram() const
{
	return this->program_;
}

inline GLint Shader::GetUniformLocation(const std::string& name) const
{
	return glGetUniformLocation(GetProgram(), name.c_str());
}

inline void Shader::SetUniform(const std::string& name, glm::vec2 value) const
{
	glUniform2fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

inline void Shader::SetUniform(const std::string& name, glm::vec3 value) const
{
	glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

inline void Shader::SetUniform(const std::string& name, glm::vec4 value) const
{
	glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

inline void Shader::SetUniform(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

inline void Shader::SetUniform(const std::string& name, GLfloat value) const
{
	glUniform1f(GetUniformLocation(name), value);
}

inline void Shader::SetUniform(const std::string& name, GLuint value) const
{
	glUniform1ui(GetUniformLocation(name), value);
}

inline void Shader::SetUniform(const std::string& name, GLint value) const
{
	glUniform1i(GetUniformLocation(name), value);
}
