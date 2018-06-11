#pragma once
#include"Person.h"
class Employee : public Person {
	friend class Manager;
public:
	Employee() {};
	Employee(std::string _f_name, std::string _l_name, int _age, int _id) :
		Person(_f_name, _l_name, _age), id(_id) {
		salary = 0;
		department = "none";
	};
	Employee(const Employee &e);
	Employee& operator=(const Employee &e);
	void SetSalary(int s);
	void SetDepartment(string dept);
	void SetId(int n);
	int GetId() const;
	int GetAge()const;
	int GetSalary() const;
	string GetDepartment() const;
	void Display() override;

protected:
	string department;
	int salary;
	int id;
};
