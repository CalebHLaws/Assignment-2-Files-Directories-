make:
	gcc --std=gnu99 -g -c movies.c
	gcc --std=gnu99 -g -c main.c
	gcc --std=gnu99 -g movies.o main.o -o movies_by_year main.c
