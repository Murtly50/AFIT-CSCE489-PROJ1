/*************************************************************************************
 * shellfuncts.c - code definitions for your functions
 *
 *************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include "shellfuncts.h"

/*************************************************************************************
 * create - creates a new file in the current directory with the given name.
 *					Prints an error message if the file already exists.
 *
 *		Params:	fileName1 - name of the file to be created
 *
 *************************************************************************************/

void create(char* fileName) {
	FILE *file;
	// Only create the file if the read attempt returns a null
	if (fopen(fileName, "r") == NULL) {
		// Open the file with writing permissions
		file = fopen(fileName, "w+");
		// Close the file after
		fclose(file);
	}
	else
		printf("File name already used!\n");
	exit(0);
}

/*************************************************************************************
 * update - appends lines of text to the named file. the command sleeps
 *					for a few seconds determined by the length of the added text.
 *
 *		Params:	fileName - the file that the text will be appended into
 *						numTime - number of times the text gets looped in the fileName
 *						upText - text that will be looped into the file
 *
 *************************************************************************************/

void update(char* fileName, int numTime, char* upText) {
	printf("%s\n", fileName);
	printf("%d\n", numTime);
	printf("%s\n", upText);
	if (fopen(fileName, "r") == NULL) {
		printf("File does not exhist");
	}
	// Open the file with the pointer at the end
	FILE *file = fopen(fileName, "a");
	for (int i = 0; i < numTime; i++) {
		fprintf(file, "%s\n", upText);
		fflush(file);
		sleep(strlen(upText)/5);
	}
	fclose(file);
	printf("File update completed on process: %d\n", getpid());
	exit(0);
}

/*************************************************************************************
 * list - displays the contents of the named file on the screen. prints an error
 *				message and terminates the command if the file does not exist.
 *
 *		Params:	fileName - the file we want the contents out of
 *
 *************************************************************************************/

 void list(char* fileName) {
	// Add 5 to the buffer size due to the .txt added on the end of the filename
 	int bufSize = strlen(fileName) + 5;
 	char buffer[bufSize];
 	FILE *file = fopen(fileName, "r");
	// Print error if file not found
 	if (file == NULL) {
 		printf("File does not exist! Use create() instead.\n");
 		exit(0);
 	}
	// Use cat
 	snprintf(buffer, bufSize, "cat %s", fileName);
 	execl("/bin/cat", "cat", fileName, NULL);
 	fclose(file);
 	exit(0);
 }

/*************************************************************************************
 * dir - lists the names of all files in the current directory.
 *
 *************************************************************************************/

void dir() {
	execl("/bin/ls", "ls", NULL);
	exit(0);
}

/*************************************************************************************
 * halt - terminates the shell.
 *
 *************************************************************************************/

void halt() {
	kill(0, SIGKILL);
}
