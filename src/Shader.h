#pragma once

#include <string>

#include <glad/glad.h>

class Shader {
public:
	GLuint id;
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void use();
	// Utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};
