/************************************************************************
*file: ptr_str_mas.c
*synopsis: The argz functions use malloc to allocate argz vectors. Argz function
*designed for work with string and elements of string. Element of string is substring
*highlighted with '\0'. Also use functions with "string.h" : strlen - for get length of
*elements and strcmp for compare elements
* These functions are declared in the include file "ptr_str_mas.h".
*related files: none
*author: Volodymyr Kravchuk
*written: 19/09/2017
************************************************************************/

#include "ptr_str_mas.h"

/*-------------------------------------------------------------------------------------------------------*
Name            argz_create_sep - split the string into substrings

Usage            argz_create_sep(str,':',&result,&length);

Prototype in    ptr_str_mas.h

Synopsis     function split string into substrings by a given character , replaces 
the character with '\0' (replace string by elements)

Return value    return OK if performance successful else return ERROR
*----------------------------------------------------------------------------------------------------------------*/

error_t argz_create_sep(const char *string,
	                 int sep,
	                 char **argz,
	                 size_t *argz_len) {

	int i = 0;
	
	if (string == NULL) {
		(*argz_len) = 0;
		return ERROR;
	}
	
	(*argz_len) = strlen(string) + 1;
	(*argz) = (char*)malloc(sizeof(char)*(*argz_len));
	
	if (*argz == NULL)
		return ERROR;                //memory allocation error

	for (i = 0; i < (*argz_len); i++) {
		if (string[i] == sep)
			(*argz)[i] = '\0';
		else
			(*argz)[i] = string[i];
	}

	(*argz)[(*argz_len)] = '\0';    // add last '\0'         

	return OK;
}

/*-------------------------------------------------------------------------------------------------------*
Name            argz_count - count the elements in string

Usage            int len = argz_count(str,length)

Prototype in    ptr_str_mas.h

Synopsis     function count number elements in a given string

Return value    return number of substrings
*----------------------------------------------------------------------------------------------------------------*/

size_t argz_count(const char *argz,
	              size_t argz_len) {

	int i = 0 , res = 0;

	if (argz == NULL || argz_len == 0)
		return 0;

	for (i = 0; i < argz_len; i++)
		if (argz[i] == '\0')
			res += 1;

	return res;
}

/*-------------------------------------------------------------------------------------------------------*
Name            argz_add - add new element

Usage            argz_add(&str,&length,new_substr);

Prototype in    ptr_str_mas.h

Synopsis     function add new element at the end of given string , changes given string
and value length of string

Return value    return OK if performance successful else return ERROR
*----------------------------------------------------------------------------------------------------------------*/

error_t argz_add(char **argz, 
	             size_t *argz_len, 
	             const char *str) {
	
    int i = 0 , add_len;
	char *dest;                           // new pointer for save result

	if (str == NULL)
		return OK;
   
	add_len = strlen(str) + 1;
	dest = (char*)malloc(sizeof(char)*((*argz_len)+add_len));

	free(argz);

	if (dest == NULL)
		return ERROR;
	/*record to new string */
	for (i = 0; i < (*argz_len) + add_len ; i++) {
		if (i < (*argz_len)) 
			dest[i] = (*argz)[i];
		else
			dest[i] = str[i - (*argz_len)];
	}
	
	(*argz_len) += add_len;
	dest[(*argz_len)] = '\0';
	(*argz) = dest;

	return OK;
}

/*-------------------------------------------------------------------------------------------------------*
Name            argz_delete - delete element

Usage            argz_delete(&string,&length,elem_for_delete)

Prototype in    ptr_str_mas.h

Synopsis     function delete a given element with string , changes string and length of string

Return value    function has type VOID and not return value
*----------------------------------------------------------------------------------------------------------------*/

void argz_delete(char **argz, 
	             size_t *argz_len, 
	             char *entry) {

	int i , len, k;
	char *result, *p;
	
	if (entry == NULL || (*argz) == NULL)
		return;

	p = (*argz);
	result = (char*)malloc(sizeof(char)*((*argz_len) - strlen(entry)));
	
	len = argz_count((*argz), *argz_len);
	i = 0;
	k = 0;
	/*record all elements argz to new string except for the entry*/
	while (i < len) {
		if (strcmp(p, entry) != 0) {
			argz_add(&result, &k, p);
		}
		p += strlen(p) + 1;
		i += 1;
	}

	(*argz_len) = k;
	(*argz) = result;
}

/*-------------------------------------------------------------------------------------------------------*
Name            argz_insert - insert element

Usage            argz_insert(&string,&length,before,elem_for_insert)

Prototype in    ptr_str_mas.h

Synopsis     function insert new element in string to the position before the element "before",
and changes input line and length

Return value    return OK if performance successful else return ERROR
*----------------------------------------------------------------------------------------------------------------*/

error_t argz_insert(char **argz, 
	                size_t *argz_len, 
	                char *before,
	                const char *entry) {

	int i, k, len;
	char *result, *p;

	if (before == NULL) {
		return argz_add(argz, argz_len, entry);
    }

	p = (*argz);
	result = (char*)malloc(sizeof(char)*((*argz_len) + strlen(entry)));

	if (result == NULL)
		return ERROR;

	len = argz_count((*argz), *argz_len);
	i = 0;
	k = 0;

	while (i < len) {
		if (strcmp(p, before) == 0) {
			argz_add(&result, &k, entry);
		}
		argz_add(&result, &k, p);
		
		p += strlen(p) + 1;
		i += 1;
	}

	(*argz_len) = k;
	(*argz) = result;
    
	return OK;
}

/*-------------------------------------------------------------------------------------------------------*
Name            argz_next - sets pointer at element

Usage            argz_next(string,length,entry)

Prototype in    ptr_str_mas.h

Synopsis     function sets pointer in element of string after element "entry"

Return value    return pointer char*
*----------------------------------------------------------------------------------------------------------------*/


char * argz_next(char *argz, 
	             size_t argz_len,  
	             const char *entry) {
	
	int i, len;
	char *p;

	if (entry == NULL)
		return argz;

	p = argz;

	len = argz_count(argz, argz_len);
	i = 0;

	while (i < len) {
		if (strcmp(p, entry) == 0) {
			p += strlen(p) + 1;
			break;
		}
		p += strlen(p) + 1;
		i += 1;
	}
	if (i < len - 1)
		return p;
	else
		return NULL;
}

/*-------------------------------------------------------------------------------------------------------*
Name            argz_replace - replace elements of string

Usage            argz_repalce(&string,&length,str_for_changes,with)

Prototype in    ptr_str_mas.h

Synopsis     function insert new element in string in place of element "with"

Return value    return OK if performance successful else return ERROR
*----------------------------------------------------------------------------------------------------------------*/

error_t argz_replace(char **argz,
	                 size_t *argz_len, 
	                 const char *str, 
	                 const char *with) {
	
	if (str == NULL || with == NULL)
		return ERROR;

	if (argz_insert(argz, argz_len, str, with) == OK) {
		argz_delete(argz, argz_len, str);
		return OK;
	}
	else
		return ERROR;
}

/*-------------------------------------------------------------------------------------------------------*
Name            argz_print - print string

Usage            argz_print(string,length)

Prototype in    ptr_str_mas.h

Synopsis     function print all element of given string

Return value    no return value
*----------------------------------------------------------------------------------------------------------------*/

void argz_print(const char *argz,
	            size_t argz_len) {
	const char *p = 0;

	if (argz == NULL)
		return;
	
	while((p = argz_next(argz, argz_len, p)))
		printf("%s'\\0'", p);

	printf("\n");
}