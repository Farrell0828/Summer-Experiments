#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int IsAlphabet(char c) {
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
		return 1;
	}
	else {
		return 0;
	}
}

int main() {
	char string[101];
	printf("Please enter the string. No more than 100 characters: ");
	scanf("%s", string);

	int i = 0, count = 0;
	while (string[i]) {
		if (!IsAlphabet(string[i])) {
			i++;
		}
		else {
			break;
		}
	}

	while (string[i]) {
		if (IsAlphabet(string[i])) {
			i++;
		}
		else {
			count++;
			while (string[i] && !IsAlphabet(string[i])) {
				i++;
			}
		}
	}

	if (IsAlphabet(string[--i])) {
		count++;
	}

	printf("The number of words is: %d\n", count);
	system("pause");
	return 0;
}