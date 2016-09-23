#include "shader_loader.h"

void ShaderLoader::LoadShaders(	std::vector<RawObjData>& data,
									std::vector<int>& ObjToProgramID,
									std::vector<Shader>& shader)
{
	for (unsigned int i=0; i < data.size(); i++) {
		if (IsNewShader(i, data)) {
			
			/// START LOADING SHADERS ///
			//
			//// Create the shaders
			//GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
			//GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

			//// Read the Vertex Shader code from the file
			//std::string VertexShaderCode;
			//std::ifstream VertexShaderFile(data[i].vertexShaderPath.c_str(), std::ios::in);
			//if (VertexShaderFile.is_open()) {
			//	std::string Line = "";
			//	while (getline(VertexShaderFile, Line))
			//		VertexShaderCode += "\n" + Line;
			//	VertexShaderFile.close();
			//}
			//else {
			//	std::cout << "Impossible to open " << data[i].vertexShaderPath << ". Remember to put files in the right directory! \n";
			//	getchar();
			//	exit(EXIT_FAILURE);
			//}

			//// Read the Fragment Shader code from the file
			//std::string FragmentShaderCode;
			//std::ifstream FragmentShaderFile(data[i].fragmentShaderPath.c_str(), std::ios::in);
			//if (FragmentShaderFile.is_open()) {
			//	std::string Line = "";
			//	while (getline(FragmentShaderFile, Line))
			//		FragmentShaderCode += "\n" + Line;
			//	FragmentShaderFile.close();
			//}
			//else {
			//	std::cout << "Impossible to open " << data[i].fragmentShaderPath << ". Remember to put files in the right directory! \n";
			//	getchar();
			//	exit(EXIT_FAILURE);
			//}

			//GLint Result = GL_FALSE;
			//int InfoLogLength;

			//// Compile Vertex Shader
			//std::cout<<"Compiling shader : "<< data[i].vertexShaderPath.c_str() << "\n";
			//char const * VertexSourcePointer = VertexShaderCode.c_str();
			//glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
			//glCompileShader(VertexShaderID);

			//// Check Vertex Shader
			//glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
			//glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
			//if (InfoLogLength > 0) {
			//	std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
			//	glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			//	std::cout << &VertexShaderErrorMessage[0] << std::endl;
			//}

			//// Compile Fragment Shader
			//printf("Compiling shader : %s\n", data[i].fragmentShaderPath.c_str());
			//char const * FragmentSourcePointer = FragmentShaderCode.c_str();
			//glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
			//glCompileShader(FragmentShaderID);

			//// Check Fragment Shader
			//glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
			//glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
			//if (InfoLogLength > 0) {
			//	std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
			//	glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			//	std::cout << &FragmentShaderErrorMessage[0] << std::endl;
			//}

			//// Link the program
			//std::cout << "Linking program\n";
			//programID.emplace_back(glCreateProgram());
			//glAttachShader(programID.back(), VertexShaderID);
			//glAttachShader(programID.back(), FragmentShaderID);
			//glLinkProgram(programID.back());

			//// Check the program
			//glGetProgramiv(programID.back(), GL_LINK_STATUS, &Result);
			//glGetProgramiv(programID.back(), GL_INFO_LOG_LENGTH, &InfoLogLength);
			//if (InfoLogLength > 0) {
			//	std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			//	glGetProgramInfoLog(programID.back(), InfoLogLength, NULL, &ProgramErrorMessage[0]);
			//	std::cout << &ProgramErrorMessage[0] << std::endl;
			//}

			//glDetachShader(programID.back(), VertexShaderID);
			//glDetachShader(programID.back(), FragmentShaderID);

			//glDeleteShader(VertexShaderID);
			//glDeleteShader(FragmentShaderID);
			shader.emplace_back(data[i].vertexShaderPath.c_str(), data[i].fragmentShaderPath.c_str());
			ObjToProgramID.push_back(shader.size() - 1);
			/// END OF LOADING SHADERS ///
		}
		else ObjToProgramID.push_back(GetSimilarShaders(i, data, ObjToProgramID));
	}
}

bool ShaderLoader::IsNewShader(int objID, std::vector<RawObjData>& data)
{
	for (int i = 0; i < objID; i++)
		if (data[i].fragmentShaderPath == data[objID].fragmentShaderPath) return false;
		else if (data[i].vertexShaderPath == data[objID].vertexShaderPath) return false;

		return true;
}


int ShaderLoader::GetSimilarShaders(int objID, std::vector<RawObjData>& data, std::vector<int>& ObjToProgramID) // returns the index of the similar 
{
	for (int i = 0; i < objID; i++)
		if (data[i].fragmentShaderPath == data[objID].fragmentShaderPath
			&& data[i].vertexShaderPath == data[objID].vertexShaderPath) return ObjToProgramID[i];
	return -1; //cause it shouldnt happen;
}
