#include "GlavniMeni.h"
#include <iostream>
#include "MeniZaAdministratora.h"
#include "MeniZaAnaliticara.h"

void glavniMeni()
{
	int  brojPokusaja = 5;
	int tipNaloga;
	do
	{
		
		Nalog nalog;
		std::cout << "Unesite ime naloga: ";
		std::cin >> nalog.imeNaloga;
		std::cout << "Unesite svoj PIN: ";
		std::cin >> nalog.pinNaloga;
		std::cout << std::endl;
		tipNaloga = imalNaloga(nalog.imeNaloga, nalog.pinNaloga);
		brojPokusaja--;
		if (tipNaloga == 0)
		{
			std::cout << "Neuspjesna prijava"  << std::endl;
			std::cout << "Broj preostalih pokusaja: "<< brojPokusaja << std::endl << std::endl;
		}
	} while (tipNaloga == 0 && brojPokusaja > 0);
	switch (tipNaloga)
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

	

}
