//Copyright Mazilu Flavius-Romeo 314CAb 2021-2022
#ifndef __ROTATE__
#define __ROTATE__

void rotate90_square(pixel **a, int x1, int y1, int x2, int y2, int RGB);

void rotate180_square(pixel **a, int x1, int y1, int x2, int y2);

pixel **ROTATE(pixel **a, info *p, int *x1, int *y1, int *x2, int *y2);

pixel **rotate_all90(pixel **a, int *n, int *m, int RGB, int *x2, int *y2);

void rotate_all180(pixel **a, int n, int m);

#endif
