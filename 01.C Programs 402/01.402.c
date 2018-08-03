#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char string[10001];
	printf("Please enter a string. No more than 10000 characters: ");
	scanf("%s", &string);
	char* sub_string = "debug";

	if (strstr(string, sub_string)) {
		printf("Include \"debug\" substring.\n");
	}
	else {
		printf("Don't include \"debug\" substring.\n");
	}

	system("pause");
	return 0;
}