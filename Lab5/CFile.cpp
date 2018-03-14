#include"CFile.h"
CFile::CFile() {
	_filename = NULL;
	_size = 0;
	_creation_date = NULL;
}
CFile::~CFile() {
	delete[] _filename;
	delete[] _creation_date;
}
CFile::CFile(const char * name ,const char * date, int size) 
:	_size(size)
{
	if (name == NULL || date == NULL) {
		throw new exception("null pointer exception");
	}
	_filename = new char[strlen(name) + 1];
	strcpy(_filename, name);
	_creation_date = new char[strlen(date) + 1];
	strcpy(_creation_date, date);
}
CFile::CFile(const CFile& obj) {
	if (obj._filename == NULL)
		_filename = NULL;
	else {
		_filename = new char[strlen(obj._filename) + 1];
		strcpy(_filename, obj._filename);
	}
	if (obj._creation_date == NULL)
		_creation_date = NULL;
	else {
		_creation_date = new char[strlen(obj._creation_date) + 1];
		strcpy(_creation_date, obj._creation_date);
	}
	_size = obj._size;
}
CFile& CFile::operator=(const CFile& obj) {
	if (this == &obj) return *this;

	if (_filename != NULL)
		delete[] _filename;
	if (obj._filename == NULL)
		_filename = NULL;
	else {
		_filename = new char[strlen(obj._filename) + 1];
		strcpy(_filename, obj._filename);
	}

	if (_creation_date != NULL)
		delete[] _creation_date;
	if (obj._creation_date == NULL)
		_creation_date = NULL;
	else {
		_creation_date = new char[strlen(obj._creation_date) + 1];
		strcpy(_creation_date, obj._creation_date);
	}
	_size = obj._size;
	return *this;
}
void CFile::rename(const char* newname) {
	if (newname == NULL)
		throw new exception("CFile::rename : nullptr exception");
	if (_filename == NULL)
		throw new exception("CFile::rename : try to rename empty object");
	delete[] _filename;
	_filename = new char[strlen(newname) + 1];
	strcpy(_filename, newname);
}
bool CFile::operator==(const CFile & data) const {
	if (_filename == NULL || data._filename == NULL)
		throw new exception("CFile : try to compare empty object");
	return strcmp(_filename, data._filename) == 0;
}
bool CFile::operator!=(const CFile & data) const {
	return !(*this == data);
}
bool CFile::operator<(const CFile & data) const {
	if (_filename == NULL || data._filename == NULL)
		throw new exception("CFile : try to compare empty object");
	if (!CFile::check_date(data._creation_date))
		throw exception("wrong date format");
	char *s1 = new char[strlen(_creation_date) + 1],
		*s2 = new char[strlen(data._creation_date) + 1];
	int res;
	strcpy(s1, _creation_date);
	strcpy(s2, data._creation_date);
	s1[2] = s1[5] = s2[2] = s2[5] = '\0';
	s1 += 6;
	s2 += 6;
	res = strcmp(s1, s2);//compare year
	if (res == 0) {
		s1 -= 3; s2 -= 3;
		res = strcmp(s1, s2);//compare month
		if (!res) {
			s1 -= 3; s2 -= 3;
			res = strcmp(s1, s2);//compare day
		}
		else {
			s1 -= 3;
			s2 -= 3;
		}
	}
	else {
		s1 -= 6;
		s2 -= 6;
	}

	delete[] s1;
	delete[] s2;
	return res < 0;
}
ostream& operator << (ostream& stream, const CFile& data) {
	if (data._filename == NULL || data._creation_date == NULL)
		throw new exception("CFile : try to print empty object");
	stream.setf(ios::left);
	stream.width(20);
	stream << data._filename;
	stream.width(20);
	stream << data._creation_date; 
	stream.width(20);
	stream<< data._size << endl;
	return stream;
}
istream& operator >> (istream& stream, CFile& data) {
	string str;
	getline(stream, str, ';');
	data._filename = new char[str.length() + 1];
	strcpy(data._filename, str.c_str());
	getline(stream, str, ';');
	if (!CFile::check_date(str.c_str()))
		throw exception("wrong data format");
	data._creation_date = new char[str.length() + 1];
	strcpy(data._creation_date, str.c_str());
	getline(stream, str);
	if (!CFile::check_size(str.c_str()))
		throw exception("wrong size");
	data._size = stoi(str);
	return stream;
}
bool CFile::check_date(const char * date) {
	if (date == NULL || date == "")
		return false;
	if (strlen(date) != 10)
		return false;
	for (int i = 0; i < 10; i++) 
		if (i != 2 && i != 5)
			if (!isdigit(date[i]))
				return false;
	return true;
}
bool CFile::check_size(const char * size) {
	if (size == NULL || size == "")
		return false;
	for (int i = 0; i < strlen(size); i++)
		if (!isdigit(size[i]))
			return false;
	return true;
}