#include "Raw_Obj_Data.h"

RawObjData::RawObjData(	std::string objFilePath_, std::string objUVMapPath_,
						std::string fragmentShaderPath_, std::string vertexShaderPath_,
						int id_, double x_, double y_, double z_, 
						double quatW_, double quatX_, double quatY_, double quatZ_,
						double scaleX_, double scaleY_, double scaleZ_ ):
	objFilePath(objFilePath_), objUVMapPath(objUVMapPath_),
	fragmentShaderPath(fragmentShaderPath_), vertexShaderPath(vertexShaderPath_),
	id(id_), x(x_), y(y_), z(z_),
	scaleX(scaleX_), scaleY(scaleY_), scaleZ(scaleZ_)
{
	rotation = glm::quat(quatW_, quatX_, quatY_, quatZ_);
	NormalizeRotation();
	/*double l = std::sqrt(quatW*quatW + quatX*quatX + quatY*quatY + quatZ*quatZ);
	quatW /= l;
	quatX /= l;
	quatY /= l;
	quatZ /= l;*/
}

RawObjData::RawObjData(	std::string objFilePath_, std::string objUVMapPath_,
						std::string fragmentShaderPath_, std::string vertexShaderPath_,
						int id_, double x_, double y_, double z_,
						glm::quat rotation_,
						double scaleX_, double scaleY_, double scaleZ_) :
	objFilePath(objFilePath_), objUVMapPath(objUVMapPath_),
	fragmentShaderPath(fragmentShaderPath_), vertexShaderPath(vertexShaderPath_),
	id(id_), x(x_), y(y_), z(z_),
	rotation(rotation_),
	scaleX(scaleX_), scaleY(scaleY_), scaleZ(scaleZ_)
{
	NormalizeRotation();
}

RawObjData::RawObjData(const RawObjData & example):
	id(example.id), x(example.x), y(example.y), z(example.z),
	rotation(example.rotation),
	scaleX(example.scaleX), scaleY(example.scaleY), scaleZ(example.scaleZ),
	objFilePath(example.objFilePath), objUVMapPath(example.objUVMapPath), 
	fragmentShaderPath(example.fragmentShaderPath), vertexShaderPath(example.vertexShaderPath)
{}

void RawObjData::NormalizeRotation()
{
	rotation = glm::normalize(rotation);
}

std::ostream & operator<<(std::ostream &screen, RawObjData &Obj) {
	screen << "Object: \t\t" << Obj.objFilePath << "\n";
	screen << "Position =\t\t( " << Obj.x << ", " << Obj.y << ", " << Obj.z << " )\n";
	screen << "Rotation =\t\t( " << Obj.rotation.w << ", " << Obj.rotation.x << ", " << Obj.rotation.y << ", "<<Obj.rotation.z <<" )\n";
	screen << "Scale = \t\t( " << Obj.scaleX << ", " << Obj.scaleY << ", " << Obj.scaleZ << " )\n";
	screen << "objUVMapPath:\t\t" << Obj.objUVMapPath << "\n";
	screen << "fragmentShaderPath:\t" << Obj.fragmentShaderPath << "\n";
	screen << "vertexShaderPath:\t" << Obj.vertexShaderPath << "\n";
	return screen;
}