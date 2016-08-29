#include "Display.h"

void Display::InitializeVertexArray()
{
	for (unsigned int i = 0; i < data.size(); i++) {
		glGenVertexArrays(i, &VertexArrayID[i]);
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
			ObjToProgramID.push_back(std::make_pair(i, programID.size() - 1));	// adds the connection, which ProgramID Object[i] uses
		}
		else {
			ObjToProgramID.push_back( std::make_pair( i,getSimilarShaders(i) ) );
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

int Display::getSimilarShaders(int objID)
{
	for (int i = 0; i < objID; i++)
		if (data[i].FragmentShaderPath == data[objID].FragmentShaderPath
			&& data[i].VertexShaderPath == data[objID].VertexShaderPath) return ObjToProgramID[i].second;
	return -1; //cause it shouldnt happen;
}


Display::Display(std::string path, GLFWwindow *const&_window) : FileLoader(path) , window(_window)
{
	//Inicialization
	if (FileLoader::Load() != 0) exit(EXIT_FAILURE); // PRZEROBIC NA TRY - CATCH exception
	
	InitializeVertexArray();
	InitializeShaders();
	
}

bool Display::Draw()
{
	return false;
}
