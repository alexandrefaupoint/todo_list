#ifndef TASK_H
#define TASK_H

#define MAX_DESC 256

typedef struct {
    int id;
    char description[MAX_DESC];
    int priority; // 1 = haute, 2 = moyenne, 3 = basse
    int done;     // 0 = non fait, 1 = fait
} Task;

void print_task(const Task* t);

#endif