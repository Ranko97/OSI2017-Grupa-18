#include "FunkcijeAdministratora.h"



int dodajNoviNalog(char imeNaloga[20], char pinNaloga[5], int tipNaloga)
{
	Nalog* noviNalog = citajNalog(imeNaloga);
	if (noviNalog != nullptr)
	{
		std::cout << "Nalog sa tim imenom vec postoji!" << std::endl;
		return 0;
	}

	noviNalog = new Nalog;
	strcpy_s(noviNalog->imeNaloga, 20, imeNaloga);
	strcpy_s(noviNalog->pinNaloga, 5, pinNaloga);
	noviNalog->tipNaloga = tipNaloga;

	bool uspjesnoUpisivanje = upisiNalog(noviNalog);
	if (!uspjesnoUpisivanje)
	{
		std::cout << "Doslo je do greske pri upisivanju!" << std::endl;
		return 0;
	}
	return 1;	
}

bool upisiNalog(Nalog* nalog)
{
	char pravoIme[33];
	char prefiks[8] = "Nalozi/";
	//Dodavanje Nalozi/
	strcpy_s(pravoIme, 8, prefiks);
	strcat_s(pravoIme, 28, nalog->imeNaloga);

	//Dodavanje ekstenzije .txt
	char ekstenzija[5] = ".txt";
	strcat_s(pravoIme, 33, ekstenzija);

	std::ofstream fajl;
	fajl.open(pravoIme);
	if (!fajl.is_open())
	{
		return false;
	}

	fajl << nalog->pinNaloga << std::endl;
	fajl << nalog->tipNaloga;

	fajl.close();
	return true;
}



int obrisiNalog(char imeBrisi[20])
{
	//Osiguravanje da se ne brise svoj nalog
	std::cout << "Unesite svoje ime da potvrdite!" << std::endl;
	char imeAdmina[20];
	std::cin >> imeAdmina;
	std::cout << "Unesite svoj PIN!" << std::endl;
	char pinAdmina[5];
	std::cin >> pinAdmina;

	if (strcmp(imeBrisi, imeAdmina) == 0)
	{
		std::cout << "Ne mozete obrisati nalog koji trenutno koristite!" << std::endl;
		return 0;
	}

	int postoji = imalNaloga(imeAdmina, pinAdmina);
	if (!postoji)
	{
		std::cout << "Ne postoji takav nalog!" << std::endl;
		return 0;
	}

	//Brisanje naloga

	char pravoIme[33];
	char prefiks[8] = "Nalozi/";
	//Dodavanje Nalozi/
	strcpy_s(pravoIme, 8, prefiks);
	strcat_s(pravoIme, 28, imeBrisi);

	//Dodavanje ekstenzije .txt
	char ekstenzija[5] = ".txt";
	strcat_s(pravoIme, 33, ekstenzija);

	int nijeObrisan = remove(pravoIme);

	if (nijeObrisan)
	{
		std::cout << "Greska pri brisanju naloga!" << std::endl;
		return 0;
	}

	std::cout << "Nalog je obrisan!" << std::endl;

	return 1;
}



bool podesiValutu()
{
	std::cout << "Unesi novu valutu:   ";
	std::string novaValuta;
	std::cin >> novaValuta;

	std::ofstream fajl;
	fajl.open("Valuta_sistema");
	if (!fajl.is_open())
	{
		std::cout << "Greska pri promjeni valute!" << std::endl;
		return false;
	}
	fajl << novaValuta;
	fajl.close();
	std::cout << "Valuta je promijenjena!" << std::endl;
	return true;
}


std::string vratiValutu()
{	
	std::string valuta;
	std::ifstream fajl;
	fajl.open("Valuta_sistema");
	if (!fajl.is_open())
	{
		std::cout << "Greska pri pristupanju nazivu valute!" << std::endl;
		return valuta;
	}
	
	fajl >> valuta;
	fajl.close();
	return valuta;
}
