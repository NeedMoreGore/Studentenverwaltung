#include <iostream>;
#include <fstream>;
#include <string>;
#include <limits>;
#include <conio.h>

using namespace std;

//Constants
const double VERSION = 0.2;
const string APPNAME = "STUDENTENVERWALTUNG";
const int STUDENT_COUNT_MAX = 10;
const string FILENAME_CSV_IMPORT_STUDENTS = "import.csv";
const string FILENAME_CSV_EXPORT_STUDENTS = "export.csv";
const int SELECTION_MIN = 1;
const int SELECTION_MAX = 7;


//Structures
struct Student //student infos
{
	string firstName = "";
	string lastName = "";
	char sex = '0';
	int matriculationNumber = -1;
	float finalGrade = -1;
};

//Array
Student students[STUDENT_COUNT_MAX];

//Prototypes
int displayMainMenu();
void validateInput(int selection);
void listAllStudents(const int occSpace);
void pauseSystem();
void addStudent(int &occSpace);
void displayTitle();
//bool hasFreeSpace();
void displayOccSpace(const int occSpace);
void saveStudentData(Student student, int &occSpace);










int main()
{
	//Variables
	int selection = 0; //menu selection
	int occSpace = 0;

	while (true)
	{
		selection = displayMainMenu(); //

		switch (selection)
		{
		case 1:
			displayTitle();
			listAllStudents(occSpace);
			pauseSystem();
			break;
		case 2:
			displayTitle();
			addStudent(occSpace);
			pauseSystem();
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			return 0;

		}
	}
}









//Functions

//
//
//displays menu in console
//
//

int displayMainMenu()
{
	int selection = 0;

	do
	{
		displayTitle();

		cout << "1) Student(in) auflisten" << endl;
		cout << "2) Student(in) anlegen" << endl;
		cout << "3) Student(in) suchen" << endl;
		cout << "4) Student(in) bearbeiten" << endl;
		cout << "5) Studierende importieren" << endl;
		cout << "6) Studierende exportieren" << endl;
		cout << "7) Programmende" << endl << endl;

		cout << "Auswahl: ";

		cin >> selection; //User input: menu selection

		validateInput(selection);
	} while (selection < SELECTION_MIN || selection > SELECTION_MAX); //display selection menu until 7 is pressed

	return selection;
}

//
//
//lists all entries in Student array
//
//

void listAllStudents(const int occSpace)
{
	cout << " ------------------------ \n| Student(in) auflisten: |\n ------------------------ " << endl << endl;
	for (int i = 0; i < occSpace; i++)
	{
		cout << "Student " << i + 1 << ":" << endl;
		cout << "__________" << endl;
		cout << "		Vorname:        " << students[i].firstName << endl;
		cout << "		Nachname:       " << students[i].lastName << endl;
		cout << "		Geschlecht:     " << students[i].sex << endl;
		cout << "		Matrikelnummer: " << students[i].matriculationNumber << endl;
		cout << "		Abschlussnote:  " << students[i].finalGrade << endl;
		cout << "----------------------------------------------------" << endl << endl;
	}
}

//
//
//Adds a new entry to array
//
//

void addStudent(int &occSpace)
{
	Student newStudent;
	char selection;

	do
	{
		cout << " ---------------------- \n| Student(in) anlegen: |\n ---------------------- " << endl << endl;

		displayOccSpace(occSpace);

		if (occSpace == STUDENT_COUNT_MAX)
			break;

		cout << "Vorname:        ";
		cin >> newStudent.firstName;
		cout << "Nachname:       ";
		cin >> newStudent.lastName;
		cout << "Geschlecht:     ";
		cin >> newStudent.sex;
		cout << "Matrikelnummer: ";
		cin >> newStudent.matriculationNumber;

		do
		{
			cout << endl << "Eingabe speichern?(j/n): ";
			cin >> selection;
			cout << endl;

			if (selection == 'j')
			{
				saveStudentData(newStudent, occSpace);

				cout << "Eintrag gespeichert" << endl;
			}
			else if (selection == 'n')
			{
				cout << "Eintrag verworfen" << endl;
			}
		} while (selection != 'j' && selection != 'n');

		do
		{
			cout << endl << "Wollen Sie einen weiteren Studenten hinzufuegen?(j/n): ";
			cin >> selection;
			cout << endl;
		} while (selection != 'j' && selection != 'n');
	} while (selection == 'j');

}

//
//
//clears the console and displays the title
//
//

void displayTitle()
{
	system("cls");
	cout << "=========================================================\n ============ " << APPNAME << " ==== V" << VERSION << " ============ \n=========================================================" << endl << endl;
}

//
//
//checks array for free space and sets the value
//NOT NEEDED ATM
//

/*
void calcOccSpace(int &occSpace)
{
for (int i = 0; i < STUDENT_COUNT_MAX; i++)
{
if (students[i].matriculationNumber == -1)
{
occSpace = i;
}
if (students[STUDENT_COUNT_MAX - 1].matriculationNumber != -1)
{
occSpace = STUDENT_COUNT_MAX;
}
}
}

*/

//
//
//displays the free space of an array
//
//

void displayOccSpace(const int occSpace)
{
	cout << "Belegte Speicherplaetze: " << occSpace << " / " << STUDENT_COUNT_MAX << endl << endl;
}

//
//
//writes input to first free space of array
//
//

void saveStudentData(Student student, int &occSpace)
{
	students[occSpace].firstName = student.firstName;
	students[occSpace].lastName = student.lastName;
	students[occSpace].sex = student.sex;
	students[occSpace].matriculationNumber = student.matriculationNumber;
	students[occSpace].finalGrade = -1;

	occSpace++;
}

//
//
//checks if input is valid
//
//

void validateInput(int selection)
{
	if (!cin.good() || (selection < SELECTION_MIN || selection > SELECTION_MAX))
	{
		cin.clear(); //clear flag
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer
		cout << endl << "Bitte waehlen Sie einen gueltigen Menuepunkt aus." << endl << endl;
		system("pause");
	}
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

