#include "Display.h"

void Display::InitializeVertexArray()
{
	for (unsigned int i = 0; i < data.size(); i++) {
		VertexArrayID.emplace_back(GLuint());
		glGenVertexArrays(1, &VertexArrayID[i]);
		glBindVertexArray(VertexArrayID[i]);
	}
}

void Display::InitializeShaders()
{
	int pID = 0;
	for (unsigned int i = 0; i < data.size(); i++) {
		if (isNewShader(i)) {
			programID.push_back( LoadShaders(data[i].VertexShaderPath.c_str(),
									data[i].FragmentShaderPath.c_str()));	/*TOCHANGE LoadShaders*/ //Compiles Fragment and Vertex Shaders
			ObjToProgramID.push_back(programID.size() - 1);	// adds the connection, which ProgramID Object[i] uses
		}
		else {
			ObjToProgramID.push_back(getSimilarShaders(i) );
		}
	}
}

bool Display::isNewShader( int objID)
{
	for (int i = 0; i < objID; i++)
		if (data[i].FragmentShaderPath == data[objID].FragmentShaderPath) return false;
		else if (data[i].VertexShaderPath == data[objID].VertexShaderPath) return false;
	
	return true;
}

int Display::getSimilarShaders(int objID) // returns the index of the similar 
{
	for (int i = 0; i < objID; i++)
		if (data[i].FragmentShaderPath == data[objID].FragmentShaderPath
			&& data[i].VertexShaderPath == data[objID].VertexShaderPath) return ObjToProgramID[i];
	return -1; //cause it shouldnt happen;
}

void Display::GetHandleMVP()
{
	for (unsigned int i = 0; i < programID.size(); i++) {
		MatrixID.emplace_back(glGetUniformLocation(programID[i], "MVP"));
		ViewMatrixID.emplace_back(glGetUniformLocation(programID[i], "V"));
		ModelMatrixID.emplace_back(glGetUniformLocation(programID[i], "M"));
	}
}

void Display::LoadTextures()
{
	for (unsigned int i = 0; i < data.size(); i++) {
		Texture.emplace_back(loadDDS(data[i].ObjUVMapPath.c_str()));
		TextureID.emplace_back(glGetUniformLocation(programID[ ObjToProgramID[i] ], "myTextureSampler")); /*TOCHANGE why myTextureSampler?*/
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
		
		if (false == loadOBJ(data[i].ObjFilePath.c_str(), vertices[i], uvs[i], normals[i])) exit(EXIT_FAILURE); /*TOCHANGE*/
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
		LightID.emplace_back( glGetUniformLocation(programID[ ObjToProgramID[i] ], "LightPosition_worldspace") );

	}
}

void Display::InitializeTime()
{
	lastTime = glfwGetTime();
}

void Display::SetDeltaTime()
{
	deltaTime = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();
}

void Display::InitializeDrawObjects()
{
	for (unsigned int i = 0; i < data.size(); i++) {
		ModelMatrix.emplace_back(glm::mat4(1.0));
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
		glDeleteTextures(1, &Texture[i]);
		glDeleteVertexArrays(1, &VertexArrayID[i]);
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
	ProjectionMatrix = getProjectionMatrix();
	ViewMatrix = getViewMatrix();

	////// Start of the rendering
	for (unsigned int i = 0; i < data.size(); i++) {

		glUseProgram(programID[ObjToProgramID[i]]);

		lightPos = glm::vec3(4, 4, 4);
		glUniform3f(LightID[ ObjToProgramID[i]], lightPos.x, lightPos.y, lightPos.z);
		glUniformMatrix4fv(ViewMatrixID[ObjToProgramID[i]], 1, GL_FALSE, &ViewMatrix[0][0]);
	
		ModelMatrix[i] = glm::mat4(1.0);
		ModelMatrix[i] = glm::translate(ModelMatrix[i], glm::vec3(data[i].x, data[i].y, data[i].z));
		MVP[i] = ProjectionMatrix * ViewMatrix * ModelMatrix[i]; /*TOCHANGE ProjectionMatrix * ViewMatrix powinno być jedną zmienną (by nie mnożyć tego non stop)*/
	
		glUniformMatrix4fv(MatrixID[ObjToProgramID[i]], 1, GL_FALSE, &(MVP[i])[0][0]);
		glUniformMatrix4fv(ModelMatrixID[ObjToProgramID[i]], 1, GL_FALSE, &(ModelMatrix[i])[0][0]);
	
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture[i]);
	
		glUniform1i(TextureID[i], 0);

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
			indices.size(),    // count
			GL_UNSIGNED_SHORT,   // type
			(void*)0           // element array buffer offset
		);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		// Swap buffers
		glfwSwapBuffers(window);
		//glfwPollEvents();
	}


	return false;
}
