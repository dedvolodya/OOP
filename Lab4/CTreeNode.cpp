#include "CTreeNode.h"

/*this function split the string to substring
and returns vector of string */
/*for example
input str = "abc;de"
output res[0] = "abc" , res[1] = "de" */
char **split(const char *str) {
	char **res;
	res = (char**)malloc(sizeof(char*)*4); // numbers of string = 4
	for (int i = 0; i < 4; i++) 
		res[i] = (char*)malloc(sizeof(char) * 64);
	int k = 0 , n = strlen(str) , i = 0 , j = 0;
	for (k = 0; k < 4; k++) {
		j = 0;
		while (i < n && str[i] != ';') {
			res[k][j] = str[i];
			i++;
			j++;
		}
		res[k][j] = '\0';
		i++;
	}
	return res;
}
void memory_free(char **mas) {
	for (int i = 0; i < 4; i++)
		free(mas[i]);
	free(mas);
}
CTreeNode::CTreeNode()
{
	height = 1;
	left = NULL;
	right = NULL;
	m_PassangerName = NULL;
	m_Destination = NULL;
	m_FlightDate = NULL;
}
CTreeNode::CTreeNode(const char *data) : CTreeNode() {
	if (data == NULL)
		return;
	char **info;
	info = split(data);
	m_Destination = new char[strlen(info[0]) + 1];
	m_PassangerName = new char[strlen(data) + 1];
	m_FlightDate = new char[strlen(info[3]) + 1];
	strcpy(m_Destination , info[0]);
	m_Flight = atoi(info[1]);
	strcpy(m_PassangerName, info[2]);
	strcpy(m_FlightDate, info[3]);
	memory_free(info);
}
CTreeNode::~CTreeNode()
{
	delete[] m_Destination;
	delete[] m_FlightDate;
	delete[] m_PassangerName;
}
void CTreeNode::PrintInfo() const {
	printf("\nPassanger Name : %s \nDestination : %s \nFlight : %d \nDate : %s \n", 
		    m_PassangerName ,
		    m_Destination ,
		    m_Flight ,
		    m_FlightDate);

}