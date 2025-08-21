#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int pid;
    char name[256];
    long memory;
    long cpu;
} Process;

int compare_mem(const void *a, const void *b) {
    return ((Process *)b)->memory - ((Process *)a)->memory;
}

int compare_cpu(const void *a, const void *b) {
    return ((Process *)b)->cpu - ((Process *)a)->cpu;
}

int list_processes(const char *sort_by) {
    DIR *dir = opendir("/proc");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    Process *procs = NULL;
    size_t count = 0;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (!isdigit(entry->d_name[0]))
            continue;

        Process p;
        p.pid = atoi(entry->d_name);
        p.memory = 0;
        p.cpu = 0;

        char path[256];
        snprintf(path, sizeof(path), "/proc/%s/comm", entry->d_name);
        FILE *f = fopen(path, "r");
        if (f) {
            if (fgets(p.name, sizeof(p.name), f) == NULL) {
                strcpy(p.name, "?");
            }
            p.name[strcspn(p.name, "\n")] = 0;
            fclose(f);
        }

        // Memory (statm field 2 = RSS)
        snprintf(path, sizeof(path), "/proc/%s/statm", entry->d_name);
        f = fopen(path, "r");
        if (f) {
            long total, rss;
            if (fscanf(f, "%ld %ld", &total, &rss) == 2) {
                p.memory = rss;
            }
            fclose(f);
        }

        // CPU (stat fields 14+15)
        snprintf(path, sizeof(path), "/proc/%s/stat", entry->d_name);
        f = fopen(path, "r");
        if (f) {
            char buf[1024];
            if (fgets(buf, sizeof(buf), f)) {
                char *token = strtok(buf, " ");
                int i = 1;
                long utime = 0, stime = 0;
                while (token) {
                    if (i == 14) utime = atol(token);
                    if (i == 15) stime = atol(token);
                    token = strtok(NULL, " ");
                    i++;
                }
                p.cpu = utime + stime;
            }
            fclose(f);
        }

        procs = realloc(procs, (count + 1) * sizeof(Process));
        procs[count++] = p;
    }
    closedir(dir);

    if (strcmp(sort_by, "mem") == 0) {
        qsort(procs, count, sizeof(Process), compare_mem);
    } else if (strcmp(sort_by, "cpu") == 0) {
        qsort(procs, count, sizeof(Process), compare_cpu);
    }

    printf("%-10s %-40s %-10s %-10s\n", "PID", "NAME", "MEM", "CPU");
    for (size_t i = 0; i < count; i++) {
        printf("%-10d %-40s %-10ld %-10ld\n",
               procs[i].pid, procs[i].name, procs[i].memory, procs[i].cpu);
    }

    free(procs);
    return 0;
}

