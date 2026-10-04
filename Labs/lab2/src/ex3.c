/**
 * ex3.c
 * Author: Prof. Neerja Mhaskar
 * Course: Operating Systems
 *
 * Helper program exec'd by ex2. Prints its argument count and concatenates
 * all of its arguments (including argv[0]) into a single string.
 */

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    int i = 0;
    char str[100] = "";

    printf("argument count: %d\n", argc);
    while (i < argc) {
        strcat(str, argv[i]);
        i = i + 1;
    }
    printf("Print from ex3\n");
    printf("%s\n", str);
    return 0;
}
