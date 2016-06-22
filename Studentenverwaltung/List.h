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
	void sort(Student* first, Student* second);
	Student* search_linear(Student* start, int matriculationNumber);

	//setter getter
	void setHead(Student* student);
	Student* getHead();
	void setTail(Student* student);
	Student* getTail();
	void setListSize(int i);
	int getListSize();
	
private:
	Student *head, *tail, *tmp_next, *tmp_prev;
	static const std::string FILENAME_CSV;
	int list_size;
	bool bs_repeat;
};


#endif

