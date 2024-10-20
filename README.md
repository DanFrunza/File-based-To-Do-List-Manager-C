# Task Manager
# Description:
This program is a simple command-line task manager where users can add, delete, update, and view tasks. Each task has an ID, description, deadline, and completion status. The tasks are stored in a file, and the program allows users to interact with tasks, save the changes back to the file, and load tasks from the file when restarting the program.

# Features:
Add Task: Users can add new tasks by providing a description and a deadline.
Delete Task: Users can delete tasks by providing the ID of the task.
Toggle Task Completion: Users can toggle the status of a task (complete/incomplete) by providing the task ID.
Save Tasks: The current tasks are saved to a file.
Load Tasks: The program loads the tasks from the file upon start.
Show Tasks: Display all tasks in a formatted table.

# Code Breakdown:
1. addTask Function:
Adds a new task to the list, reallocates memory to hold the new task, and assigns an incremental ID.
Sets the description, deadline, and marks the task as incomplete.
Increments the task counter (countTasks) and the ID counter (countIDs).
2. showTask Function:
Displays all the tasks in a neatly formatted table.
Iterates through the list of tasks and prints the task ID, description, deadline, and completion status (Yes/No).
3. deleteTask Function:
Deletes a task by ID, shifts the remaining tasks up in the list, and reallocates memory to shrink the list.
If there are no tasks left, it frees the memory and sets the task pointer to NULL.
4. toggleTaskCompletion Function:
Modifies the completion status of a task. If the task is incomplete, it marks it as complete, and vice versa.
The task is identified by its ID.
5. saveTasksToFile Function:
Writes the current tasks into a file in a formatted manner.
Each task is saved with its ID, description, deadline, and completion status.
6. loadTasksFromFile Function:
Reads the tasks from a file and loads them into memory.
Skips the header and delimiter lines using a helper function isDelimiterLine().
Each valid task line is parsed and stored in the task list.
7. Memory Management:
Memory is dynamically allocated using malloc() and realloc() to handle a flexible number of tasks.
The program ensures that memory is freed after usage to prevent memory leaks.
8. Task Formatting:
Tasks are printed and saved in a neat table format with fixed column widths to ensure readability.

# How to Run:
Compilation: Compile the program using a C compiler. For example:
Copy the files in VS Code and run in terminal this commands

For compiling:
gcc main.c task-manager.c -o program

For running:
.\program.exe


# Interaction:
Follow the prompts to add, delete, or modify tasks.
After interacting with the tasks, the task will be saved automatically, rewriting the tasks.txt file.

# File Persistence:
Tasks are stored in a file called tasks.txt.
When you rerun the program, tasks from this file are automatically loaded.

# File format
________________________Tasks________________________
|----|---------------------|------------|-----------|
| Id |     Description     |    Date    | Completed |
|----|---------------------|------------|-----------|
|   0|      DescriptionHere|  DD-MM-YYYY|        Yes|
|----|---------------------|------------|-----------|

# Example Interaction:
You want to add a task? (0 - No, 1 - Yes)
1
Task description? Project
The deadline? (DD-MM-YYYY) 30-10-2024
The task with the id 0 was added successfully.
________________________Tasks________________________
|----|---------------------|------------|-----------|
| Id |     Description     |    Date    | Completed |
|----|---------------------|------------|-----------|
|   0|              Project|  30-10-2024|         No|
|----|---------------------|------------|-----------|
