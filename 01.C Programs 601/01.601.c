#include <stdio.h>
#include <stdlib.h>

int* Insert(int* list, size_t n, int iterm) {
	int* new_list = (int*)malloc(sizeof(int) * (n + 1));
	for (int i = 0; i < n; i++) {
		new_list[i] = list[i];
	}
	free(list);
	list = new_list;

	int i;
	for (i = 0; i < n; i++) {
		if (list[i] > iterm) {
			break;
		}
	}

	if (i == n) {
		list[n] = iterm;
		return list;
	}

	for (int j = n; j > i; j--) {
		list[j] = list[j - 1];
	}
	list[i] = iterm;
	return list;
}

void PrintList(int* list, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", list[i]);
	}
	printf("\n");
}

int main() {
	printf("Please enter integer sequence. Separated by \"Enter\" or \"Space\", \n");
	printf("and End with any non-numeric character: \n");
	int temp, n = 0;
	int* list = (int*)malloc(sizeof(int) * 0);

	while (scanf("%d", &temp) == 1) {
		list = Insert(list, n, temp);
		n++;
	}
	printf("Sort result of the integer sequence you entered is: ");
	PrintList(list, n);

	int* list_odd = (int*)malloc(sizeof(int) * 0);
	int* list_even = (int*)malloc(sizeof(int) * 0);
	int odd_count = 0, even_count = 0;
	for (int i = 0; i < n; i++) {
		if (list[i] % 2) {
			list_odd = Insert(list_odd, odd_count, list[i]);
			odd_count++;
		}
		else {
			list_even = Insert(list_even, even_count, list[i]);
			even_count++;
		}
	}

	printf("The odd integer sequence is: ");
	PrintList(list_odd, odd_count);
	printf("The even integer sequence is: ");
	PrintList(list_even, even_count);

	free(list);
	free(list_odd);
	free(list_even);
	system("pause");
	return 0;
}