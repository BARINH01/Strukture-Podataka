#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)
#define MAX_LINE (1024)
struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthyear;
	Position next;
} Person;
// 2. zadatak
int Prependlist(Position head, char* name, char* surname, int birthyear);
Position Createperson (char* name, char* surname, int birthyear);
void Printlist (Position p);
Position FindLast(Position head);
void Insertafter(Position position, Position newPosition);
Position FindbyLastName(Position first, char *surname);
int AppendList(Position head, char* name, char* surname, int birthyear);
Position FindBefore(Position head, char* surname);
void toDeleteAfter(Position head);
Position* importList(char* filename);

// 3. zadatak
void addBehind(Position head, char* name, char* surname, int birthyear);
void addBefore(Position head, char* name, char* surname, int birthyear);
void sortByLastname(Position head);
void swapPerson(Position temp);
int exportList(Position head, char* filename);
int main(int argc, char** argv)
{
	Person head = { .next = NULL, .name = {0}, .surname = {0}, .birthyear = 0 };
	Position p = &head;

	return 0;
}
Position CreatePerson(char* name, char* surname, int birthyear)
{
	Position newPerson = NULL;
	Position head;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		perror("Can't allocate memory!\n");
		return -1;
	}
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthyear = birthyear;
	newPerson->next = NULL;
	head->next = newPerson;

	return newPerson;
}
int Prependlist(Position head, char* name, char* surname, int birthyear)
{
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));

	if (!newPerson) {

		return -1;
	}
	InsertAfter(head, newPerson);

	return 0;
}
void Printlist(Position first) {
	Position temp = first;

	while (temp) {

		printf(" %s %s %d", temp->name, temp->surname, temp->birthyear);
		temp = temp->next;
	}

	return;
}
Position FindLast(Position head)
{
	Position temp = head;

	while (temp ->next != NULL) {

		temp = temp->next;
	}
	return temp;
}
void Insertafter(Position position, Position newPosition)
{
	Position newPerson;
	newPerson->next = position->next;
	position->next = newPerson;

	return;
}

Position FindbyLastName(Position first, char* surname)
{
	Position temp = first;

	while (temp) {
		if (strcmp(temp->surname, surname) == 0)
			return temp; 
		temp = temp->next;
			}

	return temp;
}
int AppendList(Position head, char* name, char* surname, int birthyear) {

	Position newPerson = NULL;
	Position last = NULL;

	newPerson = CreatePerson(name, surname, birthyear);
	if (!newPerson)
	{
		return -1;
	}
	last = FindLast(head);

	return 0;
}
Position FindBefore(Position head, char* surname) {
	Position temp = NULL;

	for (temp = head; temp->next; temp = temp->next) {
		if (strcmp(temp->next->surname, surname) == 0) {
			return temp;
		}
		if (head->next == NULL) {
			return NULL;
		}

	}
}
void toDeleteAfter(Position head) {
	Position temp = head;
	Position before = NULL;
	
	before = FindBefore(head, char *surname);

	if (before == NULL) {
		printf("Error!");
	}

	temp = before->next;
	before->next = temp->next;

	free(temp);
	return;
} // kraj 2.zadatka

//3. zadatak

void addBehind(Position head, char* name, char* surname, int birthyear)
{
	Position temp = head;
	Position Persontoinsert = NULL;
	
	Persontoinsert = CreatePerson(name, surname, birthyear);
	if (!Persontoinsert) {
		printf("Greska pri dodavanju iza elementa!\n");
		return 1;
	}
	temp = FindbyLastName(temp, surname);
	Insertafter(temp, Persontoinsert);
}
void addBefore(Position head, char* name, char* surname, int birthyear)
{
	Position temp = head;
	Position Persontoinsert = NULL;

	Persontoinsert = CreatePerson(name, surname, birthyear);
	if (!Persontoinsert) {
		printf("Greska pri dodavanju iza elementa!\n");
		return 1;
	}
	temp = FindBefore(temp, surname);
	Insertafter(temp, Persontoinsert);

	return;
}
void sortByLastname(Position head)
{
	Position temp = head;
	int (*sort_check)(char* str1, char* str2);
	int choice = 0;
	int swapped = 1;

	if (!temp->next) 
		return;
	if (!temp->next->next)
		return;

	while (1) {
		printf("Zelite li uzlazno ili silazno sortiranje\n"
			"1 - uzlazno\n"
			"2 - silazno\n");
		scanf(" %d", &choice);
		if (choice == 1) {
			sort_check = ascending;
			break;
		}
		else if (choice == 2) {
			sort_check = descending;
			break;
		}
		else {
			printf("Pogresan unos. Pokusajte ponovno:\n");
		}
	}

	while (swapped) {
		swapped = 0;
		temp = head;
		while (temp->next->next) {
			if (sort_check(temp->next->surname, temp->next->next->surname) > 0) {
				swapPerson(temp);
				swapped = 1;
			}
			temp = temp->next;
		}
	}
}

void swapPerson(Position temp) {
	Position first = temp->next;
	if (!first) {
		printf("Error!! Person 1 doesn't exist\n");
	}
	Position second = first->next;
	if (!second) {
		printf("Error! Person 2 doesn't exist\n");
	}
	first->next = second->next;
	second->next = first;
	temp->next = second;
}
Position* importList(char* filename) {
	char buffer[MAX_LINE];
	FILE* file = NULL;
	Position head = { .name = "", .surname = "", .birthyear = 0, .next = NULL };
	char name[MAX_SIZE], surname[MAX_SIZE];
	int byear;

	file = fopen(filename, "r");
	if (!file) {
		perror("Failed to open file in function importList");
		return NULL;
	}

	while (!feof(file)) {
		strcpy(buffer, "");
		fgets(buffer, MAX_LINE, file);
		if (sscanf(buffer, " %s %s %d", name, surname, &birthyear) == 3) {
			prependList(&head, name, surname, birthyear);
		}
	}
	fclose(file);
	return head.next;
}
int exportList(Position head, char* filename) {
	FILE* file = NULL;
	Position temp = head->next;

	file = fopen(filename, "w");
	if (!file) {
		perror("Failed to open file in function exportList\n");
		return -1;
	}

	while (temp) {
		fprintf(file, "%s %s %d\n", temp->name, temp->surname, temp->birthyear);
		temp = temp->next;
	}
	fclose(file);
	return 0;
}

//ne znam sto staviti u main funkciju da sve povezem;
