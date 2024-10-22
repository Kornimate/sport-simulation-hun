#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "csapatok.h"
#include "sportagak.h"

class Menu
{
private:
	Labdarugas* lr;
	Motorsport* ms;
	Jegkorong* jk;
public:
	void run();
	Menu()
	{
		try
		{
			lr = new Labdarugas("Resource-Files/Labdarugas.txt");
			ms = new Motorsport("Resource-Files/Motorsport.txt");
			jk = new Jegkorong("Resource-Files/Jegkorong.txt");
		}
		catch (const Sportag::FajlMegnyitasiKivetel& fmk)
		{
			std::cerr << "Nem tudtam megnyitni a fajlt!" << std::endl;
			exit(1);
		}
		catch (const Sportolo::HelytelenErtekKivetel& hek)
		{
			std::cerr << "Ervenytelen adat a sportolo letrehozasa kozben!" << std::endl;
		}
	}
	~Menu()
	{
		delete lr;
		delete jk;
		delete ms;
	}
};

#endif // MENU_H_INCLUDED
