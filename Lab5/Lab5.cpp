#include<iostream>
#include<fstream>
#include"List.h"
#include"CFile.h"

using namespace std;
//function move all elements , that < then obj ,  from lst1   to lst2
template<typename T>
void delete_less_than(List<T> &lst, List<T> &lst2, T &obj);


int main()
{
	List<CFile> catalog;
	List<CFile> deleted;
	try {
		catalog.load("catalog.csv");
	}
	catch (exception ex) {
		cout << ex.what()<<endl;
		cout << "Press ENTER";
		getchar();
		return 0;
	}
	char ch = 0;
	do {
		cout << "File Catalog " << endl;
		if (catalog.empty())
			cout << "EMPTY" << endl;
		else
			catalog.print();
		cout << "Deleted files " << endl;
		if (deleted.empty())
			cout << "EMPTY" << endl;
		else
			deleted.print();
		cout << "1 - delete file\n2 - rename file \n3 - restore last deleted file\n4 - delete file for date\nq - exit \n";
		cin >> ch;
		switch (ch) {
		case '1': {
			char for_pause;
			cout << "print the file's name :";
			string str;
			cin >> str;
			auto it = catalog.find(CFile(str.c_str(), "", 0));
			if (it.empty()) {
				cout << "file not found  , press any key and ENTER\n";
				cin >> for_pause;
				system("cls");
			}
			else {
				catalog.splice(it, deleted);
				system("cls");
			}
		} break;
		case '2': {
			char for_pause;
			cout << "print the file's name :";
			string str;
			cin >> str;
			auto it = catalog.find(CFile(str.c_str(), "", 0));
			if (it.empty()) {
				cout << "file not found  , press any key and ENTER\n";
				cin >> for_pause;
				system("cls");
			}
			else {
				cout << "print new file's name : ";
				cin >> str;
				(*it).data.rename(str.c_str());
				system("cls");
			}
		} break;
		case '3': {
			char for_pause;
			if (deleted.empty()) {
				cout << "have not deleted files  , press any key and ENTER\n";
				cin >> for_pause;
				system("cls");
			}
			else {
				deleted.splice(deleted.begin(), catalog);
				system("cls");
			}
		} break;
		case '4' : {
			cout << "There will delete all files , date of creating its less than given\n";
			cout << "print date in format dd.mm.yyyy :";
			string str;
			cin >> str;
			try {
				delete_less_than(catalog, deleted, CFile("", str.c_str(), 0));
			}
			catch (exception ex) { //if wrong date
				cout << ex.what() << endl;
				cout << "Press any key and ENTER";
				cin >> str;
			}
			system("cls");
		}
		default:
			system("cls");
		}
	} while (ch != 'q');
	
	getchar();
    return 0;
}
template<typename T>
void delete_less_than(List<T> &lst, List<T> &lst2, T &obj) {
	auto it = lst.begin();
	while (it != lst.end()) {
		if ((*it).data < obj) {
			lst2.push_front((*it).data);
			it = lst.remove(it);
		}
		else
			it++;
	}
}
