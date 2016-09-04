#include "file_loader.h"

/* LoadNextObject returns:
	0 = succes.
	1 = eof(), safely loaded whole file
   -1 = error occured */
int FileLoader::LoadNextObject()
{
	if (file.is_open()) {
		std::string ObjFilePath;
		std::string ObjUVMapPath;
		std::string FragmentShaderPath;
		std::string VertexShaderPath;
		glm::mat4 modelMatrix;

		//file.good checks if there are no errors and it is not EOF, so I can safely read more data;
		if (!file.good()) return -1;
		
		file >> ObjFilePath;
		if (file.eof()) return 1;
		file >> ObjUVMapPath;
		file >> FragmentShaderPath;
		file >> VertexShaderPath;
		file >> modelMatrix;
		/*file >> y;
		file >> z;
		file >> quatW;
		file >> quatX;
		file >> quatY;
		file >> quatZ;
		file >> ScaleX;
		file >> ScaleY;
		file >> ScaleZ;*/

		/*	Either no characters were extracted, or the characters extracted
		could not be interpreted as a valid value of the appropriate type.*/
		if (file.fail())return -1;

		data.emplace_back(ObjFilePath, ObjUVMapPath,
			FragmentShaderPath, VertexShaderPath,
			data.size(), modelMatrix);

		return 0;
	}
	else return -1;
}

/* SaveObject returns:
0 = succes.
-1 = error occured */
int FileLoader::SaveObject(int id)
{
	if (file.is_open()) {
		if (!file.good()) return -1;
		file << data[id].objFilePath<<"\t";
		file << data[id].objUVMapPath << "\t";
		file << data[id].fragmentShaderPath << "\t";
		file << data[id].vertexShaderPath << "\n";
		file << data[id].modelMatrix;
		/*file << data[id].x << "\t";
		file << data[id].y << "\t";
		file << data[id].z << "\t";
		file << data[id].rotation.w << "\t";
		file << data[id].rotation.x << "\t";
		file << data[id].rotation.y << "\t";
		file << data[id].rotation.z << "\t";
		file << data[id].scaleX << "\t";
		file << data[id].scaleY << "\t";
		file << data[id].scaleZ << "\n";*/

		/*Some errors occured duh*/
		if (!file.good()) return -1;
		if (file.fail())return -1;

		return 0;
	}
	else return -1;
}

FileLoader::FileLoader(std::string path): DefaultPath(path)
{}

int FileLoader::Load(const std::string path)
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
		if (result == -1) return -1;	//not enough variables  
	}
	this->file.close();
	this->file.clear();
	return 0;
}

int FileLoader::Load()
{
	return Load(DefaultPath);
}

int FileLoader::Save(const std::string path)
{
	if (this->file.is_open()) this->file.close();
	file.open(path , std::fstream::trunc | std::fstream::out);

	for (int i = 0; i < data.size(); i++) {
		if (SaveObject(i) == -1) return -1;	//saving i'th object
	}

	this->file.close();
	this->file.clear();

	return 0;
}

int FileLoader::Save()
{
	return Save(DefaultPath);
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
	for (unsigned int i = 0; i < File.data.size(); i++) {
		screen << File.data[i] << std::endl;
	}
	return screen;
}

std::fstream & operator>>(std::fstream & screen, glm::mat4 & modelMatrix)
{
	screen >> modelMatrix[0][0] >> modelMatrix[0][1] >> modelMatrix[0][2] >> modelMatrix[0][3];
	screen >> modelMatrix[1][0] >> modelMatrix[1][1] >> modelMatrix[1][2] >> modelMatrix[1][3];
	screen >> modelMatrix[2][0] >> modelMatrix[2][1] >> modelMatrix[2][2] >> modelMatrix[2][3];
	screen >> modelMatrix[3][0] >> modelMatrix[3][1] >> modelMatrix[3][2] >> modelMatrix[3][3];
	return screen;
}

std::fstream & operator<<(std::fstream & screen, glm::mat4 & modelMatrix)
{
	screen << modelMatrix[0][0] << "\t" << modelMatrix[0][1] << "\t" << modelMatrix[0][2] << "\t" << modelMatrix[0][3] << "\n";
	screen << modelMatrix[1][0] << "\t" << modelMatrix[1][1] << "\t" << modelMatrix[1][2] << "\t" << modelMatrix[1][3] << "\n";
	screen << modelMatrix[2][0] << "\t" << modelMatrix[2][1] << "\t" << modelMatrix[2][2] << "\t" << modelMatrix[2][3] << "\n";
	screen << modelMatrix[3][0] << "\t" << modelMatrix[3][1] << "\t" << modelMatrix[3][2] << "\t" << modelMatrix[3][3] << "\n";
	return screen;
}
