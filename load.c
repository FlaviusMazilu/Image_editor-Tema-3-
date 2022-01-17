//Copyright Mazilu Flavius-Romeo 314CAb 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "load.h"

void read_values_fscanf(int n, int m, int RGB, pixel **a, FILE *f)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			//RGB = 1 sau 3, se citesc 1 sau 3 valori pt fiecare pixel
			for (int k = 0; k < RGB; k++)
				fscanf(f, "%lf", &a[i][j].intensity[k]);
		}
	}
}

void read_values_fread(int n, int m, int RGB, pixel **a, FILE *f)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < RGB; k++) {
				unsigned char aux;
				fread(&aux, sizeof(unsigned char), 1, f);
				a[i][j].intensity[k] = (unsigned char)aux;
			}
		}
	}
}

pixel **read_binary(FILE *f, int n, int m, int RGB)
{
	pixel **a = alocare_matrice(n, m, RGB);
	if (!a)
		return NULL;
	read_values_fread(n, m, RGB, a, f);
	return a;
}

pixel **read_ascii(FILE *f, int n, int m, int RGB)
{
	pixel **a = alocare_matrice(n, m, RGB);
	if (!a)
		return NULL;
	read_values_fscanf(n, m, RGB, a, f);
	return a;
}

void LOAD(info *p, pixel ***a)
{
	char parametru[50];//numele fisierului care e citit dupa LOAD
	scanf("%s", parametru);
	FILE *f = fopen(parametru, "r");
	if (!f) {
		printf("Failed to load %s\n", parametru);
		return;
	}

	//citirea pe rand a caracteristicilor pozei
	char magic_word[3];
	ignore_comments(f);
	fscanf(f, "%s", magic_word);

	ignore_comments(f);
	fscanf(f, "%d", &p->width);

	ignore_comments(f);
	fscanf(f, "%d", &p->height);

	ignore_comments(f);
	fscanf(f, "%d", &p->maxim);

	ignore_comments(f);
	int pos = ftell(f);//retinut pozitia pt reopen in format read binary
	p->RGB = 1; //1 sau 3, greyscale sau rgb
	if (strcmp(magic_word, "P3") == 0 || strcmp(magic_word, "P6") == 0)
		p->RGB = 3;

	if (strcmp(magic_word, "P5") == 0 || strcmp(magic_word, "P6") == 0) {
		f = freopen(parametru, "rb", f);//reopen in format binar fiind P5/P6
		fseek(f, pos, SEEK_SET);//mers la pozitia de dinainte de reopen
		(*a) = read_binary(f, p->height, p->width, p->RGB);

		if (*a)//*a != NULL inseamna ca a reusit incarcarea in memorie a pozei
			printf("Loaded %s\n", parametru);
		else
			printf("Failed to load %s\n", parametru);
		return;
	}
	(*a) = read_ascii(f, p->height, p->width, p->RGB);

	if (*a)
		printf("Loaded %s\n", parametru);
	else
		printf("Failed to load %s\n", parametru);
	fclose(f);
}
