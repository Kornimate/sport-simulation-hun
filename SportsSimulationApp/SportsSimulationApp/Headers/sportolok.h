#ifndef SPORTOLOK_H_INCLUDED
#define SPORTOLOK_H_INCLUDED

#include <iostream>
#include "csapatok.h"
#include "sportolok.h"

class Csapat;

class Sportolo
{
protected:
	std::string nev;
	int eletkor;
	int ertek;
	Csapat* csapat;
	int pontok; //ez csak a pilota hasznalja( de ha az o adattagja csak akkor nem inicializalodik jol)
public:
	class HelytelenErtekKivetel : public std::exception {};
	std::string GetNev()const { return nev; } //getterek
	int GetEletkor() const { return eletkor; }
	int GetErtek() { return ertek; }
	Sportolo(std::string, int, Csapat*, int);
	void ErtekNovel(int szam) { ertek += szam; }
	Csapat* GetCsapat() const { return csapat; }
};

class Focista : public Sportolo
{
public:
	Focista(std::string, int, Csapat*, int);
};

class Pilota : public Sportolo
{
public:
	Pilota(std::string, int, Csapat*, int); //fuggvenyek a szimulaciohoz
	void PontszamNullaz() { pontok = 0; } //csak a pilotanal, de olyan adattagot nullaz ami ososztalybeli, de csak o hasznalja
	int GetPontszam() const { return pontok; } //olyan adattag amit csak o hasznal
	void PontszamNovel(int szam) { pontok += szam; } //olyan adattag amit csak o hasznal
};

class Jegkorongozo : public Sportolo
{
public:
	Jegkorongozo(std::string, int, Csapat*, int);
};
#endif // SPORTOLOK_H_INCLUDED
