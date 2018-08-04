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

int LegalDate(int y, int m, int d) {
	if (m > 12) {
		return 0;
	}
	if (d > 31) {
		return 0;
	}

	if (!IsBigMonth(m) && d > 30) {
		return 0;
	}

	if (IsLeapYear(y) && m == 2 && d > 29) {
		return 0;
	}

	if (!IsLeapYear(y) && m == 2 && d > 28) {
		return 0;
	}

	return 1;
}

int main() {
	printf("Please enter the date. Like \"2018 8 28\": ");
	int year, month, day;
	scanf("%d %d %d", &year, &month, &day);
	if (!LegalDate(year, month, day)) {
		printf("Illegal input date.\n");
		system("pause");
		return 0;
	}

	int leap_year[12] = { 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };
	int not_leap_year[12] = { 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 224, 365 };

	int num_of_days = 0;
	if (month == 1) {
		num_of_days = day;
	} 
	else if (IsLeapYear(year)) {
		num_of_days = leap_year[month - 2] + day;
	}
	else {
		num_of_days = not_leap_year[month - 2] + day;
	}

	printf("The result is: %d\n", num_of_days);
	system("pause");
	return 0;
}