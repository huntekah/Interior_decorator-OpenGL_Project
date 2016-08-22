#pragma once
#include <string>
class RawObjData {
	public:
		RawObjData(const RawObjData& example); //kostruktor kopiujący
		int id;
		double x, y, z;
		double RotationX, RotationX, RotationX;
		const std::string ObjFilePath;
		const std::string ObjUVMapPath;
		const std::string FragmentShaderPath;
		const std::string VertexShaderPath;
};