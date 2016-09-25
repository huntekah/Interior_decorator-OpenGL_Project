#pragma once


#include <string>
#include <GL/glew.h>

class Shader
{
public:
	GLuint Program;
	// Constructor generates the shader on the fly
	Shader();
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	// Uses the current shader
	void Use();
	~Shader();
	void Delete();
};

