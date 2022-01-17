//Copyright Mazilu Flavius-Romeo 314CAb 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "apply.h"

pixel **APPLY(pixel **a, int x1, int y1, int x2, int y2, info p)
{
	char c;
	//testez daca e APPLY simplu fara vreun parametru
	scanf("%c", &c);
	if (c == '\n') {
		printf("Invalid command\n");
		return a;
	}

	if (p.RGB == 1) {//APPLY nu se apica pentru greyscale(RGB == 1)
		printf("Easy, Charlie Chaplin\n");
		c = 'C';
		while (c != '\n')
			scanf("%c", &c);
		return a;
	}

	char parametru[20];
	float matrix[4][4];//matricea kernel
	int valid = apply_transformare(matrix, parametru);
	if (valid == -1)//daca nu s-a selectat niciunul din filtrele definite
		return a;

	//in b se vor pune valorile rezultate in urma inmultirii cu kernel-ul
	pixel **b = alocare_matrice(y2 - y1, x2 - x1, p.RGB);
	if (!b)
		return a;
	int k1 = 0;
	for (int i = y1; i < y2; i++) {
		int k2 = 0;
		for (int j = x1; j < x2; j++) {
			//cond. daca pixelul la care s-a ajuns se afla pe rama pozei
			if (i == 0 || j == 0 || i == p.height - 1 || j == p.width - 1) {
				for (int z = 0; z < p.RGB; z++)
					b[k1][k2].intensity[z] = a[i][j].intensity[z];
				k2++;
				continue;
			}

			//daca nu e pe rama se calculeaza in mod normal cu kernel-ul
			for (int k = 0; k < p.RGB; k++) {
				double S = 0;
				S = suma_elem(matrix, a, k, i, j);
				if (strcmp(parametru, "BLUR") == 0)
					S = S / 9.0;
				if (strcmp(parametru, "GAUSSIAN_BLUR") == 0)
					S = S / 16.0;
				S = clamp(S);
				b[k1][k2].intensity[k] = S;
			}
			k2++;
		}
		k1++;
	}

	//se inlocuiesc valorile din selectia lui a cu cele din b cu filtru
	k1 = 0;
	for (int i = y1; i < y2; i++) {
		int k2 = 0;
		for (int j = x1; j < x2; j++) {
			for (int z = 0; z < p.RGB; z++)
				a[i][j].intensity[z] = b[k1][k2].intensity[z];
			k2++;
		}
		k1++;
	}

	//se dezaloca matricea auxiliara b
	EXIT(b, y2 - y1, x2 - x1);
	printf("APPLY %s done\n", parametru);
	return a;
}

int apply_transformare(float matrix[4][4], char parametru[])
{
	//se initializeaza matricea kernel (matrix) cu valorile corespunzatoare
	//fiecarui tip de filtru selectat
	scanf("%s", parametru);
	if (strcmp(parametru, "EDGE") == 0) {
		EDGE(matrix);
		return 0;
	}
	if (strcmp(parametru, "SHARPEN") == 0) {
		SHARPEN(matrix);
		return 0;
	}
	if (strcmp(parametru, "BLUR") == 0) {
		BLUR(matrix);
		return 0;
	}
	if (strcmp(parametru, "GAUSSIAN_BLUR") == 0) {
		GAUSSIAN_BLUR(matrix);
		return 0;
	}
	printf("APPLY parameter invalid\n");
	//in cazul in care nu a fost selectat unul din filtrele de mai sus
	return -1;
}

float suma_elem(float matrix[4][4], pixel **a, int k, int i, int j)
{
	//calc suma inmultirilor elementelor kernel si poza
	float S = 0;
	S += matrix[0][0] * a[i - 1][j - 1].intensity[k] +
	matrix[0][1] * a[i - 1][j].intensity[k] +
	matrix[0][2] * a[i - 1][j + 1].intensity[k] +
	matrix[1][0] * a[i][j - 1].intensity[k] +
	matrix[1][1] * a[i][j].intensity[k] +
	matrix[1][2] * a[i][j + 1].intensity[k] +
	matrix[2][0] * a[i + 1][j - 1].intensity[k] +
	matrix[2][1] * a[i + 1][j].intensity[k] +
	matrix[2][2] * a[i + 1][j + 1].intensity[k];
	return S;
}

void EDGE(float matrix[][4])
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			matrix[i][j] = -1;
	}
	matrix[1][1] = 8;
}

void SHARPEN(float matrix[][4])
{
	matrix[0][0] = 0;
	matrix[0][2] = 0;
	matrix[2][0] = 0;
	matrix[2][2] = 0;
	matrix[0][1] = -1;
	matrix[1][0] = -1;
	matrix[1][2] = -1;
	matrix[2][1] = -1;
	matrix[1][1] = 5;
}

void BLUR(float matrix[][4])
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			matrix[i][j] = 1;
	}
}

void GAUSSIAN_BLUR(float matrix[][4])
{
	matrix[0][0] = 1;
	matrix[0][2] = 1;
	matrix[2][0] = 1;
	matrix[2][2] = 1;
	matrix[0][1] = 2;
	matrix[1][0] = 2;
	matrix[1][2] = 2;
	matrix[2][1] = 2;
	matrix[1][1] = 4;
}
