#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include "Interior_decorator/Raw_Obj_Data.h"
#include "Shader.h"

class ShaderLoader{
private:
	bool IsNewShader(int objID, std::vector<RawObjData>& data);
	int GetSimilarShaders(int objID, std::vector<RawObjData>& data, std::vector<int>& ObjToProgramID);
protected:
	void LoadShaders(std::vector<RawObjData>& data,
						std::vector<int>& ObjToProgramID,
						std::vector<Shader>& shader);
};