#include "Raw_Obj_Data.h"

RawObjData::RawObjData(	std::string ObjFilePath_, std::string ObjUVMapPath_,
						std::string FragmentShaderPath_, std::string VertexShaderPath_,
						int id_, double x_, double y_, double z_, 
						double RotationX_, double RotationY_, double RotationZ_,
						double ScaleX_, double ScaleY_, double ScaleZ_ ):
	ObjFilePath(ObjFilePath_), ObjUVMapPath(ObjUVMapPath_),
	FragmentShaderPath(FragmentShaderPath_), VertexShaderPath(VertexShaderPath_),
	id(id_), x(x_), y(y_), z(z_),
	RotationX(RotationX_), RotationY(RotationY_), RotationZ(RotationZ_),
	ScaleX(ScaleX_), ScaleY(ScaleY_), ScaleZ(ScaleZ_)
{}

RawObjData::RawObjData(const RawObjData & example):
	id(example.id), x(example.x), y(example.y), z(example.z),
	RotationX(example.RotationX), RotationY(example.RotationY), RotationZ(example.RotationZ),
	ScaleX(example.ScaleX), ScaleY(example.ScaleY), ScaleZ(example.ScaleZ),
	ObjFilePath(example.ObjFilePath), ObjUVMapPath(example.ObjUVMapPath), 
	FragmentShaderPath(example.FragmentShaderPath), VertexShaderPath(example.VertexShaderPath)
{}

std::ostream & operator<<(std::ostream &screen, RawObjData &Obj) {
	screen << "Object: \t\t" << Obj.ObjFilePath << "\n";
	screen << "Position =\t\t( " << Obj.x << ", " << Obj.y << ", " << Obj.z << " )\n";
	screen << "Rotation =\t\t( " << Obj.RotationX << ", " << Obj.RotationY << ", " << Obj.RotationZ << " )\n";
	screen << "Scale = \t\t( " << Obj.ScaleX << ", " << Obj.ScaleY << ", " << Obj.ScaleZ << " )\n";
	screen << "ObjUVMapPath:\t\t" << Obj.ObjUVMapPath << "\n";
	screen << "FragmentShaderPath:\t" << Obj.FragmentShaderPath << "\n";
	screen << "VertexShaderPath:\t" << Obj.VertexShaderPath << "\n";
	return screen;
}