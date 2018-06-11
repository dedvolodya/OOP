#pragma once
#include"Manager.h"
#include<vector>
enum class PersonType {
	EMPLOYEE, MANAGER
};
class DataBase{

public:
	DataBase() { employees = vector<Person*>(0); };
	~DataBase() {};//no need in destructor
				   //creates “flat” database
	bool LoadFromFile(const char *file);
	//arranges "flat" database after loading from the file
	void ArrangeSubordinates();
	//hire a new employee
	Person* HireEmployee(Person *p);
	void DisplayDepartmentEmployees(string _department)const;
	//fire the employee
	bool FireEmployee(int id);
	void DisplayAll()const;
	vector<Person*> SQL(string field, string  cond, string value) const;
	void ShowRecordSet(vector<Person*>rs) const;

private:
	bool checkLine(string str);
	string * parseStr(string str);
	void createEmployee(string str);
	void fillSubList(Manager * manager);
	bool deleteFromSubList(Employee * employee);

	vector<Person*> employees;
};
