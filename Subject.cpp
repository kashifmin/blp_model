#include "Subject.h"

Subject::Subject(char mName[30], int mLevel) {
	this->temp = 0;
	strcpy(this->name, mName);
	this->level = mLevel;
}

int Subject::readObject(Object *obj) {
	this->temp = obj->value;
	return obj->value;
}

void Subject::writeObject(Object *obj, int value) {
	obj->value = value;
}

int Subject::getLevel() {
	return this->level;
}