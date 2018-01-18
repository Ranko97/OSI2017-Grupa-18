#include "MeniZaAnaliticara.h"
#include "UcitavanjeRacuna.h"
#include <string>
#include <iostream>

void meniZaAnaliticara(){
	ucitavanje_racuna();
	int opcija = 1;
	char buffer[100];
	std::string kupac;
	std::string naziv;
while (opcija)
{
	std::cout << std::endl << "	==== Meni za analiticara ====" << std::endl << std::endl;
	std::cout << "Filtriraj racune po kupcu		- 1 -" << std::endl;
	std::cout << "Filtriraj racune po mjesecu		- 2 -" << std::endl;
	std::cout << "Filtriraj racune po artiklu	        - 3 -" << std::endl;
	std::cout << "Sortiranje artikala po prometu		- 4 -" << std::endl;
	std::cout << "Sortiranje klijenata po prometu	        - 5 -" << std::endl;
	std::cout << "Ispis ukupnog poslovanja preduzeca	- 6 -" << std::endl;
	std::cout << "Ispis racuna sa greskom	                - 7 -" << std::endl;
	std::cout << "Nazad na meni prijave			- 0 -" << std::endl;
	std::cout << "Opcija:  ";

	do {
		opcija = 9; // Da bi provjera ispravno radila
		std::cin >> opcija;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
		}

	} while (opcija < 0 || opcija>8 || std::cin.fail()); //Provjera da li je unos dobar

	std::cout << std::endl << std::endl;
	switch (opcija)
	{
	case 1:
		std::cout << std::endl << "Unesite naziv kupca po kom hocete da filtrirate: ";
		std::cin >> kupac;
		std::cout << std::endl;
		filtrirajPoKupcu(kupac);
		break;

	case 2:
		int godina, mjesec;
		do {
			std::cout << std::endl << "Unesite godinu: ";
			std::cin >> godina;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore();
			}
		} while (godina < 1900 || godina>3000 || std::cin.fail());

		do {
			std::cout << std::endl << "Unesite mjesec: ";
			std::cin >> mjesec;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore();
			}
		} while (mjesec < 1 || mjesec>12 || std::cin.fail());


		filtrirajPoMjesecu(godina, mjesec);
		break;

	case 4: 
		sortirajPoPrometu();
		break;
	case 6:
		ispisUkupnogPoslovanja();
		break;
	case 5:
		sortirajKlijente();
		break;
	case 7:
		ispisRacunaGreska();
		break;
	case 3:
		
		std::cout << std::endl << "Unesite naziv artikla po kom hocete da filtrirate: "<<std::endl;
		std::getline(std::cin, naziv);
		std::getline(std::cin, naziv);

		
		filtrirajpoArtiklu(naziv);
		break;

	case 0:
		return;
	default:
		std::cout << "Pogresna opcija! Probajte ponovo!" << std::endl;
		break;

	}


}


}