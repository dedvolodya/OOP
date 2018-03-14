#pragma once
#include"Iterator.h"

template <typename T>
class List {
	struct ListNode {
		T data;
		ListNode * next;
		ListNode() {
			next = NULL;
		}
		ListNode(T& dat) {
			data = dat;
		}		
		ListNode(const ListNode &node) {
			data = node.data;
			next = NULL;
		}
		void Print() {
			cout << data;
		}
	};

public:
	typedef ListNode node_type;
	typedef _iterator<node_type> iterator;
	//constructors / destructors
	List();
	~List();

	//methods
	iterator begin() const; //Returns an iterator addressing the first element 
	iterator end() const; //Returns an iterator that addresses the location 
				   //succeeding the last element
	int size() const; //Returns the number of elements in a list.
	bool empty() const; //Tests if a list is empty.

	bool load(const char *filename);//Initializes object from csv-file
	void clear();//Erases all the elements of a list.
	iterator find(const node_type & val) const;//Returns an iterator to the 
										 // first element in a list that match a specified value.
										//return empty iterator if doesn't find
	void pop_front();//Deletes the element at the beginning of a list.
	void push_front(const node_type& val);//Adds an element to the //beginning of a list.
	void remove(const node_type &val);//Erases first element in a list that 
									 //match a specified value.
	iterator remove(iterator _where);//	Erases element from specified 
									 //position and returns iterator to position next to removed element.
									 //return empty iterator if doesn't find node or if it's last node in list
	void splice(iterator _Where, List<T>& _Right);//Removes element from //the target list and inserts it in first
												  // position of the argument list.
	void print() const;//Dumps list into the screen
private:
	node_type *head;
	iterator *first, *last;
	int _size;
};
/********************************************************************/
template<typename T>
List<T>::List() {
	_size = 0;
	head = NULL;
	first = new iterator();
	last = new iterator();
}
template<typename T>
List<T>::~List() {
	clear();
}
template<typename T>
typename List<T>::iterator List<T>::begin() const { 
	return *first; 
}
template<typename T>
typename List<T>::iterator List<T>::end() const {
	return iterator(); 
}
template<typename T>
int List<T>::size() const { 
	return _size; 
}
template<typename T>
bool List<T>::empty() const { 
	return (_size == 0); 
}
template<typename T>
void List<T>::push_front(const node_type& val) {
	if (head == NULL) {
		head = new ListNode(val);
		head->next = NULL;
	}
	else {
		ListNode *tmp = new ListNode(val);
		tmp->next = head;
		head = tmp;
	}
	_size++;
	delete first;
	first = new iterator(head);
}
template<typename T>
void List<T>::pop_front() {
	if (head == NULL) return;
	if (head->next == NULL) {
		delete head;
		head = NULL;
	}
	else {
		ListNode *tmp = head;
		head = head->next;
		delete tmp;
	}
	delete first;
	first = new iterator(head);
	_size--;
}
template<typename T>
void List<T>::clear() {
	while (!empty()) {
		pop_front();
	}
}
template<typename T>
typename List<T>::iterator List<T>::find(const node_type & val) const {
	ListNode *ptr = head;
	while (ptr && (val.data != ptr->data) ) 	
		ptr = ptr->next;
	return iterator(ptr);
}
template<typename T>
void List<T>::remove(const node_type &val) {
	if (!head) return; //remove from empty list
	ListNode *ptr = head;
	if (ptr->data == val.data) {
		pop_front();
		return;
	}
	while (ptr->next && ptr->next->data != val.data)
		ptr = ptr->next;
	if (ptr->next) {
		ListNode *tmp = ptr->next;
		ptr->next = tmp->next;
		delete tmp;
		_size--;
	}
	//else node not foung
}
template<typename T>
typename List<T>::iterator List<T>::remove(iterator _where) {
	if (_where.empty()) return iterator();
	auto it = _where;
	it++;
	remove(*_where);
	return it;
}
template<typename T>
void List<T>::splice(iterator _Where, List<T>& _Right) {
	if (_Where.empty()) return; //empty iterator
	_Right.push_front(*_Where);
	remove(_Where);
}
template<typename T>
void List<T>::print() const {
	for (auto it : *this) 
		it.Print();
	cout << endl;
}
template<typename T>
bool List<T>::load(const char *filename) {
	if (filename == NULL)
		return false;
	ifstream stream(filename);
	if (!stream) {
		return false;
	}
	string str;
	getline(stream, str);
	if (str.length() == 0)
		return false; //empty file
	stream.seekg(ios::beg);
	int line = 0;
	T data;
	while (!stream.eof() || !stream.failbit) {
		try {
			stream >> data;
			push_front(data);
		}
		catch (exception ex) {
			stream.close();
			string str = "wrong file : ";
			string err = ex.what();
			str += err;
			throw exception(str.c_str());
		}
	}	
	stream.close();
	return true;
}