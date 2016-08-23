#include "file_loader.h"

FileLoader::FileLoader(std::string path): DefaultPath(path)
{}

FileLoader::~FileLoader()
{
	data.clear();
}
