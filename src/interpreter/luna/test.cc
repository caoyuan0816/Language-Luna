#include <iostream>

using namespace std;

class Test{
public:
	int intVal = 1;
	double doubleVal = 2.0;
	bool boolVal = false;
	virtual int getValue(){return -1;}
};

class TestInt: public Test{
public:
	int getValue(){
		return this->intVal;
	}
};

class TestDouble: public Test{
public:
	double getValue(){
		return this->doubleVal;
	}
};

class TestBool: public Test{
public:
	bool getValue(){
		return this->boolVal;
	}
};

int main(void){
	Test t1 = *new TestInt();
	Test t2 = *new TestDouble();
	Test t3 = *new TestBool();

	cout << t1.getValue() << endl;
	cout << t2.getValue() << endl;
	cout << t3.getValue() << endl;

	return 0;
}