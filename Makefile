all:	newshell numbers letters firstname userinput

newshell:	newshell.c
		cc -o newshell newshell.c

numbers:	numbers.c
		cc -o numbers numbers.c

letters:	letters.c
		cc -o letters letters.c

firstname:	firstname.c
		cc -o firstname firstname.c

userinput:	userinput.c
		cc -o userinput userinput.c


clean:
		rm -f 
