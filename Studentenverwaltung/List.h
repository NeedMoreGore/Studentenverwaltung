#pragma once
#ifndef List_h
#define List_h
#include "Student.h"
#include <fstream>
#include <string>
#include <iostream>


class List
{
public:
	List();
	~List();

	void insert(Student* student);
	void remove(Student* student);
	Student* search(int matriculationnumber);
	void print();
	void importToCSV();
	void exportToCSV();
	void sort(Student* head, Student* next, int iteration);
	Student* binary_search(Student* start, Student* end, int searchIndex, int matriculationNumber);
	Student* linear_search(Student* start, int matriculationNumber);
	//setter getter
	void setHead(Student* student);
	Student* getHead();
	void setTail(Student* student);
	Student* getTail();
	void setListSize(int i);
	int getListSize();
	
private:
	Student *head, *tail; 
	static const std::string FILENAME_CSV;
	int listSize;
};


#endif

