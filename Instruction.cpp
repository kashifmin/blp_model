class Instruction {
	int type; //0 for READ, 1 for WRITE

	char subjectName[20];
	char objectName[20];
	int value;

public:
	Instruction(int mType, char mSname[20], char mObjName[20], int mValue=0) {
		this->type = mType;
		strcpy(this->subjectName, mSname);
		strcpy(this->objectName, mObjName);
		this->value = mValue;
	}

};