#define _CRT_SECURE_NO_WARNINGS
#include "declarations.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv[])
{
	double rezultat = 0;

	if (argc == 1) {

		CalculatePostfixFromFile("postfix.txt", &rezultat);

		printf("Rezultat je: %lf\n", rezultat);
	}
	else {
		CalculatePostfixFromFile(argv[1], &rezultat);

		printf("Rezultat je: %lf\n", rezultat);
	}


	return 0;
}