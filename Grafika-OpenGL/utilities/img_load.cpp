#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "img_load.h"

unsigned char * load_img(char const * filename, int * x, int * y, int * comp, int req_comp)
{
	return  stbi_load(filename, x, y, comp, req_comp);
}

void free_img(void * retval_from_stbi_load)
{
	stbi_image_free(retval_from_stbi_load);
}
