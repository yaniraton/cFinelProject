#ifndef FILESH
#define FILESH

#define FALSE 0
#define TRUE !FALSE
#define MAX_STRING 50

#include <string.h>
#include <stdlib.h>
#include "linkedList.h"

void lodeProject(FrameNode** head, char* filePath);
void saveProject(FrameNode* head, char* projectName);
FILE* createSaveFile(char* projectName);
int isFileExist(char* fileName);
char* intToString(int num);
char readUntil(FILE* file, char* str, char stopChar);

#endif