#include "Subject.h"
#include <string.h>
#include "Instruction.cpp"
class ReferenceMonitor {

	int objCount;
	int subCount;

	Object *objects[10];
	Subject *subjects[10];


	void executeRead(char subName[20], char objName[30]);
	void executeWrite(char subName[20], char objName[30], int value);


	Object* getObjByName(char name[20]);
	Subject* getSubByName(char name[20]);

public:
	ReferenceMonitor();
	void createObject(char name[20], int level);
	void createSubject(char name[20], int level);

	void executeInstruction(Instruction *ins);

	void printState();
};