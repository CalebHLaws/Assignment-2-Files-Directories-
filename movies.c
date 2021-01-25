#include "movies.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Movie{
  char *title;
  int year;
  char *languages;
  double rating;
  struct Movie *next;
}Movie;

void createYears(char* directory,char* csv){
  struct Movie *list = processMovie(csv);
  printf("Anylizing : %s",csv);
  highestRated(list,directory);
}


/* Parse the current line which is space delimited and create a
*  Movie struct with the data in this line
*/
struct Movie *createMovie(char *currLine)
{
    struct Movie *currMovie = malloc(sizeof(struct Movie));

    // For use with strtok_r
    char *saveptr;

    // The first token is the title
    char *token = strtok_r(currLine, ",", &saveptr);
    currMovie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->title, token);

    // The next token is the year
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->year = atoi(token);

    // The next token is the languages
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->languages = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->languages, token);

    // The last token is the rating
    token = strtok_r(NULL, "\n", &saveptr);
    currMovie->rating = strtod(token,NULL);

    // Set the next node to NULL in the newly created Movie entry
    currMovie->next = NULL;

    return currMovie;
}

/*
* Return a linked list of Movies by parsing data from
* each line of the specified file.
*/
struct Movie *processMovie(char *filePath)
{
    // Open the specified file for reading only
    FILE *movieFile = fopen(filePath, "r");

    char *currLine = NULL;
    size_t len = 0;
    ssize_t nread;
    char *token;

    // The head of the linked list
    struct Movie *head = NULL;
    // The tail of the linked list
    struct Movie *tail = NULL;

    //Skip First line of CSV 
    nread = getline(&currLine, &len, movieFile);

    // Read the file line by line
    while ((nread = getline(&currLine, &len, movieFile)) != -1)
    {
        // Get a new Movie node corresponding to the current line
        struct Movie *newNode = createMovie(currLine);

        // Is this the first node in the linked list?
        if (head == NULL)
        {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newNode;
            tail = newNode;
        }
        else
        {
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }
    }
    free(currLine);
    fclose(movieFile);
    return head;
}

/*
* Print data for the given Movie
*/
void printMovie(struct Movie* aMovie){
  printf("%s, %d %s, %.1f\n", aMovie->title,
               aMovie->year,
               aMovie->languages,
               aMovie->rating);
}

/*
* Returns number of movies
*/
int countMovies(struct Movie *list){
  int count=0;
  while (list != NULL)
    {
        count++;
        list = list->next;
    }
  return count;
}

/*
* Checks to see if the year has already been checked
*/
int notInBlacklist(int testyear,int* blacklist){
  int i=0;
    while(blacklist[i]!=-1){
      if(testyear == blacklist[i]){
        //printf("Skipped year %i\n",testyear); //FOR TESTING
        return 0;        
      }
      i++;
    }
  return 1;
}

/*
* Prints the highest rated movie of a given year
*/
void printHighestYear(int testyear,struct Movie *list,char* directory){
  printf("Checking year: %i\n",testyear); //FOR TESTING
  
  FILE *pFile;
  char* name = calloc(12+sizeof(directory), sizeof(char));
  strcat(name,directory);
  sprintf(name,"%i",testyear);
  strcat(name,".txt");

  pFile = fopen(name,"w");


  while(list!=NULL){
    if(list->year == testyear){
      /*
      fputs(list->title,pFile);
      fputs(" : ",pFile);
      fputs("This is the rating", pFile);
      fputs("\n",pFile);
      */
    }
    list=list->next;
  }
  fclose(pFile);
  free(name);
  
}
/*
* Adds number to the blacklist
*/
void updateBlacklist(int num,int* blacklist){
  int i =0;
  while(blacklist[i]!=-1){
    i++;
  }
  blacklist[i]=num;
  //printf("Blacklisted: %i\n",num); //FOR TESTING
}

/*
* Prints the highest rated movie for each year
*/
void highestRated(struct Movie *list,char* directory){
  printf("\n");
  int count = countMovies(list)+1;
  int* blacklist = calloc(count,sizeof(int));
  
    
  for(int i=0;i<count;i++){
    blacklist[i] = -1;
  }

  while (list != NULL){
    if(notInBlacklist(list->year,blacklist)){
      
      printHighestYear(list->year,list,directory);
      updateBlacklist(list->year,blacklist);
    }
      list = list->next;
  }
  printf("\n\n");
  free(blacklist);
}

/*
* Prints each movie that has a certain language
*/