#include "ReferenceMonitor.h"
#include <strings.h>
#include <iostream>
#include <iomanip>
using namespace std;

ReferenceMonitor::ReferenceMonitor(){
	this->objCount = 0;
	this->subCount = 0;
}

void ReferenceMonitor::createObject(char name[20], int level) {
	// Create a new Object and add it to our array of objects
	this->objects[this->objCount++] = new Object(name, level);
}

void ReferenceMonitor::createSubject(char name[20], int level) {
	// Create a new Subject and add it to our array of subjects
	this->subjects[this->subCount++] = new Subject(name, level);
}

/*
 * Searches the array of Objects maintained by the ReferenceMonitor
 * that has its name field matching with the argument 'name'
 */
Object* ReferenceMonitor::getObjByName(char name[20]) {
	int i = 0;
	while(i < this->objCount) {
		if(strcasecmp(name, (this->objects[i])->name) == 0)
			return this->objects[i++];
		i++;
	}
	return NULL;
}

/*
 * Searches the array of Subjects maintained by the ReferenceMonitor
 * that has its name field matching with the argument 'name'
 */
Subject* ReferenceMonitor::getSubByName(char name[20]) {
	int i = 0;
	while(i < this->subCount) {
		if(strcasecmp(name, (this->subjects[i])->name) == 0)
			return this->subjects[i++];
		i++;
	}
	return NULL;
}

/*
 * Recieves an Instruction object from SecureSystem
 * and decides whether to READ or WRITE
 */
void ReferenceMonitor::executeInstruction(Instruction *ins) {
	if(ins->type == 0) {
		this->executeRead(ins->subjectName, ins->objectName);
	} else {
		this->executeWrite(ins->subjectName, ins->objectName, ins->value);
	}
}

/*
 * Allows a subject to read a value from an object if the
 * access labels of the both allow reading by the policies of BLP model.
 */
void ReferenceMonitor::executeRead(char subName[20], char objName[30]) {

	Subject *subject = getSubByName(subName);
	Object *object = getObjByName(objName);

	if(subject == NULL) { // if a subject with subName does not exist
		cout << "\nexecWrite: Invalid Subject name: " << subName;
		return;
	}

	if(object == NULL) {
		cout << "\nexecWrite: Invalid Object name: " << objName;
		return;
	}

	/* Allow READ only if the subject has a higher access level than the object */
	if(subject->getLevel() >= object->getLevel()) {
		// Grant access
		subject->readObject(object);
		cout << "\nAcess Granted: " << subName << " reads " << objName;
		this->printState();
	} else {
		//Access denied
		cout << "\nAccess DENIED! " << subName << " reads " << objName; 

	}
}

void ReferenceMonitor::executeWrite(char subName[20], char objName[30], int value) {

	Subject *subject = getSubByName(subName);
	Object *object = getObjByName(objName);

	if(subject == NULL) {
		cout << "\nexecWrite: Invalid Subject name: " << subName;
		return;
	}

	if(object == NULL) {
		cout << "\nexecWrite: Invalid Object name: " << objName;
		return;
	}

	/* Allow WRITE only if the subject has a lower access level than the object */
	if(subject->getLevel() <= object->getLevel()) {
		// Grant access
		subject->writeObject(object, value);
		cout << "\nAcess Granted: " << subName << " writes value " << value << " to " << objName; 
		this->printState();
	} else {
		//Access denied
		cout << "\nAccess DENIED!" << subName << " writes value " << value << " to " << objName;

	}


}

void ReferenceMonitor::printState() {
	int i=0;

	cout << "\n+------------------------The current state is-------------------------+\n";
	cout << "| subject |";
	while(i < subCount) {
		cout << "\t" << (this->subjects[i])->name << " |";
		i++;
	}
	i=0;
	cout << "\n| value |";
	while(i < subCount) {
		cout << "\t" << setw(4) << (this->subjects[i])->temp << " |";
		i++;
	}
	i=0;
	cout << "\n+---------------------------------------------------------------------+\n";
	cout << "| object |";
	while(i < objCount) {
		cout << "\t" << (this->objects[i])->name << " |";
		i++;
	}
	i=0;
	cout << "\n| value |";
	while(i < subCount) {
		cout << "\t" << (this->objects[i])->value << " |";
		i++;
	}

	cout << "\n+---------------------------------------------------------------------+\n";



}