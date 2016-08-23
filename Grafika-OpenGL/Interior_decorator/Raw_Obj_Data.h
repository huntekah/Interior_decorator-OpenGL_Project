#pragma once
#include <string>
class RawObjData {
	public:
		RawObjData(const RawObjData& example); //copy constructor
		int id;
		double x, y, z;
		double RotationX, RotationY, RotationZ;
		const std::string ObjFilePath;
		const std::string ObjUVMapPath;
		const std::string FragmentShaderPath;
		const std::string VertexShaderPath;
};