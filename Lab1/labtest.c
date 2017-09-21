/************************************************************************
*file: labtest.c
*synopsis: this file has a code for testing argz functionö
*related files: none
*author: Volodymyr Kravchuk
*written: 19/09/2017
************************************************************************/

#include "ptr_str_mas.h"


int main() {
	const char *str = "SHELL=/bin/bash:usr=monty:PWD=/bin/monty:LANG=en_US.UTF-8";
	char *res;
	int len ,a;

	if (argz_create_sep(str, ':', &res, &len) == ERROR)
		printf("ERROR\n");
	else {
		a = argz_count(res, len);
		printf("%d  %d\n", a, len);
		argz_print(res, len);
	}
	
	if (argz_add(&res, &len, "add_to_end_of_string") == ERROR) 
		printf("ERROR\n");
	else {
		a = argz_count(res, len);
		printf("%d  %d\n", a, len);
		argz_print(res, len);
	}
	
	argz_delete(&res, &len, "PWD=/bin/monty");
	
	a = argz_count(res, len);
	printf("%d  %d\n", a, len);
	argz_print(res, len);
	
	if(argz_insert(&res, &len, "SHELL=/bin/bash", "insert_before") == ERROR)
		printf("ERROR\n");
	else {
		a = argz_count(res, len);
		printf("%d  %d\n", a, len);
		argz_print(res, len);
	}

	if (argz_replace(&res, &len, "usr=monty", "there was usr=monty") == ERROR)
		printf("ERROR");
	else {
		a = argz_count(res, len);
		printf("%d  %d\n", a, len);
		argz_print(res, len);
	}

	getch();


	return 0;
}

