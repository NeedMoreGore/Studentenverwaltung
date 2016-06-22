#include "List.h"

using namespace std;

const string List::FILENAME_CSV = "data.csv";

List::List()
{
	this->bs_repeat = "false";
	this->list_size = 0;
	this->tmp_prev = new Student();
	this->tmp_next = new Student();
}


List::~List()
{

}

// Add Student to list
void List::insert(Student* student)
{
	// save Student pntr temporarily
	Student *pntr1 = NULL, *pntr2 = NULL;
	setTail(new Student()); // allocate free space
	// if there's no free space available
	if (getTail() == NULL) {
		fprintf(stderr, "FEHLER: Kein Speicherplatz vorhanden");
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
	}
}
//sort list  - bubble sort (recursive)
void List::sort(Student* left, Student* right) 
{
	if (right != NULL)
	{
		if (left->getMatriculationNumber() > right->getMatriculationNumber()) //if left is bigger than right
		{
			bs_repeat = true; //repeat until list is completly sorted
			tmp_prev = left->getPrev(); //safe element previous to left
			tmp_next = left->getNext(); //safe element next to left

			if (right != getTail()) //if right element is not tail element
			{
				left->setNext(right->getNext());
				right->getNext()->setPrev(left);
			}

			left->setPrev(right); 

			if (getHead() != left && getTail() != right) //if left and right not tail or head element
			{
				right->setPrev(tmp_prev);
				right->setNext(left);
				right->getPrev()->setNext(right);
			}
			else if (getHead() == left) //if left is head element
			{
				setHead(right);
				right->setPrev(NULL);
				right->setNext(left);
				left->setPrev(right);
			}
			else if (right == getTail()) //if right is tail element
			{
				left->setNext(NULL);
				left->setPrev(right);
				setTail(left);
				right->setNext(left);
				right->setPrev(tmp_prev);
				right->getPrev()->setNext(right);
			}
		}

		if (left->getMatriculationNumber() > right->getMatriculationNumber()) //if swapped
			tmp_next = left;
		else //if not swapped
			tmp_next = right;

		if (tmp_next->getNext() != NULL) //if it's not end of list
		{
			sort(tmp_next, tmp_next->getNext());
		}
		else if (bs_repeat) //if end of list and elements were swapped
		{
			bs_repeat = false;
			sort(getHead(), getHead()->getNext()); //start new sort
		}
		else //exit if list is sorted
			return;
	}

	return;
}



//load csv data into Student array
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

		sort(getHead(), getHead()->getNext()); //sort list after importing

		csv.close();
	}
	else
		cout << "FEHLER: Datei \"" << FILENAME_CSV << "\" konnte nicht importiert werden." << endl << endl;
}
//display entire list
void List::print()
{
	int i = 1;
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
//write student data to csv
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
//delete student from list
void List::remove(Student* student)
{
	//if student is not head or tail
	if (student != getHead() && student != getTail())
	{
		student->getNext()->setPrev(student->getPrev());
		student->getPrev()->setNext(student->getNext());
		delete student;
	}
	//if student is head but not tail
	else if (student == getHead() && student != getTail())
	{
		student->getNext()->setPrev(NULL);
		delete student;
	}
	//if student is tail but not head
	else if (student == getTail() && student != getHead())
	{
		student->getPrev()->setNext(NULL);
		delete student;
	}
	//if there's only one student in the list
	else if (student == getTail() && student == getHead())
	{
		setHead(NULL);
		setTail(NULL);
		delete student;
	}
}
//search for student in list
Student* List::search(int matriculationNumber)
{
	return search_linear(getHead(), matriculationNumber);

}

//linear search for student in list (recursive)
Student* List::search_linear(Student* start, int matriculationNumber)
{
	if (start->getMatriculationNumber() == matriculationNumber)
		return start;
	else if (start->getNext() != NULL)
		search_linear(start->getNext(), matriculationNumber);
	else
		return NULL;
}
//getter and setter
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
	return this->list_size;
}
void List::setListSize(int i)
{
	this->list_size = i;
}