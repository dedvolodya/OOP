#include"Manager.h"
Manager::Manager(const Manager &m){
	this->age = m.age;
	this->department = m.department;
	this->f_name = m.f_name;
	this->id = m.id;
	this->l_name = m.l_name;
	this->salary = m.salary;
	this->subordinates = m.subordinates;
}
Manager& Manager::operator=(const Manager &m) {
	this->age = m.age;
	this->department = m.department;
	this->f_name = m.f_name;
	this->id = m.id;
	this->l_name = m.l_name;
	this->salary = m.salary;
	this->subordinates = m.subordinates;
	return *this;
}
void Manager::Display() {
	cout << "Empolyement type : manager \n"
		<< "id : " << id << "\n"
		<< f_name << " " << l_name
		<< "   age : " << age << " salary : " << salary << "\n"
		<< "department : " << department << "\n"
		<< "subordinates : \n";
	DisplaySubordinates();
}
Person* Manager::AddSubordinate(Person *p){
	this->subordinates.push_front(p);
	return *(subordinates.begin());
}
void Manager::DisplaySubordinates()const {
	if (subordinates.size() == 0)
		cout << "\tnone\n\n";
	
	for (auto it : subordinates) {
		Employee *employee = dynamic_cast<Employee*>(it);
		cout << "\tEmpolyement type : employee \n"
			<< "\tid : " << employee->id << "\n\t"
			<< employee->f_name << " " << employee->l_name
			<< "   age : " << employee->age << " salary : " << employee->salary << "\n\n";
	}
	cout << endl;
}
bool Manager::DeleteSubordinate(Person *p) {

	Employee *willDelete = dynamic_cast<Employee *>(p);
	auto it = subordinates.begin();
	while (it != subordinates.end() ) {
		Employee *employee = dynamic_cast<Employee*>(*it);
		if (employee->GetId() == willDelete->GetId()) 
			break;
		it++;
	}

	if (it == subordinates.end())
		return false;

	subordinates.erase(it);
	return true;
}