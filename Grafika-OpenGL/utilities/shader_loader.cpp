#include "shader_loader.h"

void ShaderLoader::LoadShaders(	std::vector<RawObjData>& data,
									std::vector<int>& ObjToProgramID,
									std::vector<Shader>& shader)
{
	for (unsigned int i=0; i < data.size(); i++) {
		if (IsNewShader(i, data)) {
			/// START LOADING SHADERS ///
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
