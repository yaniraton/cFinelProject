#ifndef LINKEDLISTH
#define LINKEDLISTH

#define FALSE 0
#define TRUE !FALSE
#define MAX_STRING 50



// Frame struct
typedef struct Frame
{
	char name[MAX_STRING];
	unsigned int duration;
	char path[MAX_STRING];  
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;


Frame* createFrame(char* name, unsigned int duration, char* path);
FrameNode* createFrameNode(Frame* frame);
int isFrameExist(FrameNode* head, char* name);
void addFrame(FrameNode** head, FrameNode* newFrame);
void freeFrame(FrameNode* frame);
void deleteFrame(FrameNode** head, char* name);
void switchFrames(FrameNode** head, char* name, int indexToMoveTo);
FrameNode* getFrame(FrameNode* head, int index);
void printList(FrameNode* head);
void freeList(FrameNode* head);
void changeFrameDuration(FrameNode* head, char* name, int newDuration);
void changeAllFramesDuration(FrameNode* head, int newDuration);
void printFullList(FrameNode* head);
void moveFrame(FrameNode** head, char* name, int indexToMoveTo);


#endif