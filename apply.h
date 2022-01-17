//Copyright Mazilu Flavius-Romeo 314CAb 2021-2022
#ifndef __APPLY__
#define __APPLY__

pixel **APPLY(pixel **a, int x1, int y1, int x2, int y2, info p);

int apply_transformare(float matrix[4][4], char parametru[]);

float suma_elem(float matrix[4][4], pixel **a, int k, int i, int j);

void EDGE(float matrix[4][4]);

void SHARPEN(float matrix[4][4]);

void BLUR(float matrix[4][4]);

void GAUSSIAN_BLUR(float matrix[4][4]);

#endif
