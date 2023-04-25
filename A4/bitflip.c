/*
 *Author: Samuel Casto
  AI Affirmation: I affirm this work is original and written by me, Samuel Casto. I affirm that the written work I am submitting was 
fully and originally written by myself. I did not copy and paste any section or sub-section of said work in this 
submission. I affirm that I did not use chatGPT or any other software that generates written work in the 
production of my written work.
 *Description: This program will flip bits in an unsigned integer using the binary representation of the number. This program will accept input that will 
 dictate how the bits are flipped as well as how the results of the program will output to the screen or to a file. This program will accomplish these 
 tasks only using bitwise operators. 
 *
 *
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>


int main(int argc, char **argv) {
        extern char *optarg;
        extern int optind;
        int c, err = 0;
        int eflag = 0, oflag = 0, fflag = 0, aflag = 0, sflag = 0;//flags set to 0 for input validation
        char *opFileName = NULL;
	uint16_t input = 0;
        static char usage[] = "usage: bitflip [-e] [-f] [-a] [-s] [-o outputfilename] intval\n";

        while ((c = getopt(argc, argv, "efaso:")) != -1){
                switch (c) {
                        case 'a':
                                aflag = 1;
                                break;
                        case 'f':
                                fflag = 1;
                                break;
                        case 's':
                                sflag = 1;
                                break;
			case'e':
				eflag = 1;
				break;
			case'o':
				oflag = 1;
				opFileName = optarg;
				break;
                }//end of switch
        }//end of while loop


        //checking int value to perform operations on
        if (optind >= argc) {
                fprintf(stderr, "Expected intval input\n");
                fprintf(stderr, "usage: bitflip [-e] [-f] [-a] [-s] [-o outputfilename] intval\n", argv[0]);
                return(1);
        }
	//assigning our inputted value to input
	input = atoi(argv[optind]);
	uint16_t temp = input;

	//given how this program is set up we will see if the user wants to write output to file first, then perform our calculations
	if(oflag == 1){
		if(opFileName == NULL){
			printf("Error: Did not input an output file name\n");
			return(1);
		}
		FILE *file = fopen(opFileName,"w");
		//need to run all of our already written program logic here into file
                //now we need to use our flags to determine which operations to perform
                fprintf(file,"Value: %u\n",input);
                //user wants all even bits flipped
                if(eflag == 1){
                        //we need to flip only the even bits so we need a number that has 1s in even spots
                        temp ^= 21845;//binary representation of 21845 = 0101 0101 0101 0101
                        fprintf(file,"All even bits flipped: %u\n",temp);
                }
                //need to update temp so that we are performing the operations on the same number each time
                temp = input;
                //user wants all odd bits flipped
                if(fflag == 1){
                        //we need to flip only the odd bits so we need a number that has 1s in odd spots
                        temp ^= 43690;//binary representation of 43690 = 1010 1010 1010 1010
                        fprintf(file,"All odd bits flipped: %u\n",temp);
                }
                temp = input;
                //use wants all the bits flipped
                if(aflag == 1){
                        //we need to flip all the bits so we will use the binary complement operator to flip it
                        temp = ~temp;
                        fprintf(file,"All bits flipped: %u\n",temp);
                }
                temp = input;
		if(sflag == 1){
                        //we need to iterate through the binary number and swap each value where the rightmost bit becomes the leftmost
                        //I think we need another copy of temp
                        uint16_t flipped = 0;
                        //iterating through each bit
                        for(int i = 0; i < 16; i++){
                                //creating a temporary 'bit' value to hold the value from temp at our current position
                                //temp is shifted i times to the right making our wanted value to get the right most
                                //then we use the & operator with 1 to compare the rightmost value since 1 binary is 0000 0000 0000 0001
                                //bit becomes 1 if the rightmost value in temp is a 1 or becomes 0 if the rightmost value is 0 in temp
                                uint16_t bit = (temp >> i) & 1;
                                //we have our rightmost value now and need to assign it to the leftmost value in flipped
                                //we use the or operator because we want to assign the new value no matter what into flipped
                                flipped |= bit << (15 - i);
                        }
                                //updating temp with our new number
                        temp = flipped;
                        fprintf(file,"Switched all bits: %u\n",temp);
                }
		fclose(file);//closing our file

	}//end of oflag == 1 or writing to file
	else{
		//now we need to use our flags to determine which operations to perform
		printf("Value: %u\n",input);
		//user wants all even bits flipped
		if(eflag == 1){
			//we need to flip only the even bits so we need a number that has 1s in even spots
			temp ^= 21845;//binary representation of 21845 = 0101 0101 0101 0101
			printf("All even bits flipped: %u\n",temp);
		}
		//need to update temp so that we are performing the operations on the same number each time
		temp = input;
		//user wants all odd bits flipped
		if(fflag == 1){
			//we need to flip only the odd bits so we need a number that has 1s in odd spots
			temp ^= 43690;//binary representation of 43690 = 1010 1010 1010 1010
			printf("All odd bits flipped: %u\n",temp);
		}
		temp = input;
		//use wants all the bits flipped
		if(aflag == 1){
			//we need to flip all the bits so we will use the binary complement operator to flip it
			temp = ~temp;
			printf("All bits flipped: %u\n",temp);
		}
		temp = input;
		//user wants all bits switched ie leftmost bit is rightmost etc
		if(sflag == 1){
			//we need to iterate through the binary number and swap each value where the rightmost bit becomes the leftmost
			//I think we need another copy of temp
			uint16_t flipped = 0;
			//iterating through each bit
			for(int i = 0; i < 16; i++){
				//creating a temporary 'bit' value to hold the value from temp at our current position
				//temp is shifted i times to the right making our wanted value to get the right most
				//then we use the & operator with 1 to compare the rightmost value since 1 binary is 0000 0000 0000 0001
				//bit becomes 1 if the rightmost value in temp is a 1 or becomes 0 if the rightmost value is 0 in temp
				uint16_t bit = (temp >> i) & 1;
				//we have our rightmost value now and need to assign it to the leftmost value in flipped
				//we use the or operator because we want to assign the new value no matter what into flipped
        			flipped |= bit << (15 - i);
    			}
				//updating temp with our new number
			temp = flipped;
			printf("Switched all bits: %u\n",temp);
		}
	}//end of else 


	return(0);
}

