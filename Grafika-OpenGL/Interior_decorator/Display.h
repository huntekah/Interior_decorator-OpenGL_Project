#pragma once
#include "file_loader.h"

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include <vector>

#include "utilities/shader_loader.h"
#include "utilities/time.h"			
#include "utilities/controls.h"
#include "utilities/Model.h"
#include "utilities/Shader.h"
#include "utilities/Skybox.h"

class Display : protected FileLoader, 
				protected ShaderLoader, 
				public Controls,
				private virtual Time{
private:
	std::vector<GLuint> vertexArrayID;	// 1 .. 1

	std::vector<GLuint> matrixID;		// 1 .. many
	std::vector<GLuint> viewMatrixID;	// 1 .. many
	std::vector<GLuint> modelMatrixID;	// 1 .. many
	
	std::vector<GLuint> texture;		// 1 .. 1
	std::vector<GLuint> textureID;		// 1 .. 1
	
	std::vector<std::vector<glm::vec3> > vertices;	// 1 .. 1
	std::vector<std::vector<glm::vec2> > uvs;		// 1 .. 1
	std::vector<std::vector<glm::vec3> > normals;	// 1 .. 1

	std::vector<std::vector<unsigned short> > indices;	// 1 .. 1
	std::vector<std::vector<glm::vec3> > indexedVertices;// 1 .. 1
	std::vector<std::vector<glm::vec2> > indexedUvs;		// 1 .. 1
	std::vector<std::vector<glm::vec3> > indexedNormals;	// 1 .. 1

	std::vector<GLuint> vertexBuffer;	// 1 .. 1
	std::vector<GLuint> uvBuffer;		// 1 .. 1
	std::vector<GLuint> normalBuffer;	// 1 .. 1
	std::vector<GLuint> elementBuffer;	// 1 .. 1

	std::vector<GLuint> lightID;		// 1 .. many (per shader)
	std::vector<GLuint> lightPowerID;	// 1.. many (per shader)
	std::vector<GLuint> lightGlobalID;		// 1 .. many (per shader)


	//inicialised not to inicialise them in each draw loop;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	
	glm::vec3 lightGlobalPos;

	//std::vector<glm::mat4> modelMatrix;	// 1 .. 1
	std::vector<glm::mat4> MVP;			// 1 .. 1

	/* corelation between porgramID and specific Object;
	(since two or more objects can have the same programID) */
	std::vector<int> ObjToProgramID;	//binds object with ProgramID (shaders) first - obj id, second - program id
	GLFWwindow *const&window;

	// needed for Assimp Object Loading (class Model.h)
	std::vector<Shader> shader;		// 1 .. many
	std::vector<Model> model;	// 1 .. 1
	GLuint shineID;

	Skybox skybox;
	Shader skyboxShader;

	void InitializeVertexArray();
	void InitializeShaders();
	void GetHandleMVP();
	void LoadOpenGLObjects();
	void LoadIntoVBO();
	void InitializeMVP();
	void InitializeSkybox();
	
public:
	Display(std::string, GLFWwindow*const&);
	~Display();
	bool Draw();
	void Save();
	void Translate(int id, double x, double y, double z);
	void Translate(int id, glm::vec3 translation);
	void Scale(int id, double x, double y, double z);
	void Scale(int id, glm::vec3 scale);
	void Rotate(int id, glm::quat rotation);
	void Rotate(int id, double yaw, double pitch, double roll);
	void Rotate(int id, glm::vec3 rotation);

};