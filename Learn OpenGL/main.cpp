#pragma once

#include <glad/glad.h>
#include "glad.c"
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\n\0";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);


	unsigned int vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int secondFragmentShader;
	secondFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(secondFragmentShader, 1, &fragmentShaderSource2, NULL);
	glCompileShader(secondFragmentShader);
	glGetShaderiv(secondFragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(secondFragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	unsigned int secondShaderProgram;
	secondShaderProgram = glCreateProgram();

	glAttachShader(secondShaderProgram, vertexShader);
	glAttachShader(secondShaderProgram, secondFragmentShader);
	glLinkProgram(secondShaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(secondFragmentShader);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}


	float firstTriangleVertices[] = {
		// first triangle
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
	};
	float secondTriangleVertices[] = {
		 0.0f, -0.5f, 0.0f,  // left
		 0.9f, -0.5f, 0.0f,  // right
		 0.45f, 0.5f, 0.0f   // top 
	};

	unsigned int VAO[2], VBO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	glBindVertexArray(VAO[0]);

	// First triangle
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangleVertices), firstTriangleVertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// Unbind first
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Bind second VBO and VAO
	glBindVertexArray(VAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangleVertices), secondTriangleVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// Rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(secondShaderProgram);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
