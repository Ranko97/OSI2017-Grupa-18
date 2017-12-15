#include "PrijavaNaSistem-provjeraNaloga.h"


Nalog* citajNalog(char imeNaloga[20])
{
	char pravoIme[33];
	char prefiks[8] = "Nalozi/";
	//Dodavanje Nalozi/
	strcpy_s(pravoIme, 8, prefiks);
	strcat_s(pravoIme, 28, imeNaloga);

	//Dodavanje ekstenzije .txt
	char ekstenzija[5] = ".txt";
	strcat_s(pravoIme, 33, ekstenzija);

	std::ifstream fajl;
	fajl.open(pravoIme);
	if (!fajl.is_open())
	{
		return nullptr;
	}

	Nalog* nalog = new Nalog;
	strcpy_s(nalog->imeNaloga, 20, imeNaloga);

	char pin[5];
	fajl >> pin;
	strcpy_s(nalog->pinNaloga, 5, pin);
	int tip;
	fajl >> tip;
	nalog->tipNaloga = tip;
	fajl.close();

	return nalog;

}




int imalNaloga(char imeNaloga[20], char pinNaloga[5])
{



	Nalog* procitani = citajNalog(imeNaloga);

	if (procitani == nullptr)
	{
		std::cout << "Ne postoji nalog sa tim imenom!" << std::endl;
		return 0;
	}

	if (strcmp(pinNaloga, procitani->pinNaloga) != 0)
	{
		std::cout << "Ne podudara se PIN!" << std::endl;
		return 0;
	}

	int temp = procitani->tipNaloga;
	delete procitani;
	return temp;

}


