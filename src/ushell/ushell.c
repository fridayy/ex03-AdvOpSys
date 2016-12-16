/*
    example.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "parser.h"
#include "CommandExecutor.h"
#include "Colors.h"

void show_command (command * C);

char * getCurrentPath() {
    long size = pathconf(".", _PC_PATH_MAX);
    char *buf = malloc(sizeof(char) * size);

    return getcwd(buf, (size_t) size);
}

int main ()
{
    command C;
    int r;


    printf("Welcome to "GRN"λ"RESET"shell.\n > Advanced Operating Systems "BLU"uah."RESET"es");
    printf(RESET"\nUse "GRN"'help'"RESET" to show all available commands.");
    printf (RESET"\nType commands (press Ctrl-D to finish)\n");

    do
    {
        init_command (&C);
        char * path = getCurrentPath();
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


