#include "file_loader.h"

/* LoadNextObject returns:
	0 = succes.
	1 = eof(), safely loaded whole file
   -1 = error occured */
short FileLoader::LoadNextObject()
{
	if (file.is_open()) {
		std::string ObjFilePath;
		std::string ObjUVMapPath;
		std::string FragmentShaderPath;
		std::string VertexShaderPath;
		double x, y, z;
		double RotationX, RotationY, RotationZ;
		double ScaleX, ScaleY, ScaleZ;

		//stworzyc nowy obiekt daty, do którego wczytam a pózniej pushnac do vectora.
		//file.good checks if there are no errors and it is not EOF, so I can safely read more data;
		if (!file.good()) return -1;
		
		file >> ObjFilePath;
		if (file.eof()) return 1;
		file >> ObjUVMapPath;
		file >> FragmentShaderPath;
		file >> VertexShaderPath;
		file >> x;
		file >> y;
		file >> z;
		file >> RotationX;
		file >> RotationY;
		file >> RotationZ;
		file >> ScaleX;
		file >> ScaleY;
		file >> ScaleZ;

		/*	Either no characters were extracted, or the characters extracted
		could not be interpreted as a valid value of the appropriate type.*/
		if (file.fail())return -1;

		data.emplace_back(ObjFilePath, ObjUVMapPath,
			FragmentShaderPath, VertexShaderPath,
			data.size(), x, y, z,
			RotationX, RotationY, RotationZ,
			ScaleX, ScaleY, ScaleZ);

		return 0;
	}
	else return -1;
}

FileLoader::FileLoader(std::string path): DefaultPath(path)
{}

short FileLoader::Load(const std::string path)
{
	std::ifstream DoesFileExist(path);
	if (DoesFileExist.fail()) {
// file path does not exist.
		return -2;
	}

	if (this->file.is_open()) this->file.close();
	file.open(path);

	int result = 0;
	while(!file.eof()){
		result = LoadNextObject();
		if (result == -1) return -1;	//not enogh variables  
	}
	this->file.close();
	this->file.clear();
	return 0;
}

short FileLoader::Load()
{
	return Load(DefaultPath);
}

short FileLoader::Save(const std::string path)
{
	//TODO
	return 0;
}

short FileLoader::Save()
{
	//TODO
	return 0;
}

void FileLoader::SetPath(const std::string path)
{
	DefaultPath = path;
}

void FileLoader::Clear()
{
	data.clear();
}

RawObjData & FileLoader::get(unsigned id)
{
	return data[id];
}

FileLoader::~FileLoader()
{
	if (this->file.is_open()) this->file.close();
	data.clear();
}

std::ostream & operator<<(std::ostream & screen, FileLoader & File)
{
	for (int i = 0; i < File.data.size(); i++) {
		screen << File.data[i] << std::endl;
	}
	return screen;
}
