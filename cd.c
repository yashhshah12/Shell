#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>


#define MAX_ARGS 10
#define buffer_size 50
int changedirectory(int argc , char *arr[]){
    if(argc == 0 || arr[0] == NULL){
            return 1;
        }
            if(strcmp(arr[0] , "exit" ) == 0){
                printf("bye bye! meet you tommorrow Existing_my_shell...\n");
                return -1;
            }
            if(strcmp(arr[0] , "cd") == 0){
                if(arr[2] != NULL){            
                    fprintf(stderr , "Nonsense You don't Command you should learn then use it Command invalide : Too many argument \n");
                    return 1;
                }
                
            if(arr[1] == NULL){
                char *home = getenv("HOME");
                if(home != NULL){
                     if(chdir(home) != 0){
                         perror("Command failed");
                     }
                     printf("See i have take you to home ");
                }
            }else{
                if(chdir(arr[1]) != 0){
                    perror("Command failed");
                }
            }
               

            return 1;
        }
        return 0;
    }