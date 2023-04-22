//This program was written by me, Samuel Casto, only and I affirm that I wrote
//this program myself without any help from any other people or sources from
//the internet. My panther ID is 6330314.

//Description of program: This program will assign 12 seats in an airplane. The
//seats are divided into a group of 4 first class and 8 economy seats. The 
//program will accept user input to assign a seat based on input. The 
//program will have functionality to not assign two people to the
//same seat. The program will attempt to get the user another seat on the plane
//if all the seats in the requested section is full. If both sections are full
//the program will inform the user and tell them the next flight is tomorrow.
//If the user does not want a seat in a different section the program will 
//tell them the next flight is tomorrow.
#include <stdio.h>
#include <string.h>

int main(){
	int planeSeats[12];//array holding our seats for the plane
	int arraySize = 12;//size of our array
	int input;//holds user input for program logic
	int running = 1;//pseudo boolean for our while loop menu
	int boardingNum = -1;//holds our i value that will be the empty seat
			     //set to -1 for testing
	//populating our array with 0s to indicate empty seats
	for(int i = 0; i < arraySize; i++)
		planeSeats[i] = 0;

	//printing the first set of menu instructions for the user
	printf("Please type 1 for \"first class\"\nPlease type 2 for \"economy\"\nPlease type 0 to quit \n");
        

	//menu logic
	//takes user input and then decides what to do 
	//accepted values are 1, 2, and 0
	while(running > 0){
		//gathering user input
		scanf("%d",&input);
		if(input == 0){
			//user wants to exit
			break;
		}
		else if( input == 1){
			//user wants to try and get a first class seat
			//first class seats are index 0-3
			for(int i = 0; i < 4; i++){
				//we need to check if the seats are empty
				if(planeSeats[i] == 0){
					//found an empty seat
					boardingNum = i;//saving our seat number
					planeSeats[i]=1;//changing the seat to full
					break;//breaking out of the loop because we need only the first seat we find
				}
			}
			if(boardingNum > -1){
				//if boardingNum > -1 we found a seat
				printf("We found a first class seat at %d\n",boardingNum + 1);//adding one because there is not a seat 0 on planes
			}
			else{
				//if boardingNum !> -1 there was not a first class seat
				printf("We did not find a first class seat\n");
				//we need to see if there is a seat in an available section and if the user wants it
				for(int i = 4; i < arraySize; i++){
					if(planeSeats[i] == 0){
						boardingNum = i;
						break;
					}
				}
				if(boardingNum > -1){
					//there was an available seat in the other section
					printf("There are other seats available would you like one? Type 1 for \'Yes\' and 2 for \'No\'\n");
					scanf("%d",&input);
					if(input == 1){
						//user wanted the seat in the other section
						planeSeats[boardingNum] = 1;
						printf("Your economy seat is at %d\n",boardingNum + 1);
					}
					else{
						//user did not want the seat in the other section
						printf("The next flight will be tomorrow.\n");
					}
				}
				else {
					//informing the user there were no seats in either section and when the next flight is
					printf("There were no other seats available.\nThe next flight will be tomorrow.\n");
				}
			}


		}//end of else if for 1
		else if(input == 2){
			//user wants an economy seat
			for(int i = 4; i < arraySize; i++){
				if(planeSeats[i] == 0){
					//we found an empty seat
					boardingNum = i;
					planeSeats[i] = 1;
					break;
				}
			}
			if(boardingNum > -1){
				//if true we found a seat and need to inform the user
				printf("We found an economy seat at %d\n",boardingNum + 1);
			}
			else{
				//we did not find an economy seat
				printf("We did not find an economy seat\n");
				//checking if there is a first class seat available
				for(int i = 0; i < 4; i++){
                                        if(planeSeats[i] == 0){
                                                boardingNum = i;
                                                break;
                                        }
                                }
                                if(boardingNum > -1){
                                        //there was an available seat in the other section
                                        printf("There are other seats available would you like one? Type 1 for \'Yes\' and 2 for \'No\'\n");
                                        scanf("%d",&input);
                                        if(input == 1){
                                                planeSeats[boardingNum] = 1;
                                                printf("Your first class seat is at %d\n",boardingNum + 1);
                                        }
                                        else{
                                                printf("The next flight will be tomorrow.\n");
                                        }
                                }
				else{
					printf("There are no other seats available.\nThe next flight will be tomorrow.\n");
				}
			}

		}//end of else if for 2
		else{
			//user entered an incompatible menu value
			printf("Please enter a value between 0 and 2\n");
		}
		//reprinting the menu and resetting our boarding number for the next loop
		printf("Please type 1 for \"first class\"\nPlease type 2 for \"economy\"\nPlease type 0 to quit \n");
		boardingNum = -1;

	}//end of while loop



	return(0);	
}//end of main
