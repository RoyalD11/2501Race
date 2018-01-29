#pragma once

#include <GL/glew.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ResourceManager.h"

class Shader {
public:
	Shader(const char *vertPath, const char *fragPath);
	~Shader();

	void enable();
	void disable();

	void setUniform1i(const GLchar *name, int value);
	void setUniform1f(const GLchar *name, float value);
	void setUniform2f(const GLchar *name, const glm::vec2 &vector);
	void setUniform3f(const GLchar *name, const glm::vec3 &vector);
	void setUniform4f(const GLchar *name, const glm::vec4 &vector);
	void setUniformMat4(const GLchar *name, const glm::mat4 &matrix);

	inline GLuint getShaderID() { return shaderProgram; }
private:
	GLuint shaderProgram;
};