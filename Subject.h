#include <string.h>
#include "Object.h"
class Subject {
	int level;
public:
	char name[20];
	int temp;

	Subject(char mName[30], int level);

	int readObject(Object *obj);

	void writeObject(Object *obj, int value);

	int getLevel();

};