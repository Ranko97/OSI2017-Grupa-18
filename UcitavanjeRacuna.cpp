#include <Windows.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "FunkcijeZaObraduRacuna.h"
#include "UcitavanjeRacuna.h"

vector<string> imena_fajlova_u_folderu(string folder) {

	vector<string> names;
	/*
	Algoritam koji sve fajlove u jednom folderu smijesta u vektor
	stringova i njega vraca. Ulazni parametar je direktorijum foldera
	(relativni ili direktni)
	*/
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;

}

int tip_racuna(const char* naziv) {
	/*
	Funkcija odredjuje tip racuna tako sto uporedjuje prvo
	slovo 4 linije fajla sa svim mogucim slovima koji se mogu naci.
	U slucaju da je to slovo razlicito od mogucih u datim formatima
	odnosno u slucaju da format racuna nije ispravan,
	vraca se -1.Ulazni parametar je naziv racuna
	*/
	string direktorijum = "racuni/";
	string puniNaziv = direktorijum;
	puniNaziv += naziv;
	ifstream fajl(puniNaziv.c_str());
	//cout <<endl<<"naziv: "<< puniNaziv.c_str() << endl;
	if (!fajl.is_open()) {
		std::cout << "Greska pri otvaranju fajla" << std::endl;
		return -2;
	}
	char buffer[100];
	fajl.getline(buffer, 100);
	fajl.getline(buffer, 100);
	fajl.getline(buffer, 100);
	fajl >> buffer;
	if (buffer[0] == 'R') {
		fajl.close();
		return 1;
	}
	if (buffer[0] == 'M') {
		fajl.close();
		return 2;
	}
	if (buffer[0] == 'D') {
		fajl.close();
		return 3;
	}
	if (buffer[0] == 'e') {
		fajl.close();
		return 4;
	}

	std::cout << "Neispravan format racuna!" << std::endl;
	fajl.close();
	return -1;

}


void obradi_racun(const char* naziv) {
	/*
	NAPOMENA: Komentari se odnose za dio koda iznad njih!
	*/

	int tipNovogRacuna = tip_racuna(naziv);
	if (tipNovogRacuna == -1) {
		std::cout << "GRESKA! Pogresan tip(format) racuna)" << std::endl;
		/*
		ovde mozda da stavimo neku f-ju koja ce prebaciti taj racun u error folder?!
		*/
		return;
	}

	std::fstream brfajl("obradjeni racuni/broj racuna.txt", ios::in);
	if (!brfajl.is_open()) {
		std::cout << "Greska pri otvaranju fajla koji sadrzi broj fajlova!" << std::endl;
		return;
	}
	char buffer[100];
	brfajl.getline(buffer, 100);
	int ukupan_broj_racuna = strtol(buffer, NULL, 10);
	ukupan_broj_racuna++;
	brfajl.close();
	brfajl.open("obradjeni racuni/broj racuna.txt", ios::out);
	brfajl << ukupan_broj_racuna << "\n";
	brfajl.close();
	/*
	Otvaramo fajl "broj racuna" koji se nalazi u folderu "obradjeni racuni"
	i iz njega citamo trenutni broj racuna, uvecavamo ga za jedan i pisemo ga u isti fajl.
	*/

	std::string nazivBrojRacuna = std::to_string(ukupan_broj_racuna);
	std::string direktorijum = "obradjeni racuni/";
	std::string ekstenzija = ".txt";
	std::string puniNaziv = direktorijum;
	puniNaziv += nazivBrojRacuna;
	puniNaziv += ekstenzija;

	/*
	Kreiramo i otvaramo novi racun u folderu obradjeni racuni
	u koji cemo upisati racun iz foldera racuni.
	*/

	std::string direktorijum2 = "racuni/";
	std::string puniNaziv2 = direktorijum2;
	puniNaziv2 += naziv;
	switch (tipNovogRacuna) {
	case 1:
		obradi_racun1(puniNaziv2, puniNaziv);
		break;
	case 2:
		obradi_racun2(puniNaziv2, puniNaziv);
		break;
	case 3:
		obradi_racun3(puniNaziv2, puniNaziv);
		break;
	case 4:
		obradi_racun4(puniNaziv2, puniNaziv);
		break;
	}
	remove(puniNaziv2.c_str());
	provjeraRacuna(puniNaziv);

}

void ucitavanje_racuna() {
	vector<string> niz = imena_fajlova_u_folderu("./racuni");
	for (string v : niz) {
		obradi_racun(v.c_str());
	}
}

inline bool ispravniPodaci(double cijena, double kolicina, double ukupno)
{
	return (ukupno == cijena*kolicina) ? true : false;
}


//Ovdje se provjerava da li je racun ispravan
void provjeraRacuna(std::string imeRacuna)
{
	bool ispravan = true;
	std::ifstream racunProvjera(imeRacuna.c_str());
	char buffer[100];
	racunProvjera.getline(buffer, 100);
	racunProvjera.getline(buffer, 100);

	double ukupno, pdv, saPdv;
	racunProvjera >> ukupno;
	racunProvjera >> pdv;
	racunProvjera >> saPdv;
	if (ukupno + pdv != saPdv)
		ispravan = false;
	//Provjera konzistentnosti

	std::string artikal;

	if (!racunProvjera.is_open())
	{
		std::cout << "Greska pri provjeri racuna";
		return;
	}

	double kolicina = 0, cijena = 0, ukupno1 = 0;

	std::getline(racunProvjera, artikal, '-');
	while (artikal != "\n")
	{
		racunProvjera >> kolicina;
		racunProvjera >> cijena;
		racunProvjera >> ukupno1;
		cijena = -cijena;   //Jer se dobiju negativne vrijednosti
		ukupno1 = -ukupno1;

		if (!ispravniPodaci(cijena, kolicina, ukupno1))
			ispravan = false;
		std::getline(racunProvjera, artikal, '-');
	}
	racunProvjera.close();


	if (!ispravan)
	{
		std::ifstream brRac("Racuni sa greskom/brRac.txt");
		if (!brRac.is_open()) {
			std::cout << "Greska pri otvaranju fajla koji sadrzi broj racuna!" << std::endl;
			return;
		}
		//Povecanje broja racuna sa greskom
		int broj;
		brRac >> broj;
		broj++;
		brRac.close();
		std::ofstream brRacuna("Racuni sa greskom/brRac.txt");
		brRacuna << broj;
		brRacuna.close();

		std::string novoImeRacuna = "Racuni sa greskom/";
		novoImeRacuna += std::to_string(broj);
		novoImeRacuna += ".txt";

		if (rename(imeRacuna.c_str(), novoImeRacuna.c_str()) != 0)
		{
			std::cout << "Greska pri prebacivanju fajla";
			return;
		}
		// Premjestanje racuna

		std::ifstream brRac2("obradjeni racuni/broj racuna.txt");
		if (!brRac2.is_open()) {
			std::cout << "Greska pri otvaranju fajla koji sadrzi broj racuna!" << std::endl;
			return;
		}

		// Smanjivanje broja obradjenih racuna
		int broj2;
		brRac2 >> broj2;
		broj2--;
		brRac2.close();
		std::ofstream brRacuna2("obradjeni racuni/broj racuna.txt");
		brRacuna2 << broj2;
		brRacuna2.close();

	}

}
