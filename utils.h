//Copyright Mazilu Flavius-Romeo 314CAb 2021-2022
#ifndef __UTILS__
#define __UTILS__

typedef struct {
	double *intensity; //intre 1-255
} pixel;

typedef struct {
	int height;
	int width;
	int maxim;
	int RGB;
} info;

pixel **alocare_matrice(int n, int m, int RGB);

void EXIT(pixel **a, int n, int m);

void SELECT(int *x1, int *x2, int *y1, int *y2, int n, int m);

void ignore_comments(FILE *f);

void free_junk(void);

int verif(void);

void swap(int *x, int *y);

void swap_db(double *x, double *y);

void invalid_command(char comanda[]);

double clamp(double S);

#endif

