#define CRT_SECURE_NO_WARNINGS
#include "polynomial.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	polinom head1 = { .eksponent = 0, .koeficijent = 0, .next = NULL };
	polinom head2 = { .eksponent = 0, .koeficijent = 0, .next = NULL };
	polinom zbroji_head = { .eksponent = 0, .koeficijent = 0, .next = NULL };
	polinom umnrez_head = { .eksponent = 0, .koeficijent = 0, .next = NULL };

	char fileName[MAX_SIZE] = { 0 };

	Procitajnaziv(fileName);

	if (ProcitajDatoteku(&head1, &head2, fileName) == EXIT_SUCCESS)
	{
		IspisiPolinom(head1.next);
		IspisiPolinom(head2.next);

		zbroji_head.next = sum(&head1, &head2);
		Pomnozipolinome(&umnrez_head, &head1, &head2);

		ispisiPolinom(zbroji_head.next);
		ispisiPolinom(umnrez_head.next);

		oslobodiMemoriju(&head1);
		oslobodiMemoriju(&head2);
		oslobodiMemoriju(&zbroji_head);
		oslobodiMemoriju(&umnrez_head);
	}

	return EXIT_SUCCESS;
}
