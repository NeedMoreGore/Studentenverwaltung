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
const string FILENAME_CSV_IMPORT_STUDENTS = "import.csv";
const string FILENAME_CSV_EXPORT_STUDENTS = "export.csv";
const int SELECTION_MIN = 1, SELECTION_MAX = 7; 


//Structures
struct Student //student infos
{
	string firstName = "", lastName = "";
	char sex = '0';
	int matriculationNumber = -1;
	double finalGrade = -1;

	struct Student *next;
	struct Student *previous;
};

//Pointer
struct Student *first = NULL;
struct Student *last = NULL;


//Array
Student students[STUDENT_COUNT_MAX];

//Prototypes
void addStdnt();
void addStdnt_old(int &occSpace);
void dspMainMenu();
void dspOccSpc(const int occSpace);
void dspTitle();
void expStdntData(const int occSpace, const string filename = FILENAME_CSV_EXPORT_STUDENTS);
int getSelection();
Student getStdntData();
void initPntr(void);
void impStdntData(int &occSpace, const string filename = FILENAME_CSV_IMPORT_STUDENTS);
void listAllStdnts(const int occSpace);
void pauseSystem();
void saveStdntData(Student student, int &occSpace);
int validateSelection(const int selection);

//bool hasFreeSpace();




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
			listAllStdnts(occSpace);
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
			impStdntData(occSpace);
			pauseSystem();
			break;
		case 6:
			dspTitle();
			expStdntData(occSpace);
			pauseSystem();
			break;
		case 7:
			return 0;

		}
	}
}

//Functions
void addStdnt()
{
	Student newStudent;

	/* Zeiger zum Zugriff auf die einzelnen Elemente
	* der Struktur */
	struct Student *pntr1 = NULL;
	struct Student *pntr2 = NULL;

	/* Wurde schon Speicher für den ende-Zeiger bereitgestellt? */

	last = new Student;

	if (last == NULL) {
		printf("Konnte keinen Speicherplatz für ende "
			"reservieren\n");
		return;
	}

	/* Wir fragen ab, ob es schon ein Element in der Liste gibt.
	* Wir suchen das Element, auf das unser Zeiger *anfang
	* zeigt. Falls *anfang immer noch auf NULL zeigt, bekommt
	* *anfang die Adresse unseres 1. Elements und ist somit der
	* Kopf (Anfang) unserer Liste. */
	if (first == NULL) {
		/* Wir reservieren Speicherplatz für unsere
		* Struktur für das erste Element der Liste. */

		first = new Student;

		if (first == NULL) {
			fprintf(stderr, "Kein Speicherplatz vorhanden "
				"fuer anfang\n");
			return;
		}
		
		newStudent = getStdntData();

		first->firstName = newStudent.firstName;
		first->lastName = newStudent.lastName;
		first->sex = newStudent.sex;
		first->matriculationNumber = newStudent.matriculationNumber;
		first->finalGrade = newStudent.finalGrade;

		first->next = NULL;
		last = first;
		last->previous = NULL;
	}
	
	else 
	{
		pntr1 = first;    /* Wir zeigen auf das 1. Element. */
		while (pntr1->next != NULL)
			pntr1 = pntr1->next;
		/* Wir reservieren einen Speicherplatz für das letzte
		* Element der Liste und hängen es an. */
		
		pntr1->next = new Student;
		if (pntr1 == NULL) {

			fprintf(stderr, "Kein Speicherplatz fuer "
				"letztes Element\n");
			return;
		}


		newStudent = getStdntData();

		pntr2 = pntr1;

		pntr1 = pntr1->next;/* zeiger auf neuen Speicherplatz */
		pntr1->firstName = newStudent.firstName;
		pntr1->lastName = newStudent.lastName;
		pntr1->sex = newStudent.sex;
		pntr1->matriculationNumber = newStudent.matriculationNumber;
		pntr1->finalGrade = newStudent.finalGrade;

		pntr1->next = NULL;
		last = pntr1;
		pntr1->previous = pntr2;
		pntr2->next = pntr1;
	}
}

//
//
//Adds a new entry to array
//
//
void addStdnt_old(int &occSpace)
{
	Student newStudent;
	char selection;

	do
	{
		cout << " ---------------------- \n| Student(in) anlegen: |\n ---------------------- " << endl << endl;

		dspOccSpc(occSpace);

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
				saveStdntData(newStudent, occSpace);

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
//displays the free space of an array
//
//
void dspOccSpc(const int occSpace)
{
	cout << "Belegte Speicherplaetze: " << occSpace << " / " << STUDENT_COUNT_MAX << endl << endl;
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
void expStdntData(int occSpace, const string filename)
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

	if (csv.good())
		cout << "Datei \"" << filename << "\" erfolgreicht exportiert." << endl << endl;
	else
		cout << "FEHLER: Datei \"" << filename << "\" konnte nicht exportiert werden." << endl << endl;

	csv.close();
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
void impStdntData(int &occSpace, const string filename)
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
// Pointer initilisieren
//
//
void initPntr(void) 
{
	first = last = NULL;
}

//
//
//lists all entries in Student array
//
//
void listAllStdnts(const int occSpace)
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
//writes input to first free space of array
//
//
void saveStdntData(Student student, int &occSpace)
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

//
//
//checks array for free space and sets the value
//
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
