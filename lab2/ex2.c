/**
 * ex2.c
 * Author: Prof. Neerja Mhaskar
 * Course: Operating Systems
 *
 */

#include <stdio.h>
#include <unistd.h>      /* fork(), getpid(), execvp() */
#include <sys/wait.h>    /* wait()                     */
#include <sys/types.h>   /* pid_t                      */

int main(void)
{
    pid_t pid;
    printf("Root: %d\n", getpid());   /* the root/parent */

    pid = fork();
    if (pid == 0) {
        printf("Child: %d\n", getpid()); /*This will print the child*/

        char *argv[] = {"Hello ", "World!", NULL};
        int j = execvp("./ex3", argv);
        if (j < 0) {
            printf("Error executing execvp\n");
        }
    }
    else {
        wait(NULL);
        printf("Child process is complete\n");
    }

    return 0;
}
