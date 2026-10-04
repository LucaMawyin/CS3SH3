/**
 * ex4.c
 * Author: Prof. Neerja Mhaskar
 * Course: Operating Systems 
 *
 * Three consecutive fork() calls create 2^3 = 8 processes in total
 * (the original parent plus 7 descendants). Each process prints its pid,
 * so you can verify there are 8 unique pids.
 * Note: 'printf("%d\n", getpid());' prints the pid of the current process.
 */

#include <stdio.h>
#include <unistd.h>      /* fork(), getpid() */
#include <sys/types.h>   /* pid_t            */

int main(void)
{
    fork();
    fork();
    fork();

    printf("%d\n", getpid());

    return 0;
}
