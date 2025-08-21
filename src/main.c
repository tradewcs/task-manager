#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "process_list.h"
#include "process_info.h"

void print_usage() {
    printf("Usage:\n");
    printf("  taskman list\n");
    printf("  taskman info <pid>\n");
    printf("  taskman kill <pid>\n");
    printf("  taskman search <name>\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    if (strcmp(argv[1], "list") == 0) {
        return list_processes();
    } else if (strcmp(argv[1], "info") == 0) {
        if (argc < 3) {
            printf("Error: info requires a PID\n");
            return 1;
        }
        return process_info(argv[2]);
    } else if (strcmp(argv[1], "kill") == 0) {
        if (argc < 3) {
            printf("Error: kill requires a PID\n");
            return 1;
        }
        printf("Killing PID %s (not yet implemented)\n", argv[2]);
    } else if (strcmp(argv[1], "search") == 0) {
        if (argc < 3) {
            printf("Error: search requires a process name\n");
            return 1;
        }
        printf("Searching for process with name: %s (not yet implemented)\n", argv[2]);
    } else {
        print_usage();
        return 1;
    }

    return 0;
}

