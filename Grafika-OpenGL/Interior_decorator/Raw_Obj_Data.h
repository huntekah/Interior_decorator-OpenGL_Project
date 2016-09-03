#pragma once
#include <string>
#include <iostream>
#include <math.h>
#include <glm/gtx/quaternion.hpp>
class RawObjData {
	public:

		//constructor
		RawObjData(	std::string, std::string, std::string, std::string,
					int = 0, double = 0.0f, double = 0.0f, double = 0.0f,
					double = 1.0f, double = 0.0f, double = 0.0f, double = 0.0f,
					double = 1.0f, double = 1.0f, double = 1.0f);
		RawObjData(std::string, std::string, std::string, std::string,
			int = 0, double = 0.0f, double = 0.0f, double = 0.0f,
			glm::quat = glm::quat(1.0f,0.0f,0.0f,0.0f),
			double = 1.0f, double = 1.0f, double = 1.0f);
		//copy constructor
		RawObjData(const RawObjData& example);
		void NormalizeRotation();
		int id;
		double x, y, z;
	//	double quatW, quatX, quatY, quatZ;
		glm::quat rotation;
		double scaleX, scaleY, scaleZ;
		const std::string objFilePath;
		const std::string objUVMapPath;
		const std::string fragmentShaderPath;
		const std::string vertexShaderPath;

		
};

//overload for cout<< purposes;
std::ostream & operator<<(std::ostream &screen, RawObjData &Obj);