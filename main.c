#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <limits.h>
#include <fcntl.h>

#include "movies.h"

//TODO SEGFAULT ON processFile movies.c:76 it's using Dir instead of actuall .csv file name CHANGE THIS 

bool isCSV(char* fileName){
  char* ext = strchr(fileName,'.');
  if(!ext)
    ;
  else
    if(strstr(ext,".csv"))
      return (true);

  return false;
}

int mylog10(int num){
  int i=0;
  while(num >= 1){
    num=num/10;
    i++;
  }
  return i;
}

void processFile(struct dirent *aDir,char* filename){
  int num = rand()%100000;
  char* temp = calloc( mylog10(num)+1,sizeof(char) ); 
  sprintf(temp,"%i",num);
  //Promissions should be rwxr-x--- / 0750
  char* directory = calloc(strlen("./lawsc.movies.")+mylog10(num)+1,sizeof(char) );
  strcat(directory,"./lawsc.movies.");
  strcat(directory,temp);
  mkdir(directory,0750);
  printf("Created directory : %s",directory);
  
  createYears(directory,filename);
	free(directory);
  free(temp);
}
/*
* Finds the largest csv file in the current directory. This is done by comparing the * stats of each file with the csv suffix.
*/
void findLargestFile(){
    // Open the current directory
  DIR* currDir = opendir(".");
  struct dirent *aDir;
  struct stat dirStat;
  char *entryName = NULL;
  long int maxSize = 0;
  
  // Go through all the entries
  while((aDir = readdir(currDir)) != NULL){
    if(isCSV(aDir->d_name)){
      printf("Testing file: %s\n",aDir->d_name);
      stat(aDir->d_name, &dirStat); 
      if(dirStat.st_size > maxSize){
        // Set max Stat to stat
        maxSize = dirStat.st_size; 
        free(entryName);
        entryName = calloc(strlen(aDir->d_name)+1,sizeof(char));
        strcpy(entryName, aDir->d_name);
      }
    }
  }
  printf("\nThe largest file is %s, at a size of %li bytes\n\n", entryName, maxSize);
  processFile(aDir,entryName);
  // Close the directory
  closedir(currDir);
  free(entryName);
}
/*
* Finds the smallest csv file in the current directory. This is done by comparing the * stats of each file with the csv suffix.
*/
void findSmallestFile(){
  DIR* currDir = opendir(".");
  struct dirent *aDir;
  struct stat dirStat;
  long int minSize;
  char *entryName = NULL;

  minSize = INT_MAX;
  // Go through all the entries
  while((aDir = readdir(currDir)) != NULL){
    if(isCSV(aDir->d_name)){
      printf("Testing file: %s\n",aDir->d_name);
      stat(aDir->d_name, &dirStat); 
      if(dirStat.st_size < minSize){
        // Set max Stat to stat
        minSize = dirStat.st_size;
        free(entryName);
        entryName = calloc(strlen(aDir->d_name)+1,sizeof(char));
        strcpy(entryName, aDir->d_name);
        printf("Smallest size name: %s\n",entryName);
      }
    }
  }
  printf("\nThe smallest file is %s, at a size of %li bytes\n\n", entryName, minSize);
  processFile(aDir,entryName);
  // Close the directory
  closedir(currDir);
  free(entryName);
}

/*
* Finds and proccesses a file by name in the current directory. Returns 0 if file not found 1 otherwise
*/

int findSpecificFile(char* searchName){
  DIR* currDir = opendir(".");
  struct dirent *aDir;
  struct stat dirStat;
  printf("Searching for File: %s\n",searchName);
  // Go through all the entries
  while((aDir = readdir(currDir)) != NULL){
    if(strcmp(aDir->d_name,searchName) == 0){
      printf("Processing file : %s\n",aDir->d_name);
      processFile(aDir,searchName);
      return 1;
    }
  }
  printf("\nFile not found\n\n");
  // Close the directory
  return 0;
}

int main(void) {
  char entry[256];
  int choice;
  time_t t;
  srand((unsigned) time(&t)); //Random seed
  
  while(1==1){
      printf("1. Select file to process\n");
      printf("2. Exit the program\n");
      printf("\nEnter a choice 1 or 2: ");
      scanf("%i",&choice);
      
      while(choice == 1){
        printf("\n");
        printf("Which file you want to process?\n");
        printf("Enter 1 to pick the largest file\n");
        printf("Enter 2 to pick the smallest file\n");
        printf("Enter 3 to specify the name of a file\n");
        printf("\nEnter a choice from 1 to 3: ");
        scanf("%i",&choice);
        if (choice == 1){
          findLargestFile();
          choice = 0;
        }
        else if (choice == 2){
          findSmallestFile();
          choice = 0;
        }
        else if (choice == 3){
          printf("\nEnter The file you which to process\n");
          scanf("%s",&entry);
          findSpecificFile(entry);
          choice =0;
        }
        else if (choice == 0)
          ;
        else{
          printf("ERROR1: Please input a valid input\n\n");
        }
      }
      if (choice == 2){
        return EXIT_SUCCESS;
      }
      else if(choice !=0){
        printf("ERROR2: Please input a valid input\n\n");
      }
      

    }

}
