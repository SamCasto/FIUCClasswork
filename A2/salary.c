//Author: Samuel Casto
//Purpose of program: This program will take command line arguments and perform a salary calculation.  The accepted inputs will be hours, an optional bonus
//, and an hourly rate along with a -p flag for a percentage salary increase. The program will parse the command line input and output the salary
// information. It will not accept user input during runtime.

//I affirm this work is original and written by me, Samuel Casto. I affirm that the written work I am submitting was 
//fully and originally written by myself. I did not copy and paste and section or sub-section of said work in this 
//submission. I affirm that I did not use chatGPT or any other software that generates written work in the 
//production of my written work.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

int main(int argc, char **argv) {
        extern char *optarg;
        extern int optind;
        int c, err = 0;
	int pflag = 0, bflag = 0, hflag = 0;//flags set to 0 for input validation
      	double hrate = -1.0, hours = -1.0, bonus = -1.0;//values for program set to -1 for input validation
        static char usage[] = "salary: [-p] -h hours [-b bonus] hourlyrate\n";
	
	while ((c = getopt(argc, argv, "ph:b:")) != -1){
                switch (c) {
			case 'p':
				pflag = 1;
				break;
			case 'h':
                       	 	hflag = 1;
                        	hours = atof(optarg);
				break;
			case 'b':
				bflag = 1;
				bonus = atof(optarg);
				break;
                }//end of switch
	}//end of while loop

	//flag verification to make sure we have all needed information for the program
        if (hflag == 0) {       /* -h was mandatory */
                fprintf(stderr, "%s: missing -h option\n", argv[0]);
                fprintf(stderr, usage, argv[1]);
                exit(1);
        }
	//if false then we do not have our extra value for hourlyrate
        else if ((optind) > argc) {
                // need at least one argument (change +1 to +2 for two, etc. as needeed) 
                printf("optind = %d, argc=%d\n", optind, argc);
                fprintf(stderr, "%s: missing value arg\n", argv[0]);
                fprintf(stderr, usage, argv[0]);
                exit(1);
        }
        else if (err) {
                fprintf(stderr, usage, argv[0]);
                exit(1);
        }
	
	//if we are here then there is a value to use for the hourly rate and all other flags have been accounted for
        hrate = atof(argv[optind]);
	
	//we need to verify all our preconditions are met
        //      1. hours cannot be more than 80
        //      2. the bonus cannot be more than 50% of our initial salary value
        //	3. not required but we will check for negative values and convert them to positive values 
	//
	if(hours > 80){
		printf("Error: hours cannot be > 80\n");
		return(1);
	}
	if(((hours * hrate) / 2) < bonus){
		printf("Error: bonus cannot be more than 50%% of our initial salary value\n");
		return(1);
	}

	
	//declaring our salary value
	double salary;
	//calculating our salary value according to the steps listed
	//step 1: Multiply the hourly rate by the number of hours
	salary = round(( hours * hrate ) * 1000.0 ) / 1000.0 ;
	//step 2: If there is a percentage increase then multiply the previous result by 10% ie multiply by 0.10
	if(pflag > 0)
		salary = round((salary + (salary * 0.10)) * 1000.0) / 1000.0;
	//step 3: If there is a bonus then add it to the previous result
	if(bflag > 0)
		salary = round((salary + bonus)* 1000.0) / 1000.0;

	//outputting our salary in the desired format
	printf("The salary for this period is $%2.2f\n",salary);






	

	return(0);
}
