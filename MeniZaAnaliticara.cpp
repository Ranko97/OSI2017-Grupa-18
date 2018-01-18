#include "MeniZaAnaliticara.h"
#include "UcitavanjeRacuna.h"
#include <string>
#include <iostream>

void meniZaAnaliticara(){
	ucitavanje_racuna();
	int opcija = 1;
	char buffer[100];
	std::string kupac;

while (opcija)
{
	std::cout << std::endl << std::endl;
	std::cout << "Filtriraj racune po kupcu		- 1 -" << std::endl;
	std::cout << "Filtriraj racune po mjesecu		- 2 -" << std::endl;
	std::cout << "Sortiranje artikala po prometu		- 3 -" << std::endl;
	std::cout << "Izlaz					- 0 -" << std::endl;
	std::cout << "Opcija:  ";

	do {
		opcija = 6; // Da bi provjera ispravno radila
		std::cin >> opcija;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
		}

	} while (opcija < 0 || opcija>5 || std::cin.fail()); //Provjera da li je unos dobar

	std::cout << std::endl << std::endl;
	switch (opcija)
	{
	case 1:
		std::cout << std::endl << "Unesi naziv kupca po kom hocete da filtrirate: ";
		std::cin >> kupac;
		std::cout << std::endl;
		filtrirajPoKupcu(kupac);
		break;

	case 2:
		int godina, mjesec;
		do {
			std::cout << std::endl << "Unesi godinu: ";
			std::cin >> godina;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore();
			}
		} while (godina < 1900 || godina>3000 || std::cin.fail());

		do {
			std::cout << std::endl << "Unesi mjesec: ";
			std::cin >> mjesec;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore();
			}
		} while (mjesec < 1 || mjesec>12 || std::cin.fail());


		filtrirajPoMjesecu(godina, mjesec);
		break;

	case 3:
		sortirajPoPrometu();
		break;

	case 0:
		return;
	default:
		std::cout << "Pogresna opcija! Probajte ponovo!" << std::endl;
		break;

	}


}


}