#include"DataBase.h"
#include<fstream>
bool DataBase::checkLine(string str) {
	if (str[0] != '0' && str[0] != '1')
		return false;
	if (str[1] != ';' || str[3] != ';')
		return false;
	return true;
}
string* DataBase::parseStr(string str) {

	string* res = new string[7];
	int element = 0;

	for (size_t i = 0; i < str.size(); i++) {
		if (str[i] == ';')
			element++;
		else
			res[element] += str[i];
	}
	return res;
}
void DataBase::createEmployee(string str) {

	string* fields = parseStr(str);

	int typeOfEmployee = stoi(fields[0]);
	int id = stoi(fields[1]);
	string firstName = fields[2];
	string lastName = fields[3];
	int age = stoi(fields[4]);
	string department = fields[5];
	int salary = stoi(fields[6]);

	Employee *employee; 
	if (typeOfEmployee == 0)
		employee = new Employee(firstName, lastName, age, id);
	else
		employee = new Manager(firstName, lastName, age, id);

	employee->SetDepartment(department);
	employee->SetSalary(salary);

	employees.push_back(employee);
}
void DataBase::fillSubList(Manager* manager) {
	for (auto it : employees) {
		if (typeid(*it) == typeid(Employee)) {
			Employee *employee = dynamic_cast<Employee*>(it);
			if (manager->GetDepartment() == employee->GetDepartment())
				manager->AddSubordinate(employee);
		}
	}
}
bool DataBase::deleteFromSubList(Employee * employee) {
	for (auto it : employees) {
		if (typeid(*it) == typeid(Manager)) {
			Manager *manager = dynamic_cast<Manager*>(it);
			manager->DeleteSubordinate(employee);
			return true;
		}
	}
	return false;
}
bool DataBase::LoadFromFile(const char *filename) {
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
	string employee;
	while (stream >> employee) {
		if (checkLine(employee) == false)
			return false;

		createEmployee(employee);
	}
	return true;
}
void DataBase::ArrangeSubordinates() {
	for (auto it : employees) {
		if (typeid(*it) == typeid(Manager)) {
			Manager *manager = dynamic_cast<Manager*>(it);
			fillSubList(manager);
		}
	}
}
Person* DataBase::HireEmployee(Person *p) {
	if (p == NULL)
		return NULL;
	employees.push_back(p);
	return employees.back();
}
void DataBase::DisplayDepartmentEmployees(string _department) const  {
	for (auto it : employees) {
		Employee *employee = dynamic_cast<Employee*>(it);
		if (employee->GetDepartment() == _department)
			employee->Display();
	}
}
bool DataBase::FireEmployee(int id) {
	auto it = employees.begin();
	while (it != employees.end()) {
		Employee *employee = dynamic_cast<Employee*>(*it);
		if (employee->GetId() == id)
			break;
		it++;
	}

	if (it == employees.end())
		return false;

	deleteFromSubList(dynamic_cast<Employee*>(*it));
	employees.erase(it);

	return true;
}
void DataBase::DisplayAll() const  {
	for (auto it : employees)
		it->Display();
}
vector<Person*> DataBase::SQL(string field, string cond, string value) const
{
	vector<Person*> res;
	for (auto it : employees) {
		Employee *employee = dynamic_cast<Employee*>(it);
		if (field == "department") {	
			if (employee->GetDepartment() == value)
					res.push_back(it);
		}
		else if (field == "id") {
			if (employee->GetId() == stoi(value) && 
				cond == "eq")
				res.push_back(it);
			else if (employee->GetId() < stoi(value) &&
				cond == "lt")
				res.push_back(it);
			else if (employee->GetId() > stoi(value) &&
				cond == "gt")
				res.push_back(it);
		}
		else if (field == "salary") {
			if (employee->GetSalary() == stoi(value) &&
				cond == "eq")
				res.push_back(it);
			else if (employee->GetSalary() < stoi(value) &&
				cond == "lt")
				res.push_back(it);
			else if (employee->GetSalary() > stoi(value) &&
				cond == "gt")
				res.push_back(it);
		}
		else if (field == "age") {
			if (employee->GetAge() == stoi(value) &&
				cond == "eq")
				res.push_back(it);
			else if (employee->GetAge() < stoi(value) &&
				cond == "lt")
				res.push_back(it);
			else if (employee->GetAge() > stoi(value) &&
				cond == "gt")
				res.push_back(it);
		}
		else {
			throw exception("Wrong filed in SQL");
		}
	}
	return res;
}
void DataBase::ShowRecordSet(vector<Person*> rs) const {
	for (auto it : rs) {
		Employee *employee = dynamic_cast<Employee*>(it);
		employee->Display();
	}
}