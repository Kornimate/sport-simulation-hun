#ifndef ESEMENY_H_INCLUDED
#define ESEMENY_H_INCLUDED

#include <iostream>
#include <sstream>
#include "csapatok.h"

class Meccs
{
private:
	Csapat* cs1;
	Csapat* cs2;
public:
	Meccs() {}
	Csapat* HazaiCsapat() { return cs1; } //getterek amennyiben szukseg van rajuk
	Csapat* IdegenCsapat() { return cs2; }
	void MeccsCsapatok(Csapat* cs1s, Csapat* cs2s) { cs1 = cs1s; cs2 = cs2s; } //generalo fuggveny, 1 Meccset hasznalunk vegig, igy nem a konstrukot allitja be ezeket
	void Szimulal(int, int); //eredmeny meghatarozasa a vegeredmeny ismereteben
};

class Futam
{
public:
	Futam() {}
	void Szimulal(std::vector<Sportolo*>& versenyzok); //szimulalja a versenyt 1 futamat random szamot hasznalo matematikaval
	//kiirja a futam eredmenyet es valtoztat is az erossegeken az egyenletesseg miatt, meg javithato pontosabb adatok ismereteben
};
#endif // ESEMENY_H_INCLUDED
