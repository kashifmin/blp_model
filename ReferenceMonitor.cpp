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
	this->objects[this->objCount++] = new Object(name, level);
}

void ReferenceMonitor::createSubject(char name[20], int level) {
	this->subjects[this->subCount++] = new Subject(name, level);
}

Object* ReferenceMonitor::getObjByName(char name[20]) {
	int i = 0;
	while(i < this->objCount) {
		//cout << "\nComparing "<< name << " and "<< (this->objects[i])->name;
		if(strcasecmp(name, (this->objects[i])->name) == 0)
			return this->objects[i++];
		i++;
	}
	return NULL;
}

Subject* ReferenceMonitor::getSubByName(char name[20]) {
	int i = 0;
	while(i < this->subCount) {
		if(strcasecmp(name, (this->subjects[i])->name) == 0)
			return this->subjects[i++];
		i++;
	}
	return NULL;
}

void ReferenceMonitor::executeRead(char subName[20], char objName[30]) {

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

	if(subject->getLevel() >= object->getLevel()) {
		// Grant access
		subject->readObject(object);
		cout << "\nAcess Granted: " << subName << " reads " << objName;
	} else {
		//Access denied
		cout << "\nAccess DENIED! " << subName << " reads " << objName; 

	}
	this->printState();
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

	if(subject->getLevel() <= object->getLevel()) {
		// Grant access
		subject->writeObject(object, value);
		cout << "\nAcess Granted: " << subName << " writes value " << value << " to " << objName; 
	} else {
		//Access denied
		cout << "\nAccess DENIED!" << subName << " writes value " << value << " to " << objName;

	}

	this->printState();

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