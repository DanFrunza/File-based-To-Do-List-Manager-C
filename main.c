#include <stdio.h>
#include <stdlib.h>
#include "task-manager.h"


int main()
{
    Task* tasks = NULL;
    free(tasks);
    tasks = NULL;
    int countIDs = 0;
    int countTasks = 0;

    loadTasksFromFile(&tasks, &countIDs, &countTasks, "tasks.txt");
    showTask(&tasks, &countTasks);

    int a=1;
    while (a) {
        int b = 0;
        printf("\nYou want to add a task? (0 - No, 1 - Yes)\n");
        scanf("%d", &b);
        
        while (b) {
            char description[30];
            printf("Task description? ");
            scanf("%s", description);

            char data[20];
            printf("The deadline? (DD-MM-YYYY) ");
            scanf("%s", data);

            addTask(&tasks, &countIDs, &countTasks, description, data);
            showTask(&tasks, &countTasks);
            
            printf("\nYou want to add another task? (0 - No, 1 - Yes)\n");
            scanf("%d", &b);
        }

        // Proces pentru ștergerea unui task
        b = 0;
        printf("\nYou want to delete a task? (0 - No, 1 - Yes)\n");
        scanf("%d", &b);
        
        while (b) {
            int id;
            printf("The id of the task you want to delete: ");
            scanf("%d", &id);
            deleteTask(&tasks, &countTasks, id);
            showTask(&tasks, &countTasks);

            printf("\nYou want to delete another task? (0 - No, 1 - Yes)\n");
            scanf("%d", &b);
        }

        // Proces pentru modificarea statusului unui task
        b = 0;
        printf("\nYou want to modify the status of a task? (0 - No, 1 - Yes)\n");
        scanf("%d", &b);
        
        while (b) {
            int id;
            printf("The id of the task you want to modify the status: ");
            scanf("%d", &id);
            toggleTaskCompletion(&tasks, &countTasks, id);
            showTask(&tasks, &countTasks);

            printf("\nYou want to modify the status of another task? (0 - No, 1 - Yes)\n");
            scanf("%d", &b);
        }

        // Întreabă utilizatorul dacă dorește să revină la început
        printf("\nYou want to retake the process? (0 - No, 1 - Yes)\n");
        scanf("%d", &a);
    }

    saveTasksToFile(&tasks, &countTasks, "tasks.txt");

    free(tasks);
    tasks = NULL;
    return 0;
}