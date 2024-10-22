#ifndef SPORTAGAK_H_INCLUDED
#define SPORTAGAK_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "csapatok.h"

class Csapat;

class Sportag
{
protected:
	Sportag(const std::string&);
	std::vector<Csapat*> csapatok;
public:
	class FajlMegnyitasiKivetel : public std::exception {}; //kivetelosztalyok a kulonbozo felmerulheto problemakhoz
	class MarLetezoCsapatKivetel : public std::exception {};
	class MegNincsCsapatKivetel : public std::exception {};
	void Adatbazisleker(); //univerzalis, minden sportag eseten ugyanugy nez ki, minden bekert adat kiirasa
	virtual void UjCsapat() = 0; //
	virtual void Szimulacio() = 0; //absztraktta teszi az osztaly, nem lehet peldanyositani belole (nem is kell)
	void SajatCsapatTorles();
	virtual ~Sportag()
	{
		for (auto i : csapatok) delete i;
	}
	virtual void TabellaKiir();
};

class Labdarugas : public Sportag //feladat specifikus alosztalyok
{
public:
	Labdarugas(const std::string&);
	void Szimulacio() override; //felulirt fuggveny, minden alosztalyban mashogy viselkedik
	void UjCsapat() override; //felulirt fuggveny, minden alosztalyban mashogy viselkedik
};
class Motorsport : public Sportag
{
private:
	std::vector <Sportolo*> versenyzok;
public:
	Motorsport(const std::string&);
	void Szimulacio() override; //felulirt fuggveny, minden alosztalyban mashogy viselkedik
	void UjCsapat() override; //felulirt fuggveny, minden alosztalyban mashogy viselkedik
	void TabellaKiir() override; //felulirt fuggveny, ebben az alosztalyban mashogy viselkedik
	std::vector <Sportolo*> GetVersenyzok() { return versenyzok; }
};
class Jegkorong : public Sportag
{
public:
	Jegkorong(const std::string&);
	void Szimulacio() override; //felulirt fuggveny, minden alosztalyban mashogy viselkedik
	void UjCsapat() override; //felulirt fuggveny, minden alosztalyban mashogy viselkedik
};

#endif // SPORTAGAK_H_INCLUDED
