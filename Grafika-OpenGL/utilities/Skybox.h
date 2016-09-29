#pragma once

#include <vector>
// Include GLEW
#include <GL/glew.h>

#include <glm/glm.hpp>
// Shader handling
#include "Shader.h"
#include "img_load.h"


class Skybox {
private:
	GLuint skyboxTextureID;
	GLuint skyboxVAO, skyboxVBO;
	GLfloat skyboxVertices[108];
	std::vector<GLchar*> faces;
	void setVAOandVBO();
public:
	Skybox();
	Skybox(std::vector<std::string>& faces);
	Skybox(Skybox&skybox);
	GLuint loadCubemap();
	void Draw(Shader& shader, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

};