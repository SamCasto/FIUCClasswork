/*Author: Samuel Casto
 * AI affirmation: I affirm this work is original and written by me, Samuel Casto. I affirm that the written work I am submitting was 
fully and originally written by myself. I did not copy and paste any section or sub-section of said work in this 
submission. I affirm that I did not use chatGPT or any other software that generates written work in the 
production of my written work.
 *Description: Accept alphabetic input via stdin change it to all capital letters and print it to the screen. Do not ask the user to enter the input. Assume the user will know to input alphabetic input.
 * */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int main(){
	//holding what the user inputs
	char input[100];
	//reading user input until we get a new line character
	scanf("%[^\n]", input);
	//looping through the string and converting letters to uppercase
	for(int i = 0; i < strlen(input); i++)
               if(isalpha(input[i]))
			       input[i] = toupper(input[i]);
	//printing the string with the updated letters
	for(int i = 0; i < strlen(input); i++)
		printf("%c",input[i]);
	//new line to make it pretty
	printf("\n");

        return(0);
}
