#pragma once
#include <string>
#include <iostream>
class RawObjData {
	public:

		//constructor
		RawObjData(	std::string, std::string, std::string, std::string,
					int = 0, double = 0.0f, double = 0.0f, double = 0.0f,
					double = 0.0f, double = 0.0f, double = 0.0f,
					double = 1.0f, double = 1.0f, double = 1.0f);

		//copy constructor
		RawObjData(const RawObjData& example);

		int id;
		double x, y, z;
		double RotationX, RotationY, RotationZ;
		double ScaleX, ScaleY, ScaleZ;
		const std::string ObjFilePath;
		const std::string ObjUVMapPath;
		const std::string FragmentShaderPath;
		const std::string VertexShaderPath;

		
};

//overload for cout<< purposes;
std::ostream & operator<<(std::ostream &screen, RawObjData &Obj);