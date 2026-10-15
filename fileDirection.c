#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

 int direction(char **arr){
         for(int i = 0 ; arr[i] != NULL ; i++){
                    if(strcmp(arr[i] , "<") == 0){
                         char *file = arr[i+1];
                        int fd = open(file ,   O_RDONLY);
                    
                        if(fd < 0){
                        perror("Command failed");
                        exit(1);
                        }

                    dup2(fd , 0);
                    close(fd);
                    arr[i] = NULL;
                    printf("%p\n" , arr[i]);
                    
                    return 0;
                }
                else if(strcmp(arr[i] , ">>") == 0){
                     char *file = arr[i+2];
                 
                    int fd = open(file, O_WRONLY   | O_CREAT  | O_APPEND , 0644);
                    if(fd < 0){
                        perror("Command failed");
                        _exit(1);
                    }
                    dup2(fd , 1);
                    close(fd);
                    arr[i] = NULL;
                    return 0;
                }
                
               else if(strcmp(arr[i] , ">") == 0  ){
               
                char *file = arr[i+1];
                int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC , 0644);
                if(fd < 0){
                    perror("Command failed");
                    _exit(1);
                }
                dup2(fd , 1);
                close(fd);
                arr[i] = NULL;
                return 0;
            }
        }
        return 1;
    }    
   