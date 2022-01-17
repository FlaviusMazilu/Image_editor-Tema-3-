//Copyright Mazilu Flavius-Romeo 314CAb 2021-2022
#ifndef __LOAD__
#define __LOAD__

void read_values_fscanf(int n, int m, int RGB, pixel **a, FILE *f);

void read_values_fread(int n, int m, int RGB, pixel **a, FILE *f);

pixel **read_binary(FILE *f, int n, int m, int RGB);

pixel **read_ascii(FILE *f, int n, int m, int RGB);

void LOAD(info *p, pixel ***a);

#endif
