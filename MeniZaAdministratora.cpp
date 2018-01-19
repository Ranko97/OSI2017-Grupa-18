#include "MeniZaAdministratora.h"

void meniZaAdministratora()
{
	std::string valuta;
	char ime[20];
	char pin[5];
	int tip;
	int dobro;
	int opcija = 111;
	while (opcija)
	{
		std::cout << std::endl << "	==== Meni za administratora ====" << std::endl << std::endl;
		std::cout << "Registracija novih korisnika na sistem - 1 -" << std::endl;
		std::cout << "Brisanje naloga sa sistema             - 2 -" << std::endl;
		std::cout << "Podesavanje valute sistema             - 3 -" << std::endl;
		std::cout << "Provjera valute                        - 4 -" << std::endl;
		std::cout << "Nazad na meni prijave                  - 0 -" << std::endl;
		std::cout << "Opcija:  ";
		do {
			
			std::cin >> opcija;
			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore();
			}

		} while (opcija < 0 || opcija>5|| std::cin.fail() ); //Provjera da li je unos dobar
		std::cout << std::endl << std::endl;
		switch (opcija)
		{
		case 1: 
			system("cls");
			std::cout << "Dodaj ime novog naloga: ";
			std::cin >> ime;
			std::cout << "Dodaj novi PIN (max 4 znaka): ";
			std::cin >> pin;
			do {
				std::cout << "Izaberi tip naloga (1-administrator, 2-analiticar): ";
				std::cin >> tip;
			} while (tip != 1 && tip != 2);
			dobro = dodajNoviNalog(ime, pin, tip);
			if(dobro)
				std::cout << "Nalog je uspjesno dodan!" << std::endl;
			system("pause");
			system("cls");
			break;

		case 2:
			system("cls");
			std::cout << "Dodaj ime naloga za brisanje: ";
			std::cin >> ime;
			obrisiNalog(ime);
			system("pause");
			system("cls");
			break;

		case 3:
			system("cls");
			podesiValutu();
			system("pause");
			system("cls");
			break;

		case 4:
			system("cls");
			valuta = vratiValutu();
			std::cout << "Valuta je: ";
			std::cout << valuta << std::endl;
			system("pause");
			system("cls");
			break;
		case 0:
			system("cls");
			return;

		default:
			opcija = 111;
			break;

		}


	}

}
