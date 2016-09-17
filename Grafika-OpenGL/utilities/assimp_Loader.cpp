
#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing fla

#include "assimp_Loader.h"

bool AssimpLoader::LoadOBJ(const char * path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
{
	const aiScene* scene = importer.ReadFile( path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);
/*
	if (!scene)
	{
		printf("Couldn't load model: %s \nError Importing Asset",path);
		fprintf( stderr, importer.GetErrorString());
		getchar();
		return false;
	}
	*/
	return false;
}
