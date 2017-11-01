/************************************************************************
*file: labtest.c
*synopsis: this file has a code for testing functions
*related files: none
*author: Volodymyr Kravchuk
*written: 25/09/2017
************************************************************************/
#include"Scanner.h"


int main() {
	int res;
	RECORD_SET *rs;
	
	create_db("Scanners.csv", "Scanners.db");
	print_db("Scanners.db");
	del_scanner("Scanners.db", 3);
	print_db("Scanners.db");
	add_scanner("Scanners.db", "Asus;AS1055;2009;99.99;210;297");
	print_db("Scanners.db");
	make_index("Scanners.db", "year");
	reindex("Scanners.db");
	rs = get_recs_by_index("Scanners.db", "year");
	rs = select("Scanners.db", "year", "2009");
	print_rec_set(rs);
	scanf("%i", &res);
}