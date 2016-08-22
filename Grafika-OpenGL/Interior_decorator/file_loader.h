#pragma once
#include <vector>
#include "Raw_Obj_Data.h"
class FileLoader {
	private:
		std::string DefaultPath;
	public:
		//used to store info needed to buffer and render data
		std::vector<RawObjData> data;

		FileLoader(std::string path);
		// succes when returning 0, failure when 
		int Load(const std::string path);
		int Load();
		int Save(const std::string path);
		int Save();
		RawObjData get(unsigned id);
		~FileLoader();

};