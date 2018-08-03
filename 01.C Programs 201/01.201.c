#include <stdio.h>
#include <stdlib.h>

int IsLeapYear(int y) {
	if (!(y % 4) && (y % 100)) {
		return 1;
	}
	else if (!(y % 400)) {
		return 1;
	}
	else {
		return 0;
	}
}

int IsBigMonth(int m) {
	if (m == 1 || m == 3 || m == 5 || m == 7 ||
		m == 8 || m == 10 || m == 12) {
		return 1;
	}
	else {
		return 0;
	}
}

int main() {
	int y, m, d;
	printf("Please input the date: ");
	scanf("%d %d %d", &y, &m, &d);

	if (m > 12) {
		printf("不正确\n");
		system("pause");
		return 0;
	}
	if (d > 31) {
		printf("不正确\n");
		system("pause");
		return 0;
	}

	if (!IsBigMonth(m) && d > 30) {
		printf("不正确\n");
		system("pause");
		return 0;
	}

	if (IsLeapYear(y) && m == 2 && d > 29) {
		printf("不正确\n");
		system("pause");
		return 0;
	}

	if (!IsLeapYear(y) && m == 2 && d > 28) {
		printf("不正确\n");
		system("pause");
		return 0;
	}

	printf("正确\n");
	system("pause");
	return 0;
}