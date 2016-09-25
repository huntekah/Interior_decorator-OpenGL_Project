#pragma once
#include "Display.h"



void Display::InitializeVertexArray()
{
	for (unsigned int i = 0; i < data.size(); i++) {
		vertexArrayID.emplace_back(GLuint());
		glGenVertexArrays(1, &(vertexArrayID[i])); 
		glBindVertexArray(vertexArrayID[i]);
	}
}

void Display::InitializeShaders()
{
	LoadShaders(data, ObjToProgramID, shader);
}

void Display::GetHandleMVP()
{
	for (unsigned int i = 0; i < shader.size(); i++) {
		matrixID.emplace_back(glGetUniformLocation(shader[i].Program, "MVP"));
		viewMatrixID.emplace_back(glGetUniformLocation(shader[i].Program, "V"));
		modelMatrixID.emplace_back(glGetUniformLocation(shader[i].Program, "M"));
	}
}



void Display::LoadOpenGLObjects()
{
	for (unsigned int i = 0; i < data.size(); i++) { 
		model.emplace_back((GLchar*)data[i].objFilePath.c_str());
	
	}
}

void Display::LoadIntoVBO()
{
	for (unsigned int i = 0; i < data.size(); i++) {
		glUseProgram(shader[ ObjToProgramID[i] ].Program);
		lightID.emplace_back( glGetUniformLocation(  (shader[ ObjToProgramID[i] ]).Program, "LightPosition_worldspace" ) );
	}
	shineID = glGetUniformLocation( (shader[ObjToProgramID[0]]).Program, "shine" );
}


void Display::InitializeMVP()
{
	for (unsigned int i = 0; i < data.size(); i++) {
		MVP.emplace_back(glm::mat4());
	}
}

Display::Display(std::string path, GLFWwindow *const&_window) : FileLoader(path) , window(_window), Controls(_window)
{
	//Inicialization
	if (FileLoader::Load() != 0) exit(EXIT_FAILURE); // /*TOCHANGE*/PRZEROBIC NA TRY - CATCH exception
	
	InitializeVertexArray();
	InitializeShaders();
	GetHandleMVP();
	LoadOpenGLObjects();
	LoadIntoVBO();
	
	InitializeMVP();

	SetObjectAmout(data.size());  // ControlObjects requirement.
}

Display::~Display()
{
	for (unsigned int i = 0; i < data.size(); i++)	glDeleteVertexArrays(1, &vertexArrayID[i]);
}

bool Display::Draw()
{
		///TEMP
	ControlInput();
		if (ControlObjects::transformation_t == translation_t) Translate(ControlObjects::GetObjectID(), ControlObjects::translation);
		if (ControlObjects::transformation_t == scale_t) Scale(ControlObjects::GetObjectID(), ControlObjects::scale);
		if (ControlObjects::transformation_t == rotation_t) Rotate(ControlObjects::GetObjectID(), ControlObjects::rotation);
	SetDeltaTime();
	if (Action == Controls::save) {std::cout << "Saved scene\n"; Save();}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (data[ControlObjects::GetObjectID()].type == "const") ControlObjects::NextObject(); // dont allow to change objects that are "const"

	///computeMatricesFromInputs();
	/////HERE
	projectionMatrix = Controls::getProjectionMatrix();
	viewMatrix = Controls::getViewMatrix();
	
	////// Start of the rendering
	for (unsigned int i = 0; i < data.size(); i++) {

		shader[ObjToProgramID[i]].Use(); // glUseProgram

		if (ControlObjects::GetObjectID() == i && Action == Controls::edit) glUniform3f(shineID, 0.5, 0.5, 0.5);
		else glUniform3f(shineID, 0, 0, 0);

		

		lightPos = glm::vec3(4, 34, 4);
		glUniform3f(lightID[ ObjToProgramID[i]], lightPos.x, lightPos.y, lightPos.z);
		glUniformMatrix4fv(viewMatrixID[ObjToProgramID[i]], 1, GL_FALSE, &viewMatrix[0][0]);
		
		MVP[i] = projectionMatrix * viewMatrix * data[i].modelMatrix; /*TOCHANGE ProjectionMatrix * ViewMatrix powinno być jedną zmienną (by nie mnożyć tego non stop)*/
	
		glUniformMatrix4fv(matrixID[ObjToProgramID[i]], 1, GL_FALSE, &(MVP[i])[0][0]);
		glUniformMatrix4fv(modelMatrixID[ObjToProgramID[i]], 1, GL_FALSE, &(data[i].modelMatrix)[0][0]);
	
		model[i].Draw(shader[ObjToProgramID[i]]);
		
	}

	glfwSwapBuffers(window);
	// glfwPollEvents();
	return false;
}

void Display::Save()
{
	this->FileLoader::Save();
}

void Display::Translate(int id, double x, double y, double z)
{
	data[id].modelMatrix = glm::translate(data[id].modelMatrix, glm::vec3(x, y, z));
}

void Display::Translate(int id, glm::vec3 translation)
{
	data[id].modelMatrix = glm::translate(data[id].modelMatrix, translation);
}

void Display::Scale(int id, double x, double y, double z)
{
	data[id].modelMatrix = glm::scale(data[id].modelMatrix, glm::vec3(x,y,z));
}

void Display::Scale(int id, glm::vec3 scale)
{
	data[id].modelMatrix = glm::scale(data[id].modelMatrix, scale);

}

void Display::Rotate(int id, glm::quat rotation)	// quaternion rotation
{
	rotation = glm::normalize(rotation);
	data[id].modelMatrix = data[id].modelMatrix * glm::toMat4(rotation);				

}

void Display::Rotate(int id, double yaw, double pitch, double roll) // radian rotation
{
	double c1, c2, c3, s1, s2, s3;
	glm::quat rotation;
	c1 = cos(yaw / 2);
	c2 = cos(pitch / 2);
	c3 = cos(roll / 2);
	s1 = sin(yaw / 2);
	s2 = sin(pitch / 2);
	s3 = sin(roll / 2);
	rotation.w = (float)(c1*c2*c3 - s1*s2*s3);
	rotation.x = (float)(s1*s2*c3 + c1*c2*s3);
	rotation.y = (float)(s1*c2*c3 + c1*s2*s3);
	rotation.z = (float)(c1*s2*c3 - s1*c2*s3);
	Rotate(id, rotation);
}

void Display::Rotate(int id, glm::vec3 rotation)
{
	double c1, c2, c3, s1, s2, s3;
	glm::quat _rotation;
	c1 = cos(rotation.x / 2);
	c2 = cos(rotation.y / 2);
	c3 = cos(rotation.z / 2);
	s1 = sin(rotation.x / 2);
	s2 = sin(rotation.y / 2);
	s3 = sin(rotation.z / 2);
	_rotation.w = (float)(c1*c2*c3 - s1*s2*s3);
	_rotation.x = (float)(s1*s2*c3 + c1*c2*s3);
	_rotation.y = (float)(s1*c2*c3 + c1*s2*s3);
	_rotation.z = (float)(c1*s2*c3 - s1*c2*s3);
	Rotate(id, _rotation);
}
