//Copyright Mazilu Flavius-Romeo 314CAb 2021-2022
#include <stdio.h>
#include <string.h>

#include "select.h"
#include "utils.h"

#define minn -999999

void SELECT(int *x1, int *y1, int *x2, int *y2, int n, int m)
{
	int x1_cp = minn, x2_cp = minn, y1_cp = minn, y2_cp = minn;
	//pentru testarea daca urmatorul dupa SELECT e ALL sau numar pt coordonata
	char buffer[20];
	scanf("%s", buffer);

	//situatia in care e SELECT ALL
	if (strcmp(buffer, "ALL") == 0) {
		*x1 = 0;
		*x2 = m;
		*y1 = 0;
		*y2 = n;
		printf("Selected ALL\n");
		return;
	}
	//daca nu e ALL ar trebui sa fie prima coordonata x1
	sscanf(buffer, "%d", &x1_cp);
	int vrf = verif();//verifica daca mai urmeaza vreo valoare pe rand de citit
	if (vrf == -1) {
		printf("Invalid command\n");
		return;
	}
	scanf("%d", &y1_cp);
	vrf = verif();
	if (vrf == -1) {
		printf("Invalid command\n");
		return;
	}
	scanf("%d", &x2_cp);
	vrf = verif();
	if (vrf == -1) {
		printf("Invalid command\n");
		return;
	}
	scanf("%d", &y2_cp);

	//daca vreuna din coordonate nu si-a schimbat valoarea
	//deci nu a fost citita corect
	if (x1_cp == minn || y1_cp == minn || x2_cp == minn || y2_cp == minn) {
		printf("Invalid command\n");
		free_junk();
		return;
	}

	if (x1_cp == x2_cp || y1_cp == y2_cp) {
		printf("Invalid set of coordinates\n");
		return;
	}
	if (x1_cp < 0 || x2_cp < 0 || y1_cp < 0 || y2_cp < 0) {
		printf("Invalid set of coordinates\n");
		return;
	}
	if (x1_cp > m || x2_cp > m) {
		printf("Invalid set of coordinates\n");
		return;
	}
	if (y1_cp > n || y2_cp > n) {
		printf("Invalid set of coordinates\n");
		return;
	}

	if (x1_cp > x2_cp)
		swap(&x1_cp, &x2_cp);
	if (y1_cp > y2_cp)
		swap(&y1_cp, &y2_cp);
	//daca coordonatele sunt valide, se vor pune in variabilele finale
	*x1 = x1_cp;
	*x2 = x2_cp;
	*y1 = y1_cp;
	*y2 = y2_cp;
	printf("Selected %d %d %d %d\n", x1_cp, y1_cp, x2_cp, y2_cp);
}
