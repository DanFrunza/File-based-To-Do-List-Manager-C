#ifndef TASK_MANAGER
#define TASK_MANAGER

typedef struct{
    int id;
    char description[50];
    char deadline[20];      //DD-MM-YYYY
    int completed;          // 0 = incomplet, 1 = complet
}Task;

void addTask(Task** tasks, int* countIDs, int* countTasks, char* name, char* deadline);
void showTask(Task** tasks, int* countTasks);
void deleteTask(Task** tasks, int* countTasks, int id);
void toggleTaskCompletion(Task** tasks, int* countTasks, int id);
void saveTasksToFile(Task** tasks, int* countTasks, const char* filename);
void loadTasksFromFile(Task** tasks, int* countIDs, int* countTasks, const char* filename);







#endif