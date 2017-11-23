/************************************************************************
*file: StringList.cpp
*synopsis: this file has a code for realization methods
*related files: none
*author: Volodymyr Kravchuk
*written: 10/11/2017
************************************************************************/
#include "StringList.h"


StringList::StringList()
{
	this->num_elem = 0;
	this->position = NULL;
	this->ptr = NULL;
	this->head = NULL;
	this->tail = NULL;
}
StringList::~StringList()
{
	this->RemoveAll();
}
const ListNode* StringList::GetHead() {
	return this->head;
}
const ListNode* StringList::GetTail() {
	return this->tail;
}
void StringList::AddHead(const char *str) {
	if (str == NULL)
		return;
	this->ptr = new ListNode;
	ptr->str = new char[strlen(str)+1];
	strcpy(ptr->str, str);

	if (this->head == NULL) {
		head = ptr;
		tail = ptr;
		ptr->next = NULL;
		ptr->prev = NULL;
	}
	else {
		ptr->next = head;
		head->prev = ptr;
		ptr->prev = NULL;
		head = ptr;
	}
	this->num_elem++;
}
void StringList::AddHead(const StringList *lst) {
	if (lst != NULL) {
		if (this->head == NULL) {
			this->head = lst->head;
			this->tail = lst->tail;
			this->num_elem = lst->num_elem;
		}
		else {
			ListNode *p = lst->tail;
			while (p != NULL) {
				this->AddHead(p->str);
				p = p->prev;
			}
		}
	}
}
void StringList::AddTail(const char *str) {
	if (str == NULL)
		return;
	this->ptr = new ListNode;
	ptr->str = new char[strlen(str)];
	strcpy(ptr->str, str);

	if (this->tail == NULL) {
		head = ptr;
		tail = ptr;
		ptr->next = NULL;
		ptr->prev = NULL;
	}
	else {
		ptr->prev = tail;
		tail->next = ptr;
		ptr->next = NULL;
		tail = ptr;
	}
	this->num_elem++;
}
void StringList::AddTail(const StringList *lst) {
	if (lst != NULL) {
		if (this->tail == NULL) {
			this->head = lst->head;
			this->tail = lst->tail;
			this->num_elem = lst->num_elem;
		}
		else {
			ListNode *p = lst->head;
			while (p != NULL) {
				this->AddTail(p->str);
				p = p->next;
			}
		}
	}
}
void StringList::RemoveAll() {
	while (this->num_elem != 0) {
		this->RemoveHead();
	}
}
void StringList::RemoveHead() {
	if (head != NULL) {
		if (head->next != NULL) {
			ptr = head;
			head = ptr->next;
			delete ptr;
			head->prev = NULL;
		}
		else {
			delete head;
			head = NULL;
			tail = NULL;
			
		}
		this->num_elem--;
	}
}
void StringList::RemoveTail() {
	if (tail != NULL) {
		if (tail->prev != NULL) {
			ptr = tail;
			tail = ptr->prev;
			delete ptr;
			tail->next = NULL;
		}
		else {
			delete tail;
			tail = NULL;
			head = NULL;
		}
		this->num_elem--;
	}
}
int StringList::GetSize()const {
	return this->num_elem;
}
void StringList::AppendExclusively(const StringList *lst) {
	if (lst != NULL) {
		if (this->tail == NULL) {
			this->AddTail(lst);
		}
		else {
			ListNode *p = lst->head;
			while (p != NULL) {
				if (this->FindIndex(p->str) == -1) 
					this->AddTail(p->str);
				p = p->next;
			}
		}
	}
}
void StringList::Splice(POSITION where, StringList *sl, POSITION first, POSITION last) {
	if (where && first && last && sl) {
		int begin, b, e;
		begin = this->FindIndex(where->str);
		b = sl->FindIndex(first->str);
		e = sl->FindIndex(last->str);
		while (e >= b) {
			this->InsertAfter((char*)sl->GetAt(b),begin);
			begin++;
			sl->RemoveAt(b);
			e--;
		}
	}
}
void StringList::Unique() {
	if (head != NULL) {
		ListNode *p = head;
		ListNode *p2 = head->next;
		while (p->next != NULL) {
			while (p2 != NULL) {
				if (strcmp(p->str, p2->str) == 0) {
					ListNode *tmp;
					tmp = p2;
					p2 = p2->next;
					if (tmp->next == NULL) {
						this->RemoveTail();
					}
					else {
						tmp->next->prev = tmp->prev;
						tmp->next->prev->next = tmp->next;
						delete tmp;
						this->num_elem--;
					}
				}
				else
				    p2 = p2->next;
			}
			p = p->next;
			if (p == NULL)
				return;
			    p2 = p->next;
		}
	}
}
POSITION StringList::GetNext() {
	position = position->next;
	return position;
}
POSITION StringList::GetPrev() {
	position = position->prev;
	return position;
}
POSITION StringList::GetHeadPosition() {
	position = head;
	return position;
}
const char* StringList::GetAt(int indx)const {
	if (this->IsEmpty() == false && indx >= 0 && indx < this->num_elem) {
		ListNode *p = this->head;
		while (indx != 0) {
			indx--;
			p = p->next;
		}
		return p->str;
	}
}
void StringList::SetAt(char *s, int indx) {
	if (this->IsEmpty() == false && indx >= 0 && indx < this->num_elem) {
		ListNode *p = this->head;
		while (indx != 0) {
			indx--;
			p = p->next;
		}
		strcpy(p->str, s);
	}
}
void StringList::InsertAfter(char *str, int indx) {
	if (this->IsEmpty() == false 	&& indx >= 0 && indx < this->num_elem) {
		ListNode *p = this->head;
		if (indx == this->num_elem - 1) {
			this->AddTail(str);
			return;
		}
		this->ptr = new ListNode;
		ptr->str = new char[strlen(str)];
		strcpy(this->ptr->str, str);
		while (indx != 0) {
			indx--;
			p = p->next;
		}
		this->ptr->prev = p;
		this->ptr->next = p->next;
		this->ptr->next->prev = this->ptr;
		p->next = this->ptr;
	}
}
void StringList::InsertBefore(char *str, int indx) {
	if (this->IsEmpty() == false && indx >= 0 && indx < this->num_elem) {
		ListNode *p = this->head;
		if (indx == 0 ) {
			this->AddHead(str);
			return;
		}
		this->ptr = new ListNode;
		ptr->str = new char[strlen(str)];
		strcpy(this->ptr->str, str);
		while (indx != 0) {
			indx--;
			p = p->next;
		}
		this->ptr->next = p;
		this->ptr->prev = p->prev;
		this->ptr->prev->next = this->ptr;
		p->prev = this->ptr;
	}
}
void StringList::RemoveAt(int indx) {
	if (this->IsEmpty() == false && indx >= 0 && indx < this->num_elem) {
		ListNode *p = this->head;
		if (indx == 0) {
			this->RemoveHead();
			return;
		}
		if (indx == this->num_elem - 1) {
			this->RemoveTail();
			return;
		}
		while (indx != 0) {
			indx--;
			p = p->next;
		}
		p->next->prev = p->prev;
		p->next->prev->next = p->next;
		delete p;
		this->num_elem--;
	}
}
const ListNode* StringList::Find(char *str) {
	ListNode *p = this->head;
	while (p != NULL) {
		if (strcmp(p->str, str) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}
bool StringList::IsEmpty()const {
	if (this->num_elem == 0)
		return true;
	else
		return false;
}
int StringList::FindIndex(char *str)const {
	ListNode *p = this->head;
	int index = 0;
	while (p != NULL) {
		if (strcmp(p->str, str) == 0)
			return index;
		p = p->next;
		index++;
	}
	return -1;
}
void StringList::PrintNode(const ListNode *p) {
	if (p != NULL)
	    printf("%s ", p->str);
}