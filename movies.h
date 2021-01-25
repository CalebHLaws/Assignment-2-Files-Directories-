#ifndef MOVIES
#define MOVIES

struct Movie *createMovie(char *currLine);
struct Movie *processMovie(char *filePath);

void printMovie(struct Movie* aMovie);


int countMovies(struct Movie *list);
int notInBlacklist(int testyear,int* blacklist);

void printHighestYear(int testyear,struct Movie *list,char* directory);
void updateBlacklist(int num,int* blacklist);

void highestRated(struct Movie *list,char* directory);

#endif