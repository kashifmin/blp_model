#include "ReferenceMonitor.h"
#include "Instruction.cpp"
#include <stdlib.h>
#include <cstring>
#include <iostream>

enum LEVEL {LOW, MEDIUM, HIGH};

ReferenceMonitor *refMon;

int hasNumbersOnly(const char *s) {
	while(*s) {
		if(isdigit(*s++) == 0)
			return 0;

	}
	return 1;
}

/* The following function takes a line of instruction
 * as input and creates an Instruction object for the line 
 * if the instruction is valid.
 * The Instruction Object is then passed to 
 */

void parse(char *line) {
	int tokenCount = 0;
	char *pch, orgLine[80];
	char tokens[4][30];

	strcpy(orgLine, line);

	//std::cout << "here";
	pch = strtok(line, "\n");
	pch = strtok(line, " ");
	while(pch != NULL) {
		if(tokenCount > 4) {
			std::cout << "\nBad Instruction: " << orgLine;
			return;
		}
		//std::cout << "here";
		strcpy(tokens[tokenCount++], pch);
		pch = std::strtok(NULL, " ");
	}

	if((strcasecmp(tokens[0], "read")) == 0) {
		//read
		if(tokenCount != 3) {
			std::cout << "\nBad Instruction: " << orgLine;
			return;
		}
		refMon->executeRead(tokens[1], tokens[2]);
	} else if(strcasecmp(tokens[0], "write") == 0) {
		//write
		if(tokenCount != 4) {
			std::cout << "\nBad Instruction: " << orgLine;
			return;
		}
		if(hasNumbersOnly(tokens[3]))
			refMon->executeWrite(tokens[1], tokens[2], atoi(tokens[3]));
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

	refMon = new ReferenceMonitor();

	std::cout << "\nHIGH is " << HIGH;


	refMon->createSubject("adam", LOW);
	refMon->createSubject("james", MEDIUM);
	refMon->createSubject("tim", HIGH);
	refMon->createSubject("sara", LOW);
	refMon->createSubject("kristy", MEDIUM);
	refMon->createSubject("liz", HIGH);

	refMon->createObject("aobj", LOW);
	refMon->createObject("jobj", MEDIUM);
	refMon->createObject("tobj", HIGH);
	refMon->createObject("sobj", LOW);
	refMon->createObject("kobj", MEDIUM);
	refMon->createObject("lobj", HIGH);

	while(!feof(fp)) {
		fgets(line, 80, fp);
		//std::cout << "Read: " << line;
		parse(line);
	}

	return 0;



}