/*********************************
* Class: MAGSHIMIM C2			 *
* openCV template      			 *
**********************************/
#define _CRT_SECURE_NO_WARNINGS
#define CV_IGNORE_DEBUG_BUILD_GUARD
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedList.h"
#include "files.h"


#define MAX_STRING 50


void myFgets(char str[], int n);
void printMenu();
void action(int userCoice, FrameNode** head);
void getFrameInfo(char* fileName, int* duration, char* path, FrameNode* head);

int main(void)
{

    // create the head of the linked list and the user choice variables
    FrameNode* head = NULL;
    int userCoice = -1;

    // print the welcome message and ask the user if he wants to load a project or create a new one
    printf("Welcome to Magshimim Movie Maker! what would you like to do?\n");
    printf("  [0] create new project\n");
    printf("  [1] load project\n");
    scanf("%d", &userCoice);
    getchar();


    // if the user wants to load a project
    if(userCoice == 1){
        char filePath[MAX_STRING];
        printf("Enter file path of the project(include the file name): ");
        myFgets(filePath, MAX_STRING);
        lodeProject(&head, filePath);
    }

    printf("\n");

    // main loop of the program that print the menu and calls the right functions
    while (userCoice != 0)
    {
        // manu printing and user input
        printMenu();
        scanf("%d",&userCoice);
        getchar();

        // call the right function
        action(userCoice, &head);
    }
    getchar();
    return 0;
}


/* Function that performs the fgets command and also removes the newline
   that might be at the ned of the string.
 * input: the array to input to, and the number of chars to input.
 * output: none.
 * time complexity: O(n)
 * where n is the number of chars to input because the function goes over all the chars in the string
 */
void myFgets(char str[], int n)
{
    fgets(str, n, stdin);
    str[strcspn(str, "\n")] = 0;
}

/**
 * Function that prints the menu
 * input: none
 * output: none
 * time complexity: O(1)
 * because the function prints the menu and it doesn't depend on any input and has a number of operations
*/
void printMenu() {
    printf(" What would you like to do?\n");
    printf("  [0] Exit\n");
    printf("  [1] Add new Frame\n");
    printf("  [2] Remove a Frame\n");
    printf("  [3] Change frame index\n");
    printf("  [4] Change frame duration\n");
    printf("  [5] Change duration of all frames\n");
    printf("  [6] List frames\n");
    printf("  [7] Play movie!\n");
    printf("  [8] Save project\n");
}


/**
 * this function is responsible for doing all the havy lifting by calling the right functions for user choice
 * input: the user choice and the head of the linked list
 * output: none
*/
void action(int userCoice, FrameNode** head) {
    if (userCoice == 1)
    {
        printf("*** Create new frame ***\n");
        // create the new variables for the frame
        char fileName[MAX_STRING];
        int duration = 0;
        char path[MAX_STRING];

        // get the frame info from the user
        getFrameInfo(fileName, &duration, path, *head);

        if(isFileExist(fileName))
        {
            printf("File already exists\n");
            return;
        }

        // create the new frame
        Frame* newFrame = createFrame(fileName, duration, path);

        // create the new node
        FrameNode* newNode = createFrameNode(newFrame);

        // add the new node to the list
        addFrame(head, newNode);      
    }
    else if (userCoice == 2)
    {
        // get the name of the frame to remove
        char fileName[MAX_STRING];
        printf("Enter frame name: \n");

        // get the name from the user and remove the frame
        myFgets(fileName, MAX_STRING);
        deleteFrame(head, fileName);
        
    }
    else if (userCoice == 3)
    {
        printf("change frame index\n");
        // get the name of the frame to move and the new index
        char fileName[MAX_STRING];
        int index = 0;
        printf("Enter frame name: \n");
        myFgets(fileName, MAX_STRING);
        printf("Enter new index: \n");
        scanf("%d", &index);
        getchar();

        // move the frame
        moveFrame(head, fileName, index);

    }
    else if (userCoice == 4)
    {
        // get the name of the frame to change
        printf("Enter frame name: \n");
        char fileName[MAX_STRING];
        myFgets(fileName, MAX_STRING);

        // get the new duration
        int newDuration = 0;
        printf("Enter new duration: \n");
        scanf("%d", &newDuration);
        getchar();

        // change the duration
        changeFrameDuration(*head, fileName, newDuration);

    }
    else if (userCoice == 5)
    {
        // get the new duration
        printf("Enter new duration: \n");
        int newDuration = 0;
        scanf("%d", &newDuration);
        getchar();

        // change the duration of all the frames
        changeAllFramesDuration(*head, newDuration);
    }
    else if (userCoice == 6)
    {
        printf("list frames\n");

        // print the list
        printFullList(*head);
    }
    else if (userCoice == 7)
    {
        printf("play movie\n");
    }
    else if (userCoice == 8)
    {
        char filePath[MAX_STRING];
        printf("Where would you like to save the project? (include the file name): ");
        myFgets(filePath, MAX_STRING);
        saveProject(*head, filePath);
    }
    else if (userCoice == 0)
    {
        printf("bye bye\n");
        // free the list
        freeList(*head);
        
    }
    else if (userCoice == 9)
    {
        printf("debug\n");
        printList(*head);
    }
    else
    {
        printf("invalid input\n");
    }

    printf("\n");
}


/**
 * Function that gets the frame info from the user
 * input: the frame name, duration, path and the head of the linked list
 * output: none
 * time complexity: O(n)
 * because we need to check if the frame name already exists so the worst case is that we need to go through the whole list
*/
void getFrameInfo(char* fileName, int* duration, char* path, FrameNode* head) {
    printf("Enter frame path: \n");
    myFgets(path, MAX_STRING);
    printf("Enter frame duration: \n");
    scanf("%d", duration);
    getchar();
    printf("Enter frame name: \n");
    myFgets(fileName, MAX_STRING);
    while (isFrameExist(head, fileName) != -1)
    {
        printf("Frame already exists, please enter a different name: \n");
        myFgets(fileName, MAX_STRING);
    }
}
