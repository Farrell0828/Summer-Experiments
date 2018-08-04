#include <stdio.h>
#include <stdlib.h>

int main() {
	long i = 0, n;
	printf("Please enter n: ");
	scanf("%d", &n);

	while (i < n) {
		n -= i;
		i++;
	}

	if (i % 2 == 0) {
		printf("%d/%d\n", n, i + 1 - n);
	}
	else {
		printf("%d/%d\n", i + 1 - n, n);
	}

	system("pause");
	return 0;
}