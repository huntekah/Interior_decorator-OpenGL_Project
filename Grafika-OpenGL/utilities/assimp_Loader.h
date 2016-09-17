#pragma once
#include <vector>
#include <glm/glm.hpp>

class AssimpLoader {
	Assimp::Importer importer;
public:
	bool LoadOBJ(
		const char * path,
		std::vector<glm::vec3> & out_vertices,
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals);

};