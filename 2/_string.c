#include <stdio.h>
#include <stdlib.h>

/*TODO: 1. Follow your codestyle. 
       	   There are some missed spaces and so on.
	2. Comments about function input must be with function declaration.
	   Comments about function implementation(some tips, explanations) must be with function description.	 
*/

int _strlen (char* string) { // input MUST end with \0
    int i;	  //TODO: Not initialized. I see, that it will be initialized in the next line, but that's the rule you should obey
		  //      It will help you in future. Ilya Ded calls it "culture of coding", if I translate it right.
	
    for (i = 0; string[i]!='\0'; i++);//No codestyle
    return i;
};

int _is_digit (char symbol) {
    if ((symbol >= (int)'0')&&(symbol<=(int)'9')) 
        return 1;
    return 0;
};

int _atoi (char* string) { // for wrong input returns zero value
    int is_minus = 0;
    if (*string=='-') {
        is_minus = 1;
        *string++;
    }
    int number = 0;
    while (_is_digit(*string)) {
        number+=(*string)-(int)'0';
        number*=10;
        string++;
    };
    return (is_minus ? -1 : 1)*number/10;
};

void swap_chars (char* a, char* b) {
    char buffer = *a;
    *a = *b;
    *b = buffer;
}

char* _itoa(int number) {
    char* output = malloc(sizeof(char)*13);// SUGGESTION: Why here dinamic? It makes user free memory.
					   // Why not following? User uses static memory with 33 chars. 
    char buffer;
    int j = 0, i = 0, temp = abs(number), current;
    
    while (temp) {
        current=temp%10;
        output[i]=current+(int)'0';
        temp-=current;
        temp/=10;
        i++;
    }

    if (number < 0) {
        output[i]='-';
        i++;
    }

    output[i] = '\0';

    do {
        i--;
        swap_chars(&output[i], &output[j]);
        j++;
    } while (i>j);
    
    return output;
}


