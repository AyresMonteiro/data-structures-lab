#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main () {
	execl("/usr/bin/python3", "/usr/bin/python3", "hello_world_across_languages.py", NULL);

	return 0;
}


