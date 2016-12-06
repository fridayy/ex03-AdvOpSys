/*
    example.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "parser.h"
#include "CommandExecutor.h"
#define GRN   "\x1B[32m"
#define BLU   "\x1B[34m"
#define RESET "\x1B[0m"
void show_command (command * C);

int main ()
{
    command C;
    int r;
    char *path;
    long size = pathconf(".", _PC_PATH_MAX);
    char *buf = malloc(sizeof(char) * size);

    printf("Welcome to "GRN"λ"RESET"shell.\n > Advanced Operating Systems "BLU"uah."RESET"es");
    printf (RESET"\nType commands (press Ctrl-D to finish)\n");

    do              // Read commands and show them
    {
        init_command (&C);
        path = getcwd(buf, (size_t)size);
        printf (GRN"%s ~ λ " RESET, path);
        r = read_command (&C, stdin);

        if (r < 0) {
            fprintf (stderr, "\nError %d: %s\n",
                     -r, err_messages[-r]);
        } else {
            executeCommand(C.argv);
        }

        free_command (&C);
    }
    while (r==0);   // Repeat until error or EOF

    return 0;
}


