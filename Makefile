#Copyright Mazilu Flavius-Romeo 314CAb 2021-2022
build: main.c utils.c
	gcc main.c utils.c rotate.c load.c crop.c apply.c save.c select.c -o image_editor -Wall -Wextra -lm

pack:
	zip -FSr 314CA_MaziluFlaviusRomeo_Tema3.zip README Makefile *.c *.h

clean:
	rm image_editor
