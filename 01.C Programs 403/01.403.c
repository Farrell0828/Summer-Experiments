#include <stdio.h>
#include <stdlib.h>

int comp(const void* a, const void* b) {
	return *(double*)a - *(double*)b;
}

void PrintNums(double* nums, int n) {
	for (int i = 0; i < n; i++) {
		printf("%lf ", nums[i]);
	}
	printf("\n");
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

	qsort(nums, N, sizeof(nums[0]), comp);
	printf("The sorted numbers are: ");
	PrintNums(nums, N);

	double new_num;
	printf("Please enter the new number: ");
	scanf("%lf", &new_num);

	double* new_nums = (double*)malloc(sizeof(double) * (N + 1));

	int i = 0;
	while (nums[i] < new_num) {
		new_nums[i] = nums[i];
		i++;
	}
	new_nums[i] = new_num;
	for (; i <= N; i++) {
		new_nums[i + 1] = nums[i];
	}

	printf("The new numbers are: ");
	PrintNums(new_nums, N + 1);

	free(nums);
	free(new_nums);
	system("pause");
	return 0;
}