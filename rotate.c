//Copyright Mazilu Flavius-Romeo 314CAb 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "rotate.h"

void rotate90_square(pixel **a, int x1, int y1,	int x2, int y2, int RGB)
{
	//aux=mat. unde vor fi puse valorile rotite
	pixel **aux = alocare_matrice(x2 - x1, y2 - y1, RGB);
	if (!aux)
		return;
	//transpunerea matricei aux
	int d1 = 0;
	for (int i = x1; i < x2; i++) {
		int d2 = 0;
		for (int j = y1; j < y2; j++) {
			for (int k = 0; k < RGB; k++)
				aux[d1][d2].intensity[k] = a[j][i].intensity[k];
			d2++;
		}
		d1++;
	}

	//inversarea ordinii coloanelor din aux pt a obtine rotate 90 grade
	for (int i = 0; i < y2 - y1; i++) {
		int st = 0, dr = x2 - x1 - 1;
		while (st < dr) {
			for (int k = 0; k < RGB; k++)
				swap_db(&aux[i][st].intensity[k], &aux[i][dr].intensity[k]);
			st++;
			dr--;
		}
	}

	//punerea la loc a valorilor noi in matricea a
	d1 = 0;
	for (int i = y1; i < y2; i++) {
		int d2 = 0;
		for (int j = x1; j < x2; j++) {
			for (int k = 0; k < RGB; k++)
				a[i][j].intensity[k] = aux[d1][d2].intensity[k];
			d2++;
		}
		d1++;
	}
	EXIT(aux, x2 - x1, y2 - y1);
}

pixel **ROTATE(pixel **a, info *p, int *x1, int *y1, int *x2, int *y2)
{
	int unghi;
	scanf("%d", &unghi);
	if (unghi > 360 || unghi < -360) {
		printf("Unsupported rotation angle\n");
		return a;
	}
	if (abs(unghi) % 90 != 0) {
		printf("Unsupported rotation angle\n");
		return a;
	}
	if (*y2 - *y1 != *x2 - *x1)
		if (!(*x1 == 0 && *y1 == 0 && *x2 == p->width && *y2 == p->height)) {
			printf("The selection must be square\n");
			return a;
	}

	if (unghi == 90 || unghi == -270) {
		if (*y2 - *y1 == *x2 - *x1)//selectia e patrat
			rotate90_square(a, *x1, *y1, *x2, *y2, p->RGB);
		else
			a = rotate_all90(a, &p->height, &p->width, p->RGB, x2, y2);
	}
	if (unghi == -90 || unghi == 270) {
		if (*y2 - *y1 == *x2 - *x1) {
			//3 rotiri de 90 grade la dreapta
			rotate90_square(a, *x1, *y1, *x2, *y2, p->RGB);
			rotate90_square(a, *x1, *y1, *x2, *y2, p->RGB);
			rotate90_square(a, *x1, *y1, *x2, *y2, p->RGB);
		} else {
			a = rotate_all90(a, &p->height, &p->width, p->RGB, x2, y2);
			a = rotate_all90(a, &p->height, &p->width, p->RGB, x2, y2);
			a = rotate_all90(a, &p->height, &p->width, p->RGB, x2, y2);
		}
	}
	if (unghi == 180 || unghi == -180) {
		if (*y2 - *y1 == *x2 - *x1) {
			//2 rotiri de 90 grade la dreapta
			rotate90_square(a, *x1, *y1, *x2, *y2, p->RGB);
			rotate90_square(a, *x1, *y1, *x2, *y2, p->RGB);
		} else {
			a = rotate_all90(a, &p->height, &p->width, p->RGB, x2, y2);
			a = rotate_all90(a, &p->height, &p->width, p->RGB, x2, y2);
		}
	}

	printf("Rotated %d\n", unghi);
	return a;
}

pixel **rotate_all90(pixel **a, int *n, int *m, int RGB, int *x2, int *y2)
{
	pixel **b = alocare_matrice(*m, *n, RGB);
	if (!b)
		return a;
	//punerea valorile in forma transpusa in noua matrice b
	for (int i = 0; i < *m; i++) {
		for (int j = 0; j < *n; j++) {
			for (int z = 0; z < RGB; z++)
				b[i][j].intensity[z] = a[j][i].intensity[z];
		}
	}

	//inversarea ordinii coloanelor matricei b
	for (int i = 0; i < *m; i++) {
		int j = 0, dr = *n - 1;
		while (j < dr) {
			for (int z = 0; z < RGB; z++) {
				double aux = b[i][j].intensity[z];
				b[i][j].intensity[z] = b[i][dr].intensity[z];
				b[i][dr].intensity[z] = aux;
			}
			j++; dr--;
		}
	}
	//dezalocarea vechii matrice si returnarea noii
	EXIT(a, *n, *m);
	int aux = *n;
	*n = *m;
	*m = aux;
	*x2 = *m;
	*y2 = *n;
	return b;
}
