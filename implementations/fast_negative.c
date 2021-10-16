#include <stdio.h>
#include <stdlib.h>

int fast_negative(int x) {
	return ~x + 1;
}

int main () {
	printf("fast_negative(10): %d\n", fast_negative(10));

	return 0;
}

