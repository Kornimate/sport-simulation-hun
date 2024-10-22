#include "../Headers/sportagak.h"
#include "../Headers/csapatok.h"
#include <iostream>
#include <vector>
#include "../Headers/read.hpp"
#include "../Headers/eredmeny.h"
#include <conio.h>
#include <algorithm>
#include "../Headers/esemeny.h"
#include <time.h>
#include <stdlib.h>
#include <cmath>
#include <random> //jobb random fuggveny mint a srand() es rand()

class Csapat;

Sportag::Sportag(const std::string& forras)
{
	int csapatokszama;
	std::string csnev, csadat;
	int csletszam;
	std::ifstream fin(forras);
	if (fin.fail()) throw FajlMegnyitasiKivetel(); //ne hasaljon el ha nincs ilyen fajl
	getline(fin, csadat);
	csapatokszama = atoi(csadat.c_str());
	for (int i = 0; i < csapatokszama; ++i)
	{
		getline(fin, csnev, ','); //beolvasas tobb fazisban tortenik ez az elso
		getline(fin, csadat);
		csletszam = atoi(csadat.c_str());
		csapatok.push_back(new Csapat(csnev, csletszam, fin));
	}
	fin.close();
}
Labdarugas::Labdarugas(const std::string& forras) : Sportag(forras) {}
Motorsport::Motorsport(const std::string& forras) : Sportag(forras) {}
Jegkorong::Jegkorong(const std::string& forras) : Sportag(forras) {}

void Sportag::Adatbazisleker() //beolvasott adatok kiirasa
{
	std::cout << "--------------------" << std::endl;
	for (auto i : csapatok)
	{
		std::cout << "[" << i->GetNev() << "]" << std::endl;
		for (Sportolo* s : i->GetTagok())
		{
			std::cout << s->GetNev() << " " << s->GetEletkor() << std::endl;
		}
		std::cout << "--------------------" << std::endl;
	}
}
void Labdarugas::UjCsapat()
{
	bool jo = false;
	std::string csapatnev;
	std::string jatnev;
	int ekor;
	int ertek;
	while (!jo)
	{
		std::cout << "Adja meg az uj csapat nevet!: ";
		getline(std::cin >> std::ws, csapatnev);
		jo = true;
		for (auto i : csapatok)
		{
			if (i->GetNev() == csapatnev) jo = false; //csak valid nev eseten lepjen tovabb, valid ha meg nem letezik
		}
		if (!jo)
		{
			std::cerr << "A csapat neve mar letezik" << std::endl;
		}
	}
	Lcsapat* nlcs = new Lcsapat(csapatnev, 12);
	std::cout << "A csapatnak 12 jatekosa van!" << std::endl;
	for (int i = 0; i < 12; ++i) //csapat jatekosainak inicializalasa
	{
		std::cout << "Adja meg a(z) " << i + 1 << ". jatekos adatait!: \nNev: ";
		getline(std::cin >> std::ws, jatnev);
		ekor = read<int>("Eletkor: ", "16-40 kozotti szamot adjon meg!", [](int szam) { return szam > 15 && szam < 41; });
		ertek = read<int>("Ertek: ", "50-99 kozotti szamot adjon meg!", [](int szam) { return szam > 49 && szam < 100; });
		try
		{
			nlcs->TagHozzaad(new Focista(jatnev, ekor, nlcs, ertek));
		}
		catch (const Csapat::ErvenytelenAdat& ea) //ervenytelen adat eseten nem jon letre jatekos
		{
			std::cerr << "Ervenytelen uj tag hozzadasa!" << std::endl;
		}
	}
	nlcs->ErossegMeghataroz(); // inicializacional a szimulaciohoz kell a csapat erossege ami a jatekosos adataibol szamolando, van ra keplet
	csapatok.insert(csapatok.begin() + 9, nlcs);

}
void Motorsport::UjCsapat()
{
	bool jo = false;
	std::string csapatnev;
	std::string jatnev;
	int ekor;
	int ertek;
	while (!jo)
	{
		std::cout << "Adja meg az uj csapat nevet!: ";
		getline(std::cin >> std::ws, csapatnev);
		jo = true;
		for (auto i : csapatok)
		{
			if (i->GetNev() == csapatnev) jo = false; //addig olvas be amig nem valid a nev
		}
		if (!jo)
		{
			std::cerr << "A csapat neve mar letezik" << std::endl;
		}
	}
	Mcsapat* nmcs = new Mcsapat(csapatnev, 2);
	std::cout << "A csapatnak 2 pilotaja van!" << std::endl;
	for (int i = 0; i < 2; ++i)
	{
		std::cout << "Adja meg a(z) " << i + 1 << ". pilota adatait!: \nNev: ";
		getline(std::cin >> std::ws, jatnev);
		ekor = read<int>("Eletkor: ", "16-40 kozotti szamot adjon meg!", [](int szam) { return szam > 15 && szam < 41; });
		ertek = read<int>("Ertek: ", "50-99 kozotti szamot adjon meg!", [](int szam) { return szam > 49 && szam < 100; });
		try
		{
			nmcs->TagHozzaad(new Pilota(jatnev, ekor, nmcs, ertek));
		}
		catch (const Csapat::ErvenytelenAdat& ea) //ervenytelen adat eseten nem jon letre jatekos
		{
			std::cerr << "Ervenytelen uj tag hozzadasa!" << std::endl;
		}
	}
	nmcs->ErossegMeghataroz();
	csapatok.insert(csapatok.begin() + 9, nmcs);
}
void Jegkorong::UjCsapat()
{
	bool jo = false;
	std::string csapatnev;
	std::string jatnev;
	int ekor;
	int ertek;
	while (!jo)
	{
		std::cout << "Adja meg az uj csapat nevet!: ";
		getline(std::cin >> std::ws, csapatnev);
		jo = true;
		for (auto i : csapatok)
		{
			if (i->GetNev() == csapatnev) jo = false; //addig olvas be amig nem valid a nev
		}
		if (!jo)
		{
			std::cerr << "A csapat neve mar letezik" << std::endl;
		}
	}
	Jcsapat* njcs = new Jcsapat(csapatnev, 2);
	std::cout << "A csapatnak 8 jatekosa van!" << std::endl;
	for (int i = 0; i < 8; ++i)
	{
		std::cout << "Adja meg a(z) " << i + 1 << ". jatekos adatait!: \nNev: ";
		getline(std::cin >> std::ws, jatnev);
		ekor = read<int>("Eletkor: ", "16-40 kozotti szamot adjon meg!", [](int szam) { return szam > 15 && szam < 41; });
		ertek = read<int>("Ertek: ", "50-99 kozotti szamot adjon meg!", [](int szam) { return szam > 49 && szam < 100; });
		try
		{
			njcs->TagHozzaad(new Jegkorongozo(jatnev, ekor, njcs, ertek));
		}
		catch (const Csapat::ErvenytelenAdat& ea) //ervenytelen adat eseten nem jon letre jatekos
		{
			std::cerr << "Ervenytelen uj tag hozzadasa!" << std::endl;
		}
	}
	njcs->ErossegMeghataroz();
	csapatok.insert(csapatok.begin() + 9, njcs);
}

void Sportag::SajatCsapatTorles()
{
	delete csapatok[9]; //invarians tulajdonsag hogy csak paros szamu csapat legyen a ket csapatsportban ezertaz uj csapat az utolso loki ki a 10-bol
	csapatok.erase(csapatok.begin() + 9);
}
void Labdarugas::Szimulacio() //szimulacio fordulonkent majd a vegen tabellakiiras 
{
	Meccs m;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> dis1(0, 3);
	std::cout << "Szimulacio kezdodik!" << std::endl;
	int fordszam = 1;
	for (int i = 1; i <= 2; ++i) //2szer jatszanak egymassal a csapatok
	{
		for (int j = 0; j < 9; ++j) //10 csapat jatszik
		{
			std::cout << std::endl << ">>>>>>>>>>>>" << fordszam << ". fordulo:" << "<<<<<<<<<<" << std::endl;
			for (int k = 0; k < 5; ++k) //5 meccs / fordulo
			{
				int a = dis1(generator);
				int b = a + dis1(generator);
				m.MeccsCsapatok(csapatok[k], csapatok[9 - k]); //csapatok beallitasa
				m.Szimulal(a, b); //eredmeny szimulalasa 1 meccsre
			}
			Csapat* seged = csapatok[9];
			for (int s = 9; s > 1; --s) //rotacioert felelos fuggveny: a forduloban utan a parositasok
			{
				csapatok[s] = csapatok[s - 1];
			}
			csapatok[1] = seged;
			++fordszam;
			std::cout << "A Szimulacio folytatasahoz nyomjon meg egy billentyut!...";
			_getch();
			std::endl(std::cout);
		}
	}
	TabellaKiir(); //tabella konzolra irasa
	for (auto i : csapatok)
	{
		i->Visszaallit(); //pontok nullazasa
		i->ErossegMeghataroz(); //eredeti erossegek visszaallitasa
	}
}
void Motorsport::Szimulacio()
{
	versenyzok.clear();
	Futam f;
	for (auto i : csapatok)
	{
		for (auto s : i->GetTagok())
		{
			versenyzok.push_back(s); //versenyzok egyeniben es csapatban is versenyeznek: kulon kellenek a szimulaciohoz
		}
	}
	std::cout << "Szimulacio kezdodik!" << std::endl;
	for (int i = 1; i <= 22; ++i) //22 futam egy szezonban
	{
		std::cout << std::endl << "---------" << i << ". fordulo:--------" << std::endl;
		f.Szimulal(versenyzok);
		std::cout << "A Szimulacio folytatasahoz nyomjon meg egy billentyut!...";
		_getch();
		std::endl(std::cout);
	}
	TabellaKiir();
	for (auto i : versenyzok)
	{
		((Pilota*)i)->PontszamNullaz(); //visszaallitja a pontokat, de erosseget nem : minden szimulacio jellemfejlodes
	}
	for (auto i : csapatok)
	{
		i->Visszaallit(); //csapatok pontszamanak nullazasa
	}
}
void Jegkorong::Szimulacio()
{
	Meccs m;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> dis1(0, 3);
	std::cout << "Szimulacio kezdodik!" << std::endl;
	int fordszam = 1;
	for (int i = 1; i <= 2; ++i) //minden csapat 2-szer jatszik egymassal
	{
		for (int j = 0; j < 9; ++j) //10 csapat jatszik
		{
			std::cout << std::endl << ">>>>>>>>>>>>" << fordszam << ". fordulo:" << "<<<<<<<<<<" << std::endl;
			for (int k = 0; k < 5; ++k) // 5 meccs / fordulo
			{
				int a = dis1(generator);
				int b = a + dis1(generator);
				m.MeccsCsapatok(csapatok[k], csapatok[9 - k]); //meccsezo csapatok beallitasa
				m.Szimulal(a, b); //eredmeny szimulalasa egy meccsre
			}
			Csapat* seged = csapatok[9];
			for (int s = 9; s > 1; --s)//rotacioert felelos fuggveny: a forduloban utan a parositasok
			{
				csapatok[s] = csapatok[s - 1];
			}
			csapatok[1] = seged;
			++fordszam;
			std::cout << "A Szimulacio folytatasahoz nyomjon meg egy billentyut!...";
			_getch();
			std::endl(std::cout);
		}
	}
	TabellaKiir();
	for (auto i : csapatok)
	{
		i->Visszaallit();
		i->ErossegMeghataroz();
	}
}
void Sportag::TabellaKiir() //a csak csapatoknal azonos a kiiras
{
	int gy;
	int v; //ket valtozobol mar meghatarpzhato a 3. adat a meccsek szamanak ismeretevel
	int szamolo = 1;
	std::cout << ">>>>>>>>>>>>>>[Tabella]<<<<<<<<<<<<" << std::endl;
	std::cout << "Csapatnev - Lejatszott meccsek - Gyoztes meccsek - Dontetlenek - Vesztes meccsek - Pontszam" << std::endl;
	sort(csapatok.begin(), csapatok.end(), [](Csapat* cs1, Csapat* cs2) { return cs1->GetPontszam() > cs2->GetPontszam(); });
	for (auto i : csapatok) //minden csapatnal kiirja a helyezest, nevet, meccsek szamat, gyozelmeket, dontetleneket, vereseget 
	{
		gy = 0;
		v = 0;
		std::cout << szamolo << ". " << i->GetNev() << " " << i->GetEredmenyek().size() << " - ";
		for (auto s : i->GetEredmenyek())
		{
			if (s->Pontszam() == Eredmeny::eredmeny::GYOZTES)
			{
				++gy;
			}
			else if (s->Pontszam() == Eredmeny::eredmeny::VESZTES)
			{
				++v;
			}
		}
		std::cout << gy << " - " << (((int)csapatok.size()) - 1) * 2 - gy - v << " - " << v << " (" << i->GetPontszam() << ")" << std::endl;
		++szamolo;
	}
	std::cout << "-----------------------------------" << std::endl << std::endl;
}
void Motorsport::TabellaKiir() //Motorsportnal mas a kiiras mert egyenit is avatnak
{
	std::cout << "-------------[Tabella Konstruktori]-------------" << std::endl;
	std::cout << ">>>>>>>>>>>>>Csapatnev - Pontszam<<<<<<<<<<<<<<<" << std::endl;
	sort(csapatok.begin(), csapatok.end(), [](Csapat* cs1, Csapat* cs2) { return cs1->GetPontszam() > cs2->GetPontszam(); });
	for (auto i : csapatok) // kiirja a helyezest, nevet, pontszamot
	{
		std::cout << i->GetNev() << " - " << i->GetPontszam() << std::endl;
	}
	std::endl(std::cout);
	std::cout << "-------------[Tabella Egyeni]-------------" << std::endl;
	std::cout << ">>>>>>>>>>>>>Nev - Pontszam<<<<<<<<<<<<<<<" << std::endl;
	sort(versenyzok.begin(), versenyzok.end(), [](Sportolo* s1, Sportolo* s2) { return ((Pilota*)s1)->GetPontszam() > ((Pilota*)s2)->GetPontszam(); });
	for (auto i : versenyzok)// kiirja a helyezest, nevet, pontszamot
	{
		std::cout << i->GetNev() << " - " << ((Pilota*)i)->GetPontszam() << std::endl;
	}
	std::cout << "------------------------------------------" << std::endl << std::endl;
}
