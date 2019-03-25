/*********************************************************************************************************
Diego Pina
Dr Ragsdale
3/8/2019

Project Description: This project defines and implements a List ADT as an in-memory, ordered, double 
linked list. 
**********************************************************************************************************/
#include "List.h"
#include <iostream>
#include <string>

using namespace std;

//constructor - creates an "empty" linked list by setting Head to NULL
List::List() : Head(NULL)
{}

// destructor - deletes EVERY node in the linked list since each node
//was DYNAMICALLY allocated
List::~List()
{
	Node * Temp = Head;
	while (Head != NULL)
	{
		Temp = Head->next;
		delete Head;
		Head = Temp;
	}
}

//This function uses a for loop to traverse the list until it finds the data it needs to delete. 
//It has four cases it takes into account: The data wasnt found, data is in the middle of list(or just one nodde), 
//data is at the end of the list, and dadta was at the beggining of list.
bool List::Delete(ListType data)
{
	bool found = false;
	Node * findNode = Head;

	//for loop traverses list until data is found or it gets to the end of the list
	for (findNode = Head; findNode->info != data && findNode->next != NULL; findNode = findNode->next) {}

	//No data found
	if (findNode->info != data)
		return found;
	else {
		//node is not at beggining
		if (findNode->prev == NULL) {

			//Node is not at the end, so its in the middle
			if (findNode->next != NULL) {
				Head = findNode->next;
				findNode->next->prev = NULL;
			}
			//Else its the first and only node
			else
				Head = NULL;
			found = true;
		}

		//Node is at the end of list
		else if (findNode->next == NULL) {
			findNode->prev->next = NULL;
			found = true;
		}

		//Node is at beggining of list
		else {
			findNode->prev->next = findNode->next;
			findNode->next->prev = findNode->prev;
			found = true;
		}

		delete findNode;
	}
	return found;
}

//This function gets two strings, 1) the string to be edited and 2) the edited text; the function locates the string
//to be edited and then edits the text. The function then has to revaluate where in the list the new data belongs
//It reuses the code by calling on the "Delete" function first and then the "Insert" function.
bool List::Edit(ListType findData, ListType newData) {
	bool found = false;
	Node * findNode = Head;

	for (findNode = Head; findNode->info != findData && findNode->next != NULL; findNode = findNode->next) {}
	if (findNode->info != findData)
		return found;
	else {
		if (Delete(findData))
			found = Insert(newData);
	}
	return found;
}


//Inserts new node with the data that was sent in correct alphabetical order.
bool List::Insert(ListType data) {
	Node * P = new Node;
	if (P == NULL)
		return false;

	//initialize the node
	P->info = data;
	P->next = NULL;
	P->prev = NULL;
	Node * findNode = Head;

	//If list is empty
	if (Head == NULL) {
		Head = P;
		return true;
	}

	else {
		//If new node is smallest item on list
		if (findNode->info >= P->info) {
			P->prev = NULL;
			P->next = findNode;
			findNode->prev = P;
			Head = P;
			return true;
		}
		
		//Traverses list to find when new node stops being of lesser value
		for (findNode = Head; findNode->next != NULL; findNode = findNode->next) {}
		if (findNode->info < P->info) {
			P->prev = findNode;
			P->next = NULL;
			findNode->next = P;
			return true;
		}
		else {
			for (findNode = Head; findNode->info < P->info; findNode = findNode->next) {}
			P->prev = findNode->prev;
			P->next = findNode;
			findNode->prev->next = P;
			findNode->prev = P;
			return true;
		}
	}
	return false;
}


//Prints the data in each node from Head to the end of the list
void List::Print() {
	//traverse entire list, stop when p contains NULL
	for (Node * P = Head; P != NULL; P = P->next)
		cout << P->info << endl;
}