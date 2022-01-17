//Copyright Mazilu Flavius-Romeo 314CAb 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "crop.h"

pixel **CROP(pixel **a, info *p, int *x1, int *y1, int *x2, int *y2)
{
	//se aloca memorie pt matrice noua care va contine crop-ul
	pixel **b;
	b = alocare_matrice(*y2 - *y1, *x2 - *x1, p->RGB);
	if (!b)
		return a;

	int new_height = *y2 - *y1;
	int new_width = *x2 - *x1;

	//punerea valorilor din selectie in noua matrice
	for (int i = 0; i < new_height; i++) {
		for (int j = 0; j < new_width; j++) {
			for (int z = 0; z < p->RGB; z++)
				b[i][j].intensity[z] = a[*y1 + i][*x1 + j].intensity[z];
		}
	}

	//dezalocarea matricei vechi
	EXIT(a, p->height, p->width);
	p->height = *y2 - *y1;//noua inaltime
	p->width = *x2 - *x1;//noua latime
	*x1 = 0;
	*y1 = 0;
	*x2 = p->width;
	*y2 = p->height;
	printf("Image cropped\n");
	return b;
}
