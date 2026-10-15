#include<stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
int initShell(int fileDescriptor , pid_t *shell_pgid){

    if(isatty(fileDescriptor) == 0){
        perror("Command failed");
        exit(1);
    }

    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP , SIG_IGN);
    signal(SIGTTIN , SIG_IGN);
    signal(SIGTTOU , SIG_IGN);

    if(setpgid(0 , 0) == -1){
        perror("Command failed");
        exit(1);
    }
    *shell_pgid = getpid();
    tcsetpgrp(fileDescriptor , *shell_pgid );
    return 0;
}
