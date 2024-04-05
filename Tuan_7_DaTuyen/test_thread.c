#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	/* code */
	printf("POSIX version is set to %ld\n", _POSIX_VERSION);
	if(_POSIX_VERSION < 199506L)
		printf("This system does not support thread!\n");
	else
		printf("Thread is available in this system!\n");
	return 0;
}