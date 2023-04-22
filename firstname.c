/*Author: Samuel Casto
 * AI affirmation: I affirm this work is original and written by me, Samuel Casto. I affirm that the written work I am submitting was 
fully and originally written by myself. I did not copy and paste any section or sub-section of said work in this 
submission. I affirm that I did not use chatGPT or any other software that generates written work in the 
production of my written work.
 *Description: Print out a first name that was passed in as an argument to the screen. Expected usage: firstname yourfirstname
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char **argv) {
	//I'm not sure if I need all of these variables
        extern char *optarg;
        extern int optind;
        static char usage[] = "usage: firstname yourfirstname";
	char name[30];
	//if true then there is no input value
	if (optind >= argc) {
       	        fprintf(stderr, "Expected yourfirstname input\n");
               	fprintf(stderr, "usage: firstname yourfirstname\n", argv[0]);
               	return(1);
        }
	//we should only have one string argument to copy 
	if(strcpy(name,argv[1]))
		//on successful copy we print
		printf("%s\n",name);
	else
		printf("Improper name input\n");

	return(0);
}

