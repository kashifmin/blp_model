#include "ReferenceMonitor.h"
#include <stdlib.h>
#include <cstring>
#include <iostream>

enum LEVEL {LOW, MEDIUM, HIGH}; // Access levels/labels

ReferenceMonitor *refMon;

/*
 * Checks if a string consists only of digits
 */
int hasNumbersOnly(const char *s) {
	while(*s) {
		if(isdigit(*s++) == 0)
			return 0;

	}
	return 1;
}

/* 
 * The following function takes a line of instruction
 * as input and creates an Instruction object for the line 
 * if the instruction is valid.
 * The Instruction Object is then passed to 
 */

void parse(char *line) {
	int tokenCount = 0;
	char *pch, orgLine[80];
	char tokens[4][30];

	strcpy(orgLine, line); // save a copy of the current line

	//std::cout << "here";
	pch = strtok(line, "\n"); // Remove the trailing new line character added by fgets

	/* Now we use strok to tokenize a line of instruction */
	pch = strtok(line, " "); 
	while(pch != NULL) {
		if(tokenCount > 4) { // number of tokens should never be more than 4
			std::cout << "\nBad Instruction: " << orgLine;
			return;
		}
		//std::cout << "here";
		strcpy(tokens[tokenCount++], pch);
		pch = std::strtok(NULL, " ");
	}

	/* Check the first token to decide whether it is a READ or WRITE instruction */
	if((strcasecmp(tokens[0], "read")) == 0) {
		//read
		if(tokenCount != 3) {
			std::cout << "\nBad Instruction: " << orgLine;
			return;
		}
		// Create a new Instruction object that is passed to the ReferenceMonitor
		Instruction *ins = new Instruction(0, tokens[1], tokens[2]);
		refMon->executeInstruction(ins);
	} else if(strcasecmp(tokens[0], "write") == 0) {
		//write
		if(tokenCount != 4) {
			std::cout << "\nBad Instruction: " << orgLine;
			return;
		}
		// We check if the last token i.e the value, is a valid numeric
		if(hasNumbersOnly(tokens[3])) {
			Instruction *ins = new Instruction(1, tokens[1], tokens[2], atoi(tokens[3]));
			refMon->executeInstruction(ins);
		}
		else 
			std::cout << "\nBad Instruction: " << orgLine;
	} else {
		std::cout << "\nBad Instruction: " << orgLine;
	}
	

}

int main(int argc, char* argv[]) {

	FILE *fp;
	char line[80];

	if(argc != 2) {
		std::cout << "Usage: ./securesystem input";
		exit(0);
	}

	fp = fopen(argv[1], "r");

	refMon = new ReferenceMonitor(); // Create ReferenceMonitor for our SecuritySystem

	/* Create Subjects */
	refMon->createSubject("adam", LOW);
	refMon->createSubject("james", MEDIUM);
	refMon->createSubject("tim", HIGH);
	refMon->createSubject("sara", LOW);
	refMon->createSubject("kristy", MEDIUM);
	refMon->createSubject("liz", HIGH);

	/* Create Objects */
	refMon->createObject("aobj", LOW);
	refMon->createObject("jobj", MEDIUM);
	refMon->createObject("tobj", HIGH);
	refMon->createObject("sobj", LOW);
	refMon->createObject("kobj", MEDIUM);
	refMon->createObject("lobj", HIGH);

	// Parse the input file
	while(!feof(fp)) {
		fgets(line, 80, fp); // assume a line to have maximum of 80 characters
		parse(line);
	}

	return 0;



}