#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <conio.h>
#include "List.h"
#include "Student.h"

using namespace std;

//Constants
const double VERSION = 1.0;
const string APPNAME = "STUDENTENVERWALTUNG";

const int SELECTION_MIN = 1, SELECTION_MAX = 5; 

//Pointer
Student *head = NULL, *tail = NULL;

/*
//Prototypes
void addStdnt(const string fristName, const string lastName, const char sex, const int matriculationNumber, const double finalGrade);

void clearStdntData();
void deleteListElement(Student &deleteStdnt);
void editListElement(Student &editStdnt);
void editStdntData();



int validateSelection(const int selection);
*/

void addStdnt();
string checkInput(string input);
double checkInput(double input);
char checkInput(char input);
void dspMainMenu();
void dspTitle();
Student* getStdntData();
void listAllStdnts();
int getSelection();
void pauseSystem();
void searchStdnt();

List* sList;

int main()
{
	sList = new List();
	sList->importToCSV();

	//Variables
	int selection = 0; //menu selection

	while (true)
	{
		do
		{
			dspTitle();
			dspMainMenu();
			selection = getSelection();
		} while (selection == 0);

		switch (selection)
		{
		case 1:
			dspTitle();
			listAllStdnts();
			pauseSystem();
			break;
		case 2:
			dspTitle();
			addStdnt();
			pauseSystem();
			break;
			
		case 3:
			dspTitle();
			searchStdnt();
			pauseSystem();
			break;
			
		case 4:
			/*
			dspTitle();
			editStdntData(); 
			pauseSystem();
			break;
			*/
		case 5:
			sList->exportToCSV();
			return 0;

		}
	}
}

//Functions

//
//
// Add Student to list
//
//
void addStdnt()
{
	sList->insert(getStdntData());
}

//
//
//lists all entries in Student array
//
//
void listAllStdnts()
{
	cout << " ------------------------ \n| Student(in) auflisten: |\n ------------------------ " << endl << endl;

	sList->print();
}

//
//
// checks if input was empty or not
//
//
string checkInput(string input)
{
	string newInput = "";

	getline(cin, newInput);

	if (!newInput.empty())
		return newInput;
	else
		return input;
}

char checkInput(char input)
{
	string newInput = "";

	getline(cin, newInput);

	if (!newInput.empty())
		return input = newInput.at(0);
	else
		return input;
}

double checkInput(double input)
{
	string newInput = "";

	getline(cin, newInput);

	if (!newInput.empty())
		return input = stod(newInput);
	else
		return input;
}

/*

//
//
// clears the list
//
//
void clearStdntData() 
{
	struct Student *pntr1, *pntr2;
	bool singleEntry = true;

	if (head != NULL) 
	{
		pntr1 = head->next;
		while (pntr1 != NULL) 
		{
			singleEntry = false;
			pntr2 = head->next->next;
			if (pntr2 == NULL)
				break;
			head->next = pntr2;
			pntr2->previous = head;
			delete pntr1;
			pntr1 = pntr2;
		}

		delete head;
		if(!singleEntry)
			delete tail;
		head = NULL;
		tail = NULL;
	}
}

//
//
// delete single list element
//
//

void deleteListElement(Student &deleteStdnt)
{
	if (&deleteStdnt == head && &deleteStdnt == tail)
	{
		delete &deleteStdnt;
		head = NULL;
		tail = NULL;
	}

	else if (&deleteStdnt == head)
	{
		head = deleteStdnt.next;
		head->previous = NULL;
		delete &deleteStdnt;
	}

	else if (&deleteStdnt == tail)
	{
		tail = deleteStdnt.previous;
		tail->next = NULL;
		delete &deleteStdnt;
	}

	else
	{
		deleteStdnt.next->previous = deleteStdnt.previous;
		deleteStdnt.previous->next = deleteStdnt.next;
		delete &deleteStdnt;
	}
}

*/

//
//
//displays menu in console
//
//
void dspMainMenu()
{
		cout << "1) Student(in) auflisten" << endl;
		cout << "2) Student(in) anlegen" << endl;
		cout << "3) Student(in) suchen" << endl;
		cout << "4) Student(in) bearbeiten" << endl;
		cout << "5) Programmende" << endl << endl;

		cout << "Auswahl: ";
}

//
//
//clears the console and displays the title
//
//
void dspTitle()
{
	system("cls");
	cout << "=========================================================\n ============ " << APPNAME << " ==== V" << VERSION << " ============ \n=========================================================" << endl << endl;
}

/*

//
//
// delete single entry from list
//
//
void editStdntData()
{
	Student *searchFor = NULL;
	int matriculationNumber = 0;
	int selection;

	cout << " -------------------------- \n| Studierende bearbeiten: |\n -------------------------- " << endl << endl;

	cout << "Geben Sie bitte die Matrikelnummer ein: " << endl;

	cin >> matriculationNumber;

	//start search at the first element
	searchFor = head;

	while (searchFor->matriculationNumber != matriculationNumber)
	{
		if (searchFor == tail)
			break;
		searchFor = searchFor->next;
	}

	if (searchFor->matriculationNumber == matriculationNumber)
	{
		cout << "\nSuchergebnis: " << endl;
		cout << "__________" << endl;
		cout << "		Vorname:        " << searchFor->firstName << endl;
		cout << "		Nachname:       " << searchFor->lastName << endl;
		cout << "		Geschlecht:     " << searchFor->sex << endl;
		cout << "		Matrikelnummer: " << searchFor->matriculationNumber << endl;
		cout << "		Abschlussnote:  " << searchFor->finalGrade << endl;
		cout << "----------------------------------------------------" << endl << endl;

		cout << "\n1. Student bearbeiten" << endl;
		cout << "2. Student loeschen" << endl;
		cout << "3. Verlassen" << endl << endl;
		cout << "Auswahl: ";
		cin >> selection;

		do
		{
			switch (selection)
			{
			case 1:
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer otherwise it won't work properly
				editListElement(*searchFor);
				break;
			case 2:
				deleteListElement(*searchFor);
				break;
			case 3:
				break;
			default:
				cout << "\nBitte geben Sie einen gültigen Menüpunkt an." << endl;
			}
		} while (selection < 1 || selection > 3);
	}
	else
		cout << "\nKein Student mit der angegebenen Matrikelnummer gefunden!" << endl << endl;
}

//
//
// edit single list element
//
//
void editListElement(Student &editStdnt)
{
	cout << "\nBearbeiten: " << endl;
	cout << "__________" << endl;
	cout << "		Vorname:        ";
	editStdnt.firstName = checkInput(editStdnt.firstName);
	cout << "		Nachname:       ";
	editStdnt.lastName = checkInput(editStdnt.lastName);
	cout << "		Geschlecht:     ";
	editStdnt.sex = checkInput(editStdnt.sex);
	cout << "		Abschlussnote:  ";
	editStdnt.finalGrade = checkInput(editStdnt.finalGrade);

	cout << "\nNeuer Datensatz: " << endl;
	cout << "__________" << endl;
	cout << "		Vorname:        " << editStdnt.firstName << endl;
	cout << "		Nachname:       " << editStdnt.lastName << endl;
	cout << "		Geschlecht:     " << editStdnt.sex << endl;
	cout << "		Matrikelnummer: " << editStdnt.matriculationNumber << endl;
	cout << "		Abschlussnote:  " << editStdnt.finalGrade << endl;
	cout << "----------------------------------------------------" << endl << endl;

}

*/
//
//
//return value of user input
//
//
int getSelection()
{
	int selection = 0;

	cin >> selection; //User input: menu selection

	if (!cin.good() || (selection < SELECTION_MIN || selection > SELECTION_MAX))
	{
		cin.clear(); //clear flag
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer
		cout << endl << "Bitte waehlen Sie einen gueltigen Menuepunkt aus." << endl << endl;
		system("pause");
		return 0;
	}
	else
		return selection;
}
/*
*/

//
//
//get student data via user input
//
//
Student* getStdntData()
{
	Student* newStudent = new Student();
	string firstName;
	string lastName;
	char sex;
	int matriculationNumber;

	cout << "Vorname:        ";
	cin >> firstName;
	cout << "Nachname:       ";
	cin >> lastName;
	cout << "Geschlecht:     ";
	cin >> sex;
	cout << "Matrikelnummer: ";
	cin >> matriculationNumber;

	newStudent->setFirstName(firstName);
	newStudent->setLastName(lastName);
	newStudent->setSex(sex);
	newStudent->setMatriculationNumber(matriculationNumber);

	return newStudent;
}





void searchStdnt()
{
	Student *searchFor;

	int matriculationNumber = 0;

	cout << " -------------------------- \n| Studierende suchen: |\n -------------------------- " << endl << endl;

	cout << "Geben Sie bitte die Matrikelnummer ein: " << endl; 

	cin >> matriculationNumber;

	//start search at the first element
	searchFor = sList->search(matriculationNumber);

	if(searchFor != NULL)
	{

	cout << "\nSuchergebnis: " << endl;
	cout << "__________" << endl;
	cout << "		Vorname:        " << searchFor->getFirstName() << endl;
	cout << "		Nachname:       " << searchFor->getLastName() << endl;
	cout << "		Geschlecht:     " << searchFor->getSex() << endl;
	cout << "		Matrikelnummer: " << searchFor->getMatriculationNumber() << endl;
	cout << "		Abschlussnote:  " << searchFor->getFinalGrade() << endl;
	cout << "----------------------------------------------------" << endl << endl;
	}
	else
		cout << "\nKein Student mit der angegebenen Matrikelnummer gefunden!" << endl << endl;
}



//
//
//Pauses the programm (only Windows)
//
//
void pauseSystem()
{
	cout << "Druecken Sie eine beliebige Taste um in das Hauptmenue zu gelangen..." << endl << endl;
	_getch(); //pause until key is pressed
}

/*
//
//
//checks if input is valid
//
//
int validateSelection(const int selection)
{

}

*/