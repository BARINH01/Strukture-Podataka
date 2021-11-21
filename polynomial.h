#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#define MAX_LINE (1024)
#define MAX_SIZE (50)
struct _polinom;
typedef struct _polinom* Position;
typedef struct _polinom {
	int koeficijent;
	int eksponent;
	Position next;
} polinom;
int ProcitajNazivDatoteke(char* fileName);
int ProcitajDatoteku(Position head1, Position head2, char* fileName);
int PrebaciNizulistu(Position head, char* buffer);
Position Stvorielement(int koeficijent, int eksponent);
int Unesisortirano(Position head, Position newElement);
int PrebaciIza(Position position, Position newElement);
int Umetninakon(Position position, Position newElement);
int Izbrisinakon(Position previous);
int ispisiPolinom(Position head);
int ispisielement(Position p);
Position suma(Position head1, Position head2);
int oslobodiMemoriju(Position head);
int Pomnozipolinome(Position resultHead, Position head1, Position head2);






#endif // !POLYNOMIAL_H