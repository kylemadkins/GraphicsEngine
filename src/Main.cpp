#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::string loadShader(const std::string& filePath) {
	std::ifstream shaderFile(filePath);
	if (!shaderFile.is_open()) {
		throw std::runtime_error("Failed to open shader file: " + filePath);
	}
	std::stringstream buffer;
	buffer << shaderFile.rdbuf();
	return buffer.str();
}

int main()
{
	std::string vertexShaderSrc;
	std::string fragmentShaderSrc;
	try {
		vertexShaderSrc = loadShader("shaders/triangle.vert");
		fragmentShaderSrc = loadShader("shaders/triangle.frag");
	}
	catch (const std::runtime_error& error) {
		std::cerr << error.what() << std::endl;
		return 1;
	}

	if (!glfwInit()) {
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	int width = 640;
	int height = 480;

	GLFWwindow* window = glfwCreateWindow(width, height, "Graphics Engine", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return 1;
	}

	glViewport(0, 0, width, height);

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vertexSrc = vertexShaderSrc.c_str();
	glShaderSource(vertexShader, 1, &vertexSrc, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fragmentSrc = fragmentShaderSrc.c_str();
	glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLuint vao, vbo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
