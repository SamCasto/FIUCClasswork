/*Author: Samuel Casto
 * AI affirmation: I affirm this work is original and written by me, Samuel Casto. I affirm that the written work I am submitting was 
fully and originally written by myself. I did not copy and paste any section or sub-section of said work in this 
submission. I affirm that I did not use chatGPT or any other software that generates written work in the 
production of my written work.
 *Description: Prints all the letters of the alphabet printed in lower case one at a time to the same line.
 *
 * */
#include <stdio.h>
#include <ctype.h>


int main() {
	char ch;
	//looping through the alphabet printing each letter one at a time 
	for (ch = 'a'; ch <= 'z'; ch++) {
		printf("%c", tolower(ch));
  	}
	//printing a new line
  	printf("\n");

  	return 0;
}
