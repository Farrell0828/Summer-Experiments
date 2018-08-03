#include <stdio.h>
#include <stdlib.h>

int Change(int x) {
	return (x + 7) % 10;
}

int ReChange(int y) {
	return (y + 3) % 10;
}

int Encode(int input) {
	int a, b, c, d;
	a = input / 1000;
	b = input % 1000 / 100;
	c = input % 100 / 10;
	d = input % 10;

	a = Change(a);
	b = Change(b);
	c = Change(c);
	d = Change(d);

	return c * 1000 + d * 100 + a * 10 + b;

}

int Decode(int input) {
	int c, d, a, b;
	c = input / 1000;
	d = input % 1000 / 100;
	a = input % 100 / 10;
	b = input % 10;

	a = ReChange(a);
	b = ReChange(b);
	c = ReChange(c);
	d = ReChange(d);

	return a * 1000 + b * 100 + c * 10 + d;
}

int main() {
	printf("Please enter the number: ");
	int x;
	scanf("%d", &x);
	int y = Encode(x);
	printf("Encode result: %d\n", y);
	printf("Decode result: %d\n", Decode(y));

	system("pause");
	return 0;
}