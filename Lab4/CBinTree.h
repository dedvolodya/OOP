#pragma once
#include "CTreeNode.h"
class CBinTree
{
public:
	CBinTree();
	~CBinTree();
	//Created tree with .csv file
	void MakeTree(char *file);
	//Make node and add to tree , take string with information "Destination;Flight;PassangerName;Date"
	void AddApplication(const char *info);
	//Delete node for given string with info "Destination;Flight;PassangerName;Date"
	void DeleteApplication(const char *info);
	//Print all records from tree
	void Print()const;
	//Print and delete node with parametr flight
	void ExtractApplication(int flight);
	//Print and delete node with parametr date
	void ExtractApplication(char *date);
	
private:
	CTreeNode *root;
	//delete all node in tree
	void DeleteTree(CTreeNode *p);
	//print tree
	void PrintInOrder(CTreeNode *p)const;
	//insert element to tree
	CTreeNode* Add(CTreeNode *r, CTreeNode *node);
	//save pointer on node with given date to parametr find 
	void FindDate(CTreeNode* r, char *date, CTreeNode *&find);
	//save pointer on node with given flight number to parametr find
	void FindFlight(CTreeNode* r, int flight, CTreeNode *&find);
	//find in tree given node and return pointer to this
	CTreeNode* FindNode(CTreeNode *r, CTreeNode *node);
	//delete given node given node
	CTreeNode* DeleteNode(CTreeNode *node);
	//find and delete node from tree on given pointer
	CTreeNode* Delete(CTreeNode *r, CTreeNode *node);
	/*****methods for balance tree****/
	//return height subtree under given node
	int GetHeight(CTreeNode *node) const;
	//fix height given node
	void FixHeight(CTreeNode *node);
	//return balance factor of node 
	int BalanceFactor(CTreeNode *node)const;
	//return minimum node in subtree
	CTreeNode* FindMin(CTreeNode *p)const;
	//delete min node
	CTreeNode* DelMin(CTreeNode *p);
	//balance node
	CTreeNode* Balance(CTreeNode *node);
	//rotation
	CTreeNode* RightRightCase(CTreeNode *node);
	CTreeNode* LeftLeftCase(CTreeNode *node);
	CTreeNode* RightLeftCause(CTreeNode *node);
	CTreeNode* LeftRightCause(CTreeNode *node);
};


