#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
int pipeDirection(char *arr[]){
     int index = -1;
         char  **cmd = NULL;
         char **cmd2 = NULL;
        // char *const argv[];
        for(int i = 0 ; arr[i] != NULL ; i++){
            
            if(strcmp(arr[i], "|") == 0){
            arr[i] = NULL;
            index = 0;
            cmd = &arr[0]; // arr (i+1)
            cmd2 = &arr[i+1];      
            printf("This is executed pipe\n");     
            break;
            }

            }
            if(index == 0){
            int pipef2[2];
            if(pipe(pipef2) < 0){
                perror("Command failed");
                
                exit(1);
             
            }

            pid_t pid = fork();
            if(pid < 0){
                perror("fork failed");
            }
            else if(pid == 0){
        
                dup2(pipef2[1] , 1);
                close(pipef2[0]);
                close(pipef2[1]);
                execvp(*cmd ,cmd);
                perror("Command failed");
                exit(1);


            }
            pid_t pid2 = fork();
            if(pid2 < 0){
                perror("fork failed");
            }else if(pid2 == 0){
                dup2(pipef2[0], 0);
            
                close(pipef2[0]);
                close(pipef2[1]);
                execvp(*cmd2 , cmd2);
               
                perror("Command ailed");
                exit(1);
            }
           
            close(pipef2[0]);
            close(pipef2[1]);
            waitpid(pid , NULL ,0);
            waitpid(pid2 , NULL,0);
            return 1;

        }
        return 0;
}