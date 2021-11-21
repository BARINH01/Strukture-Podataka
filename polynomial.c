#include "Polynomial.h"
#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int ProcitajNazivDatoteke(char* fileName) {
	printf("Unesite ime datoteke iz koje zelite procitati koeficijente i eksponente: \n");
	scanf(" %s", fileName);
	return EXIT_SUCCESS;
}
int ProcitajDatoteku(Position head1, Position head2, char* fileName) {
	FILE* file = NULL;
	int status = EXIT_SUCCESS;
	char buffer = { 0 };

	file = fopen(fileName, "r");
	if (!file) {
		perror("Neuspjesno otvaranje datoteke!\n");
		return -1;
	}
	fgets(buffer, MAX_LINE, file);
	status = PrebaciNizulistu(head1, buffer);
	if (status != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_LINE, file);
	status = PrebaciNizulistu(head2, fileName);
	if (status != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}

	fclose(file);
}
int PrebaciNizulistu(Position head, char* buffer) {
	char* currentBuffer = buffer;
	int koeficijent = 0;
	int eksponent = 0;
	int numBytes = 0;
	int status = 0;
	Position newElement = NULL;

	while (strlen(currentBuffer) > 0)
	{
		status = sscanf(currentBuffer, " %d %d %n", &koeficijent, &eksponent, &numBytes);
		if (status != 2)
		{
			printf("nevaljala datoteka!\n");
			return EXIT_FAILURE;
		}

		newElement = Stvorielement(koeficijent, eksponent);
		if (!newElement)
		{
			return EXIT_FAILURE;
		}

		Unesisortirano(head, newElement);

		currentBuffer += numBytes;
	}

	return EXIT_SUCCESS;
}
Position Stvorielement(int koeficijent, int eksponent) {
	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(polinom));
	if (!newElement) {

		perror("Neuspješna alokacoja memorije!\n");
		return NULL;
	}
	newElement->koeficijent = koeficijent;
	newElement->eksponent = eksponent;
	newElement->next = NULL;

	return newElement;
}
int Unesisortirano(Position head, Position newElement) {
	Position temp = head;

	while (temp->next != NULL && temp->next->eksponent < newElement->eksponent)
	{
		temp = temp->next;
	}

	PrebaciIza(temp, newElement);

	return EXIT_SUCCESS;
}
int PrebaciIza(Position position, Position newElement) {
	if (position->next == NULL || position->next->eksponent != newElement->eksponent) {
		Umetninakon(position, newElement);
	}
	else {
		int zbrojkoeficijenata = position->next->koeficijent + newElement->koeficijent;

		if (zbrojkoeficijenata == 0) {
			Izbrisinakon(position);
		}
		else {
			position->next->koeficijent = zbrojkoeficijenata;
		}
		free(newElement);
	}
	return EXIT_SUCCESS;
}
int Izbrisinakon(Position previous) {
	
	Position toDelete = NULL;

	toDelete = previous->next;
	previous->next = toDelete->next;
	free(toDelete);

	return EXIT_SUCCESS;

}
int Umetninakon(Position position, Position newElement) {
	newElement->next = position->next;
	position->next = newElement;

	return EXIT_SUCCESS;
}
int ispisiPolinom(Position head) {

		Position p = head->next;

		if (p == NULL) {
			printf("Nema èlanova polinoma!\n");
		}

		if (p->koeficijent == 1 || p->koeficijent == -1)
			printf("%d\b", p->koeficijent);
		else   
			printf("%d", p->koeficijent);

		if (p->eksponent == 0);
		else if (p->eksponent == 1)  
			printf("x", p->eksponent);
		else   
			printf("x^%d", p->eksponent);

	for (p = p->next; p; p = p->next) {
			ispisielement(p);
		}
		puts("");

}
int ispisielement(Position p) {
	if (p->koeficijent == 1 || p->koeficijent == -1)
		printf("%+d\b", p->koeficijent);
	else  
		printf("%+d", p->koeficijent);

	if (p->eksponent == 0);
	else if (p->eksponent == 1) 
		printf("x", p->eksponent);
	else   
		printf("x^%d", p->eksponent);
}
Position suma(Position head1, Position head2) {
	Position zbrojihead = { .eksponent = 0, .koeficijent = 0, .next = NULL }; //ne znam kako ispraviti ovu gresku
	Position sumptr = &zbrojihead;
	Position temp1 = head1->next;
	Position temp2 = head2->next;

	while (temp1) {
		zbrojihead->next = Stvorielement(temp1->eksponent, temp1->koeficijent);
		sumptr = sumptr->next;
		temp1 = temp1->next;
	}

	while (temp2) {
		if (Unesisortirano(Stvorielement(temp2->eksponent, temp2->koeficijent), zbrojihead) == EXIT_FAILURE) {
			oslobodimemoriju(&zbrojihead);
			return NULL;
		}
		temp2 = temp2->next;
	}

	return zbrojihead->next;
}
int oslobodimemoriju(Position head) {
	Position temp1 = head;
	Position temp2 = head->next;

	if (!temp2) return;

	do {
		temp1 = temp2;
		temp2 = temp2->next;
		free(temp1);
	} while (temp2);
	head->next = NULL;

	return EXIT_SUCCESS;
}
int Pomnozipolinome(Position resultHead, Position head1, Position head2)
{
	Position i = NULL;
	Position j = NULL;

	for (i = head1->next; i != NULL; i = i->next)
	{
		for (j = head2->next; j != NULL; j = j->next)
		{
			Position newElement = CreateElement(i->koeficijent * j->koeficijent, i->eksponent + j->eksponent);
			if (!newElement)
			{
				return EXIT_FAILURE;
			}

			Unesisortirano(resultHead, newElement);
		}
	}
	return EXIT_SUCCESS;
}