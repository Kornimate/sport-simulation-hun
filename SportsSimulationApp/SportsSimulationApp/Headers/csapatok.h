#ifndef CSAPATOK_H_INCLUDED
#define CSAPATOK_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "sportolok.h"
#include "eredmeny.h"

class Sportolo;
class Focista;
class Jegkorongozo;
class Pilota;

class Csapat
{
public:
	class ErvenytelenAdat : public std::exception {}; //kozos kivetel
	Csapat(std::string, int, std::ifstream&);
	int Erosseg() { return erosseg; }
	void ErossegNovel(int); //szimulacional a kiegyenliteshez hasznalt fuggveny
	std::vector<Sportolo*> GetTagok() { return tagok; }
	std::string GetNev() { return nev; }
	void TagHozzaad(Sportolo*); //ujcsapatnal a hozzadashoz kell
	void ErossegMeghataroz(); //inicializacional es ujcsapatnal a szimulacio elofeltetele ennek az ismerete
	void EredmenyHozzaad(Eredmeny* e) { eredmenyek.push_back(e); } //szimulaciohoz a statisztikai adatokhoz kell
	std::vector<Eredmeny*> GetEredmenyek() const { return eredmenyek; }
	virtual ~Csapat()
	{
		for (auto i : tagok) { delete i; }
		for (auto i : eredmenyek) { delete i; }
	}
	void PontszamNovel(int szam) { pontszam += szam; } //motorsportnal kell
	int GetPontszam()const { return pontszam; }
	void Visszaallit() { eredmenyek.clear(); pontszam = 0; } //szimulacio utan a tobbszorhasznalhatosag miatt
protected:
	int erosseg;
	int pontszam;
	std::string nev;
	int letszam;
	std::vector<Sportolo*> tagok;
	std::vector<Eredmeny*> eredmenyek;
	Csapat() {}
};

class Lcsapat : public Csapat //feladata specifikus szarmaztatott osztalyok
{
public:
	Lcsapat(std::string, int, std::ifstream&);
	Lcsapat(std::string, int);
};

class Mcsapat : public Csapat
{
public:
	Mcsapat(std::string, int, std::ifstream&);
	Mcsapat(std::string, int);
};

class Jcsapat : public Csapat
{
public:
	Jcsapat(std::string, int, std::ifstream&);
	Jcsapat(std::string, int);
};

#endif // CSAPATOK_H_INCLUDED
