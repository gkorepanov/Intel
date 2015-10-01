
/*TODO: All "include"s you use in .c must be in .h
	Also here must be defense from "multiinclude"
	For example
	#pragma once
	
	or		
	
	#ifndef BLABLA_H
	#define BLABLA_H
	your code
	#endif  //BLABLA_H	
	 
*/

/*TODO: In this file in comments you should explain, how to use your function
	About free memory of some pointers, about input. 
*/

/*TODO: I advised you to look the declarations of real functions in stdlib. Try to do it. It may help you.
*/

int _strlen (char* string);
int _atoi (char* string); 
int _is_digit (char symbol);//SUGGESTION: I'm not sure, this two functions will be needed for user.
void swap_chars (char* a, char* b);// They are kinda detail of implementation. I suggest not to include them in this file.
char* _itoa(int number);
