/**
 * ex1.c
 * Author: Prof. Neerja Mhaskar
 * Course: Operating Systems
 *
 * fork() returns the pid of the child in the parent process and 0 in the
 * child process. Using this you can print the pid of both the parent and the
 * child. The statement 'printf("%d\n", getpid());' prints the pid of the
 * current process.
 */

#include <stdio.h>
#include <unistd.h>      /* fork(), getpid() */
#include <sys/types.h>   /* pid_t            */

int main(void)
{
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        printf("Child Process with PID: %d\n", getpid());
    }
    else {
        printf("Parent Process with PID: %d\n", getpid());
    }

    return 0;
}
