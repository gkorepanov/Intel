#include "_string.h"
#include <stdlib.h>
#include <stdio.h>

/*TODO: Implement testing.
	You input some data into your functions. And compare output  with what you expect to get.
	
	Example:
		int testNumber = 0;
		int failed_tests[NUM_TESTS] = {};
		int last_failed = 0;
		...
		int positive_number = 1234;
		char positive_string[33] = {};
		testNumber++;
		_itoa(positive_number,positive_string);
		printf("%i Test positive number to string ", testNumber);
		if (strcmp(positive_string, "1234") == 0) {
			printf("passed\n");
			}
		else {
			failed_tests[last_failed++] = test_Number;
			printf("FAILED");	
			}

		...
		//logs after Tests about failed tests. 			
*/

main() { // for check
    char string[10];//TODO: Initialize
    char* string_from_num;//
    int num;//

    scanf("%s%i", string, &num);
    string_from_num = _itoa(num);
    printf("%i\n%s\n", _atoi(string), string_from_num);// I can't distinguish string and int in output.
    free(string_from_num);// SUGGESTION: That's not good. When you force user to free memory.
			  // Look at the examples of real string.h 's functions. 	
    return 0;
};

