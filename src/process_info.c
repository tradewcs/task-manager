#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int process_info(const char *pid) {
    char path[256];
    snprintf(path, sizeof(path), "/proc/%s/status", pid);

    FILE *f = fopen(path, "r");
    if (!f) {
        perror("fopen");
        return 1;
    }

    char line[512];
    printf("Process info for PID %s:\n", pid);

    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "Name:", 5) == 0 ||
            strncmp(line, "State:", 6) == 0 ||
            strncmp(line, "VmRSS:", 6) == 0 ||
            strncmp(line, "Threads:", 8) == 0) {
            printf("%s", line);
        }
    }

    fclose(f);
    return 0;
}

