#ifndef EREDMENY_H_INCLUDED
#define EREDMENY_H_INCLUDED

#include <iostream>

class Eredmeny
{
private:
	int pont;
public:
	enum eredmeny { VESZTES = 0, DONTETLEN = 1, GYOZTES = 3 }; //statisztika miatt kell, illetve tovabbi bovites miatt erdemes bevezetni(pl meccs tobbi adatainak tarolasahoz)
	Eredmeny(int pontmennyiseg) : pont(pontmennyiseg) {}
	int Pontszam() const { return pont; }
};


#endif // EREDMENY_H_INCLUDED
