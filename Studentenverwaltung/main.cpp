#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <conio.h>

using namespace std;

//Constants
const double VERSION = 0.4;
const string APPNAME = "STUDENTENVERWALTUNG";
const int STUDENT_COUNT_MAX = 10;
const string FILENAME_CSV_IMPORT_STUDENTS = "import.csv", FILENAME_CSV_EXPORT_STUDENTS = "export.csv";
const int SELECTION_MIN = 1, SELECTION_MAX = 7; 


//Structures
struct Student //student infos
{
	string firstName = "", lastName = "";
	char sex = '0';
	int matriculationNumber = -1;
	double finalGrade = -1;

	struct Student *next, *previous;
};

//Pointer
struct Student *first = NULL, *last = NULL;


//Array
Student students[STUDENT_COUNT_MAX];

//Prototypes
void addStdnt(const string fristName, const string lastName, const char sex, const int matriculationNumber, const double finalGrade);
void addStdnt();
void clearStdntData();
void dspMainMenu();
void dspTitle();
void expStdntData(const string filename = FILENAME_CSV_EXPORT_STUDENTS);
int getSelection();
Student getStdntData();
void impStdntData(const string filename = FILENAME_CSV_IMPORT_STUDENTS);
void listAllStdnts();
void pauseSystem();
int validateSelection(const int selection);




int main()
{
	//Variables
	int selection = 0; //menu selection
	int occSpace = 0;

	while (true)
	{
		do
		{
			dspTitle();
			dspMainMenu();
			selection = validateSelection(getSelection());
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
			break;
		case 4:
			break;
		case 5:
			dspTitle();
			impStdntData();
			pauseSystem();
			break;
		case 6:
			dspTitle();
			expStdntData();
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
// Add Student to list
//
//
void addStdnt()
{
	Student newStudent;

	/* Zeiger zum Zugriff auf die einzelnen Elemente
	* der Struktur */
	struct Student *pntr1 = NULL, *pntr2 = NULL;

	last = new Student; // allocate free space

	// if there's no free space available
	if (last == NULL) {
		fprintf(stderr, "FEHLER: Kein Speicherplatz vorhanden.");
		return;
	}

	//if there's no first element in list set first pointer to first element in list
	if (first == NULL) {

		first = new Student;

		// if there's no free space available
		if (first == NULL) {
			fprintf(stderr, "FEHLER: Kein Speicherplatz vorhanden.");
			return;
		}
		
		newStudent = getStdntData(); //get data per user input

		//allocate input to element in list
		first->firstName = newStudent.firstName;
		first->lastName = newStudent.lastName;
		first->sex = newStudent.sex;
		first->matriculationNumber = newStudent.matriculationNumber;
		first->finalGrade = newStudent.finalGrade;

		first->next = NULL; //set next pointer to NULL
		last = first; //set last element to first element
		last->previous = NULL; //set last pointer to NULL
	}
	
	else 
	{
		pntr1 = first; //point to first element

		//search while there's no space available
		while (pntr1->next != NULL)
			pntr1 = pntr1->next; //set pntr1 to next element
		
		pntr1->next = new Student; //allocate free space
		
		//catch error if there's no free space after all
		if (pntr1 == NULL)
		{
			fprintf(stderr, "FEHLER: Kein Speicherplatz fuer letztes Element\n");
			return;
		}

		newStudent = getStdntData(); //get user input

		pntr2 = pntr1; //save active pointer

		pntr1 = pntr1->next; //point to free space
		pntr1->firstName = newStudent.firstName;
		pntr1->lastName = newStudent.lastName;
		pntr1->sex = newStudent.sex;
		pntr1->matriculationNumber = newStudent.matriculationNumber;
		pntr1->finalGrade = newStudent.finalGrade;

		pntr1->next = NULL; //set next pointer to NULL
		last = pntr1; //set active pointer to last element in list
		pntr1->previous = pntr2; //set previous pointer to saved pointer
		pntr2->next = pntr1; //set next pointer from saved pointer to active pointer
	}
}

//
//
// Add Student to list
//
//
void addStdnt(const string firstName, const string lastName, const char sex, const int matriculationNumber, const double finalGrade)
{
	Student newStudent;

	/* Zeiger zum Zugriff auf die einzelnen Elemente
	* der Struktur */
	struct Student *pntr1 = NULL, *pntr2 = NULL;

	last = new Student; // allocate free space

						// if there's no free space available
	if (last == NULL) 
	{
		fprintf(stderr, "FEHLER: Kein Speicherplatz vorhanden.");
		return;
	}

	//if there's no first element in list set first pointer to first element in list
	if (first == NULL)
	{


		first = new Student;

		// if there's no free space available
		if (first == NULL) 
		{
			fprintf(stderr, "FEHLER: Kein Speicherplatz vorhanden.");
			return;
		}
									 //allocate input to element in list
		first->firstName = firstName;
		first->lastName = lastName;
		first->sex = sex;
		first->matriculationNumber = matriculationNumber;
		first->finalGrade = finalGrade;

		first->next = NULL; //set next pointer to NULL
		last = first; //set last element to first element
		last->previous = NULL; //set last pointer to NULL
	}

	else
	{
		pntr1 = first; //point to first element

					   //search while there's no space available
		while (pntr1->next != NULL)
			pntr1 = pntr1->next; //set pntr1 to next element

		pntr1->next = new Student; //allocate free space

								   //catch error if there's no free space after all
		if (pntr1 == NULL)
		{
			fprintf(stderr, "FEHLER: Kein Speicherplatz fuer letztes Element\n");
			return;
		}

		pntr2 = pntr1; //save active pointer

		pntr1 = pntr1->next; //point to free space
		pntr1->firstName = firstName;
		pntr1->lastName = lastName;
		pntr1->sex = sex;
		pntr1->matriculationNumber = matriculationNumber;
		pntr1->finalGrade = finalGrade;

		pntr1->next = NULL; //set next pointer to NULL
		last = pntr1; //set active pointer to last element in list
		pntr1->previous = pntr2; //set previous pointer to saved pointer
		pntr2->next = pntr1; //set next pointer from saved pointer to active pointer
	}
}

//
//
// clears the list
//
//
void clearStdntData() 
{
	struct Student *pntr1, *pntr2;
	bool singleEntry = true;

	/* Ist �berhaupt eine Liste zum L�schen vorhanden? */
	if (first != NULL) 
	{
		/* Es ist eine vorhanden ... */
		pntr1 = first->next;
		while (pntr1 != NULL) 
		{
			singleEntry = false;
			pntr2 = first->next->next;
			if (pntr2 == NULL)
				break;
			first->next = pntr2;
			pntr2->previous = first;
			delete pntr1;
			pntr1 = pntr2;
		}

		/* Jetzt l�schen wir erst den Anfang der Liste und
		* dann das Ende der Liste. */
		delete first;
		if(!singleEntry)
			delete last;
		first = NULL;
		last = NULL;
	}
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
		cout << "5) Studierende importieren" << endl;
		cout << "6) Studierende exportieren" << endl;
		cout << "7) Programmende" << endl << endl;

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
//exports array as csv
//
//
void expStdntData(const string filename)
{
	ofstream csv;
	struct Student *pntr;
	string filename2 = "";

	cout << " -------------------------- \n| Studierende exportieren: |\n -------------------------- " << endl << endl;

	cout << "Geben Sie einen Dateinamen an: (Druecken Sie Enter fuer Standardname: export.csv)" << endl;
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear buffer otherwise it won't work properly ToDo: Replace "cin >> .." with "getline()"

	getline(cin, filename2);

	if (!filename2.empty())
		csv.open(filename2, ios::out);
	else
		csv.open(filename, ios::out);
	pntr = first;

	if (pntr != NULL)
	{
		do
		{
			csv << pntr->firstName << ";"
				<< pntr->lastName << ";"
				<< pntr->sex << ";"
				<< pntr->matriculationNumber << ";"
				<< pntr->finalGrade << ";";
			pntr = pntr->next;

		} while (pntr != NULL);
	}

	if (csv.good())
		cout << "Datei \"" << filename << "\" erfolgreicht exportiert." << endl << endl;
	else
		cout << "FEHLER: Datei \"" << filename << "\" konnte nicht exportiert werden." << endl << endl;
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

	return selection;
}

//
//
//get student data via user input
//
//
Student getStdntData()
{
	Student newStudent;

	cout << "Vorname:        ";
	cin >> newStudent.firstName;
	cout << "Nachname:       ";
	cin >> newStudent.lastName;
	cout << "Geschlecht:     ";
	cin >> newStudent.sex;
	cout << "Matrikelnummer: ";
	cin >> newStudent.matriculationNumber;

	return newStudent;
}

//
//
//load csv data into Student array
//
//
void impStdntData(const string filename)
{
	Student importStudent;
	ifstream csv;
	string value;
	char c;

	csv.open(filename);

	cout << " -------------------------- \n| Studierende importieren: |\n -------------------------- " << endl << endl;

	if (csv.good())
	{

		clearStdntData(); //clear list

		//read from csv
		while(true)
		{
		
			//get first name
			getline(csv, value, ';');
			importStudent.firstName = value;

			if (csv.eof() != 0) //break, if getline hits the end of file
			{
				csv.close();
				break;
			}

			//get last name
			getline(csv, value, ';');
			importStudent.lastName = value;

			//get sex
			csv.get(c);
			importStudent.sex = c;
			csv.ignore(1);

			//get matriculation number
			getline(csv, value, ';');
			importStudent.matriculationNumber = atoi(value.c_str());

			//get final grade
			getline(csv, value, ';');
			importStudent.finalGrade = atof(value.c_str());

			addStdnt(importStudent.firstName, importStudent.lastName, importStudent.sex, importStudent.matriculationNumber, importStudent.finalGrade);
		}

		csv.close();
		cout << "Datei \"" << filename << "\" erfolgreicht importiert." << endl << endl;
	}
	else
		cout << "FEHLER: Datei \"" << filename << "\" konnte nicht importiert werden." << endl << endl;
}

//
//
//lists all entries in Student array
//
//
void listAllStdnts()
{
	struct Student *pntr;
	int i = 1;

	pntr = first;

	cout << " ------------------------ \n| Student(in) auflisten: |\n ------------------------ " << endl << endl;

	if (pntr != NULL)
	{
		do
		{
			cout << "Student " << i << ":" << endl;
			cout << "__________" << endl;
			cout << "		Vorname:        " << pntr->firstName << endl;
			cout << "		Nachname:       " << pntr->lastName << endl;
			cout << "		Geschlecht:     " << pntr->sex << endl;
			cout << "		Matrikelnummer: " << pntr->matriculationNumber << endl;
			cout << "		Abschlussnote:  " << pntr->finalGrade << endl;
			cout << "----------------------------------------------------" << endl << endl;
			pntr = pntr->next;
			i++;
		} while (pntr != NULL);
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

//
//
//checks if input is valid
//
//
int validateSelection(const int selection)
{
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
