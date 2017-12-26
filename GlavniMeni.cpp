#include "GlavniMeni.h"
#include <iostream>
#include "MeniZaAdministratora.h"
#include "MeniZaAnaliticara.h"

void glavniMeni()
{
	int tipNaloga;
	do
	{
		Nalog nalog;
		std::cout << "Unesite ime naloga: " << std::endl;
		std::cin >> nalog.imeNaloga;
		std::cout << "Unesite svoj PIN: " << std::endl;
		std::cin >> nalog.pinNaloga;

		tipNaloga = imalNaloga(nalog.imeNaloga, nalog.pinNaloga);
		if (tipNaloga == 0)
			std::cout << "Neuspjesna prijava" << std::endl << std::endl;

	} while (tipNaloga == 0);
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
