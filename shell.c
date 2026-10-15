#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

#define MAX_ARGS 10
#define buffer_size 50

int my_token(char *input ,  char** arr);
int changedirectory(int argc , char** arr);
int pipeDirection(char **arr);
int direction(char **arr);
int initShell(int fileDescriptor ,  pid_t *shell_pgid);
int main(){
    pid_t shell_pgid  = 0;
    int fileDescriptor = STDIN_FILENO;
    printf("%d\n" ,fileDescriptor);
     initShell(fileDescriptor , &shell_pgid);
     char input[buffer_size];
     char *arr[MAX_ARGS] = {NULL};
     char cwd[1024]; 

     while(1){      
     if(getcwd(cwd , sizeof(cwd)) != NULL){
        printf("my_shell:%s> ", cwd);
     }else{
        printf("myshell>>");
     }  
        fflush(stdout);

        if(fgets(input , buffer_size , stdin) == NULL){
              printf("Existing_my_shell...\n");    
            break;
        }
         
        input[strcspn(input , "\n")] = '\0';
        int argc =  my_token(input , arr);
        int inbuildcommandsignal = changedirectory(argc , arr);
        if(inbuildcommandsignal == 1){
            continue;
        }
        else if(inbuildcommandsignal == -1){
            break;
        }
        
        int pipeSignal = pipeDirection(arr);
        if(pipeSignal == 1){
            continue;
        }
        pid_t pid = fork();
    
        if(pid < 0){
        perror("Fork failed");
          _exit(1);
        }
        else if(pid == 0){
        pid_t child_pid = getpid();
        if(tcsetpgrp(fileDescriptor , child_pid) < 0){
            perror("parent tcsetpgrp failed");
        };  
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP , SIG_DFL);
        signal(SIGTTIN , SIG_DFL);
        signal(SIGTTOU , SIG_DFL);

        if(setpgid(0 , 0) == -1){
        perror("Command failed");
         _exit(1);
        }
      
            
        int signalPipe = direction(arr);
            execvp(*arr , arr);
            perror("Command failed");
            _exit(1);
            
    }else{
        if(setpgid(pid , pid) == -1){
        perror("Command failed");
     
    }
  
         tcsetpgrp(fileDescriptor , pid );  
        int statuscode;
        waitpid(pid, &statuscode , WUNTRACED);
        tcsetpgrp(fileDescriptor , shell_pgid);  
        // if(WIFEXITED(statuscode)){
        //     int code = WEXITSTATUS(statuscode);
        //     printf("Child exited normally with code: %d\n" ,code);
        // }else if(WIFSIGNALED(statuscode)){
        //     int sig = WTERMSIG(statuscode);
        // printf("Child crashed or was killed by signal number: %d\n", sig);
        // }
  
  
    }   
  
}
  return 0;

     
}