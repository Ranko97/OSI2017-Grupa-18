#include "FunkcijeAnaliticara.h"
#include <string>
#include <fstream>
#include <iostream>

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
}
	std::cout <<std::endl;


}

void ispisi_racun(std::string nazivRacuna) {
	std::ifstream fajl(nazivRacuna.c_str());
	if (!fajl.is_open()) {
		std::cout <<std::endl<< "Fajl za ispis ne postoji ili je doslo do greske pri otvaranju " << std::endl;
		return;
	}
	char buffer[100];
	fajl.getline(buffer, 100);
	std::cout << std::endl<< "Naziv kupca: " << buffer << std::endl;
	fajl.getline(buffer, 100);
	std::cout << "Datum kreiranja racuna: " << buffer << std::endl;
	fajl.getline(buffer, 100);
	std::cout << "Ukupna cijena(bez PDVa): " << buffer << std::endl;
	fajl.getline(buffer, 100);
	std::cout << "PDV: " << buffer << std::endl;
	fajl.getline(buffer, 100);
	std::cout << "Ukupna cijena sa PDVom: " << buffer << std::endl;
	std::cout << "Proizvod    -  kolicina  -  cijena  -  ukupno " << std::endl;
	while (fajl.getline(buffer, 100)) {
		ispisi_artikal(buffer);
	}
	std::cout << std::endl;
	fajl.close();
	}

bool provjeriKupca(std::string nazivRacuna, std::string Kupac) {
	std::ifstream racun(nazivRacuna.c_str());
	if (!racun.is_open()) {
		std::cout << std::end << "Greska pri otvaranju racuna kod provjere kupca! " << std::end;
		return false;
	}
	std::string firstLine;
	racun.getline(firstLine);
	racun.close();
	if (firstLine == kupac)
		return true;
	return false;


}

void filtrirajPoKupcu(std::string kupac) {
	std::ifstream brrac("obradjeni racuni/broj racuna.txt");
	if (!brrac.is_open()) {
		std::cout << std::endl; << "Greska pri otvaranju fajla sa brojem racuna! " << std::endl;
		return;
	}
	char buffer[50];
	brrac.getline(buffer, 50);
	int ukupan_broj_racuna = strtol(buffer, NULL, 10);
	std::string direktorijum = "obradjeni racuni/";
	std::string ekstenzija = ".txt";
	std::string nazivBrojRacuna;
	std::string puniNaziv;
	for (int j = 1; j <= ukupan_broj_racuna; j++) {
		puniNaziv = direktorijum+std::to_string(j)+ekstenzija;
		if (provjeriKupca(puniNaziv, kupac))
			ispisi_racun(puniNaziv);
			
		
	}

}