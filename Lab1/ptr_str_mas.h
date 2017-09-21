/************************************************************************
*file: ptr_str_mas.h
*synopsis: declarations for argz functions, types
*author: Kravchuk V.
*written: 19/09/2017
*last modified: none
************************************************************************/

#pragma once

#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stddef.h> // for  size_t

typedef enum { 
	OK, 
    ERROR 
} error_t;

/* function prototypes */

error_t argz_create_sep(const char *string,
	                    int sep,
	                    char **argz,
	                    size_t *argz_len);

size_t argz_count(const char *argz, 
	              size_t arg_len);

error_t argz_add(char **argz, 
	             size_t *argz_len, 
	             const char *str);

void argz_delete(char **argz, 
	             size_t *argz_len, 
	             char *entry);

error_t argz_insert(char **argz,
	                size_t *argz_len,
                 	char *before,
	                const char *entry);

char * argz_next(char *argz, 
	             size_t argz_len, 
	             const char *entry);

error_t argz_replace(char **argz, 
	                 size_t *argz_len, 
	                 const char *str, 
	                 const char *with);

void argz_print(const char *argz,
	            size_t argz_len);