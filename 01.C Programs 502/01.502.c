#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int IsPrimeNumber(int n) {
	for (int i = 2; i < n; i++) {
		if (n % i == 0) {
			return 0;
		}
	}
	return 1;
}

int CalculateNumber(int n) {
	if (IsPrimeNumber(n)) {
		return 0;
	}

	int result = 0;
	for (int i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) {
			result += (1 + CalculateNumber(i) + CalculateNumber(n / i));
		}
	}
	return result;
}

int main() {
	int n;
	printf("Please enter n: ");
	scanf("%d", &n);

	int result;
	if (IsPrimeNumber(n)) {
		result = 1;
	}
	else {
		result = CalculateNumber(n);
	}
	printf("The result is: %d\n", result);

	system("pause");
	return 0;
}