#include <stdio.h>
#include <unistd.h>    /* fork(), getpid() */
#include <sys/wait.h>  /* wait() */
#include <sys/types.h> /* pid_t */

int main(void)
{
    pid_t pid;

    pid = fork();

    // P2
    if (pid == 0)
    {
        pid = fork();

        // P9
        if (pid == 0)
        {
            printf("P9 PID: %d\n", getpid());
        }

        // P2
        else
        {
            pid = fork();

            // P3
            if (pid == 0)
            {
                pid = fork();

                // P7
                if (pid == 0)
                {
                    printf("P7 PID: %d\n", getpid());
                }

                // P3
                else
                {
                    pid = fork();

                    // P4
                    if (pid == 0)
                    {
                        pid = fork();

                        // P6
                        if (pid == 0)
                        {
                            printf("P6 PID: %d\n", getpid());
                        }

                        // P4
                        else
                        {
                            wait(NULL);
                            printf("P4 PID: %d\n", getpid());
                        }
                    }

                    // P3
                    else
                    {
                        wait(NULL);
                        wait(NULL);
                        printf("P3 PID: %d\n", getpid());
                    }
                }
            }

            // P2
            else
            {
                pid = fork();

                // P5
                if (pid == 0)
                {

                    pid = fork();

                    // P8
                    if (pid == 0)
                    {
                        printf("P8 PID: %d\n", getpid());
                    }

                    // P5
                    else
                    {
                        wait(NULL);
                        printf("P5 PID: %d\n", getpid());
                    }
                }

                // P2
                else
                {
                    wait(NULL);
                    wait(NULL);
                    wait(NULL);
                    printf("P2 PID: %d\n", getpid());
                }
            }
        }
    }

    // P1
    else
    {
        wait(NULL);
        printf("P1 PID: %d\n", getpid());
    }

    return 0;
}