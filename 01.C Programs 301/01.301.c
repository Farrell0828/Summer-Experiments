#include <stdio.h>
#include <stdlib.h>

int main() {
	int x = 1;
	for (int i = 0; i < 9; i++) {
		x = (x + 1) * 2;
	}
	printf("The total number of peach: %d\n", x);

	system("pause");
	return 0;
}