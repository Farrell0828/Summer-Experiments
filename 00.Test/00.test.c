#include <stdio.h>
#include <stdlib.h>

int main() {

	int a;

	if (scanf("%d", &a)) {
		printf("Right\n");
	}
	else {
		printf("Wrong\n");
	}

	system("pause");
	return 0;
}