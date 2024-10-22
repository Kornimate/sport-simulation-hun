#include "Headers/menu.h"

using namespace std;

int main(int argc, char* argv[])
{
	Menu* menu = new Menu();
	menu->run(); //legyen meg jobban oop a kod
	delete menu; //ez hivja a tobbi destruktorat
	return 0;
}
