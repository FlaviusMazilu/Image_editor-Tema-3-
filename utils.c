//Copyright Mazilu Flavius-Romeo 314CAb 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

pixel **alocare_matrice(int n, int m, int RGB)
{
	pixel **a = (pixel **)malloc(n * sizeof(pixel *));
	//daca nu s-a alocat corect memorie pt a
	if (!a) {
		fprintf(stderr, "Eroare la malloc\n");
		return NULL;
	}

	for (int i = 0; i < n; i++) {
		//alocarea fiecarei linii
		a[i] = (pixel *)malloc(m * sizeof(pixel));
		if (!a[i]) {
			printf("Eroare la malloc\n");
			for (int j = 0; j < i; j++)
				free(a[j]);
			free(a);
			return NULL;
		}

		//alocarea numarului de poz pt fiecare tip de pixel(RGB/greyscale)
		for (int j = 0; j < m; j++) {
			a[i][j].intensity = malloc(RGB * sizeof(double));
			if (!a[i][j].intensity) {
				fprintf(stderr, "Eroare la malloc\n");
				//dezalocarea memoriei deja alocate pana in momentul respectiv
				for (int k = 0; k < j; k++)
					free(a[i][k].intensity);
				for (int ln = 0; ln < n; ln++)
					free(a[ln]);
				free(a);
				return NULL;
			}
		}
	}
	return a;
}

void EXIT(pixel **a, int n, int m)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			free(a[i][j].intensity);//dezalocarea poz. valorilor efective
	}
	for (int i = 0; i < n; i++)
		free(a[i]);//dez. liniilor
	free(a);
	a = NULL;
}

int verif(void)
{
	//verifica daca mai e ceva de citit pana la sfarsitul liniei
	char c;
	scanf("%c", &c);
	if (c == '\n')
		return -1;
	return 0;
}

void free_junk(void)
{
	//citeste caracterele nefolositoare pana la sfarsitul randului
	char c = 'a';
	while (c != '\n')
		scanf("%c", &c);
}

void swap(int *x, int *y)
{
	//swap intre 2 int-uri
	int aux = *x;
	*x = *y;
	*y = aux;
}

void swap_db(double *x, double *y)
{
	//swap intre 2 double-uri
	double aux = *x;
	*x = *y;
	*y = aux;
}

void ignore_comments(FILE *f)
{
	//functie care trece peste comentarii
	char c;
	fscanf(f, "%c", &c);
	if (c == ' ' || c == '\n')
		fscanf(f, "%c", &c);
	if (c == '#') {
		while (c != '\n')
			fscanf(f, "%c", &c);
	} else {
		fseek(f, -1, SEEK_CUR);
	}
}

void invalid_command(char comanda[])
{
	//verifica daca o comanda e valida
	int v[8];
	v[0] = strcmp(comanda, "LOAD");
	v[1] = strcmp(comanda, "SELECT");
	v[2] = strcmp(comanda, "ROTATE");
	v[3] = strcmp(comanda, "CROP");
	v[4] = strcmp(comanda, "APPLY");
	v[5] = strcmp(comanda, "SAVE");
	v[6] = strcmp(comanda, "EXIT");
	int x = v[0];
	for (int i = 1; i < 7; i++)
		x = x && v[i];
	if (x) {
		printf("Invalid command\n");
		free_junk();
	}
}

double clamp(double S)
{
	if (S > 255)
		S = 255;
	if (S < 0)
		S = 0;
	return S;
}
