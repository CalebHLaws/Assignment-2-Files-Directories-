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

bool isCSV(char* fileName){
  char* ext = strchr(fileName,'.');
  if(!ext)
    ;
  else
    if(strstr(ext,".csv"))
      return (true);

  return false;
}

void proccessFile(){

}
/*
* Finds the largest csv file in the current directory. This is done by comparing the * stats of each file with the csv suffix.
*/
void findLargestFile(){
    // Open the current directory
  DIR* currDir = opendir(".");
  struct dirent *aDir;
  time_t lastModifTime;
  struct stat dirStat;
  struct stat maxStat;
  char *entryName = NULL;

  stat(aDir->d_name,&maxStat); //Set max size
  // Go through all the entries
  while((aDir = readdir(currDir)) != NULL){
    if(isCSV(aDir->d_name)){
      printf("Testing file: %s\n",aDir->d_name);
      stat(aDir->d_name, &dirStat); 
      if(dirStat.st_size > maxStat.st_size){
        // Set max Stat to stat
        maxStat = dirStat; 
        free(entryName);
        entryName = calloc(strlen(aDir->d_name)+1,sizeof(char));
        strcpy(entryName, aDir->d_name);
      }
    }
  }
  // Close the directory
  closedir(currDir);
  printf("The largest file is %s, at a size of %li bytes\n\n", entryName, maxStat.st_size);
  proccessFile();
  free(entryName);
}
/*
* Finds the smallest csv file in the current directory. This is done by comparing the * stats of each file with the csv suffix.
*/
void findSmallestFile(){
  DIR* currDir = opendir(".");
  struct dirent *aDir;
  time_t lastModifTime;
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
        printf("Smallest size name: %s",entryName);
      }
    }
  }
  // Close the directory
  closedir(currDir);
  printf("The smallest file is %s, at a size of %li bytes\n\n", entryName, minSize);
  proccessFile();
  free(entryName);
  proccessFile();
}

/*
* Finds and proccesses a file by name in the current directory
*/

int findSpecificFile(){
  /*
  if (filename invalid){
    printf("Filename not found\n")
    return 1; //invalid name
  }
  */
  proccessFile();
  return 0;
}

int main(void) {
  int choice;
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
          choice = findSpecificFile();
        }
        else if (choice == 0)
          ;
        else{
          printf("ERROR: Please input a valid input\n\n");
        }
      }
      if (choice == 2){
        return EXIT_SUCCESS;
      }
      if (choice == 0)
        ;
      else{
        printf("ERROR: Please input a valid input\n\n");
      }
      

    }

}