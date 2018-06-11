#pragma once
#include"Employee.h"
#include <list>

class Manager : public Employee {
public:
	Manager() {};
	Manager(string _f_name, string _l_name, int _age, int _id) :
		Employee(_f_name, _l_name, _age, _id) {
		salary = 0;
		department = "none";
	};
	Manager(const Manager &m);
	Manager& operator=(const Manager &m);
	void Display() override;
	//add an employee to the subordinates list
	Person* AddSubordinate(Person *p);
	bool DeleteSubordinate(Person *p);
	void DisplaySubordinates() const;

private:
	list<Person*> subordinates;//списокпідлеглих
};
