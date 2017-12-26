#include "MeniZaAnaliticara.h"
#include <string>
#include <iostream>

void meniZaAnaliticara(){
	int opcija = 1;
	char buffer[100];
	std::string kupac;

while (opcija)
{
	std::cout << std::endl << std::endl;
	std::cout << "Filtriraj racune po kupcu		- 1 -" << std::endl;
	std::cout << "Izlaz                         - 0 -" << std::endl;
	std::cout << "Opcija:  ";
	std::cin >> opcija;
	std::cout << std::endl << std::endl;
	switch (opcija)
	{
	case 1:
		std::cout << std::endl << "Unesi naziv kupca po kom hocete da filtrirate: ";
		std::cin.getline(kupac);
		std::cout << std::endl;
		filtrirajPoKupcu(kupac);
		break;

	case 0:
		return;
	default:
		std::cout << "Pogresna opcija! Probajte ponovo!" << std::endl;
		break;

	}


}

}