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

int main() {
	printf("Please enter the date. Like \"2018 8 28\": ");
	int year, month, day;
	scanf("%d %d %d", &year, &month, &day);

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