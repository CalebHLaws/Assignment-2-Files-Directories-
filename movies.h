#ifndef MOVIES
#define MOVIES

struct Movie *createMovie(char *currLine);
struct Movie *processFile(char *filePath);

void printMovie(struct Movie* aMovie);
void printMovieList(struct Movie *list);
void printYear(struct Movie *list, int option);

int countMovies(struct Movie *list);
int notInBlacklist(int testyear,int* blacklist);

void printHighestYear(int testyear,struct Movie *list);
void updateBlacklist(int num,int* blacklist);

void highestRated(struct Movie *list,char* directory);

void printMoviesWithLanguage(struct Movie *list,char* language);

#endif