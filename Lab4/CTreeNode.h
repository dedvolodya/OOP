#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class CTreeNode
{
	friend class CBinTree; //for allow CBinTree access to private field 
private:
	//field
	CTreeNode *left;
	CTreeNode *right;
	char *m_Destination;
	int m_Flight;
	char *m_PassangerName;
	char *m_FlightDate;
	int height;
	//methods
	CTreeNode();
	CTreeNode(const char * data);
	~CTreeNode();
	void PrintInfo()const;
	
};

