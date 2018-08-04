#include <stdio.h>
#include <stdlib.h>

int IsPrimeNumber(int n) {
	for (int i = 2; i < n; i++) {
		if (n % i == 0) {
			return 0;
		}
	}
	return 1;
}

int main() {
	int n;
	printf("Please enter n: ");
	scanf("%d", &n);

	for (int i = 1; i < n; i++) {
		if (IsPrimeNumber(i) && (i + 2) <= n && IsPrimeNumber(i + 2)) {
			printf("%d %d\n", i, i + 2);
		}
	}

	system("pause");
	return 0;
}