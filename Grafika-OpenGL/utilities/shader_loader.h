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

class ShaderLoader{
	void LoadShaders(std::vector<RawObjData>& data, std::vector<GLuint>& programID, std::vector<int>& ObjToProgramID);
};