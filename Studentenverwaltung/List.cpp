#include "List.h"

using namespace std;

const string List::FILENAME_CSV = "data.csv";
bool bs_repeat = "false";
int listSize = 0;

List::List()
{
	
}


List::~List()
{
}



//
//
// Add Student to list
//
//
void List::insert(Student* student)
{
	// save Student pntr temporarily
	Student *pntr1 = NULL, *pntr2 = NULL;

	setTail(new Student()); // allocate free space

	// if there's no free space available
	if (getTail() == NULL) {
		fprintf(stderr, "FEHLER: Kein Speicherplatz vorhanden : list.tail.");
		return;
	}

	//if there's no first element in list set first pointer to first element in list
	if (getHead() == NULL) {

		setHead(new Student());

		// if there's no free space available
		if (getHead() == NULL) {
			fprintf(stderr, "FEHLER: Kein Speicherplatz vorhanden : list.head.");
			return;
		}

		*head = *student;

		getHead()->setNext(NULL); //set next pointer to NULL
		setTail(getHead()); //set last element to first element
		getTail()->setPrev(NULL); //set last pointer to NULL
		setListSize(getListSize() + 1);
	}

	else
	{
		pntr1 = getHead(); //point to first element

		//search while there's no space available
		while (pntr1->getNext() != NULL)
			pntr1 = pntr1->getNext(); //set pntr1 to next element

		pntr1->setNext(getTail()); //allocate free space

		 //catch error if there's no free space after all
		if (pntr1 == NULL)
		{
			fprintf(stderr, "FEHLER: Kein Speicherplatz fuer letztes Element\n");
			return;
		}

		pntr2 = pntr1; //save active pointer
		pntr1 = pntr1->getNext();
		*pntr1 = *student;
		pntr1->setNext(NULL);//set next pointer to NULL
		setTail(pntr1); //set active pointer to last element in list
		pntr1->setPrev(pntr2); //set previous pointer to saved pointer
		pntr2->setNext(pntr1);//set next pointer from saved pointer to active pointer
		setListSize(getListSize() + 1);

		while (bs_repeat == true)
		{
			sort(getHead(), getHead()->getNext(), 0);
			bs_repeat = false;
		}
	}
}

//
//
//sort list
//
//
void List::sort(Student* head, Student* next, int iteration) //bubble sort // todo: repeat
{
	Student* pntr = new Student();
	if (next != NULL)
	{
		if (head->getMatriculationNumber() > next->getMatriculationNumber())
		{
			bs_repeat = true;
			*pntr = *head;
			if (next != getTail())
				head->setNext(next->getNext());
			if(next == getTail())
				head->setNext(NULL);

			head->setPrev(next);
			if(next->getNext() != NULL)
				next->getNext()->setPrev(head);
		
			if (getHead() == head)
			{
				setHead(next);
				next->setPrev(NULL);
				next->setNext(head);
			}
			else if (getHead() != head && getTail() != next)
			{
				next->setPrev(pntr->getPrev());
				pntr->getPrev()->setNext(next);
				next->setNext(head);
				head->setPrev(next);
			}
			else if (next == getTail())
			{
				head->setNext(NULL);
				head->setPrev(next);
				setTail(head);
				next->setNext(head);
				next->setPrev(pntr->getPrev());
				head->getPrev()->getPrev()->setNext(next);
				bs_repeat = true;
			}
		}
		else if (head->getMatriculationNumber() <= next->getMatriculationNumber())
		{
			*pntr = *getHead();
			if (pntr->getNext() != NULL)
			{
				for (int i = 0; i <= iteration; i++)
				{
					pntr = pntr->getNext();
				}
				sort(pntr, pntr->getNext(), iteration + 1);
			}
		}

		else
		{
			*pntr = *getHead();
			if (pntr->getNext() != NULL)
			{
				for (int i = 0; i <= iteration; i++)
				{
					pntr = pntr->getNext();
				}
				sort(pntr, pntr->getNext(), iteration + 1);
			}

			if (pntr != NULL)
				//delete pntr;

			cout << "Sortiert!";
		}

	}
}

//
//
//load csv data into Student array
//
//
void List::importToCSV()
{
	Student* importStudent = new Student();
	ifstream csv;
	string value = "";
	char c = 0;

	csv.open(FILENAME_CSV, ios::in);

	if (csv.good())
	{
		while (true)
		{

			//get first name
			getline(csv, value, ';');
			importStudent->setFirstName(value);

			if (csv.eof() != 0) //break, if getline hits the end of file
			{
				csv.close();
				break;
			}

			//get last name
			getline(csv, value, ';');
			importStudent->setLastName(value);

			//get sex
			csv.get(c);
			importStudent->setSex(c);
			csv.ignore(1);

			//get matriculation number
			getline(csv, value, ';');
			importStudent->setMatriculationNumber(atoi(value.c_str()));

			//get final grade
			getline(csv, value, ';');
			importStudent->setFinalGrade(atof(value.c_str()));

			insert(importStudent);
		}

		csv.close();

		if(getHead() != getTail())
			sort(getHead(), getHead()->getNext(), 0);
		
		/*
		while (bs_repeat == true)
		{
			bs_repeat = false;
			sort(getHead(), getHead()->getNext(), 0);
		}
		*/
	}
	else
		cout << "FEHLER: Datei \"" << FILENAME_CSV << "\" konnte nicht importiert werden." << endl << endl;
}

void List::print()
{
	unsigned short int i = 1;
	Student* pntr = getHead();

		if (getHead()!= NULL)
		{
			do
			{
				cout << "Student " << i << ":" << endl;
				cout << "__________" << endl;
				pntr->print();
				cout << "----------------------------------------------------" << endl << endl;
				pntr = pntr->getNext();
				i++;
			} while (pntr != NULL);
		}
	}


void List::exportToCSV()
{
	ofstream csv;
	Student *student;
	string filename2 = "";

	csv.open(FILENAME_CSV, ios::out);
	student = head;

	if (student != NULL)
	{
		do
		{
			csv << student->getFirstName() << ";"
				<< student->getLastName() << ";"
				<< student->getSex() << ";"
				<< student->getMatriculationNumber() << ";"
				<< student->getFinalGrade() << ";";
			student = student->getNext();

		} while (student != NULL);
	}
}

void List::remove(Student* student)
{
	if (student != getHead() && student != getTail())
	{
		student->getNext()->setPrev(student->getPrev());
		student->getPrev()->setNext(student->getNext());
		delete student;
	}
	else if (student == getHead() && student != getTail())
	{
		student->getNext()->setPrev(NULL);
		delete student;
	}
	else if (student == getTail() && student != getHead())
	{
		student->getPrev()->setNext(NULL);
		delete student;
	}
	else if (student == getTail() && student == getHead())
	{
		setHead(NULL);
		setTail(NULL);
		delete student;
	}
}

Student* List::search(int matriculationNumber)
{
	Student* start = getHead();
	Student* end = getTail();

	if (getHead()->getMatriculationNumber() == matriculationNumber && getTail()->getMatriculationNumber() == matriculationNumber)
		return start;

	//start = binary_search(start, end, (getListSize() / 2), matriculationNumber);
	start = linear_search(start, matriculationNumber);

	return start;
}

Student* List::binary_search(Student* tmp_start, Student* tmp_end, int searchIndex, int matriculationNumber)
{
		if (tmp_start->getMatriculationNumber() < matriculationNumber)
		{
			tmp_end = getTail();
			tmp_start = getHead();

			for (int i = 0; i < searchIndex; i++)
			{
				tmp_start = tmp_start->getNext();
			}
			binary_search(tmp_start, tmp_end, searchIndex + ((getListSize() - searchIndex) / 2), matriculationNumber);
		}
		if (tmp_start->getMatriculationNumber() > matriculationNumber)
		{
			tmp_start = getHead();
			tmp_end = getHead();
			for (int i = 0; i < searchIndex; i++)
			{
				tmp_end = tmp_end->getNext();
			}

			binary_search(tmp_start, tmp_end, searchIndex - ((getListSize() + searchIndex )/ 2), matriculationNumber);
		}

		if (tmp_start->getMatriculationNumber() == matriculationNumber)
		{
			return tmp_start;
		}
}

Student* List::linear_search(Student* start, int matriculationNumber)
{
	if (start->getMatriculationNumber() == matriculationNumber)
		return start;
	else if (start->getNext() != NULL)
		linear_search(start->getNext(), matriculationNumber);
	else
		return NULL;
}

void List::setHead(Student* student)
{
	this->head = student;
}
Student* List::getHead()
{
	return this->head;
}

void List::setTail(Student* student)
{
	this->tail = student;
}
Student* List::getTail()
{
	return this->tail;
}

int List::getListSize()
{
	return this->listSize;
}

void List::setListSize(int i)
{
	this->listSize = i;
}