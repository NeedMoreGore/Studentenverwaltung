#pragma once
#ifndef Student_h
#define Student_h
#include <string>
#include <iostream>

class Student
{
public:
	Student();
	~Student();

	void edit();
	void print();

	//setter getter
	void setFirstName(std::string s);
	std::string getFirstName();
	void setLastName(std::string s);
	std::string getLastName();
	void setSex(char c);
	char getSex();
	void setMatriculationNumber(int i);
	int getMatriculationNumber();
	void setFinalGrade(double d);
	double getFinalGrade();
	void setNext(Student* student);
	Student* getNext();
	void setPrev(Student* student);
	Student* getPrev();


private:
	std::string firstName, lastName;
	char sex;
	int matriculationNumber;
	double finalGrade;

	Student *next, *prev;
};

#endif

