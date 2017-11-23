/*!
* file: StringList.h
* StringList class declaration
* written: 10/11/2017
* Copyright (c) 2017 Volodymyr Kravchuk
*/

#pragma once
#include <string.h>
#include <stdio.h>

struct ListNode {
	char *str;
	ListNode* next;
	ListNode* prev;
};

typedef const ListNode* POSITION;

class StringList {
    public:
	    //Constructs an empty list for ListNode objects.
	    StringList(void);
	    ~StringList(void);

    	//Head/Tail Access 
	    const ListNode* GetHead();//Returns the head element of the list 
	    const ListNode* GetTail();//Returns the tail element of the list 

	    //Operations 
		//Adds an element to the head of the list (makes a new head).
		void AddHead(const char *);
		//Adds all the elements in another list to the head of the list (makes a new head).
		void AddHead(const StringList *);
		//Adds an element to the tail of the list (makes a new tail).
		void AddTail(const char *);
		//Adds all the elements in another list to the tail of the list (makes a new tail).
		void AddTail(const StringList *);
		//Removes all the elements from this list.
		void RemoveAll();
		//Removes the element from the head of the list.
		void RemoveHead();
		//Removes the element from the tail of the list.
		void RemoveTail();
		void AppendExclusively(const StringList *);
		void Splice(POSITION where, StringList *sl, POSITION first, POSITION last);
		//removes all duplicate elements
		void Unique();

		//Iteration 
		//Gets the next element for iterating.
		POSITION GetNext();
		//Gets the previous element for iterating.
		POSITION GetPrev();

		//Retrieval/Modification
		POSITION GetHeadPosition();

		//Gets the element at a given position.
		const char* GetAt(int)const;
		//Removes an element from this list as specified by position.
		void RemoveAt(int);
		//Sets the element at a given position.
		void SetAt(char *, int);

		//Insertion 
		//Inserts a new element after a given position.
		void InsertAfter(char *, int);
		//Inserts a new element before a given position.
		void InsertBefore(char *, int);

		//Searching 
		//Gets the position of an element specified by string value.
		const ListNode* Find(char *);
		//Gets the position of an element specified by a zero-based index.
		int FindIndex(char *)const;

		//Status 
		//Returns the number of elements in this list.
		int GetSize()const;
		//Tests for the empty list condition (no elements).
		bool IsEmpty()const;

		void PrintNode(const ListNode *p);

    private:
	    int num_elem;
	    ListNode *head;
	    ListNode *tail;
	    ListNode *ptr;
		POSITION position;
};

