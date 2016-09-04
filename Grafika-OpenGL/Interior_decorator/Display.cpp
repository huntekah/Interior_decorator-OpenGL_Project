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
	LoadShaders(data, programID, ObjToProgramID);
}

void Display::GetHandleMVP()
{
	for (unsigned int i = 0; i < programID.size(); i++) {
		matrixID.emplace_back(glGetUniformLocation(programID[i], "MVP"));
		viewMatrixID.emplace_back(glGetUniformLocation(programID[i], "V"));
		modelMatrixID.emplace_back(glGetUniformLocation(programID[i], "M"));
	}
}

void Display::LoadTextures()
{
	for (unsigned int i = 0; i < data.size(); i++) {
		texture.emplace_back(loadDDS(data[i].objUVMapPath.c_str()));
		textureID.emplace_back(glGetUniformLocation(programID[ ObjToProgramID[i] ], "myTextureSampler")); /*TOCHANGE why myTextureSampler?*/
	}
}

void Display::LoadOpenGLObjects()
{
	for (unsigned int i = 0; i < data.size(); i++) { /*TOCHANGE IMPORTANT*/ // funkcja ssie, trzeba loadOBJ i indexVBO przepisać na wersję przyjmującą vector<vector<glm::vec3>>
		//inserts empty vectors into vector of vectors.
		vertices.push_back(std::vector<glm::vec3>());
		uvs.push_back(std::vector<glm::vec2>());
		normals.push_back(std::vector<glm::vec3>());
		
		indices.push_back(std::vector<unsigned short>());
		indexedVertices.push_back(std::vector<glm::vec3>());
		indexedUvs.push_back(std::vector<glm::vec2>());
		indexedNormals.push_back(std::vector<glm::vec3>());
		
		if (false == loadOBJ(data[i].objFilePath.c_str(), vertices[i], uvs[i], normals[i])) exit(EXIT_FAILURE); /*TOCHANGE*/
		indexVBO(vertices[i], uvs[i], normals[i], indices[i], indexedVertices[i], indexedUvs[i], indexedNormals[i]); /*TOCHANGE*/
	}
}

void Display::LoadIntoVBO()
{
	for (unsigned int i = 0; i < data.size(); i++) {
		vertexBuffer.push_back(GLuint());
		glGenBuffers(1, &vertexBuffer[i]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, (indexedVertices[i]).size() * sizeof(glm::vec3), &indexedVertices[i][0], GL_STATIC_DRAW);
		
		uvBuffer.push_back(GLuint());
		glGenBuffers(1, &uvBuffer[i]);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, indexedUvs[i].size() * sizeof(glm::vec2), &indexedUvs[i][0], GL_STATIC_DRAW);

		normalBuffer.push_back(GLuint());
		glGenBuffers(1, &normalBuffer[i]);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, indexedNormals[i].size() * sizeof(glm::vec3), &indexedNormals[i][0], GL_STATIC_DRAW);

		elementBuffer.push_back(GLuint());
		glGenBuffers(1, &elementBuffer[i]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer[i]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices[i].size() * sizeof(unsigned short), &indices[i][0], GL_STATIC_DRAW);

		glUseProgram(programID[ ObjToProgramID[i] ]);
		lightID.emplace_back( glGetUniformLocation(programID[ ObjToProgramID[i] ], "LightPosition_worldspace") );

	}
}

void Display::InitializeTime()
{
	lastTime = glfwGetTime();
}

double Display::SetDeltaTime()
{
	deltaTime = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();
	return deltaTime;
}

void Display::InitializeDrawObjects()
{
	for (unsigned int i = 0; i < data.size(); i++) {
		//modelMatrix.emplace_back(glm::mat4(1.0));
		
		/*Translations*/
		//modelMatrix[i] = glm::translate(modelMatrix[i], glm::vec3(data[i].x, data[i].y, data[i].z));	// translation
		//modelMatrix[i] = glm::scale(modelMatrix[i], glm::vec3(data[i].scaleX, data[i].scaleY, data[i].scaleZ));	// scaling
		//modelMatrix[i] = modelMatrix[i] * glm::toMat4(glm::quat(data[i].rotation.w, data[i].rotation.x, data[i].rotation.y, data[i].rotation.z));	// rotating
	
		MVP.emplace_back(glm::mat4());
	}
}

Display::Display(std::string path, GLFWwindow *const&_window) : FileLoader(path) , window(_window)
{
	//Inicialization
	if (FileLoader::Load() != 0) exit(EXIT_FAILURE); // /*TOCHANGE*/PRZEROBIC NA TRY - CATCH exception
	
	InitializeVertexArray();
	InitializeShaders();
	GetHandleMVP();
	LoadTextures();
	LoadOpenGLObjects();
	LoadIntoVBO();
	
	InitializeDrawObjects();
}

Display::~Display()
{
	for (unsigned int i = 0; i < data.size(); i++) {
		glDeleteBuffers(1, &vertexBuffer[i]);
		glDeleteBuffers(1, &uvBuffer[i]);
		glDeleteBuffers(1, &normalBuffer[i]);
		glDeleteBuffers(1, &elementBuffer[i]);
		glDeleteTextures(1, &texture[i]);
		glDeleteVertexArrays(1, &vertexArrayID[i]);
	}
	for (unsigned int i = 0; i < programID.size();i++)
		glDeleteProgram(programID[i]);
}

bool Display::Draw()
{
	SetDeltaTime();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	/*TOCHANGE bardzo brzydkie rozwiązanie.
	zrobiłęm tylko po to, by zobaczyć czy pliki się poprawnie pokazują
	docelowo sterowanie powinno być wywołane z zewnątrz funkcji Draw,
	jako metoda klasy Display która nie używa extern display'a
	tylko referencję którą mamy w klasie.
	+ wtedy będzie można te dwa procesy jakoś fajnie zrównoleglić
	(rysowania i odbierania bodźców z klawiatury)*/
	computeMatricesFromInputs();
	projectionMatrix = getProjectionMatrix();
	viewMatrix = getViewMatrix();

	////// Start of the rendering
	for (unsigned int i = 0; i < data.size(); i++) {

		glUseProgram(programID[ObjToProgramID[i]]);

		lightPos = glm::vec3(4, 4, 4);
		glUniform3f(lightID[ ObjToProgramID[i]], lightPos.x, lightPos.y, lightPos.z);
		glUniformMatrix4fv(viewMatrixID[ObjToProgramID[i]], 1, GL_FALSE, &viewMatrix[0][0]);
		
		MVP[i] = projectionMatrix * viewMatrix * data[i].modelMatrix; /*TOCHANGE ProjectionMatrix * ViewMatrix powinno być jedną zmienną (by nie mnożyć tego non stop)*/
	
		glUniformMatrix4fv(matrixID[ObjToProgramID[i]], 1, GL_FALSE, &(MVP[i])[0][0]);
		glUniformMatrix4fv(modelMatrixID[ObjToProgramID[i]], 1, GL_FALSE, &(data[i].modelMatrix)[0][0]);
	
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[i]);
	
		glUniform1i(textureID[i], 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer[i]);
		glVertexAttribPointer(
			0,                  // attribute /*TOCHANGE atrybut powinien być zmienną (np. i) patrz tutorial2*/
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer[i]);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
			);

		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer[i]);
		glVertexAttribPointer(
			2,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
			);

		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer[i]);

		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			indices[i].size(),    // count
			GL_UNSIGNED_SHORT,   // type
			(void*)0           // element array buffer offset
		);


	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	// Swap buffers
	glfwSwapBuffers(window);
	//glfwPollEvents();

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
//	data[id].rotation = data[id].rotation * rotation;				

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
	rotation.w = c1*c2*c3 - s1*s2*s3;
	rotation.x = s1*s2*c3 + c1*c2*s3;
	rotation.y = s1*c2*c3 + c1*s2*s3;
	rotation.z = c1*s2*c3 - s1*c2*s3;
	Rotate(id, rotation);
}
