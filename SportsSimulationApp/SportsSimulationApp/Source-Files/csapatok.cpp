#include "../Headers/csapatok.h"
#include "../Headers/sportolok.h"

Csapat::Csapat(std::string neve, int letszama, std::ifstream& fin)
{
	int sum1 = 0, sum2 = 0;
	nev = neve;
	letszam = letszama;
	std::string jatnev;
	int eletkor;
	int ertek;
	std::string sor;
	for (int i = 0; i < letszam; ++i)
	{
		getline(fin, sor); //beolvasas meghatarozott sema szerint, kell a vesszo mert egy csapat neve es egy jatekos neve lehet barmilyen hosszu, igy ezt valasztom elvalaszto karakternek
		std::stringstream ss(sor); //felbontast segiti
		getline(ss, jatnev, ',');
		getline(ss, sor, ','); //beolvasas a karakterig vagy feherszokozig
		eletkor = atoi(sor.c_str()); //konvertalas egesz szamma 
		getline(ss, sor);
		ertek = atoi(sor.c_str());
		tagok.push_back(new Sportolo(jatnev, eletkor, this, ertek)); //uj tagok letrezhozasa most altalanos, castolassal specialisabb lesz
		sum1 += eletkor;
		sum2 += ertek;
	}
	erosseg = sum2 * ((((double)sum1) / letszam) / 100); // ezzel az osszefuggessel hatarozom meg a 
};
Lcsapat::Lcsapat(std::string neve, int letszama, std::ifstream& fin) : Csapat(neve, letszama, fin) {}
Mcsapat::Mcsapat(std::string neve, int letszama, std::ifstream& fin) : Csapat(neve, letszama, fin) {}
Jcsapat::Jcsapat(std::string neve, int letszama, std::ifstream& fin) : Csapat(neve, letszama, fin) {}
Lcsapat::Lcsapat(std::string csnev, int tagokszama) : Csapat()
{
	nev = csnev;
	letszam = tagokszama;
}
Mcsapat::Mcsapat(std::string csnev, int tagokszama) : Csapat()
{
	nev = csnev;
	letszam = tagokszama;
}
Jcsapat::Jcsapat(std::string csnev, int tagokszama) : Csapat()
{
	nev = csnev;
	letszam = tagokszama;
}
void Csapat::TagHozzaad(Sportolo* ujtag) //altalanos forma
{
	if (ujtag == nullptr) throw ErvenytelenAdat();
	tagok.push_back(ujtag);
}
void Csapat::ErossegNovel(int szam) //szimulaciohoz kell
{
	erosseg += szam;
}
void Csapat::ErossegMeghataroz() //szimulaciohoz kell
{
	int sum1 = 0;
	int sum2 = 0;
	for (auto i : tagok)
	{
		sum2 += i->GetErtek();
		sum1 += i->GetEletkor();
	}
	erosseg = sum2 * ((((double)sum1) / letszam) / 100);
}
