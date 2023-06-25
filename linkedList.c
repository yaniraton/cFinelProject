/*********************************
* Class: MAGSHIMIM Final Project *
* Link lists				 	 *
**********************************/
#include "linkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * this function creates a new frame with the given parameters - name, duration and path
 * input: name - the name of the frame, duration - the duration of the frame in milisecends, path - the path of the frame
 * output: the new frame
 * time complexity: O(1)
 * because the function only creates a new frame and returns it
*/
Frame* createFrame(char* name, unsigned int duration, char* path) {
    // create a new frame and return it
    Frame* newFrame = (Frame*)malloc(sizeof(Frame));
    strcpy(newFrame->name, name);
    newFrame->duration = duration;
    strcpy(newFrame->path, path);
    return newFrame;
}


/**
 * this function gets a frame and creates a new frameNode theat points to null
 * input: frame - the frame to create a node for
 * output: the new node
 * time complexity: O(1)
 * because the function only creates a new frame node and returns it
*/
FrameNode* createFrameNode(Frame* frame) {
    FrameNode* newNode = (FrameNode*)malloc(sizeof(FrameNode));
    newNode->frame = frame;
    newNode->next = NULL;
    return newNode;
}


/**
 * this function gets a head and a name and checks if the frame with the given name exists in the list and if it is it will return his index
 * input: head - the head of the list, name - the name of the frame to check
 * output: the index of the frame if it exists, -1 if it doesn't
 * time complexity: O(n)
 * where n is the number of frames in the list because the function goes over all the frames in the list
*/
int isFrameExist(FrameNode* head, char* name) {

    // create a temp node to iterate over the list and an index to return
    FrameNode* temp = head;
    int index = 0;

    // iterate over the list and check if the frame exists
    while (temp) {
        if (strcmp(temp->frame->name, name) == 0) {
            return index;
        }
        index++;
        temp = temp->next;
    }

    // if the frame dosent exists return -1
    return -1;
}


/**
 * this function gets a pointer to the head of the list and a new frame and adds the frame to the end of the list
 * input: head - a pointer to the head of the list, newFrame - the frame to add to the list
 * output: none
 * time complexity: O(n)
 * where n is the number of frames in the list because the function goes over all the frames in the list
*/
void addFrame(FrameNode** head, FrameNode* newFrame) {
    // check if the head is null
    if (*head == NULL) {
        *head = newFrame;
        return;
    }

    // create a temp node to iterate over the list
    FrameNode* temp = *head;

    // iterate over the list and add the frame to the end of the list
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newFrame;
}

/**
 * this function gets a frameNode and frees all the memory of the frame and the node
 * input: frame - the frameNode to free
 * output: none
 * time complexity: O(1)
 * because the function only frees the memory of the frame and the node
*/
void freeFrame(FrameNode* frame) {
    
    // free all the memory of the frame that is denmicly allocated
    free(frame->frame);
    printf("frame freed\n");

    // free the node
    free(frame);
}


/**
 * this function gets a pointer to the head and a name of a frame and deletes the frame from the list
 * it check if the frame is exsits with the isFrameExist function and if it dosent it prints the an error messege
 * input: head - pointer to the head of the list, name - the name of the frame to delete
 * output: none
 * time complexity: O(n)
 * where n is the number of frames in the list because the function goes over all the frames in the list
*/
void deleteFrame(FrameNode** head, char* name) {
        
        // create a temp node to iterate over the list and a prev node to keep the previus node
        FrameNode* temp = *head;
        FrameNode* prev = NULL;
    
        // check if the frame exists
        int frameIndex = isFrameExist(*head, name);
        if (frameIndex == -1) {
            printf("The frame %s dosent exists\n", name);
            return;
        }
    
        // iterate over the list and delete the frame
        int i = 0;
        while (temp) {
    
            // if the frame is in the right index delete it
            if (i == frameIndex) {
                if (prev == NULL) {
                    *head = (*head)->next;
                }
                else {
                    prev->next = temp->next;
                }
                freeFrame(temp);
                return;
            }
    
            // go to the next node
            prev = temp;
            temp = temp->next;
            i++;
        }
}

/**
 * this function gets a pointer to the head and a name of a frame and a index to move the frame to
 * the index starts from 1
 * for example: if the list is: 1, 2, 3, 4, 5 and we want to move the frame with the name 3 to the index 2
 * the list will be: 1, 3, 2, 4, 5
 * it will switch the frame with the given name to the given index
 * input: head - pointer to the head of the list, name - the name of the frame to move, indexToMoveTo - the index to move the frame to
 * output: none
 * time complexity: O(n)
 * where n is the number of frames in the list because the function goes over all the frames in the list
*/
void switchFrames(FrameNode** head, char* name, int indexToMoveTo) {

    // handle edge cases

    // check if the list is empty
    
    if (*head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    int frameIndex = isFrameExist(*head, name);

    // check if the frame exists
    if (frameIndex == -1) {
        printf("The frame '%s' does not exist in the list.\n", name);
        return;
    }

    int listLength = 0;
    FrameNode* current = *head;
    
    while (current != NULL) {
        listLength++;
        current = current->next;
    }

    // check if the index to move to is valid
    if (indexToMoveTo > listLength || indexToMoveTo < 0) {
        printf("Invalid index to move to.\n");
        return;
    }

    // check if the frame is already in the right position
    if (frameIndex == indexToMoveTo -1) {
        printf("The frame is already at the right position.\n");
        return;
    }


    // strat the switch

    // create pointers to the frames to move and the frames to move to
    FrameNode* frameToMove = getFrame(*head, frameIndex); //frameToMove
    FrameNode* prevFrameToMove = getFrame(*head, frameIndex - 1); //prevFrameToMove
    FrameNode* frameToMoveTo = getFrame(*head, indexToMoveTo - 1); //frameToMoveTo 
    FrameNode* prevframeToMoveTo = getFrame(*head, indexToMoveTo - 2); //prevframeToMoveTo
    FrameNode* temp = NULL;
    printf("indexToMoveTo: %d\n", indexToMoveTo);
    printf("frameIndex: %d\n", frameIndex);


    current = NULL;

    // if frameToMove is the head
    if (prevFrameToMove == NULL) {
        current = frameToMove->next;
        frameToMove->next = frameToMoveTo->next;
        frameToMoveTo->next = current;
        prevframeToMoveTo->next = frameToMove;
        *head = frameToMoveTo;
    }
    // if frameToMoveTo is the head
    else if (prevframeToMoveTo == NULL) {
        current = frameToMove->next;
        frameToMove->next = frameToMoveTo->next;
        frameToMoveTo->next = current;
        prevFrameToMove->next = frameToMoveTo;
        *head = frameToMove;
    }
    // if frameToMoveTo is right after frameToMove
    else if (indexToMoveTo == frameIndex){
        frameToMoveTo->next = frameToMove->next;
        frameToMove->next = frameToMoveTo;
        prevframeToMoveTo->next = frameToMove;
    }
    // if frameToMove is right before frameToMoveTo
    else if (indexToMoveTo == frameIndex + 2) {
        frameToMove->next = frameToMoveTo->next;
        frameToMoveTo->next = frameToMove;
        prevFrameToMove->next = frameToMoveTo;
    }
    else {
        current = frameToMove->next;
        frameToMove->next = frameToMoveTo->next;
        frameToMoveTo->next = current;
        prevFrameToMove->next = frameToMoveTo;
        prevframeToMoveTo->next = frameToMove;
    }
    

}

/**
 * this function gets a pointer to the head and a name of a frame and a index to move the frame to
 * the funcsion will move the frame with the given name to the given index
 * and push all the frames that were in the index to the right
 * input: head - pointer to the head of the list, name - the name of the frame to move, indexToMoveTo - the index to move the frame to
 * output: none
 * time complexity: O(n)
 * where n is the number of frames in the list because the function goes over all the frames in the list
*/
void moveFrame(FrameNode** head, char* name, int indexToMoveTo) {
    
        // handle edge cases
    
        // check if the list is empty
        
        if (*head == NULL) {
            printf("The list is empty.\n");
            return;
        }
    
        int frameIndex = isFrameExist(*head, name);
    
        // check if the frame exists
        if (frameIndex == -1) {
            printf("The frame '%s' does not exist in the list.\n", name);
            return;
        }
    
        int listLength = 0;
        FrameNode* current = *head;
        
        while (current != NULL) {
            listLength++;
            current = current->next;
        }
    
        // check if the index to move to is valid
        if (indexToMoveTo > listLength || indexToMoveTo < 0) {
            printf("Invalid index to move to.\n");
            return;
        }
    
        // check if the frame is already in the right position
        if (frameIndex == indexToMoveTo -1) {
            printf("The frame is already at the right position.\n");
            return;
        }

        // create a copy of the frame to move
        FrameNode* frameToMove = getFrame(*head, frameIndex);
        FrameNode* frameToMoveCopy = createFrameNode(createFrame(frameToMove->frame->name, frameToMove->frame->duration, frameToMove->frame->path));


        // remove the frame from the list
        deleteFrame(head, name);

        // add the frame to the list in the right position
        FrameNode* frameBefore = getFrame(*head, indexToMoveTo-2);
        FrameNode* frameAfter = getFrame(*head, indexToMoveTo-1);

        // add the frameToMoveCopy between the frame before and the frame after
        if (frameBefore == NULL) {
            frameToMoveCopy->next = *head;
            *head = frameToMoveCopy;
        }
        else {
            frameBefore->next = frameToMoveCopy;
            frameToMoveCopy->next = frameAfter;
        }
        printList(*head);
}



/**
 * this function gets a pointer to the head and a index and returns the frame in the given index
 * input: head - pointer to the head of the list, index - the index of the frame to return
 * output: the frame in the given index
 * time complexity: O(n)
 * where n is the number of frames in the list because the function goes over all the frames in the list
*/
FrameNode* getFrame(FrameNode* head, int index) {

    // check if the list is empty
    if (index < 0) {
        return NULL;
    }

    // create a temp node to iterate over the list
    FrameNode* temp = head;

    // iterate over the list and return the frame in the given index
    int i = 0;
    while (temp) {
        if (i == index) {
            return temp;
        }
        i++;
        temp = temp->next;
    }
    return NULL;
}

/**
 * this function gets a head and prints all the frames in the list
 * input: head - the head of the list
 * output: none
 * time complexity: O(n)
 * where n is the number of frames in the list because the function goes over all the frames in the list
*/
void printList(FrameNode* head) {

    // create a temp node to iterate over the list
    FrameNode* temp = head;

    // iterate over the list and print all the frames
    printf("%p\n", temp);
    while (temp) {
        printf("%s --> ", temp->frame->name);
        temp = temp->next;
    }
    printf("\n");
} 


/**
 * this function gets a head and frees all the memory of the list
 * input: head - the head of the list
 * output: none
 * time complexity: O(n)
 * where n is the number of frames in the list because the function goes over all the frames in the list
*/
void freeList(FrameNode* head) {
    // create a temp node to iterate over the list
    FrameNode* temp = head;

    // iterate over the list and free all the nodes
    while (temp) {
        FrameNode* next = temp->next;
        freeFrame(temp);
        temp = next;
    }
}


/**
 * this funcsion gets a head, a frame name and a new duration and changes the duration of the frame with the given name
 * input: head - the head of the list, name - the name of the frame to change, newDuration - the new duration of the frame
 * output: none
 * time complexity: O(n)
 * where n is the number of frames in the list because the function goes over all the frames in the list
*/
void changeFrameDuration(FrameNode* head, char* name, int newDuration) {

    // create a temp node to iterate over the list
    FrameNode* temp = head;

    // iterate over the list and find the frame with the given name
    while (temp) {
        if (strcmp(temp->frame->name, name) == 0) {
            temp->frame->duration = newDuration;
            return;
        }
        temp = temp->next;
    }

    // if the frame does not exist
    printf("The frame '%s' does not exist in the list.\n", name);
}


/**
 * this function gets a head and a new duration and changes the duration of all the frames in the list
 * input: head - the head of the list, newDuration - the new duration of the frames
 * output: none
 * time complexity: O(n)
 * where n is the number of frames in the list because the function goes over all the frames in the list
*/
void changeAllFramesDuration(FrameNode* head, int newDuration) {
    // create a temp node to iterate over the list
    FrameNode* temp = head;

    // iterate over the list and find the frame with the given name
    while (temp) {
        temp->frame->duration = newDuration;
        temp = temp->next;
    }
}

/**
 * this function gets a head and prints all the frames in the list
 * input: head - the head of the list
 * output: none
 * time complexity: O(n)
 * where n is the number of frames in the list because the function goes over all the frames in the list
*/
void printFullList(FrameNode* head) {

    // create a temp node to iterate over the list
    FrameNode* temp = head;
    printf("Name\t\tDuration\tPath\n");

    // iterate over the list
    while (temp) {
        // print the frame details
        printf("%s\t\t%d ms\t\t%s", temp->frame->name, temp->frame->duration, temp->frame->path);
        printf("\n");
        temp = temp->next;
    }
    printf("\n");
}
