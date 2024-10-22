#include "../Headers/menu.h"
#include <vector>
#include <iostream>
#include "../Headers/read.hpp"

void Menu::run()
{
	try
	{
		bool llcs = false;
		bool lmcs = false;
		bool ljcs = false;
		int menupont = -1;
		int almenupont = -1;
		std::vector<std::string> menu{ "Kilepes","Labdarugas","Motorsport","Jegkorong" }; //hatekony kiiras a bovithetoseg szempontjabol
		std::vector<std::string> almenu{ "Vissza a fomenube","Adatbazis megjelenitese","Sajat csapat letrehozasa","Sajat Csapat torlese", "Szimulacio" };
		while (menupont != 0)
		{
			for (unsigned int i = 0; i < menu.size(); ++i)
			{
				std::cout << "(" << i << ") " << menu[i] << std::endl;
			}
			menupont = read<int>("Adja meg a menupont szamat!: ", "1-3 kozotti szamot adjon meg!", [](int szam) { return szam > -1 && szam < 4; });
			std::cout << std::endl << "[" << menu[menupont] << "]" << std::endl << std::endl;
			if (menupont == 0) break; //ha a break elhasalna, akkor sem teljesul a ciklus feltetel, nincs vegtelen ciklus
			while (almenupont != 0)
			{
				for (unsigned int i = 0; i < almenu.size(); ++i)
				{
					std::cout << "(" << i + 1 << ") " << almenu[i] << std::endl;
				}
				almenupont = read<int>("Adja meg a menupont szamat!: ", "1-3 kozotti szamot adjon meg!", [](int szam) { return szam > 0 && szam < 6; });
				try
				{
					switch (menupont) //menustruktura alapjan esetek szetvalasztasa
					{
					case 1:
						switch (almenupont)
						{
						case 2:
							lr->Adatbazisleker();
							break;
						case 3:
							if (llcs) throw Sportag::MarLetezoCsapatKivetel();
							lr->UjCsapat();
							llcs = true;
							break;
						case 4:
							if (!llcs) throw Sportag::MegNincsCsapatKivetel();
							lr->SajatCsapatTorles();
							llcs = false;
							break;
						case 5:
							lr->Szimulacio();
							break;
						}
						break;
					case 2:
						switch (almenupont)
						{
						case 2:
							ms->Adatbazisleker();
							break;
						case 3:
							if (lmcs) throw Sportag::MarLetezoCsapatKivetel();
							ms->UjCsapat();
							lmcs = true;
							break;
						case 4:
							if (!lmcs) throw Sportag::MegNincsCsapatKivetel();
							ms->SajatCsapatTorles();
							lmcs = false;
							break;
						case 5:
							ms->Szimulacio();
							break;
						}
						break;
					case 3:
						switch (almenupont)
						{
						case 2:
							jk->Adatbazisleker();
							break;
						case 3:
							if (ljcs) throw Sportag::MarLetezoCsapatKivetel();
							jk->UjCsapat();
							ljcs = true;
							break;
						case 4:
							if (!ljcs) throw Sportag::MegNincsCsapatKivetel();
							jk->SajatCsapatTorles();
							ljcs = false;
							break;
						case 5:
							jk->Szimulacio();
							break;
						}
						break;
					}
					if (almenupont == 1) break; //duplan ved a kilepesnel , break elhasalna akkor sem teljesul a feltetel
				}
				catch (const Sportag::MarLetezoCsapatKivetel& mlcsk) //kivetelek kezelese uj csapaat eseten
				{
					std::cerr << "Mar letezik sajat csapatod, hasznald azt!" << std::endl;
				}
				catch (const Sportag::MegNincsCsapatKivetel& mncsk)
				{
					std::cerr << "Elobb hozzon letre csapatot, hogy torolhesse!" << std::endl;
				}
			}
		}
	}
	catch (...)
	{
		std::cerr << "A program futasa soran olyan hibat eszlelet ami miatt nem tud tovabb futni!" << std::endl;
		exit(2); //olyan hiba aminel a program befejezi mukodeset
	}
}
