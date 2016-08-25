#pragma once
#include <vector>
#include <fstream>  

#include "Raw_Obj_Data.h"
class FileLoader {
	private:
		std::string DefaultPath;
		std::fstream file;
		short LoadNextObject();

	public:

		//used to store info needed to buffer and render data
		std::vector<RawObjData> data;

		// default constructor
		FileLoader(std::string path = "");

		/* Load() when returning:
			0 - success
		   -1 bad data format
		   -2 file does not exist */
		short Load(const std::string path);
		short Load();
		short Save(const std::string path); // TODO
		short Save(); // TODO
		void SetPath(const std::string path);
		void Clear();
		RawObjData& get(unsigned id);
		~FileLoader();

};

//used to show all objects;
std::ostream & operator<<(std::ostream &screen, FileLoader &FileData);