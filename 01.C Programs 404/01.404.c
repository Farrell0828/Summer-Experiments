#include <stdio.h>
#include <stdlib.h>

void PrintNums(double* nums, int n) {
	for (int i = 0; i < n; i++) {
		printf("%lf ", nums[i]);
	}
	printf("\n");
}

double Average(double* nums, int n) {
	double sum = 0.0;
	for (int i = 0; i < n; i++) {
		sum += nums[i];
	}
	return sum / n;
}

int main() {
	int N;
	printf("Please enter the count of numbers: ");
	scanf("%d", &N);
	double* nums = (double*)malloc(sizeof(double) * N);

	for (int i = 0; i < N; i++) {
		double m;
		scanf("%lf", &m);
		nums[i] = m;
	}
	PrintNums(nums, N);

	double average = Average(nums, N);

	for (int i = 0; i < N; i++) {
		if (nums[i] > average) {
			printf("%lf ", nums[i]);
		}
	}
	printf("\n");

	free(nums);
	system("pause");
	return 0;
}