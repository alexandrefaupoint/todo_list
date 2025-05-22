#include <stdio.h>
#include "task.h"

void print_task(const Task* t) {
    printf("[%d] %s (Priorité: %d) - %s\n",
           t->id, t->description, t->priority,
           t->done ? "Terminée" : "En cours");
}