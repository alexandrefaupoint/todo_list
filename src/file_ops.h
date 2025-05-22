#ifndef FILE_OPS_H
#define FILE_OPS_H

#include "task.h"

int save_tasks(const char* filename, Task* tasks, int count);
int load_tasks(const char* filename, Task* tasks, int max_tasks);

#endif