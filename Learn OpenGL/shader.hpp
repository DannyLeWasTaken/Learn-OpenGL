#ifndef SHADER_H
#define SHADER_H

#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
	unsigned int ID;
	
	/*
	* Constructor for shader class
	* @param[in] vertexPath File path to vertex shader.
	* @param[in] fragmentPath File path to fragment shader.
	* @return Shader
	*/
	Shader(const char* vertexPath, const char* fragmentPath)
	{
		/*
		// 1. tretive the vertex/fragment source code from filePath given
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions
		vShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read files's buffer contents into stream
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		// 2. compile shaders
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		// vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		*/
		

		// shader Program
		int success;
		char infoLog[512];
		ID = glCreateProgram();
		//glAttachShader(ID, vertex);
		//glAttachShader(ID, fragment);
		attachShader(vertexPath, GL_VERTEX_SHADER);
		attachShader(fragmentPath, GL_FRAGMENT_SHADER);
	}

	
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
	{
		int success;
		char infoLog[512];
		ID = glCreateProgram();
		glLinkProgram(ID);
		
		attachShader(vertexPath, GL_VERTEX_SHADER);
		attachShader(geometryPath, GL_GEOMETRY_SHADER);
		attachShader(fragmentPath, GL_FRAGMENT_SHADER);
	}
	

	
	void attachShader(const char* shaderPath, GLenum shaderType)
	{
		std::string fileCode;
		std::ifstream shaderFile;
		// compile shader
		shaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
		try
		{
			shaderFile.open(shaderPath);
			std::stringstream shaderStream;
			shaderStream << shaderFile.rdbuf();
			fileCode = shaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		}
		const char* shaderCode = fileCode.c_str();
		int success;
		char infoLog[512];

		// compile shader
		const unsigned int shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &shaderCode, nullptr);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		glAttachShader(ID, shader);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(shader);
	}
	

	/*
	* Use shader. Equivalent to glUseProgram.
	* @return void
	*/
	void use()
	{
		glUseProgram(ID);
	};
	/*
	* Set a uniform bool value in the shader object
	* @param name Name of uniform value
	* @param value
	* @return void
	*/
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	};

	/*
	* Set a uniform int value in the shader object
	* @param name Name of uniform value
	* @param value
	* @return void
	*/
	void setInt(const std::string& name, int value)
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	};

	/*
	* Set a uniform float value in the shader object
	* @param name Name of uniform value
	* @param value
	* @return void
	*/
	void setFloat(const std::string& name, float value)
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	};

	void setMat4(const std::string& name, glm::mat4 &value)
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	void setVec3(const std::string& name, const glm::vec3 &value)
	{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
	}

	void setVec3(const std::string& name, float x, float y, float z)
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}

	void setVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
	}
};

#endif