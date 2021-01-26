make:
	gcc --std=gnu99 -c movies.c main.c
	gcc --std=gnu99 movies.o main.o -o movies_by_year

debug:
	gcc --std=gnu99 -ggdb -c movies.c main.c
	gcc --std=gnu99 -ggdb movies.o main.o -o movies_by_year
clean:
	rm main.o movies.o movies_by_year
