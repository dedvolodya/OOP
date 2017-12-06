#include "CBinTree.h"

CBinTree::CBinTree()
{
	root = NULL;
}
CBinTree::~CBinTree()
{
	DeleteTree(root);
}
void CBinTree::MakeTree(char *file) {
	FILE *f;
	const int BUFF_SIZE = 64;
	char *buff = new char[BUFF_SIZE];
	f = fopen(file, "rt");
	while (fgets(buff, BUFF_SIZE, f)) {
		buff[strlen(buff)-1] = '\0';
		AddApplication(buff);
	}
}
void CBinTree::Print()const {
	PrintInOrder(root);
}
void CBinTree::AddApplication(const char *info) {
	if (info == NULL)
		return;
	CTreeNode *node = new CTreeNode(info);//create node 
	root = Add(root, node);
}
void CBinTree::DeleteApplication(const char *info) {
	if (root == NULL) {
		printf("DELETE ERROR:tree is empty\n");
		return;
	}
	CTreeNode *node = new CTreeNode(info); // make node
	CTreeNode *deletNode = FindNode(root, node); // find pointer to given node in tree
	delete node;
	if (deletNode == NULL) {
		printf("DELETE ERROR:APLLICATION %s NOT FOUND\n", info);
		return;
	}
	root = Delete(root, deletNode);;//delete node from tree
}
void CBinTree::ExtractApplication(int flight) {
	CTreeNode *p = NULL;
	FindFlight(root,flight,p);//find node
	printf("******** Application with flight : %i *************\n", flight);
	//if node not found
	if (p == NULL) {
		printf("NOT FOUND\n");
		return;
	}
	else {//while is anyone nodes with parametres flight
		while (p != NULL) {
			p->PrintInfo();
			root = Delete(root, p);
			printf("DELETED\n");
			p = NULL;
			FindFlight(root, flight, p);
		}
	}
	printf("****************************************************\n\n");
}
void CBinTree::ExtractApplication(char *date) {
	CTreeNode *p = NULL;
	printf("******** Application with date : %s **************\n", date);
	FindDate(root,date,p);//find node in tree
	if (p == NULL) {
		printf("NOT FOUND\n\n");
	}
	else {//while is anyone nodes with parametres date
		while (p != NULL) {
			p->PrintInfo();
			root = Delete(root, p);
			printf("DELETED\n");
			p = NULL;
			FindDate(root, date, p);
		}
	}
	printf("****************************************************\n\n");
}
//privat methods
void CBinTree::FindDate(CTreeNode* r,char *date, CTreeNode *&find) {
	if (r != NULL) {
		if (strcmp(r->m_FlightDate, date) == 0) {
			find = r;
			return;
		}
		else {
			FindDate(r->left, date,find);
			FindDate(r->right, date,find);
		}
	}
}
void CBinTree::FindFlight(CTreeNode* r,int flight, CTreeNode *&find) {
	static CTreeNode *node ;
	if (r != NULL) {
		if (r->m_Flight == flight) {
			find = r;
			return;
		}
		else {
			FindFlight(r->left, flight,find);
			FindFlight(r->right, flight,find);
		}
	}
}
CTreeNode* CBinTree::FindNode(CTreeNode *r,CTreeNode *node) {
	if (r != NULL) {
		if (strcmp(node->m_PassangerName, r->m_PassangerName) < 0)
			FindNode(r->left, node);
		else if (strcmp(node->m_PassangerName, r->m_PassangerName) > 0)
			FindNode(r->right, node);
		else 
			return r;
	}
	else
		return NULL;
}
CTreeNode* CBinTree::Delete(CTreeNode *r,CTreeNode *node) {
	if (r == NULL)
		return NULL;
	//search given node
	if (strcmp(node->m_PassangerName, r->m_PassangerName) < 0)
		r->left = Delete(r->left, node); 
	else if (strcmp(node->m_PassangerName, r->m_PassangerName) > 0)
		r->right = Delete(r->right, node);
	else // if node found
		return DeleteNode(node); //delete this
	return Balance(r);
}
CTreeNode* CBinTree::DeleteNode(CTreeNode *node) {
	if (node != NULL && root != NULL) {
		CTreeNode *r, *l;
		l = node->left;
		r = node->right;
		delete node;
		//if node don't have right subtree , return left subtree
		if (r == NULL) return l;
		//find minimum element in right subtree and insert it on the place deleted node
		CTreeNode *min;
		min = FindMin(r);
		min->right = DelMin(r);
		min->left = l;
		return Balance(min);
	}
	else
		return NULL;
}
CTreeNode* CBinTree::FindMin(CTreeNode *p)const {
	return p->left ? FindMin(p->left) : p; //find min elem in subtree p
}
CTreeNode* CBinTree::DelMin(CTreeNode *p) {
	//destroy contacts with min element and return pointer to min elem
	if (p->left == NULL)
		return p->right;
	p->left = DelMin(p->left);
	return Balance(p);
}
int CBinTree::GetHeight(CTreeNode *node)const {
	return node == NULL ? 0 : node->height; 
}
void CBinTree::FixHeight(CTreeNode *node) {
	int hl = GetHeight(node->left);
	int hr = GetHeight(node->right);
	node->height = (hl > hr ? hl : hr) + 1;
}
int CBinTree::BalanceFactor(CTreeNode *node)const {
	//diferent of heights two subtree
	return GetHeight(node->right) - GetHeight(node->left);
}
CTreeNode* CBinTree::Balance(CTreeNode *node) {
	FixHeight(node);
	if (BalanceFactor(node) == 2) {//left subtree heigher
		if (BalanceFactor(node->right) > 0)
			node = LeftLeftCase(node);
		else
			node = RightLeftCause(node);
	}
	if (BalanceFactor(node) == -2) {//right subtree higher
		if (BalanceFactor(node->left) < 0)
			node = RightRightCase(node);
		else
			node = LeftRightCause(node);
	}
	return node;//return pointer to balanced node
}
CTreeNode* CBinTree::RightRightCase(CTreeNode *node) {
	CTreeNode *p = node->left;
	node->left = p->right;
	p->right = node;
	FixHeight(node);
	FixHeight(p);
	return p;
}
CTreeNode* CBinTree::LeftLeftCase(CTreeNode *node) {
	CTreeNode *p = node->right;
	node->right = p->left;
	p->left = node;
	FixHeight(node);
	FixHeight(p);
	return p;
}
CTreeNode* CBinTree::RightLeftCause(CTreeNode *node) {
	node->right = RightRightCase(node->right);
	return LeftLeftCase(node);
}
CTreeNode* CBinTree::LeftRightCause(CTreeNode *node) {
	node->left = LeftLeftCase(node->left);
	return RightRightCase(node);
}
CTreeNode* CBinTree::Add(CTreeNode *r, CTreeNode *node) {
	if (r == NULL) {
		return node;
	}
	else {
		if (strcmp(node->m_PassangerName, r->m_PassangerName) <= 0) {
			CTreeNode *p = Add(r->left, node);
			r->left = p;
			r = Balance(r);
		}
		else {
			CTreeNode *p = Add(r->right, node);
			r->right = p;
			r = Balance(r);
		}
	}
}
void CBinTree::PrintInOrder(CTreeNode *p)const {
	if (p != NULL) {
		PrintInOrder(p->left);
		p->PrintInfo();
		PrintInOrder(p->right);
	}
}
void CBinTree::DeleteTree(CTreeNode *p) {
	if (p != NULL) {
		DeleteTree(p->left);
		DeleteTree(p->right);
		delete p;
	}
	
}