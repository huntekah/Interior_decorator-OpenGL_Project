#include "Raw_Obj_Data.h"

RawObjData::RawObjData(const RawObjData & example):
	id(example.id), x(example.x), y(example.y), RotationX(example.RotationX),
	RotationY(example.RotationY), RotationZ(example.RotationZ),
	ObjFilePath(example.ObjFilePath), ObjUVMapPath(example.FragmentShaderPath), 
	FragmentShaderPath(example.FragmentShaderPath), VertexShaderPath(example.VertexShaderPath)
{}
