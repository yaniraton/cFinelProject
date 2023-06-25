/*********************************
* Class: MAGSHIMIM Final Project *
* Files mengment			 	 *
**********************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "files.h"
#include "linkedList.h"

/**
 * this function lodes the project from a file
 * input: the head of the linked list, and the file path
 * output: none
 * time complexity: O(n)
 * where n is the number of frames in the file because the function goes over all the frames in the file and creates them
*/
void lodeProject(FrameNode** head, char* filePath){
    FILE* saveFile = fopen(filePath, "r");
    if (saveFile == NULL)
    {
        printf("File not found\n");
        return;
    }

    char name[MAX_STRING];
    char path[MAX_STRING];
    char duration[MAX_STRING];


    // read the file by parts using readUntil function
    while (readUntil(saveFile, name, ' ') != EOF)
    {
        readUntil(saveFile, path, ' ');
        readUntil(saveFile, duration, '\n');

        // create the frame
        Frame* frame = createFrame(name, atoi(duration), path);

        // create the frame node
        FrameNode* frameNode = createFrameNode(frame);

        // add the frame to the list
        addFrame(head, frameNode);
    }

    

    fclose(saveFile);
    printf("File was loaded\n");
}

/**
 * Function that saves the project to a file
 * input: the head of the linked list, and the file path
 * output: none
 * time complexity: O(n)
 * where n is the number of frames in the list because the function goes over all the frames in the list 
*/
void saveProject(FrameNode* head, char* filePath)
{
    // create the save file
    FILE* saveFile = createSaveFile(filePath);

    // if the file is null, it means the user didn't want to override the file
    if (saveFile == NULL)
    {
        return;
    }

    // write the frames to the file
    FrameNode* currentFrame = head;
    char* num;
    while (currentFrame != NULL)
    {
        // write the frame info to the file
        num = intToString(currentFrame->frame->duration);
        fputs(currentFrame->frame->name, saveFile);
        fputs(" ", saveFile);
        fputs(currentFrame->frame->path, saveFile);
        fputs(" ", saveFile);
        fputs(num, saveFile);
        fputs("\n", saveFile);
        free(num);

        currentFrame = currentFrame->next;
    }

    // inform the user that the file was saved
    printf("File was saved\n");


    // close the file
    fclose(saveFile);
}


/**
 * Function that creates a new save file
 * input: the file path
 * output: a pointer to the file
 * time complexity: O(1)
 * because the function has a constant number of operations
*/
FILE* createSaveFile(char* filePath)
{
    //check if the file exists
    if (isFileExist(filePath))
    {
        // inform the user that the file exists and ask if he wants to override it
        printf("File already exists\n");
        printf("Do you want to override it? (y/n)\n");

        // get the user's choice
        char userChoice;
        scanf("%c", &userChoice);
        getchar();

        // if the user wants to not override the file, return null
        if (userChoice == 'n')
        {
            printf("File was not saved\n");
            return NULL;
        }
    }

    // Create the file
    FILE* saveFile = fopen(filePath, "w");
    if (saveFile == NULL)
    {
        printf("Error opening file!\n");
        return NULL;
    }

    // inform the user that the file was saved
    printf("File was saved\n");

    // return the file
    return saveFile;
}



/**
 * Function that checks if a file exists
 * input: the file name
 * output: 1 if the file exists, 0 otherwise
 * time complexity: O(1)
 * because the function has a constant number of operations
*/
int isFileExist(char* fileName) {

    // try to open the file
    FILE* file = fopen(fileName, "r");

    // if the file is null, it means it doesn't exist
    if (file == NULL)
    {
        return FALSE;
    }
    fclose(file);
    return TRUE;
}


/**
 * Function that converts an int to a string
 * input: the number
 * output: the string
 * time complexity: O(n)
 * where n is the number of digits in the number
*/
char* intToString(int num)
{
    char* str = (char*)malloc(sizeof(char) * MAX_STRING);
    // go number by number and add it to the string
    int i = 0; // the index of the string, will be the length of the string
    while (num != 0)
    {
        // add the number to the string
        str[i] = (char)(num % 10 + '0');
        num /= 10;
        i++;
    }
    // invert the string because it was created backwards (from the last digit to the first)
    int j = 0;
    char temp;
    while (j < i / 2)
    {
        // swap the chars 
        temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
        j++;
    }
    return str;
}


/**
 * this function converts a string to an int
 * input: the string
 * output: the number
 * time complexity: O(n)
 * where n is the length of the string
*/
int stringToInt(char* str)
{
    int num = 0;
    int i = 0;
    while (str[i] != '\0')
    {
        num *= 10;
        num += str[i] - '0';
        i++;
    }
    return num;
}


/**
 * Function that reads from a file until a stop char is reached
 * input: the file, the string to read to, and the stop char
 * output: the stop char
 * time complexity: O(n) 
 * where n is the length of the string or until the stop char is reached
*/
char readUntil(FILE* file, char* str, char stopChar)
{

    // declare the variables to read the file
    char ch;
    int i = 0;


    // read the file until the stop char is reached or the string is full(MAX_STRING)
    while (((ch = (char)fgetc(file)) != stopChar) && i < MAX_STRING - 1 && ch != EOF)
    {
        str[i] = ch;
        i++;
    }

    // add the null char to the end of the string
    str[i] = '\0';

    // return the stop char or EOF in case the file ended
    return ch;
}