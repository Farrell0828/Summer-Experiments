#include <stdio.h>
#include <stdlib.h>

int main() {
	long s, d, h, m;
	printf("Please input the time by second: ");
	scanf("%ld", &s);

	m = s / 60;
	s = s % 60;
	h = m / 60;
	m = m % 60;
	d = h / 24;
	h = h % 24;

	printf("The time by day is: %ld days %ld hours %ld minutes %ld seconds.\n", d, h, m, s);

	system("pause");
	return 0;
}