#include <stdio.h>
#include <stdlib.h>

void OutAll(char** names, int* outed_flag, size_t n, size_t M, size_t first) {
	size_t counted_number = 0;
	size_t pointed_sub = first;
	size_t outed_number = 0;

	while (1) {
		if (outed_flag[pointed_sub] == 0) {
			counted_number++;
			if (counted_number == M) {
				outed_flag[pointed_sub] = 1;
				outed_number++;
				printf("%s ", names[pointed_sub]);
				counted_number = 0;
			}
		}
		pointed_sub = (pointed_sub + 1) % n;
		
		if (outed_number == n) {
			break;
		}
	}
	return;
}

int main() {
	char* names[8] = { "A", "B", "C", "D", "E", "F", "G", "H" };
	size_t n = 8;
	int outed_flag[8] = { 0 };
	size_t first, M;
	printf("Please enter M: ");
	scanf("%zu", &M);
	printf("Please point the first person's subscript. Begin with 0: ");
	scanf("%zu", &first);

	OutAll(names, outed_flag, 8, M, first);
	printf("\n");

	system("pause");
	return 0;
}