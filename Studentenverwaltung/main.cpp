#include <iostream>;
#include <fstream>;
#include <string>;
#include <limits>;
#include <conio.h>

using namespace std;

//Constants
const double VERSION = 0.3;
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
void displayMainMenu(int &selection);
void validateInput(const int selection);
void listAllStudents(const int occSpace);
void importStudentData(int &occSpace, const string filename = FILENAME_CSV_IMPORT_STUDENTS);
void pauseSystem();
void addStudent(int &occSpace);
void exportStudentData(const int occSpace, const string filename = FILENAME_CSV_EXPORT_STUDENTS);
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
		displayMainMenu(selection); //

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
			displayTitle();
			importStudentData(occSpace);
			pauseSystem();
			break;
		case 6:
			displayTitle();
			exportStudentData(occSpace);
			pauseSystem();
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

void displayMainMenu(int &selection)
{
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
//load csv data into Student array
//
//

void importStudentData(int &occSpace, const string filename)
{
	ifstream csv;
	string value;
	char c;

	csv.open(filename);

	cout << " -------------------------- \n| Studierende importieren: |\n -------------------------- " << endl << endl;

	if (csv.good())
	{

		//clear array
		for (int i = 0; i < STUDENT_COUNT_MAX; i++)
		{
			students[i].firstName = "";
			students[i].lastName = "";
			students[i].sex = '0';
			students[i].matriculationNumber = -1;
			students[i].finalGrade = -1;
		}

		//read from csv
		for (int i = 0; i < STUDENT_COUNT_MAX; i++)
		{
			//get first name
			getline(csv, value, ';');
			students[i].firstName = value;

			if (csv.eof() != 0) //break, if getline hits the end of file
			{
				csv.close();
				occSpace = i;
				break;
			}

			//get last name
			getline(csv, value, ';');
			students[i].lastName = value;

			//get sex
			csv.get(c);
			students[i].sex = c;
			csv.ignore(1);

			//get matriculation number
			getline(csv, value, ';');
			students[i].matriculationNumber = atoi(value.c_str());

			//get final grade
			getline(csv, value, ';');
			students[i].finalGrade = atof(value.c_str());
		}

		csv.close();
		cout << "Datei \"" << filename << "\" erfolgreicht importiert." << endl << endl;
	}
	else
		cout << "FEHLER: Datei \"" << filename << "\" konnte nicht importiert werden." << endl << endl;
}

//
//
//exports array as csv
//
//

void exportStudentData(int occSpace, const string filename)
{
	ofstream csv;

	cout << " -------------------------- \n| Studierende exportieren: |\n -------------------------- " << endl << endl;

	csv.open(filename, ios::out);

	for (int i = 0; i < occSpace; i++)
	{
		csv << students[i].firstName << ";"
			<< students[i].lastName << ";"
			<< students[i].sex << ";"
			<< students[i].matriculationNumber << ";"
			<< students[i].finalGrade << ";";
	}

	if(csv.good())
		cout << "Datei \"" << filename << "\" erfolgreicht exportiert." << endl << endl;
	else
		cout << "FEHLER: Datei \"" << filename << "\" konnte nicht exportiert werden." << endl << endl;

	csv.close();
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

void validateInput(const int selection)
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

