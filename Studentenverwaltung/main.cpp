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
void editStdntData();

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
			dspTitle();
			editStdntData(); 
			pauseSystem();
			break;
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
	searchFor = sList->search(matriculationNumber);


	cout << "\nSuchergebnis: " << endl;
	cout << "__________" << endl;
	cout << "		Vorname:        " << searchFor->getFirstName()<< endl;
	cout << "		Nachname:       " << searchFor->getLastName() << endl;
	cout << "		Geschlecht:     " << searchFor->getSex() << endl;
	cout << "		Matrikelnummer: " << searchFor->getMatriculationNumber() << endl;
	cout << "		Abschlussnote:  " << searchFor->getFinalGrade() << endl;
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
			searchFor->edit();
			break;
		case 2:
			sList->remove(searchFor);
			break;
		case 3:
			break;
		default:
			cout << "\nBitte geben Sie einen gültigen Menüpunkt an." << endl;
		}
	} while (selection < 1 || selection > 3);
}


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