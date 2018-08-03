#include <stdio.h>
#include <stdlib.h>

int main() {
	int count = 0;
	for (int i = 1; i < 1000; i++) {
		int sum = 0;
		for (int j = 1; j < i; j++) {
			if (i % j == 0) {
				sum += j;
			}
		}
		if (sum == i) {
			printf("%d ", i);
			count++;
		}
		if (count == 5) {
			printf("\n");
			count = 0;
		}
	}

	system("pause");
	return 0;
}