#include "CBinTree.h"

int main()
{
	CBinTree *tree = new CBinTree();
	tree->MakeTree("Flights.csv");
	tree->AddApplication("Lviv;732;Bogdan;19.03");
	tree->DeleteApplication("Paris;311;Kvitka;17.09");
	tree->DeleteApplication("Paris;311;Kvitka;17.09");
	tree->ExtractApplication("26.04");
	tree->ExtractApplication("26.04");
	tree->ExtractApplication(453);
	tree->Print();

	getchar();
    return 0;
}

