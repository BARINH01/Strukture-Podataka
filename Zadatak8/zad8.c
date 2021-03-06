#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct _Stablo;
typedef struct _Stablo* Position;
typedef struct _Stablo {
	int Number;
	Position left;
	Position right;
} Stablo;

Position StvoriPrazno(Position S);
Position insertElement(int x, Position S);
int dodaj_element(Position S);
int PrintInorder(Position S);
int PrintPostorder(Position S);
int PrintPreorder(Position S);
Position deletelement(int x, Position S);
int brisi_element(Position S);
Position Find(int x, Position S);
int trazielement(Position S);
Position Findmin(Position S);
Position Findmax(Position S);
int Meni(Position S);


int main() {
	Stablo root = { .Number = 0, .left = NULL, .right = NULL };
	int i = 0;

	printf("Unesite root element(broj): \n");
	scanf_s("%d", &root.Number);

	i = Meni(&root);


	return EXIT_SUCCESS;
}

Position StvoriPrazno(Position S) {

	if (S != NULL) {
		StvoriPrazno(S->left);
		StvoriPrazno(S->right);
		free(S);
	}

	return NULL;

}
Position insertElement(int x, Position S) {

	if (S == NULL) {
		S = (Position)malloc(sizeof(Stablo));
		if (!S) {
			perror("Neuspjesna alokacija memorije!\n");
			return NULL;
		}

		S->Number = x;
		S->left = NULL;
		S->right = NULL;
	}
	else if (S->Number > x) {
		S->left = insertElement(x, S->left);
	}
	else if (S->Number < x) {
		S->right = insertElement(x, S->right);
	}

	return S;
}

int dodaj_element(Position S) {
	int to_insert = 0;
	printf("Unesite element: ");
	scanf_s(" %d", &to_insert);
	puts("");
	insertElement(to_insert, S);
	return EXIT_SUCCESS;
}

int PrintInorder(Position S) {

	if (S == NULL)
		return 0;

	PrintInorder(S->left);
	printf("%d ", S->Number);
	PrintInorder(S->right);

	return 0;
}
int PrintPostorder(Position S) {

	if (S == NULL)
		return 0;

	PrintPostorder(S->left);
	PrintPostorder(S->right);
	printf("%d ", S->Number);

	return 0;
}
int PrintPreorder(Position S) {

	if (S == NULL)
		return 0;

	printf("%d ", S->Number);
	PrintPreorder(S->left);
	PrintPreorder(S->right);

	return 0;
}
Position deletelement(int x, Position S) {

	Position temp = NULL;

	if (S == NULL) {
		printf("Element koji zelite izbrisati ne postoji unutar stabla!\n");
		return 0;
	}
	else if (S->Number > x) {

		S->left = deletelement(x, S->left);
	}

	else if (S->Number < x)
		S->right = deletelement(x, S->right);

	else if (S->left && S->right != NULL) {

		temp = Findmin(S->right);
		S->Number = temp->Number;

		S->right = deletelement(S->Number, S->right);
	}

	else {

		temp = S;

		if (S->left == NULL)
			S = S->right;

		else
			S = S->left;

		free(temp);
	}

	return S;
}
int brisi_element(Position S) {

	int broj = 0;
	printf("Unesite element koji zelite izbrisati: \n");
	scanf(" %d", &broj);
	puts("");
	if (deletelement(broj, S))
		printf("Element uspjesno izbrisan!\n");

	return 0;
}
Position Find(int x, Position S) {

	if (S == NULL) {
		printf("Element koji zelite pronaci ne postoji u stablu! Unesite element koji postoji u stablu!\n");
		return NULL;
	}

	else if (S->Number > x) {

		return Find(x, S->left);
	}

	else if (S->Number < x) {

		return Find(x, S->right);
	}

	return S;
}
int trazielement(Position S) {
	int broj = 0;
	printf("Unesite broj koji zelite pronaci u stablu: \n");
	scanf(" %d", &broj);
	puts("");
	if (Find(broj, S)) {
		printf("Broj pronaden uspjesno!\n");
	}
	return 0;
}
Position Findmin(Position S) {

	if (S == NULL) {
		return NULL;
	}
	else if (S->left == NULL)
		return S;
	else
		return Findmin(S->left);

}

Position Findmax(Position S)
{	
	if (S != NULL) {
		if (S->right != NULL) {
			S = S->right;
		}
	}
	else
		return S;
}

int Meni(Position S) {

	int k = 0;	//return val

	while (k != 9) {

		printf("Izaberite komandu:\n");
		printf("1_Unos elementa\n");
		printf("2_Inorder Ispis\n");
		printf("3_Preorder Ispis\n");
		printf("4_Postorder Ispis\n");
		printf("5_Pronadji element\n");
		printf("6_Izbrisi element\n");
		printf("9_Izlaz\n");
		scanf_s("%d", &k);

		switch (k) {

		case 1:
			dodaj_element(S);
			break;

		case 2:
			PrintInorder(S);
			puts("");
			break;

		case 3:
			PrintPreorder(S);
			puts("");
			break;

		case 4:
			PrintPostorder(S);
			puts("");
			break;

		case 5:
			trazielement(S);
			puts("");
			break;

		case 6:
			brisi_element(S);
			puts("");
			break;

		case 9:
			printf("Izlazak iz programa...\n");
			break;

		default:
			printf("Pogresan unos! Unesite broj uz zeljenu opciju ili unesite 9 za izlaz iz programa.\n");

		}

	}
	return 0;
}