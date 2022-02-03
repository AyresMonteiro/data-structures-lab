#include <stdio.h>

void doesntReturn (void) {

}

int return3 () {
	return 3;
}

void main () {
	printf("%d\n", return3());
	doesntReturn();
}

