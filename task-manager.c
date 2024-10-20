#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "task-manager.h"

//--------------------AddTask--------------------
void addTask(Task** tasks, int* countIDs, int* countTasks, char* description, char* deadline)
{
    *tasks = realloc(*tasks, (*countTasks + 1) * sizeof(Task));
    if(*tasks == NULL)
    {
        printf("\nMemory allocation failed!\n");
        return;
    }

    (*tasks)[*countTasks].id = *countIDs;
    strcpy((*tasks)[*countTasks].description, description);
    strcpy((*tasks)[*countTasks].deadline, deadline);
    (*tasks)[*countTasks].completed = 0;

    printf("\nThe task with the id %d was added succsesfully.\n", *countIDs);

    //Incrementare 
    (*countIDs)++ ;
    (*countTasks)++ ;
    
}





//--------------------ShowTask--------------------
void showTask(Task** tasks, int* countTasks)
{
    if(*tasks == NULL)
    {
        printf("\nNothing to show.");
        return;
    }

    printf("\n________________________Tasks________________________");
    printf("\n|----|---------------------|------------|-----------|");
    printf("\n| Id |     Description     |    Date    | Completed |");
    printf("\n|----|---------------------|------------|-----------|");
                                                      
    for(int i = 0; i < *countTasks ; i++)
    {
        char c[10];
        if((*tasks)[i].completed == 0)strcpy(c,"No");
        else strcpy(c,"Yes");
        printf("\n|%4d|%21s|%12s|%11s|", (*tasks)[i].id, (*tasks)[i].description, (*tasks)[i].deadline, c);
        printf("\n|----|---------------------|------------|-----------|");
    }
}




//--------------------DeleteTask--------------------
void deleteTask(Task** tasks, int* countTasks, int id)
{
    if(*tasks == NULL || *countTasks == 0)
    {
        printf("\nNothing to delete\n");
        return;
    }

    int found = 0;
    for(int i = 0; i < *countTasks; i++)
    {
        if((*tasks)[i].id == id)
        {
            found = 1;
            for(int j = i; j < *countTasks - 1; j++)
            {
                (*tasks)[j] = (*tasks)[j+1];
            }
            (*countTasks)-- ;
            break;
        }
    }

    if(found)
    {
        if(*countTasks > 0)
        {
            *tasks = realloc(*tasks, (*countTasks + 1) * sizeof(Task));
            if(*tasks == NULL)
            {
            printf("\nMemory allocation failed!\n");
            return;
            }
            printf("\nThe task with the id %d was deleted.\n", id);
        }
        else
        {
            free(*tasks);
            *tasks = NULL;
        }
        
    }
    else
    {
        printf("\nThe task with the id %d not found.", id);
    }

}



//--------------------ToggleTaskCompletion--------------------
void toggleTaskCompletion(Task** tasks, int* countTasks, int id)
{
    if(*tasks == NULL || *countTasks ==0)
    {
        printf("Nothing to modify.");
        return;
    }

    int found = 0;

    for(int i = 0; i < *countTasks; i++)
    {
        if((*tasks)[i].id == id)
        {
            found = 1;
            
            if((*tasks)[i].completed == 1)(*tasks)[i].completed = 0;
            else (*tasks)[i].completed = 1;

            printf("\nThe completion status of the task with the id %d was toggled.\n", id);
            return;
        }
    }

    if(!found)
    {
        printf("\nThe task with the id %d was not found.\n", id);
    }

}



//--------------------SaveTaskstoFile--------------------
void saveTasksToFile(Task** tasks, int* countTasks, const char* filename)
{
    if(*tasks == NULL || *countTasks == 0)
    {
        printf("\nNothing to save.");
        return;
    }

    FILE* file = fopen(filename, "w");
    if(file == NULL)
    {
        printf("\nFailed to open the file for writing.\n");
        return;
    }

    fprintf(file, "\n________________________Tasks________________________");
    fprintf(file, "\n|----|---------------------|------------|-----------|");
    fprintf(file, "\n| Id |     Description     |    Date    | Completed |");
    fprintf(file, "\n|----|---------------------|------------|-----------|");
    for(int i = 0; i < *countTasks ; i++)
    {
        char c[10];
        if((*tasks)[i].completed == 0)strcpy(c,"No");
        else strcpy(c,"Yes");
        fprintf(file, "\n|%4d|%21s|%12s|%11s|", (*tasks)[i].id, (*tasks)[i].description, (*tasks)[i].deadline, c);
        fprintf(file, "\n|----|---------------------|------------|-----------|");
    }

    fclose(file);
    printf("\nTasks saved to %s successfully.\n", filename);
    
}



//--------------------LoadTasksFromFile--------------------

// Trim
void trim(char* str)
{
    int i;
    for (i = strlen(str) - 1; i >= 0 && isspace(str[i]); i--) {
        str[i] = '\0';
    }
}

//Jump over the delimiter lines
int isDelimiterLine(const char* line)
 {
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] != '-' && line[i] != '|' && isspace(line[i]) == 0) {
            return 0; //Not delimiter
        }
    }
    return 1; //Delimiter
}

void loadTasksFromFile(Task** tasks, int* countIDs, int* countTasks, const char* filename)
{
    // clear tasks
    if (*tasks != NULL) {
        free(*tasks);
        *tasks = NULL; 
        *countTasks = 0; 
        *countIDs = 0;   
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("\nFailed to open the file for reading.\n");
        return;
    }

    char buffer[256]; // Buffer to hold each line
    // Skip header lines
    for (int i = 0; i < 5; i++) {
        fgets(buffer, sizeof(buffer), file);
    }

    // Read tasks from the file
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        //Trim
        trim(buffer);

        //Check delimiters
        if (isDelimiterLine(buffer)) {
            continue; //skip
        }

        Task newTask;
        char completed[4];

        // Parse the line
        if (sscanf(buffer, "| %d|%49[^|]|%19[^|]|%3s|", &newTask.id, newTask.description, newTask.deadline, completed) == 4) {
            // Convert the completed string to int
            newTask.completed = (strcmp(completed, "Yes") == 0) ? 1 : 0;

            // Add the task to the list
            *tasks = realloc(*tasks, (*countTasks + 1) * sizeof(Task));
            if (*tasks == NULL)
            {
                printf("\nMemory allocation failed!\n");
                fclose(file);
                return;
            }

            (*tasks)[*countTasks] = newTask;
            (*countTasks)++;
            //The Id should be the last
            *countIDs = (newTask.id >= *countIDs) ? newTask.id + 1 : *countIDs; // Update countIDs if needed
        }
    }

    fclose(file);
    printf("\nTasks loaded from %s successfully.\n", filename);
}

