#pragma once


// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mesh.h"




class Model {
public:
	/*  Functions   */
	// Constructor, expects a filepath to a 3D model.
	Model(GLchar* path);

	// Draws the model, and thus all its meshes
	void Draw(Shader shader);
private:
	/*  Model Data  */
	vector<Mesh> meshes;
	string directory;

	/*  Functions   */
	// Loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void loadModel(string path);
	
	// Processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

};
GLint TextureFromFile(const char* path, string directory);