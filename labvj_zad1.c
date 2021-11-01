#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)

typedef struct _student {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
}student;

int Procitajbrojredakaizdatoteke(char* nazivDatoteke);
student* AlocirajmemorijuiprocitajStudente(int brojStudenata, char* nazivDatoteke);
int izracunajmaksimalanbrojbodova(student* studenti, int brojac);
void isprintajpodatke(student* studenti, int brojac);
int main(){
	student* studenti = NULL;
	int brojStudenata = 0;
	char* nazivDatoteke = "studenti.txt";
	brojStudenata = Procitajbrojredakaizdatoteke(nazivDatoteke);
	if (brojStudenata == -1) {
		return 1;
	}
	studenti = AlocirajmemorijuiprocitajStudente(brojStudenata, nazivDatoteke);
	if (!studenti) {
		return ("Greska pri alociranju memorije!\n");
	}
	isprintajpodatke(studenti, brojStudenata);
	return 0;
}
int Procitajbrojredakaizdatoteke(char* nazivDatoteke) {
	int brojac = 0;
	FILE* datoteka = NULL;
	char buffer[MAX_LINE] = { 0 };

	datoteka = fopen(nazivDatoteke, "r");

	if (!datoteka) {
		printf("Greska!");
		return -1;
	}
	while (!feof(datoteka)) {
		fgets(buffer, MAX_LINE, nazivDatoteke); //ova funkcija èita redak po redak//
		brojac++;
	}

	fclose(datoteka);

	return brojac;
}
student* AlocirajmemorijuiprocitajStudente(int brojStudenata, char* nazivDatoteke) {
	int brojac = 0;
	FILE* datoteka = NULL;
	student* studenti = NULL;

	studenti = (student*)malloc(brojStudenata * sizeof(student));
	datoteka = fopen(nazivDatoteke, "r");

	if (!datoteka) {
		printf("Greska pri otvaranju datoteke!\n");
		free(datoteka);
		return NULL;
	}
	if (!studenti) {
		printf("Greška pri alociranju memorije!\n");
		free(studenti);
		fclose(datoteka);
		return NULL;
	}
	while (!feof(datoteka)) {
		fscanf(nazivDatoteke, " %s\t%s\t%d", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
		brojac++;
	}
	fclose(datoteka);

	return studenti;
}
int izracunajmaksimalanbrojbodova(student* studenti, int brojac) {

	int maxbr_bodova = 0;
	int i;

	for (i = 1; i < brojac; i++) {
		if (studenti[i].bodovi > studenti[maxbr_bodova].bodovi) {
			i = maxbr_bodova;
		}
	}

	return studenti[maxbr_bodova].bodovi;
}
void isprintajpodatke(student* studenti, int brojac) {
	int i;
	int maxbr_bodova = izracunajmaksimalanbrojbodova(studenti, brojac);

	for (i = 0; i < brojac; i++) {
		printf(" %s %s %d %.3f", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi,
			(double)studenti[i].bodovi / maxbr_bodova * 100);
	}
	return;
}

