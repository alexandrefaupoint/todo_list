#include <stdio.h>
#include <string.h>
#include "file_ops.h"

int save_tasks(const char* filename, Task* tasks, int count) {
    FILE* f = fopen(filename, "w");
    if (!f) return -1;

    for (int i = 0; i < count; i++) {
        fprintf(f, "%d|%s|%d|%d\n",
                tasks[i].id,
                tasks[i].description,
                tasks[i].priority,
                tasks[i].done);
    }
    fclose(f);
    return 0;
}

int load_tasks(const char* filename, Task* tasks, int max_tasks) {
    FILE* f = fopen(filename, "r");
    if (!f) return -1;

    char line[512];
    int count = 0;
    while (fgets(line, sizeof(line), f) && count < max_tasks) {
        // Format: id|description|priority|done
        char* token = strtok(line, "|");
        if (!token) continue;
        tasks[count].id = atoi(token);

        token = strtok(NULL, "|");
        if (!token) continue;
        strncpy(tasks[count].description, token, MAX_DESC);
        tasks[count].description[strcspn(tasks[count].description, "\n")] = '\0'; // enlever \n

        token = strtok(NULL, "|");
        if (!token) continue;
        tasks[count].priority = atoi(token);

        token = strtok(NULL, "|");
        if (!token) continue;
        tasks[count].done = atoi(token);

        count++;
    }
    fclose(f);
    return count;
}
