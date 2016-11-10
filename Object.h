#include <string.h>
class Object {
	int level;

public:
	char name[20];
	int value;

	//Constructor
	Object(char mName[20], int mLevel);
	int getLevel();

};