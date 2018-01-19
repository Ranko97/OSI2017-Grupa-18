#include "MeniZaAnaliticara.h"
#include "UcitavanjeRacuna.h"
#include <string>
#include <iostream>



void meniZaAnaliticara(){
	ucitavanje_racuna();
	int opcija = 1;
	char buffer[100];
	std::string kupac;
	std::string pocetniDatum, krajnjiDatum;
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
	std::cout << "Pregled poslovanja po mjesecima	        - 8 -" << std::endl;
	std::cout << "Ukupan profit u odredjenom intervalu	- 9 -" << std::endl;
	std::cout << "Nazad na meni prijave			- 0 -" << std::endl;
	std::cout << "Opcija:  ";

	do {
		opcija = 10; // Da bi provjera ispravno radila
		std::cin >> opcija;
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
		}

	} while (opcija < 0 || opcija>9 || std::cin.fail()); //Provjera da li je unos dobar

	std::cout << std::endl << std::endl;
	switch (opcija)
	{
	case 1:
		system("cls");
		std::cout << std::endl << "Unesite naziv kupca po kom hocete da filtrirate: ";
		std::getline(std::cin, kupac);
		std::getline(std::cin, kupac);
		std::cout << std::endl;
		filtrirajPoKupcu(kupac);
		system("pause");
		system("cls");
		break;

	case 2:
		system("cls");
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
			std::cout << std::endl << "Unesite redni broj mjeseca: ";
			std::cin >> mjesec;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore();
			}
		} while (mjesec < 1 || mjesec>12 || std::cin.fail());


		filtrirajPoMjesecu(godina, mjesec);
		system("pause");
		system("cls");
		break;

	case 4: 
		system("cls");
		sortirajPoPrometu();
		system("pause");
		system("cls");
		break;
	case 6:
		system("cls");
		ispisUkupnogPoslovanja();
		system("pause");
		system("cls");
		break;
	case 5:
		system("cls");
		sortirajKlijente();
		system("pause");
		system("cls");
		break;
	case 7:
		system("cls");
		ispisRacunaGreska();
		system("pause");
		system("cls");
		break;
	case 8:
		system("cls");
		ispisiPoMjesecima();
		system("pause");
		system("cls");
		break;
	case 9:
		system("cls");
		std::cout << "Unesite pocetni datum u obliku DD/MM/GGGG: ";
		std::cin >> pocetniDatum;
		std::cout << "Unesite krajnji datum u obliku DD/MM/GGGG: ";
		std::cin >> krajnjiDatum;
		std::cout << std::endl;
		obradiRacuneIzIntervala(pocetniDatum, krajnjiDatum);
		system("pause");
		system("cls");
		break;
	case 3:
		system("cls");
		std::cout << std::endl << "Unesite naziv artikla po kom hocete da filtrirate: "<<std::endl;
		std::getline(std::cin, naziv);
		std::getline(std::cin, naziv);
		filtrirajpoArtiklu(naziv);
		system("pause");
		system("cls");
		break;

	case 0:
		system("cls");
		return;
	default:
		system("cls");
		std::cout << "Pogresna opcija! Probajte ponovo!" << std::endl;
		system("cls");
		break;

	}

}


}