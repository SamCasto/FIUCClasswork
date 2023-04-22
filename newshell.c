/*Author: Samuel Casto
 * AI affirmation: I affirm this work is original and written by me, Samuel Casto. I affirm that the written work I am submitting was 
 *fully and originally written by myself. I did not copy and paste any section or sub-section of said work in this 
 *submission. I affirm that I did not use chatGPT or any other software that generates written work in the 
 *production of my written work.
 *Description: Presents a menu of options to the user to pick from. Based on user input the program will complete the specified program if applicable or
 *terminate runtime or inform the user of input error. These programs will be completed using the process commands of fork, pipe, wait, and dup2. The 
 *program will fork off children to run the program(s) based on the user's input
 *
 * 
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	//int variable to hold the users choice
  	int choice;
	//creating our variables for forking
	int pid, pid2, status;
	int fd[2];
	//user for holding user's first name and for user input
	char input[100];
	//array of strings holding our commands to run our menu items
	char *cmd1[] = {"letters",NULL};
	char *cmd2[] = {"numbers",NULL};
	char *cmd3[] = {"firstname",input,NULL};
	char *cmd4[] = {"userinput",NULL};
	//infinite while loop until user enters 8
  	while (1) {
		//printing our menu
		printf("\n");
    		printf("1. letters\n");
    		printf("2. numbers\n");
    		printf("3. firstname\n");
    		printf("4. userinput\n");
    		printf("5. letters > outfile\n");
    		printf("6. letters | userinput\n");
 	   	printf("7. firstname | userinput\n");
  	  	printf("8. exit\n");
  	  	printf("Enter your choice: ");
	    	scanf("%d", &choice);
		//clearing our input value each run
		input[0] = '\0';

		switch(choice){
			case(1):
				//user wants to run letters
				pid = fork();
				if(pid == 0){
					execvp(cmd1[0],cmd1); //run the child process
                                	fprintf(stderr,"%s failed\n",cmd1[0]);//error message
                                	exit(1);
				}
				else{
					//wait for the process to finish
					wait(&status);
				}
				//waiting for the child to finish and also helps with formatting of menu
				wait(&status);
				break;
			case(2):
				//user wants to run numbers
				pid = fork();
				if (pid == 0){
                                execvp(cmd2[0],cmd2);//run the child process
                                fprintf(stderr,"%s failed\n",cmd2[0]);//error message
                                exit(1);
                        	}	
                        	else {
                                	wait(&status);
                        	}
				wait(&status);
				break;
			case(3):
				//user wants to run firstname
				//need to get the first name input and assign it to input
				printf("Print your first name:\n");
				scanf("%s",input);
				pid = fork();
				if(pid == 0){
					execvp(cmd3[0],cmd3);
					fprintf(stderr,"%s failed\n",cmd3[0]);
					exit(1);
				}
				else {
					wait(&status);
				}
				wait(&status);
				break;
			case(4):
				//user wants to run userinput
				pid = fork();
				if(pid == 0){
					execvp(cmd4[0],cmd4);
					fprintf(stderr,"%s failed\n",cmd4[0]);
					exit(1);
				}
				else{
					wait(&status);
				}
				wait(&status);
				break;
			case(5):
				//user wants to print letters to outfile
				pid = fork();
				if(pid == 0){
					//opening our outfile to write letters to
					FILE *outfile = fopen("outfile","w");
					//need to redirect the output to the file using dup2
					dup2(fileno(outfile),1);//using fileno to get an int value for dup2, 1 is stdout for dup2 after some reading
					//calling the letters program
					execvp(cmd1[0],cmd1);
					fprintf(stderr,"%s failed\n",cmd1[0]);
					exit(1);
					
					fclose(outfile);
				}
				else{
					wait(&status);
				}
				wait(&status);
				break;
			case(6):
				//user wants to pipe letters into userinput
				//creating our pipe
				pipe(fd);
        			switch (pid = fork()){
                			case 0: //child process that will run letters
                        			dup2(fd[1], 1);		//changing the output to be the write end of the pipe
                        			close(fd[0]);           //closing the read end of the pipe since it is not needed
                        			execvp(cmd1[0], cmd1);  //runs letters
                        			fprintf(stderr,"%s failed\n",cmd1[0]);  //error message
                			default: //don't have the parent doing anything
                        			break;

                			case -1:
                        			fprintf(stderr, "fork failed\n");
                        			exit(1);
        			}
        			wait(&status);//waits for the first child to finish; only here to clean up output
				switch (pid = fork()){
                			case 0: //child process that will run userinput
                        			dup2(fd[0], 0); 	//changing input to be the read end of the pipe
                        			close(fd[1]);           //closing the write end of the pipe
                        			execvp(cmd4[0], cmd4);  //runs userinput
                        			fprintf(stderr,"%s failed\n", cmd2[0]); //error message
                			default: //don't have the parent doing anything
                        			break;

                			case -1:
                        			fprintf(stderr,"fork failed\n");
                        			exit(1);
        			}
				//closing the pipe
        			close(fd[0]); close(fd[1]); 
				//waiting for second child to process
				wait(&status);
				break;
			case(7):
				//user wants to pipe firstname into userinput
				//need to get first name 
                                printf("Print your first name:\n");
                                scanf("%s",input);
				//creating our pipe
                                pipe(fd);
                                switch (pid = fork()){
                                        case 0: //child process that will run firstname
                                                dup2(fd[1], 1); 	//write end of the pipe becomes stdout
                                                close(fd[0]); 		//closing the read end of the pipe becuase we do not need it
                                                execvp(cmd3[0], cmd3);  //running firstname
                                                fprintf(stderr,"%s failed\n",cmd1[0]);  //error message
                                        default: //don't have the parent doing anything
                                                break;

                                        case -1:
                                                fprintf(stderr, "fork failed\n");
                                                exit(1);
                                }
				wait(&status);//waits for the first child process to finish; only necessary to clean up output
                                switch (pid = fork()){
                                        case 0: //child process that will run userinput
                                                dup2(fd[0], 0); 	//read end of the pipe becomes stdin
                                                close(fd[1]);           //don't need the write end of the pipe
                                                execvp(cmd4[0], cmd4);  //running userinput
                                                fprintf(stderr,"%s failed\n", cmd2[0]); //error message
                                        default: //don't have the parent doing anything
                                                break;

                                        case -1:
                                                fprintf(stderr,"fork failed\n");
                                                exit(1);
                                }
                                //closing the pipe
                                close(fd[0]); close(fd[1]);
                                wait(&status);
				break;
			case(8):
				//user wants to exit the shell
				exit(0);
				break;
			default:
				//user entered an invalid expression
				printf("Invalid choice value\n");
				scanf("%*[^\n]");
				break;
		}//end of switch
 	 }//end of while loop
 	return(0);
}
