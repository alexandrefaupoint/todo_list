#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"
#include "file_ops.h"

#define MAX_TASKS 100

void print_menu() {
    printf("\n-- TODO LIST --\n");
    printf("1. Ajouter une tâche\n");
    printf("2. Lister les tâches\n");
    printf("3. Marquer tâche comme terminée\n");
    printf("4. Supprimer une tâche\n");
    printf("5. Sauvegarder\n");
    printf("6. Charger\n");
    printf("0. Quitter\n");
    printf("Choix: ");
}

int main() {
    Task tasks[MAX_TASKS];
    int task_count = 0;
    int next_id = 1;
    char input[256];

    while (1) {
        print_menu();
        if (!fgets(input, sizeof(input), stdin)) break;
        int choice = atoi(input);

        switch (choice) {
            case 1: // Ajouter
                if (task_count >= MAX_TASKS) {
                    printf("Liste pleine!\n");
                    break;
                }
                printf("Description: ");
                if (!fgets(tasks[task_count].description, MAX_DESC, stdin)) break;
                tasks[task_count].description[strcspn(tasks[task_count].description, "\n")] = '\0';

                printf("Priorité (1=haute, 2=moyenne, 3=basse): ");
                if (!fgets(input, sizeof(input), stdin)) break;
                tasks[task_count].priority = atoi(input);

                tasks[task_count].id = next_id++;
                tasks[task_count].done = 0;

                task_count++;
                printf("Tâche ajoutée.\n");
                break;

            case 2: // Lister
                for (int i = 0; i < task_count; i++) {
                    print_task(&tasks[i]);
                }
                break;

            case 3: // Marquer terminée
                printf("ID de la tâche à marquer comme terminée: ");
                if (!fgets(input, sizeof(input), stdin)) break;
                {
                    int id = atoi(input);
                    int found = 0;
                    for (int i = 0; i < task_count; i++) {
                        if (tasks[i].id == id) {
                            tasks[i].done = 1;
                            found = 1;
                            printf("Tâche marquée comme terminée.\n");
                            break;
                        }
                    }
                    if (!found) printf("Tâche non trouvée.\n");
                }
                break;

            case 4: // Supprimer
                printf("ID de la tâche à supprimer: ");
                if (!fgets(input, sizeof(input), stdin)) break;
                {
                    int id = atoi(input);
                    int found = 0;
                    for (int i = 0; i < task_count; i++) {
                        if (tasks[i].id == id) {
                            // Décaler vers la gauche pour supprimer
                            for (int j = i; j < task_count - 1; j++) {
                                tasks[j] = tasks[j + 1];
                            }
                            task_count--;
                            found = 1;
                            printf("Tâche supprimée.\n");
                            break;
                        }
                    }
                    if (!found) printf("Tâche non trouvée.\n");
                }
                break;

            case 5: // Sauvegarder
                if (save_tasks("tasks.txt", tasks, task_count) == 0) {
                    printf("Sauvegarde réussie.\n");
                } else {
                    printf("Erreur lors de la sauvegarde.\n");
                }
                break;

            case 6: // Charger
                {
                    int loaded = load_tasks("tasks.txt", tasks, MAX_TASKS);
                    if (loaded >= 0) {
                        task_count = loaded;
                        // Mettre à jour next_id
                        next_id = 1;
                        for (int i = 0; i < task_count; i++) {
                            if (tasks[i].id >= next_id) next_id = tasks[i].id + 1;
                        }
                        printf("Chargement réussi.\n");
                    } else {
                        printf("Erreur lors du chargement.\n");
                    }
                }
                break;

            case 0:
                printf("Au revoir!\n");
                exit(0);

            default:
                printf("Choix invalide.\n");
        }
    }

    return 0;
}
