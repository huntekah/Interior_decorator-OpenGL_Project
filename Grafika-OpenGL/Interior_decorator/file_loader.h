#pragma once
#include <vector>
#include <fstream>  

#include "Raw_Obj_Data.h"
class FileLoader {
	private:
		std::string DefaultPath;
		std::fstream file;
		int LoadNextObject();
		int SaveObject(int id);

	public:

		//used to store info needed to buffer and render data
		std::vector<RawObjData> data;

		// default constructor
		FileLoader(std::string path = "");

		/* Load() when returning:
			0 - success
		   -1 bad data format
		   -2 file does not exist */
		int Load(const std::string path);
		int Load();
		int Save(const std::string path);
		int Save(); 
		void SetPath(const std::string path);
		void Clear();
		RawObjData& get(unsigned id);
		~FileLoader();

};

//used to show all objects;
std::ostream & operator<<(std::ostream &screen, FileLoader &FileData);
//used for saving and loading to file
std::fstream & operator>>(std::fstream &screen, glm::mat4 &modelMatrix);
std::fstream & operator<<(std::fstream &screen, glm::mat4 &modelMatrix);


/*
suzanne.obj	uvmap.DDS	FragmentShader.frag	VertexShader.vert	1.0	2.0	3.0	0.0	-1.0	-2.0	0.43	1.0	1.0	1.0
suzanne.obj	uvmap.DDS	FragmentShader.frag	VertexShader.vert	1.0	0.0	0.0	1.0	0.0	0.0	7.0	2.0	2.0	2.0
suzanne.obj	uvmap.DDS	FragmentShader.frag	VertexShader.vert	0.0	1.70	0.0	3.0	0.0	0.0	0.23	0.1	0.1	0.12
suzanne.obj	uvmap.DDS	FragmentShader.frag	VertexShader.vert	5.0	0.0	0.0	0.0	0.0	0.0	90.0	2.0	2.0	2.0

*/