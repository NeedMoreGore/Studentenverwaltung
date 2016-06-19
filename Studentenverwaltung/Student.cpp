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

void Student::edit()
{
	cout << "\nBearbeiten: " << endl;
	cout << "__________" << endl;
	cout << "		Vorname:        ";
	setFirstName(checkInput(getFirstName()));
	cout << "		Nachname:       ";
	setLastName(checkInput(getLastName()));
	cout << "		Geschlecht:     ";
	setSex(checkInput(getSex()));
	cout << "		Abschlussnote:  ";
	setFinalGrade(checkInput(getFinalGrade()));
}

//
//
// checks if input was empty or not
//
//
string Student::checkInput(string input)
{
	string newInput = "";

	getline(cin, newInput);

	if (!newInput.empty())
		return newInput;
	else
		return input;
}

char Student::checkInput(char input)
{
	string newInput = "";

	getline(cin, newInput);

	if (!newInput.empty())
		return input = newInput.at(0);
	else
		return input;
}

double Student::checkInput(double input)
{
	string newInput = "";

	getline(cin, newInput);

	if (!newInput.empty())
		return input = stod(newInput);
	else
		return input;
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
