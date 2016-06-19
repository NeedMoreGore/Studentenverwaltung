#include "Student.h"

using namespace std;


Student::Student()
{
	this->firstName = "";
	this->lastName = "";
	this->sex = 0;
	this->matriculationNumber = 0;
	this->finalGrade = -1;
}


Student::~Student()
{
}

void Student::print()
{
	cout << "		Vorname:        " << getFirstName() << endl;
	cout << "		Nachname:       " << getLastName() << endl;
	cout << "		Geschlecht:     " << getSex() << endl;
	cout << "		Matrikelnummer: " << getMatriculationNumber() << endl;
	cout << "		Abschlussnote:  " << getFinalGrade() << endl;
}

void Student::setFirstName(std::string s)
{
	this->firstName = s;
}

std::string Student::getFirstName()
{
	return this->firstName;
}

void Student::setLastName(std::string s)
{
	this->lastName = s;
}

std::string Student::getLastName()
{
	return this->lastName;
}

void Student::setSex(char c)
{
	this->sex = c;
}
char Student::getSex()
{
	return this->sex;
}
void Student::setMatriculationNumber(int i)
{
	this->matriculationNumber = i;
}
int Student::getMatriculationNumber()
{
	return this->matriculationNumber;
}
void Student::setFinalGrade(double d)
{
	this->finalGrade = d;
}
double Student::getFinalGrade()
{
	return this->finalGrade;
}
void Student::setNext(Student* student)
{
	this->next = student;
}
Student* Student::getNext()
{
	return this->next;
}
void Student::setPrev(Student* student)
{
	this->prev = student;
}
Student* Student::getPrev()
{
	return this->prev;
}
