#include <stdio.h>
#include <limits.h>

// This function works up to the minimum signed integer plus one.
// The minimum integer value will result into itself. For example:
// a int of 4 bits size has as minimum value of -8 (1000). When
// you subtract one it becomes 7 (0111). When you bitwise invert 
// 0111 (7), you have 1000 (-8). That's why the function only works
// up to the minimum + 1 (In a signed integer of 4 bits size, the
// minimum plus one is -7: 1001).
int fast_abs(int x) {
	if(x < 0) {
		return ~(x - 1);
	}

	return x;
}

int main () {
	printf("fast_abs(%d): %d\n", INT_MIN + 1, fast_abs(INT_MIN + 1));
	printf("fast_abs(%d): %d\n", INT_MAX, fast_abs(INT_MAX));

	return 0;
}

