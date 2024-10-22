#include "../Headers/esemeny.h"
#include <time.h>
#include <stdlib.h>
#include "../Headers/eredmeny.h"
#include <iostream>
#include <algorithm>
#include <iostream>

void Meccs::Szimulal(int mini, int maxi)
{

	if (cs1->Erosseg() > cs2->Erosseg()) //erosseg alapjan lesz a gyoztes
	{
		cs1->ErossegNovel(-maxi - 5); //kiegyenlites valtozatos eredmenyek erdekeben
		cs2->ErossegNovel(mini + 7);
		cs1->EredmenyHozzaad(new Eredmeny(Eredmeny::eredmeny::GYOZTES)); //eredmenyek bevezetese a statisztikahoz
		cs2->EredmenyHozzaad(new Eredmeny(Eredmeny::eredmeny::VESZTES));
		cs1->PontszamNovel(3);
		//cs2->PontszamNovel(0);
		std::cout << cs1->GetNev() << " - " << cs2->GetNev() << " : " << maxi << " - " << mini << std::endl;
	}
	else if (cs1->Erosseg() == cs2->Erosseg())
	{
		mini = maxi; //azonos erosseg eseten nem kell ket kulon szam eleg az egyik
		cs1->ErossegNovel(1); //dontetlennel nincs radikalis valtoztatas
		cs2->ErossegNovel(1);
		cs1->EredmenyHozzaad(new Eredmeny(Eredmeny::eredmeny::DONTETLEN));
		cs2->EredmenyHozzaad(new Eredmeny(Eredmeny::eredmeny::DONTETLEN));
		cs1->PontszamNovel(1);
		cs2->PontszamNovel(1);
		std::cout << cs1->GetNev() << " - " << cs2->GetNev() << " : " << maxi << " - " << mini << std::endl;
	}
	else
	{
		cs1->ErossegNovel(mini + 7); //kiegyenlites valtozatos eredmenyek erdekeben
		cs2->ErossegNovel(-maxi - 5);
		cs1->EredmenyHozzaad(new Eredmeny(Eredmeny::eredmeny::VESZTES));
		cs2->EredmenyHozzaad(new Eredmeny(Eredmeny::eredmeny::GYOZTES));
		//cs1->PontszamNovel(0);
		cs2->PontszamNovel(3);
		std::cout << cs1->GetNev() << " - " << cs2->GetNev() << " : " << mini << " - " << maxi << std::endl;
	}
}
void Futam::Szimulal(std::vector<Sportolo*>& versenyzok)
{
	sort(versenyzok.begin(), versenyzok.end(), [](Sportolo* s1, Sportolo* s2) { return ((Pilota*)s1)->GetErtek() > ((Pilota*)s2)->GetErtek(); }); //erosseg szerint sorbarendezes
	for (unsigned int i = 0; i < versenyzok.size(); ++i) //kiiratas
	{
		std::cout << i + 1 << ". " << versenyzok[i]->GetNev() << " " << std::endl;
	}
	((Pilota*)versenyzok[0])->PontszamNovel(25); //Szimulacio menete valos eletbeli adatok alapjan
	versenyzok[0]->GetCsapat()->PontszamNovel(25);
	((Pilota*)versenyzok[1])->PontszamNovel(18);
	versenyzok[1]->GetCsapat()->PontszamNovel(18);
	((Pilota*)versenyzok[2])->PontszamNovel(15);
	versenyzok[2]->GetCsapat()->PontszamNovel(15);
	((Pilota*)versenyzok[3])->PontszamNovel(12);
	versenyzok[3]->GetCsapat()->PontszamNovel(12);
	((Pilota*)versenyzok[4])->PontszamNovel(10);
	versenyzok[4]->GetCsapat()->PontszamNovel(10);
	((Pilota*)versenyzok[5])->PontszamNovel(8);
	versenyzok[5]->GetCsapat()->PontszamNovel(8);
	((Pilota*)versenyzok[6])->PontszamNovel(6);
	versenyzok[6]->GetCsapat()->PontszamNovel(6);
	((Pilota*)versenyzok[7])->PontszamNovel(4);
	versenyzok[7]->GetCsapat()->PontszamNovel(4);
	((Pilota*)versenyzok[8])->PontszamNovel(2);
	versenyzok[8]->GetCsapat()->PontszamNovel(2);
	((Pilota*)versenyzok[9])->PontszamNovel(1);
	versenyzok[9]->GetCsapat()->PontszamNovel(1);
	std::cout << ((Pilota*)versenyzok[0])->GetPontszam() << std::endl;
	for (unsigned int i = 0; i < versenyzok.size() / 2; ++i) //versnenyzok erossegenek kiegyenlitese erdekesebb szimulacioert
	{
		srand(time(NULL));
		int a = rand() % 7 - 5;
		((Pilota*)versenyzok[i])->ErtekNovel(a);
	}
	for (unsigned int i = versenyzok.size() / 2; i < versenyzok.size(); ++i) // 10-tol rosszab eredmenynel no az erosseg alatta nohet is es csokkenhet is de nagyon esellyel
	{
		srand(time(NULL));
		int a = rand() % 6 - 2;
		((Pilota*)versenyzok[i])->ErtekNovel(a);
	}
}
