#include "GlavniMeni.h"
#include <iostream>
#include "MeniZaAdministratora.h"
#include "MeniZaAnaliticara.h"
#define brojPokusajaPrijave 5

void glavniMeni()
{
	bool komandaIzlaz = false;
	do
	{
		int  brojPokusaja = brojPokusajaPrijave; //Korisnik ima 5 pokusaja prijave na sistem
		int tipNaloga;

		do
		{
			Nalog nalog;
			std::cout << "	==== Prijava na sistem ====" << std::endl << std::endl;
			std::cout << "Unesite ime vaseg naloga, ili '0' za izlaz: " << std::endl;
			std::cin >> nalog.imeNaloga;
			if (strcmp(nalog.imeNaloga, "0") == 0)
			{
				komandaIzlaz = true;
				return;				//Provjera treba li izaci iz sistema
			}
			std::cout << "Unesite svoj PIN: " << std::endl;
			std::cin >> nalog.pinNaloga;


			tipNaloga = imalNaloga(nalog.imeNaloga, nalog.pinNaloga);
			brojPokusaja--;
			if (tipNaloga == 0)
			{
				std::cout << "Neuspjesna prijava" << std::endl;
				std::cout << "Broj preostalih pokusaja: " << brojPokusaja << std::endl << std::endl;
			}
		} while (tipNaloga == 0 && brojPokusaja > 0);

		if (brojPokusaja == 0)
		{
			std::cout << "Niste se uspjeli prijaviti na sistem." << std::endl;
			std::cout << "Pritisnite enter za izlaz." << std::endl;
			getchar();
			getchar();
			return;
		}

		switch (tipNaloga)		//Provjera tipa korisnika
		{
		case 1:
			meniZaAdministratora();
			break;

		case 2:
			meniZaAnaliticara();
			break;

		default:
			break;

		}

	} while (komandaIzlaz == false);

}
