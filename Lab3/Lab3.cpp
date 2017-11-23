/************************************************************************
*file: Lab3.cpp
*synopsis: this file has a code for testing class
*related files: none
*author: Volodymyr Kravchuk
*written: 15/11/2017
************************************************************************/
#include "StringList.h"

void PrintList(StringList *,char *);

int main()
{
	//create empty lists
	StringList *StrList1 = new StringList();  
	StringList *StrList2 = new StringList();
	
	//filling List1 
	StrList1->AddHead("a3");
	StrList1->AddHead("a2");
	StrList1->AddHead("a1");
	StrList1->AddHead("a0");
	StrList1->AddTail("a4");
	StrList1->AddTail("a5");
	StrList1->AddTail("a6");
	// StrList1 contains "a0","a1","a2","a3","a4","a5","a6"
	PrintList(StrList1, "List1");
	//filling List2
	StrList2->AddHead("b3");
	StrList2->AddHead("b2");
	StrList2->AddHead("b1");
	StrList2->AddHead("b0");
	StrList2->AddTail("b4");
	// StrList1 contains "b0","b1","b2","b3","b4"
	PrintList(StrList2, "List2");
	printf("\n");
	//add StrList2 to head StrList1
	StrList1->AddHead(StrList2);
	PrintList(StrList1, "List1");
	PrintList(StrList2, "List2");
	printf("\n");
	//add StrList1 to tail StrList2
	StrList2->AddTail(StrList1);
	PrintList(StrList1, "List1");
	PrintList(StrList2, "List2");
	printf("\n");
	//Uniqe method StrList2
	StrList2->Unique();
	PrintList(StrList1, "List1");
	PrintList(StrList2, "List2");
	printf("\n");
	//delete Head and Tail and at index
	StrList1->RemoveAt(4);//b4
	StrList1->RemoveHead();//b0
	StrList1->RemoveTail();//a6
	PrintList(StrList1, "List1");
	PrintList(StrList2, "List2");
	printf("\n");
	//AppendExclusively
	StrList1->AppendExclusively(StrList2);
	PrintList(StrList1, "List1");
	PrintList(StrList2, "List2");
	printf("\n");
	//inserts
	StrList1->InsertAfter("after", 5);
	StrList1->InsertBefore("before", 5);
	PrintList(StrList1, "List1");
	PrintList(StrList2, "List2");
	printf("\n");
	//splice
	StrList2->RemoveAll();
	StrList2->AddHead("b3");
	StrList2->AddHead("b2");
	StrList2->AddHead("b1");
	StrList2->AddHead("b0");
	StrList2->AddTail("b4");
	PrintList(StrList1, "List1");
	PrintList(StrList2, "List2");
	printf("\n");
	StrList1->Splice(StrList1->Find("b4"), StrList2, StrList2->Find("b1"), StrList2->Find("b3"));
	PrintList(StrList1, "List1");
	PrintList(StrList2, "List2");
	printf("\n");
	delete StrList1;
	delete StrList2;

	getchar();

	return 0;
}
//function for print contains StringList
void PrintList(StringList * lst,char *list_name) {
	printf("%s\t", list_name);
	POSITION pos;
	for (pos = lst->GetHeadPosition(); pos != NULL; pos = lst->GetNext())
		lst->PrintNode(pos);
	printf("\t|Size : %i", lst->GetSize());
	printf("\n");
}
