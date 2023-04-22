/*Author: Samuel Casto
 *AI Affirmation: I affirm this work is original and written by me, Samuel Casto. I affirm that the written work I am submitting was 
fully and originally written by myself. I did not copy and paste any section or sub-section of said work in this 
submission. I affirm that I did not use chatGPT or any other software that generates written work in the 
production of my written work.
Description: This program will accept command line input, create a doubly linked list, read in a list of words from a file listed in the command line in
alphabetical order and convert the words to lower case while not making duplicate nodes, and then either print out to standard output or to a file specified
from the comman line input.
 *
 *  */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

//our node struct
typedef struct NODE NODE;
struct NODE {
	char word[50];
	NODE* previous;
	NODE* next;
};

//helper function to add nodes to the list
//in this function we will make sure the word is not already in the list and that the node is added in the correct location
void addNode(NODE** head, NODE** tail, const char* word) {
    	NODE* current = *head;

    	//we traverse the list to find the correct position to insert the new node
    	while (current != NULL && strcmp(current->word, word) < 0) {
        	current = current->next;
    	}	

    	//now we check if the word is already in the list
    	if (current != NULL && strcmp(current->word, word) == 0) {
        	return;
    	}	

    	//we create a new node and copy the word into it since we know where it should go and that it should go into the list
    	NODE* newNode = (NODE*)malloc(sizeof(NODE));
    	strncpy(newNode->word, word, 50);
    	newNode->next = NULL;
    	newNode->previous = NULL;

    	// Update the previous and next pointers of the new node
    	if (*head == NULL) {
        	// If the list is empty, set both first and last pointers to the new node
        	*head = newNode;
        	*tail = newNode;
    	} 
	else if (current == NULL) {
        	// If the new node goes at the end of the list, update the last pointer
        	newNode->previous = *tail;
        	(*tail)->next = newNode;
        	*tail = newNode;
    	}
       	else if (current == *head) {
        	// If the new node goes at the beginning of the list, update the first pointer
        	newNode->next = *head;
        	(*head)->previous = newNode;
        	*head = newNode;
    	}
       	else {
        	// If the new node goes in the middle of the list, update the previous and next pointers
        	newNode->previous = current->previous;
        	newNode->next = current;
        	current->previous->next = newNode;
        	current->previous = newNode;
    	}
}//end of addNode

//method to clean the our input words
char* cleanString(char* str) {
    char* clean = (char*) malloc(strlen(str) + 1);
    int i, j;
    for (i = 0, j = 0; str[i]; i++) {
        if (isalpha(str[i])) {
            clean[j++] = tolower(str[i]);
        }
    }
    clean[j] = '\0';
    return clean;
}//end of cleanString

//method to free all the nodes
void freeList(NODE *head) {
	NODE* current = head;
    	NODE* next;
	while (current != NULL) {
        	next = current->next;
       		free(current);
        	current = next;
    	}
}//end of freeList

int main(int argc, char **argv) {
        extern char *optarg;
        extern int optind;
        int c, err = 0;
        int dflag = 0, oflag = 0;//flags set to 0 for input validation
	char *opFileName = NULL;
        static char usage[] = "doublesort [-d] [-o output_file_name] input_file_name\n";

        while ((c = getopt(argc, argv, "do:i:")) != -1){
                switch (c) {
                        case 'd':
                                dflag = 1;
                                break;
                        case 'o':
                                oflag = 1;
                                opFileName = optarg;
				break;
                }//end of switch
        }//end of while loop

	//checking for file input name
	if (optind >= argc) {
        	fprintf(stderr, "Expected input file name\n");
        	fprintf(stderr, "Usage: %s [-d] [-o output_file_name] input_file_name\n", argv[0]);
        	return(1);
   	}
    	char *ipFileName = argv[optind];

	//if we are here then we have successfully interpreted command line input and have our necessary values for the rest of the program
	//first we will make the first and last  nodes in our list
	NODE *first = malloc(sizeof(struct NODE));
    	NODE *last = malloc(sizeof(struct NODE));
	first = NULL;
	last = NULL;
	
	char temp[50];//this will hold our word while we convert it to lower case and get rid of special characters
	
	//printf("This is ipFileName: %s\n",ipFileName);
	//open the input file
	FILE* file = fopen(ipFileName,"r");
	if(file == NULL)
		printf("Could not open file\n");
	//we need to read from each line and add a node for new words
	while(fgets(temp,50,file) != NULL){
		//after testing we need to strip the new line of each word and turn it into a null character
		temp[strcspn(temp,"\n")] = '\0';//works
		//next we need to trim all non letters and then convert them to lowercase
		strcpy(temp,cleanString(temp));
		//at this point we have the words in the correct state to compare them and maybe add them to the nodes
		//printf("%s\n",temp);
		addNode(&first, &last, temp);
	}//end of while loop
	//closing our file
	fclose(file);
	//now we need to print out our nodes or write them to a file based on input 
	//as well as check if the list should be printed a-z or z-a
	if(oflag == 0){
		//flag to write to file wasn't declared and we just need to verify our reverse flag
		if(dflag ==  0){
			//we want to print normally starting from the first node and working our way back
			NODE* current = first;
			while(current != NULL){
				printf("%s\n",current->word);
				current = current->next;
			}
		}
		else {
			//we want to print from the last node and work our way forward
			NODE* current = last;
			while(current != NULL){
				printf("%s\n",current->word);
				current = current->previous;
			}
		}
	}
	else {
		//if we are here then we are going to be printing to a file
		FILE* file2 = fopen(opFileName,"w");
		if(dflag == 0){
			NODE* current = first;
			while(current != NULL){
				fprintf(file2,"%s\n",current->word);
				current = current->next;
			}
		}
		else {
			NODE* current = last;
			while(current != NULL){
				fprintf(file2,"%s\n",current->word);
				current = current->previous;
			}
		}

	}//end of else
	
	//we need to free up our memory
	freeList(first);
	



	return (0);
}//end of main
