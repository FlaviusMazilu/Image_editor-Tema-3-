//Copyright Mazilu Flavius-Romeo 314CAb 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "rotate.h"
#include "crop.h"
#include "apply.h"
#include "save.h"
#include "load.h"
#include "select.h"

int main(void)
{
	pixel **a = NULL;
	info p;//unde vor fi stocate informatii privind poza(inaltime, latime, RGB)
	char comanda[50];
	strcpy(comanda, "Uninitialized");//pt a avea sens in prima cond. la while
	int x1, x2, y1, y2;
	while (strcmp(comanda, "EXIT") != 0) {
		scanf("%s", comanda);
		if (strcmp(comanda, "LOAD") == 0) {
			if (a) {//daca e deja incarcata o poza, se dezaloca
				EXIT(a, p.height, p.width);
				a = NULL;
			}
			LOAD(&p, &a);
			x1 = 0;
			x2 = p.width;
			y1 = 0;
			y2 = p.height;
			continue;
		}

		if (!a && strcmp(comanda, "LOAD") != 0) {
			printf("No image loaded\n");
			if (strcmp(comanda, "EXIT") == 0)
				break;
			free_junk();
			continue;
		}

		if (strcmp(comanda, "SELECT") == 0)
			SELECT(&x1, &y1, &x2, &y2, p.height, p.width);

		if (strcmp(comanda, "ROTATE") == 0)
			a = ROTATE(a, &p, &x1, &y1, &x2, &y2);

		if (strcmp(comanda, "CROP") == 0)
			a = CROP(a, &p, &x1, &y1, &x2, &y2);

		if (strcmp(comanda, "APPLY") == 0) {
			a = APPLY(a, x1, y1, x2, y2, p);
			continue;
		}

		if (strcmp(comanda, "SAVE") == 0)
			SAVE(a, p.height, p.width, p.RGB);

		if (strcmp(comanda, "EXIT") == 0)
			EXIT(a, p.height, p.width);

		invalid_command(comanda);
	}
	return 0;
}
