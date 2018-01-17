#include "FunkcijeAnaliticara.h"
#include <string>
#include <fstream>
#include <iostream>
#include "FunkcijeAdministratora.h"

void ispisi_artikal(char* buffer) {
	int brojac = 0;
	int i = 0;
	while (buffer[i] != '-') {
		std::cout << buffer[i];
		brojac++;
		i++;
	}
	if (brojac < 12)
		for (int j = 0; j < 12 - brojac; j++)
			std::cout << " ";

	std::cout << buffer[i++];
	brojac = 0;
	std::cout << "  ";
	while (buffer[i] != '-') {
		std::cout << buffer[i];
		brojac++;
		i++;
	}
	brojac = brojac + 2;
	if (brojac < 12)
		for (int j = 0; j < 12 - brojac; j++)
			std::cout << " ";
	std::cout << buffer[i++];
	brojac = 0;
	std::cout << "  ";
	while (buffer[i] != '-') {
		std::cout << buffer[i];
		brojac++;
		i++;
	}
	brojac = brojac + 2;
	if (brojac < 10)
		for (int j = 0; j < 10-brojac; j++)
			std::cout << " ";
	std::cout << buffer[i++];
	std::cout << "  ";
	while (buffer[i] != '\0') {
		std::cout << buffer[i];
		i++;
}
	std::cout <<std::endl;


}

void ispisi_racun(std::string nazivRacuna) {
	std::ifstream fajl(nazivRacuna.c_str());
	if (!fajl.is_open()) {
		std::cout <<std::endl<< "Fajl za ispis ne postoji ili je doslo do greske pri otvaranju " << std::endl;
		return;
	}
	//Dodata valuta sistema
	char buffer[100];
	fajl.getline(buffer, 100);
	std::cout << std::endl << "Naziv kupca: " << buffer << std::endl;
	fajl.getline(buffer, 100);
	std::cout << "Datum kreiranja racuna: " << buffer << std::endl;
	fajl.getline(buffer, 100);
	std::cout << "Ukupna cijena(bez PDVa): " << buffer << vratiValutu() << std::endl;
	fajl.getline(buffer, 100);
	std::cout << "PDV: " << buffer << vratiValutu() << std::endl;
	fajl.getline(buffer, 100);
	std::cout << "Ukupna cijena sa PDVom: " << buffer << vratiValutu() << std::endl;
	std::cout << "Proizvod    -  kolicina  -  cijena  -  ukupno " << std::endl;
	while (fajl.getline(buffer, 100)) {
		ispisi_artikal(buffer);
		
	}
	std::cout << std::endl;
	fajl.close();
	}

bool provjeriKupca(std::string nazivRacuna, std::string kupac) {
	std::ifstream racun(nazivRacuna.c_str());
	if (!racun.is_open()) {
		std::cout << std::endl << "Greska pri otvaranju racuna kod provjere kupca! " << std::endl;
		return false;
	}
	std::string firstLine;
	std::getline(racun, firstLine);
	racun.close();
	if (firstLine == kupac)
		return true;
	return false;


}

int provjeraMjeseca(std::string nazivFajla, int godina, int mjesec)
{
	ObradjenRacun racun;
	std::ifstream obradjenR(nazivFajla);

	obradjenR >> racun.kupac;
	obradjenR >> racun.datum;
	obradjenR >> racun.ukupno;
	obradjenR >> racun.pdv;
	obradjenR >> racun.ukupnoSaPdv;

	//Provjera datuma;
	int godinaS, mjesecS;
	int datum = parseDate(racun.datum);

	godinaS = datum / 10000;
	mjesecS = datum % 10000;
	mjesecS %= 100;

	if (godina != godinaS || mjesec != mjesecS)
		return 0;
	obradjenR.close();
	ispisi_racun(nazivFajla);
	return 1;
}

int parseDate(const std::string & input)
{
	int month;
	int day;
	int year;
	if (sscanf_s(input.c_str(), "%d/%d/%d", &month, &day, &year) != 3) {
		// handle error
	}
	else {
		// check values to avoid int overflow if you can be bothered
		return 10000 * year + 100 * month + day;
	}
}

void filtrirajPoKupcu(std::string kupac) {
	std::ifstream brrac("obradjeni racuni/broj racuna.txt");
	if (!brrac.is_open()) {
		std::cout << std::endl << "Greska pri otvaranju fajla sa brojem racuna! " << std::endl;
		return;
	}
	char buffer[50];
	brrac.getline(buffer, 50);
	int ukupan_broj_racuna = strtol(buffer, NULL, 10);
	std::string direktorijum = "obradjeni racuni/";
	std::string ekstenzija = ".txt";
	std::string nazivBrojRacuna;
	std::string puniNaziv;
	int brojac = 0;
	for (int j = 1; j <= ukupan_broj_racuna; j++) {
		puniNaziv = direktorijum+std::to_string(j)+ekstenzija;
		if (provjeriKupca(puniNaziv, kupac)) {
			ispisi_racun(puniNaziv);
			brojac++;
		}
		
	}
	if (brojac == 0)
		std::cout << std::endl << "Nema racuna sa tim kupcem! " << std::endl;

}

void filtrirajPoMjesecu(int godina, int mjesec)
{
	std::ifstream brRac("obradjeni racuni/broj racuna.txt");
	if (!brRac.is_open()) {
		std::cout << std::endl << "Greska pri otvaranju fajla sa brojem racuna! " << std::endl;
		return;
	}
	int brojRacuna;
	brRac >> brojRacuna;
	brRac.close();

	if (brojRacuna == 0)
	{
		std::cout << "Nema racuna za ispis." << std::endl;
		return;
	}

	int barJedan = 0;

	for (int i = 1; i <= brojRacuna; i++)
	{
		std::string imeFajla = "obradjeni racuni/";
		imeFajla += std::to_string(i);
		imeFajla += ".txt";
		barJedan += provjeraMjeseca(imeFajla, godina, mjesec);
	}

	if (!barJedan)
		std::cout << "Nema racuna u ovom mjesecu." << std::endl;
	else
		std::cout << "Ukupno " << barJedan << " racuna u ovom mjesecu." << std::endl;
}
