#pragma once
#include "file_loader.h"

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "common/shader.hpp"
#include "common/objloader.hpp"
#include "common/vboindexer.hpp"
#include "common/texture.hpp"
#include "common/controls.hpp"

class Display : protected FileLoader{
private:
	std::vector<GLuint> VertexArrayID;	// 1 .. 1
	std::vector<GLuint> programID;		// 1 .. many

	std::vector<GLuint> MatrixID;		// 1 .. many
	std::vector<GLuint> ViewMatrixID;	// 1 .. many
	std::vector<GLuint> ModelMatrixID;	// 1 .. many
	
	std::vector<GLuint> Texture;		// 1 .. 1
	std::vector<GLuint> TextureID;		// 1 .. 1
	
	std::vector<std::vector<glm::vec3>> vertices;	// 1 .. 1
	std::vector<std::vector<glm::vec2>> uvs;		// 1 .. 1
	std::vector<std::vector<glm::vec3>> normals;	// 1 .. 1

	std::vector<std::vector<unsigned short>> indices;	// 1 .. 1
	std::vector<std::vector<glm::vec3>> indexedVertices;// 1 .. 1
	std::vector<std::vector<glm::vec2>> indexedUvs;		// 1 .. 1
	std::vector<std::vector<glm::vec3>> indexedNormals;	// 1 .. 1

	std::vector<GLuint> vertexBuffer;	// 1 .. 1
	std::vector<GLuint> uvBuffer;		// 1 .. 1
	std::vector<GLuint> normalBuffer;	// 1 .. 1
	std::vector<GLuint> elementBuffer;	// 1 .. 1

	std::vector<GLuint> LightID;		// 1 .. many
	
	double lastTime;

	//inicialised not to inicialise them in each draw loop;
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	
	glm::vec3 lightPos;

	std::vector<glm::mat4> ModelMatrix;	// 1 .. 1
	std::vector<glm::mat4> MVP;			// 1 .. 1

	/* corelation between porgramID and specific Object;
	(since two or more objects can have the same programID) */
	std::vector<int> ObjToProgramID;	//binds object with ProgramID (shaders) first - obj id, second - program id
	GLFWwindow *const&window;

	void InitializeVertexArray();
	void InitializeShaders();
	bool isNewShader( int );
	int getSimilarShaders(int);
	void GetHandleMVP();
	void LoadTextures();
	void LoadOpenGLObjects();
	void LoadIntoVBO();
	void InitializeTime(); //inicializes lastTime and DeltaTime Variables.
	void SetDeltaTime();	// updates deltaTime Variable with a time between last call of this function
	void InitializeDrawObjects();

	double deltaTime;
	
public:
	Display(std::string, GLFWwindow*const&);
	~Display();
	bool Draw();
	
	

};