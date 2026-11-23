#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10
#define OFFSET_BITS 12
#define PAGE_SIZE 4096
#define OFFSET_MASK 4095
#define PAGES 8

int main()
{
    int page_table[PAGES] = {6, 4, 3, 7, 0, 1, 2, 5};

    FILE *fptr = fopen("labaddr.txt", "r");

    if (fptr == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    char buff[BUFFER_SIZE];

    while (fgets(buff, BUFFER_SIZE, fptr) != NULL)
    {

        unsigned int virtual_address = atoi(buff);

        unsigned int page_number = virtual_address >> OFFSET_BITS;

        unsigned int offset = virtual_address & OFFSET_MASK;

        unsigned int frame_number = page_table[page_number];

        unsigned int physical_address = (frame_number << OFFSET_BITS) | offset;

        printf("Virtual addr is %u: Page# = %u & Offset = %u. Physical addr = %u.\n",
               virtual_address, page_number, offset, physical_address);
    }

    fclose(fptr);

    return 0;
}