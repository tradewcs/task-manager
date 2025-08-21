#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int process_kill(const char *pid_str) {
    int pid = atoi(pid_str);
    if (pid <= 0) {
        printf("Invalid PID: %s\n", pid_str);
        return 1;
    }

    if (kill(pid, SIGTERM) == -1) {
        perror("kill");
        return 1;
    }

    printf("Sent SIGTERM to PID %d\n", pid);
    return 0;
}

