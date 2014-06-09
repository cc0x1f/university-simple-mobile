/******************************************************************
*
* StringExtra.c
*
* Description: Helper functions for string handling. 
* Courtesy of http://www.kixor.net
*
* Computer Graphics Proseminar SS 2014
* 
* Interactive Graphics and Simulation Group
* Institute of Computer Science
* University of Innsbruck
*
*******************************************************************/

#include "../../header/objparser/StringExtra.h"


char strequal(const char *s1, const char *s2)
{
	if(strcmp(s1, s2) == 0)
		return 1;
	return 0;
}

char contains(const char *haystack, const char *needle)
{
	if(strstr(haystack, needle) == NULL)
		return 0;
	return 1;
}

int strpos(const char *haystack, const char *needle)
{
	const char *p = strstr(haystack, needle);
	if (p != NULL)
		return p - haystack;
	return -1;
}