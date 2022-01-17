//Copyright Mazilu Flavius-Romeo 314CAb 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils.h"

void write_binary(pixel **a, int n, int m, int RGB, char nume_fisier[])
{
	//scrierea mai intai a caracteristicilor in format text
	FILE *g = fopen(nume_fisier, "w");
	if (RGB == 1)
		fprintf(g, "%s\n", "P5");
	if (RGB == 3)
		fprintf(g, "%s\n", "P6");
	fprintf(g, "%d %d\n", m, n);
	fprintf(g, "%d\n", 255);
	fclose(g);

	//redeschiderea in binar pt a scrie matricea
	g = fopen(nume_fisier, "ab");
	for (int i = 0; i < n ; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < RGB; k++) {
				unsigned char aux = round(a[i][j].intensity[k]);
				fwrite(&aux, sizeof(unsigned char), 1, g);
			}
		}
	}
	fclose(g);
}

void write_ascii(pixel **a, int n, int m, int RGB, char nume_fisier[])
{
	FILE *g = fopen(nume_fisier, "w");
	if (RGB == 1)
		fprintf(g, "%s\n", "P2");
	if (RGB == 3)
		fprintf(g, "%s\n", "P3");
	fprintf(g, "%d %d\n", m, n);
	fprintf(g, "%d\n", 255);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			for (int k = 0; k < RGB; k++) {
				unsigned char aux = round(a[i][j].intensity[k]);
				fprintf(g, "%d ", aux);
			}
		}
		fprintf(g, "\n");
	}
	fclose(g);
}

void SAVE(pixel **a, int n, int m, int RGB)
{
	char nume_fisier[40];
	scanf("%s", nume_fisier);
	char c;
	scanf("%c", &c);
	if (c == '\n') {//daca nu mai urmeaza ceva dupa save <nume>
		write_binary(a, n, m, RGB, nume_fisier);
		//printf("binar\n");
	} else {
		char format;
		scanf("%c", &format);
		if (format == 'a')//daca urmeaza "ascii"
			write_ascii(a, n, m, RGB, nume_fisier);
		else
			write_binary(a, n, m, RGB, nume_fisier);
		while (format != '\n')
			scanf("%c", &format);
	}
	printf("Saved %s\n", nume_fisier);
}
