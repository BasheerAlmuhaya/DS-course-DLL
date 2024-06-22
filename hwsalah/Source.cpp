// DLList.cpp : main project file.
/*    WRITTEN BY VISUAL STUDIO 2012
 *
 *     DEPARTMENT OF SOFTWARE AND IT      - SECOND LEVEL
 *     BY - ENG SALAH_ALSSAYANY
 */

// Don't change or delete this header file
// #include "stdafx.h"
#include <string.h> //TO USE null value
#include <iostream>

using namespace std;

// this namespace used for variable on the parameters of main
// using namespace System;
typedef double object;

// class Node instead of the struct

class DoubleLinkedListNode
{

public:
	DoubleLinkedListNode *Previous;
	object data;
	DoubleLinkedListNode *Next;

	// PROVIDING CONSTRUCTORES
	// DEFAULT CONSTRUCTOR
	DoubleLinkedListNode() : data(0.0)
	{
		Next = NULL;
		Previous = NULL;
	}
	// THIRD CONSTRUCTOR ONLY WITH DATA CONSTRUCTOR

	DoubleLinkedListNode(object data) : data(data)
	{
		Next = NULL;
		Previous = NULL;
	}
};
////CLASS DOUBLE LINKED LIST
class DoubleLinkedList
{

	// PRIVATE DATA AND OPERATIONS THAT WILL BE CALLED ONLY WITH THE PUBLIC MEMBERS
private:
	DoubleLinkedListNode *Head, *Tail;
	// RECURSIVE METHOD
	int size(DoubleLinkedListNode *n)
	{
		if (n == NULL)
			return 0;
		return (1 + size(n->Next));
	}

	bool isEmpty() { return (Head == NULL); }

	void addNodeBetween(DoubleLinkedListNode *currPrev,
											DoubleLinkedListNode *NewNode, DoubleLinkedListNode *curr)
	{
		NewNode->Next = curr;
		NewNode->Previous = currPrev;
		currPrev->Next = NewNode;
		curr->Previous = NewNode;
	}

public:
	// DEFAULT CONSTRUCTOR
	DoubleLinkedList()
	{
		Head = NULL;
		Tail = NULL;
	}
	// PARAMETERIZED CONSTRUCTOR THAT MAY ACCEPT LIST
	DoubleLinkedList(DoubleLinkedListNode *List) {}
	// GETTERS AND SETTERS FOR THE HEAD
	DoubleLinkedListNode *getHead() { return (this->Head); }

	// 1- ADDING THE NODE TO THE LAST OF THE LIST
	void addNodeLast(DoubleLinkedListNode *v)
	{
		if (isEmpty())
		{
			Head = Tail = v;
			return;
		}
		Tail->Next = v;
		v->Previous = Tail;
		Tail = v;
	}
	// 2 - ADDING THE NODE TO THE BEGINING
	void addNodeFirst(DoubleLinkedListNode *v)
	{
		if (isEmpty())
		{
			Head = Tail = v;
			return;
		}
		Head->Previous = v;
		v->Next = Head;
		Head = v;
	}
	// 3- ADDING THE NODE BEFOR THE CURRENT NODE THAT HAVE THE FOLLOWING DATA
	void addNodeBefore(object befor, object d)
	{
		if (isEmpty())
		{
			cout << "\n cann't add to an empty list THE NODE WILL BE ADDED FIRST ";
			addNodeFirst(new DoubleLinkedListNode(d));
			return;
		}
		DoubleLinkedListNode *current = searchNode(befor);
		if (current == NULL)
		{
			cout << "\n Node with value " << d << " are not found addition failed \n";
			return;
		}
		else if (current->Previous == NULL)
		{
			addNodeFirst(new DoubleLinkedListNode(d));
		}
		// else if (current->Next==NULL){   addNodeLast(new DoubleLinkedListNode(d));  }
		else
		{
			addNodeBetween(current->Previous, new DoubleLinkedListNode(d), current);
			// DoubleLinkedListNode *p=new DoubleLinkedListNode(d);
			// current->Previous->Next=p;
			// current->Previous=p;
			// p->Next=
		}
	}

	void deleteNodeFirst(object d)
	{
		DoubleLinkedListNode *p = Head;
		if (isEmpty())
		{
			cout << "\nerror dll is empty";
			return;
		}
		if (size(p) == 1)
		{
			Head = Tail = NULL;
			delete p;
			return;
		}
		Head = p->Next;
		(p->Next)->Previous = NULL;
		delete p;
	}
	void deleteNodeLast(object d)
	{
		DoubleLinkedListNode *p = Tail;
		if (isEmpty())
		{
			cout << "\nerror dll is empty";
			return;
		}
		if (size(Head) == 1)
		{
			Head = Tail = NULL;
			delete p;
			return;
		}
		Tail = p->Previous;
		(p->Previous)->Next = NULL;
		delete p;
	}
	void deleteNode(object d)
	{
		DoubleLinkedListNode *p = searchNode(d);
		if (p == NULL)
		{
			cout << "\nthe node" << d << "not found\n";
			return;
		}
		if (p->Next == NULL)
		{
			deleteNodeLast(d);
			return;
		}
		if (p->Previous == NULL)
		{
			deleteNodeFirst(d);
			return;
		}
		(p->Previous)->Next = p->Next;
		(p->Next)->Previous = p->Previous;
		delete p;
	}

	// DELETE THE NODE THAT HAS A VALUE
	void deleteAt(int index)
	{
		int counter = 0;
		if (index > size(Head))
		{
			cout << "the node of" << index << "not found";
			return;
		}
		if (isEmpty())
		{
			cout << "\nerror dll is empty";
			return;
		}
		DoubleLinkedListNode *p = Head;
		while (counter != index)
		{
			counter++;
			p = p->Next;
		}
		deleteNode(p->data);
	}
	// PRINTING BUT NOT WITH RECURRSION
	void print()
	{
		if (isEmpty())
		{
			cout << "\n empty List !";
			return;
		}
		DoubleLinkedListNode *temp = Head;
		cout << endl;
		while (temp != NULL)
		{
			cout << temp->data << "\t\t";
			temp = temp->Next;
		}
		cout << endl;
	}
	// RECURSSION METHOD TO COUNT THE NODES
	int LengthIs()
	{
		return (size(Head));
	}

	// RELEASE ALL NODES ONE BY ONE
	void destroyList(DoubleLinkedListNode *v)
	{
		if (v == NULL)
			return;
		destroyList(v->Next);
		cout << "\n Destroying ......... " << v->data;
		delete v;
	}

	// WILL BE CALLED BY THE OBJECT OF THAT CLASS AND GET HEAD
	void printRevers(DoubleLinkedListNode *v)
	{
		if (v == NULL)
		{
			cout << endl;
			return;
		}
		printRevers(v->Next);
		cout << v->data << "\t\t";
	}
	// PRINTING THE ITEMS OF THE LIST USING RECURRSION
	void print(DoubleLinkedListNode *v)
	{
		if (v == NULL)
		{
			cout << endl;
			return;
		}
		cout << v->data << "\t\t";
		print(v->Next);
	}
	// THIS METHOD WILL SEARCH FOR THE NODE TO ADD BEFOR IT
	DoubleLinkedListNode *searchNode(object d)
	{
		if (isEmpty())
		{
			cout << "\nError Empty List";
			return NULL;
		}
		else
		{
			bool found = false;
			DoubleLinkedListNode *ptr = Head;
			while (ptr != NULL)
			{
				if (ptr->data == d)
				{
					found = true;
					break;
				}
				ptr = ptr->Next;
			}
			if (found)
			{
				return ptr;
			}
			else
			{
				return NULL;
			}
		}
	}

	// DESTRUCTOR THAT WILL RELEASE THE HEAD AND TAIL FROM THE LISTS
	~DoubleLinkedList()
	{
		destroyList(Head);
		Tail = NULL;
	}
};

//
int main(/*array<System::String ^> ^args*/)
{
	DoubleLinkedList *list = new DoubleLinkedList();

	list->addNodeFirst(new DoubleLinkedListNode(50.50));
	list->print();
	cout << endl;
	system("pause");
	list->addNodeLast(new DoubleLinkedListNode(80.50));
	list->print();
	cout << endl;
	system("pause");
	list->addNodeFirst(new DoubleLinkedListNode(70.50));
	list->print();
	cout << endl;
	system("pause");
	list->addNodeLast(new DoubleLinkedListNode(90.50));
	list->print();
	cout << endl;
	system("pause");
	list->addNodeFirst(new DoubleLinkedListNode(60.50));
	list->print();
	cout << endl;
	system("pause");
	list->deleteNodeFirst(0);
	list->print();
	cout << endl;
	system("pause");
	list->deleteNodeLast(0);
	list->print();
	cout << endl;
	system("pause");
	list->deleteNode(80.50);
	list->print();
	cout << endl;
	system("pause");

	list->addNodeBefore(50.50, 100.00);
	list->print();
	cout << endl;
	system("pause");
	list->deleteAt(1);
	list->print();
	cout << endl;
	system("pause");
	// SIMPLE PRINTING
	// list->print();
	// PRINT RECURRSION BY SENDING THE HEAD
	// list->print(list->getHead());
	list->printRevers(list->getHead());
	// destroying the list
	delete list;
	cout << endl;
	system("pause");
	return 0;
}
