/*************************************************************************************
 * myshell - student code for Project 1 of CSCE 489
 *
 *************************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include "shellfuncts.h"

/*************************************************************************************
 * initText - prints the header so user knows that the shell started.
 *
 *************************************************************************************/

void initText() {
	printf("**********Shell Started**********\n");
}

/*************************************************************************************
 * parseLine - parses through the command entered in stdin. Breaks up the sentence
 *						 and matches the char with the commands available.
 *
 *		Params:	line - the char line received in the shell
 *
 *************************************************************************************/

void parseLine(char *line) {
	char delim[] = " \t\r\n\a";
	char *commands[50];
	int i = 0;
	// Use strtok to break the sentence up by whitespace
	commands[i] = strtok(line, delim);
	while(commands[i] != NULL) {
		// Add the words between whitespace into an array
		commands[++i] = strtok(NULL, delim);
	}

	if (strcmp(commands[0], "create") == 0) {
		create(commands[1]);
	}
	else if (strcmp(commands[0], "update") == 0) {
		// Convert the char* back into an int
		int numTimes = atoi(commands[2]);
		update(commands[1], numTimes, commands[3]);
	}
	else if (strcmp(commands[0], "list") == 0) {
		list(commands[1]);
	}
	else if (strcmp(commands[0], "dir") == 0) {
		dir();
	}
	else if (strcmp(commands[0], "halt") == 0) {
		halt();
	}
	else {
		printf("Command not recognized!\n");
	}
}

int main() {
	initText();
	char str[50];
	pid_t child;
	int status;
	while (1) {
		printf("Process ID: %d\n", getpid());
		printf("Enter command:\n");
		// Pull the line from stdin
		fgets(str, 50, stdin);
		child = fork();
		if (child == 0) {
			parseLine(str);
		}
		else
			waitpid(child, &status, WUNTRACED);
	}
	return 0;
}
