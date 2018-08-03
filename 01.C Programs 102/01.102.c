#include <stdio.h>
#include <stdlib.h>

int main() {
	char input, output;
	printf("Please input a character: ");
	scanf("%c", &input);
	output = 'z' + 'a' - input;
	printf("The result is: %c\n", output);

	system("pause");
	return 0;
}