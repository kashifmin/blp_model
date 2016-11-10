#include "Object.h"

// Constructor
Object::Object(char mName[30], int mLevel) {
	this->value = 0;
	strcpy(this->name, mName);
	this->level = mLevel;

}

int Object::getLevel() {
	return this->level;
}