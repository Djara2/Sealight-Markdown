#include <stdio.h>
#include <string.h>

int main(void)
{
	char s[] = "\_";
	int len = strlen(s);
	printf("The length of \"%s\" is %d\n", s, len);
	return 0;
}
