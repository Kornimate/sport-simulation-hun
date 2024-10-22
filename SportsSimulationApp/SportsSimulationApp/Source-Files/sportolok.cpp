#include "../Headers/sportolok.h"

//kifejtett fuggvenyek amik tul hosszuak a fejlecbeli kifejteshez

Sportolo::Sportolo(std::string neve, int evei, Csapat* csapata, int erteke)
{
	if (csapata == nullptr) throw HelytelenErtekKivetel();
	nev = neve;
	eletkor = evei;
	csapat = csapata;
	ertek = erteke;
}
Focista::Focista(std::string neve, int evei, Csapat* csapata, int erteke) : Sportolo(neve, evei, csapata, erteke) {}
Pilota::Pilota(std::string neve, int evei, Csapat* csapata, int erteke) : Sportolo(neve, evei, csapata, erteke) { pontok = 0; }
Jegkorongozo::Jegkorongozo(std::string neve, int evei, Csapat* csapata, int erteke) : Sportolo(neve, evei, csapata, erteke) {}
