#include "MeniZaAdministratora.h"

void meniZaAdministratora()
{
	std::string valuta;
	char ime[20];
	char pin[5];
	int tip;
	int dobro;
	int opcija = 111;
	std::cout << "" << std::endl << std::endl << std::endl;

	while (opcija)
	{
		std::cout << std::endl << std::endl;
		std::cout << "Registracija novih korisnika na sistem - 1 -" << std::endl;
		std::cout << "Brisanje naloga sa sistema             - 2 -" << std::endl;
		std::cout << "Podesavanje valute sistema             - 3 -" << std::endl;
		std::cout << "Provjera valute                        - 4 -" << std::endl;
		std::cout << "Izlaz                                  - 0 -" << std::endl;
		std::cout << "Opcija:  ";
		std::cin >> opcija;
		std::cout << std::endl << std::endl;
		switch (opcija)
		{
		case 1: 
			std::cout << "Dodaj ime novog naloga: " << std::endl;
			std::cin >> ime;
			std::cout << "Dodaj novi PIN: " << std::endl;
			std::cin >> pin;
			do {
				std::cout << "Dodaj tip naloga (1-administrator, 2-analiticar)" << std::endl;
				std::cin >> tip;
			} while (tip != 1 && tip != 2);
			dobro = dodajNoviNalog(ime, pin, tip);
			if(dobro)
				std::cout << "Nalog je uspjesno dodan!" << std::endl;
			break;

		case 2:
			std::cout << "Dodaj ime naloga za brisanje: " << std::endl;
			std::cin >> ime;
			obrisiNalog(ime);
			break;

		case 3:
			podesiValutu();
			break;

		case 4:
			valuta = vratiValutu();
			std::cout << "Valuta je: " << std::endl;
			std::cout << valuta << std::endl;
			break;

		case 0:
			return;

		default:
			opcija = 111;
			break;

		}


	}

}