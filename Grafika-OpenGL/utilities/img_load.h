#pragma once

unsigned char* load_img(char const *filename, int *x, int *y, int *comp=0, int req_comp=3);
void free_img(void *retval_from_stbi_load);