//Copyright Mazilu Flavius-Romeo 314CAb 2021-2022

Scopul programului este de a implementa urmatoarele functii care pot fi date ca
si comenzi, privind editarea de imagini
	-LOAD -SELECT -SELECT ALL -CROP -APPLY -SAVE -EXIT
-------------------------------------------------------------------------------

*) structura info este folosita pentru a stoca datele despre poza incarcata in
memorie(inaltime, latime, RGB/greyscale(RGB = 3 sau 1), si valoarea maxima

**) structura pixel folosita pentru a defini campul intensity unde vor fi
stocate valorile pixelilor

***) am folosit tipul double pentru a retine poza pentru a face cast la
unsigned char doar inainte de save, astfel evitandu-se o inmultire a erorii
eps
-------------------------------------------------------------------------------
LOAD)
	-este citit mai intai numele pozei care va fi incarcata in memorie
urmata de citirea caracteristicilor acestora, apeland dupa fiecare citire
functia ignore_comments(definita in utils.c) care you guessed, trece peste
comentarii

	-daca poza care urmeaza a fi citita este de tipul P5 P6 se inchide
fisierul deschis initial ca read text si se deschide pentru read binary,
totodata apeland functia pentru a citi in modul binary

	-altfel se citeste in continuare in mod text
	
	-in ambele se apeleaza functia de alocare, mai intai a unei matrice
	de tipul pixel, unde fiecare valoare din matrice poate avea
	1 sau 3 valori, la randul ei, in functie daca este RGB sau nu
-------------------------------------------------------------------------------
SELECT)
	-se citeste primul lucru care urmeaza dupa SELECT intr-un sir buffer
daca sirul este "ALL" se selecteaza coordonatele respective, altfel se incearca
conversia la int in x1 si se verifica (verif()) daca mai urmeaza vreo valoare
pentru a fi citita pentru select)

	-toate cele 4 valori au fost initializate cu o valoare minima iar in
cazul in care a ramas pe acea valoare minima inseamna ca o coordonata era
invalida
	
	-urmeaza testarea daca vreuna din cele 4 coordonate nu respecta
conditile, daca e mai mare decat dimensiunea pozei, daca e negativa

	-in cazul in care verifica conditile, ele vor fi inlocuite in
	variabilele a caror este data adresa, altfel nu vor fi inlocuite
	si se vor pastra cele vechi
-------------------------------------------------------------------------------
CROP)
	-este alocata o matrice noua in care se vor pune valorile din selectie
	
	-urmeaza dezalocarea matricei vechi si returnarea acestei noi matrici
	si modificarea dimensiunilor stocate
-------------------------------------------------------------------------------
ROTATE)
	-sunt folosite 3 functii
		-una de rotate la 90 grade pt o selectie patratica
		-una de rotate la 90 grade pt toata imaginea
		-o functie care implementeaza acest rotate
	
	-pentru rotate 90 selectie patratica se aloca memorie pentru o
matrice auxiliara unde vor fi puse valorile din selectie rotite cu 90 de grade
la dreapta 
	-sunt copiate valorile in forma transpusa in aceasta noua matrice
	-se inverseaza ordinea linilor si a coloanelor, astfel se obtine
	rotate-ul
	-se copiaza valorile in matricea initiala si se dezaloca memoria pt
	aceasta matrice auxiliara
	-similar pt toata poza, diferenta constand in faptul ca se dezaloca
	memoria pt matricea initiala si se returneaza aceasta matrice auxiliara
	
	
	-se verifica daca unghiul citit corespunde conditiei de a fi multiplu
	de 90
	-se face rotate de 90grade de cate ori este nevoie, 180 de de ori
	270 de 3 ori
-------------------------------------------------------------------------------
SAVE)
	-functia SAVE citeste numele fisierului in care se va salva poza
	-se verifica daca se doreste a fi salvata in ascii, astfel
citeste un caracter iar daca acel caracter este endline inseamna ca 'ascii'
nu se afla pe acea linie, deci se va salva binar, altfel se mai citeste un
caracter si se verifica daca este 'a'->ascii, si se salveaza in mod text
	-se apeleaza functia de scriere in text/binar
-------------------------------------------------------------------------------
EXIT)
	-dezaloca pe rand campul din structura uc *intensity
	-dezaloca linile si coloanele
