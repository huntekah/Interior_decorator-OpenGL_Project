#include "Raw_Obj_Data.h"

RawObjData::RawObjData(	std::string objFilePath_, std::string type_,
						std::string fragmentShaderPath_, std::string vertexShaderPath_,
						int id_, glm::mat4 modelMatrix_ ):
	objFilePath(objFilePath_), type(type_),
	fragmentShaderPath(fragmentShaderPath_), vertexShaderPath(vertexShaderPath_),
	id(id_), modelMatrix(modelMatrix_)
{}


RawObjData::RawObjData(const RawObjData & example):
	id(example.id), modelMatrix(example.modelMatrix),
	objFilePath(example.objFilePath), type(example.type), 
	fragmentShaderPath(example.fragmentShaderPath), vertexShaderPath(example.vertexShaderPath)
{}


std::ostream & operator<<(std::ostream &screen, RawObjData &Obj) {
	screen << "Object: \t\t" << Obj.objFilePath << "\n";
	screen << "Model Matrix:\t\t" << Obj.modelMatrix[0][0] << "\t" << Obj.modelMatrix[0][1] << "\t" 
		   << Obj.modelMatrix[0][2] << "\t" << Obj.modelMatrix[0][3] << "\n";
	screen << "\t\t\t\t" << Obj.modelMatrix[1][0] << "\t" << Obj.modelMatrix[1][1] << "\t"
		<< Obj.modelMatrix[1][2] << "\t" << Obj.modelMatrix[1][3] << "\n";
	screen << "\t\t\t\t" << Obj.modelMatrix[2][0] << "\t" << Obj.modelMatrix[2][1] << "\t"
		<< Obj.modelMatrix[2][2] << "\t" << Obj.modelMatrix[2][3] << "\n";
	screen << "\t\t\t\t" << Obj.modelMatrix[3][0] << "\t" << Obj.modelMatrix[3][1] << "\t"
		<< Obj.modelMatrix[3][2] << "\t" << Obj.modelMatrix[3][3] << "\n";
	screen << "type:\t\t" << Obj.type << "\n";
	screen << "fragmentShaderPath:\t" << Obj.fragmentShaderPath << "\n";
	screen << "vertexShaderPath:\t" << Obj.vertexShaderPath << "\n";
	return screen;
}