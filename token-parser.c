#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>


#define MAX_ARGS 10
#define buffer_size 50

int my_token(char *input ,  char** args){
int count = 0;
int index = 0;
char *p = input;
while(*p != '\0'){  
    while(*p == ' '){
        *p = '\0';
        count++;
        p++;
    }
    while(*p == '"'){
        p++;
        count++;
    *(args + index) = p;
        while(*p != '"' && *p != '\0'){
            count++;
            p++;
        }
        if(*p == '"'){
            *p = '\0';
            p++;
            count++;
        }
        while(*p == ' ' && *p != '\0'){
            p++;
            count++;
        }
         index++;
    }
    if(*p == '\0'){
        break;
    }
    if(index >= MAX_ARGS-1 ){
        printf("Warming: Too many argument");
        break;
    }
    if(*p != '"'){
         *(args + index) = p;
         index++;
         p++;
         count++;
    }
    
    while(*p != ' ' && *p != '\0' && *p != '"'){
        p++;
        count++;
    }
}
*(args  + index) = NULL;
return index;

}  

