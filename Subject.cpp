#include "Subject.h"

// Constructor
Subject::Subject(char mName[30], int mLevel) {
	this->temp = 0;
	strcpy(this->name, mName);
	this->level = mLevel;
}

// Reads value from an Object
int Subject::readObject(Object *obj) {
	this->temp = obj->value;
	return obj->value;
}

// Writes a value to an Object
void Subject::writeObject(Object *obj, int value) {
	obj->value = value;
}

int Subject::getLevel() {
	return this->level;
}