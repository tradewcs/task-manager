#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int search_processes(const char *name_filter) {
    DIR *dir = opendir("/proc");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    int found = 0;

    printf("%-10s %-20s\n", "PID", "NAME");

    while ((entry = readdir(dir)) != NULL) {
        if (!isdigit(entry->d_name[0]))
            continue;

        char path[256];
        snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name);

        FILE *f = fopen(path, "r");
        if (!f) continue;

        char name[256];
        if (fgets(name, sizeof(name), f) != NULL) {
            name[strcspn(name, "\n")] = 0;
            if (strstr(name, name_filter) != NULL) {
                printf("%-10s %-20s\n", entry->d_name, name);
                found = 1;
            }
        }
        fclose(f);
    }

    closedir(dir);

    if (!found) {
        printf("No processes found matching: %s\n", name_filter);
    }

    return 0;
}

