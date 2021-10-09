#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int sum (int args, ...) {
	int sum = 0;
	va_list argsList;

	va_start(argsList, args);

	for (int i = 0; i < args; i++) {
		sum += va_arg(argsList, int);
	}

	va_end(argsList);

	return sum;
}

int main () {
	printf("The sum of 3, 8 and 9 is: %d\n", sum(3, 3, 8, 9));
	printf("The sum of 3 and 8 is: %d\n", sum(2, 3, 8));

	return 0;
}


