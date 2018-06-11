#include"Employee.h"
Employee::Employee(const Employee &e) {
	this->age = e.age;
	this->department = e.department;
	this->f_name = e.f_name;
	this->id = e.id;
	this->l_name = e.l_name;
	this->salary = e.salary;
}
Employee& Employee::operator=(const Employee &e) {
	if (this == &e)
		return *this;
	this->age = e.age;
	this->department = e.department;
	this->f_name = e.f_name;
	this->id = e.id;
	this->l_name = e.l_name;
	this->salary = e.salary;
	return *this;
}
void Employee::SetSalary(int s) {
	if (salary < 0)
		throw exception("Salary can't be negativ");
	this->salary = s;
}
void Employee::SetDepartment(string dept) {
	this->department = dept;
}
void Employee::SetId(int n) {
	this->id = id;
}
int Employee::GetId()const {
	return this->id;
}
int Employee::GetAge() const
{
	return age;
}
int Employee::GetSalary() const
{
	return salary;
}
string Employee::GetDepartment() const {
	return this->department;
}
void Employee::Display() {
	cout << "Empolyement type : employee \n"
		<< "id : " << id << "\n"
		<< f_name << " " << l_name
		<< "   age : " << age << " salary : " << salary << "\n"
		<< "department : " << department << "\n\n";

}