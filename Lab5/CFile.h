#pragma once
#include<iostream>
#include<string>

using namespace std;

class CFile {
public:
	CFile();//create empty object , which can't use methods and be element of container 
	~CFile();
	CFile(const char *,const char * , int);
	CFile(const CFile&);	//copy constructor
	CFile& operator=(const CFile&);

	//rename object
	void rename(const char* newname);
	//methods for output and input object using "cin" and "cout"
	friend ostream& operator << (ostream& stream, const CFile& data);
	friend istream& operator >> (istream& stream, CFile& data);
	//compare only file's name
	bool operator == (const CFile& data) const;
	bool operator != (const CFile& data) const;
	//compare date of creating
	bool operator < (const CFile& data) const;

private:
	//cheking date and size 
	static bool check_date(const char*);
	static bool check_size(const char*);
	char *_filename;
	char *_creation_date;
	int _size;
};
