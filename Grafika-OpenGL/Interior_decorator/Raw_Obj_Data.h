#pragma once
#include <string>
#include <iostream>
#include <math.h>
#include <glm/gtx/quaternion.hpp>
class RawObjData {
	public:

		//constructor
		RawObjData(	std::string, std::string, std::string, std::string,
					int = 0, glm::mat4 modelMatrix_ = glm::mat4(1.0f));
		//copy constructor
		RawObjData(const RawObjData& example);
		int id;
		glm::mat4 modelMatrix;
		const std::string objFilePath;
		const std::string type;
		const std::string fragmentShaderPath;
		const std::string vertexShaderPath;

		
};

//overload for cout<< purposes;
std::ostream & operator<<(std::ostream &screen, RawObjData &Obj);