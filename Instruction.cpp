class Instruction {

public:
	int type; //0 for READ, 1 for WRITE

	char subjectName[30];
	char objectName[30];
	int value;
	
	Instruction(int mType, char mSname[30], char mObjName[30], int mValue=0) {
		this->type = mType;
		strcpy(this->subjectName, mSname);
		strcpy(this->objectName, mObjName);
		this->value = mValue;
	}

};