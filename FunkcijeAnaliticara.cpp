#include "FunkcijeAnaliticara.h"
#include <string>
#include <fstream>
#include <iostream>
#include "FunkcijeAdministratora.h"

void ispisi_artikal(const char* buffer) {
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

int is_exist(Artikal& a, Artikal* niz, int& broj_artikala)
{
	for (int i = 0; i < broj_artikala; i++)
	{
		if (a.ime == niz[i].ime)
			return i;
	}
	return -1;
}

void upisiUArtikal(char* buffer, Artikal& a)
{
	char buffer2[20];
	int brojac = 0;
	while (buffer[brojac] != '-')
	{
		buffer2[brojac] = buffer[brojac];
		brojac++;
	}
	buffer2[brojac] = '\0';
	a.ime = buffer2;
	brojac++;
	int i = 0;
	while (buffer[brojac] != '-')
	{
		buffer2[i++] = buffer[brojac++];
	}
	buffer2[i] = '\0';
	a.kolicina = strtol(buffer2, NULL, 10);
	brojac++;
	i = 0;
	while (buffer[brojac] != '-')
	{
		buffer2[i++] = buffer[brojac++];
	}
	buffer2[i] = '\0';
	a.cijena = strtold(buffer2, NULL);
	brojac++;
	i = 0;
	while (buffer[brojac] != '\0')
	{
		buffer2[i++] = buffer[brojac++];
	}
	buffer2[i] = '\0';
	a.ukupno = strtold(buffer2, NULL);
}

Artikal* realociraj(Artikal* niz, int& kapacitet)
{
	kapacitet *= 2;
	Artikal* pom = new Artikal[kapacitet];
	for (int i = 0; i < kapacitet / 2; i++)
		pom[i] = niz[i];
	delete[] niz;
	return pom;
}

void obradiArtikal(char*  buffer, Artikal** niz, int& kapacitet, int& broj_artikala)
{
	Artikal a;
	upisiUArtikal(buffer, a);
 	int indeks = is_exist(a, *niz, broj_artikala);
	if (indeks != -1)
	{
		(*niz)[indeks].kolicina += a.kolicina;
		(*niz)[indeks].ukupno += a.ukupno;
	}
	else
	{
		(*niz)[broj_artikala++] = a;
	}
	if (broj_artikala == kapacitet)
		(*niz) = realociraj(*niz, kapacitet);
	}

void sortiraj(Artikal* niz, int broj_artikala)
{
	Artikal pom;
	for (int i = 0; i < broj_artikala - 1; i++)
	{
		for (int j = i + 1; j < broj_artikala; j++)
		{
			if (niz[j].ukupno > niz[i].ukupno)
			{
				pom = niz[j];
				niz[j] = niz[i];
				niz[i] = pom;
			}
		}
	}
}

void ispisi_artikle(Artikal* niz, int broj_artikala)
{
	std::cout << std::endl<< "    Ispis artikala sortiranih po prometu    " << std::endl;
	std::cout << "Naziv      Kolicina         Cijena        Ukupno" << std::endl;
	std::string art;
	Artikal a;
	for (int i = 0; i < broj_artikala; i++)
	{
		a = niz[i];
		art = a.ime+'-' + std::to_string(a.kolicina) +'-'+ std::to_string(a.cijena)+'-'+ std::to_string(a.ukupno);
		ispisi_artikal(art.c_str());
	}
	std::cout <<"   NAPOMENA: Sve cijene su u valuti "<<vratiValutu()<< std::endl<<std::endl;
}

void sortirajPoPrometu()
{
	char buffer[50];
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
	std::ifstream RacunUObradi;
	int n = 50;
	int broj_artikala = 0;
	Artikal* niz = new Artikal[n];
	std::string imeFajla;
	for (int i = 1; i <= brojRacuna; i++)
	{
		imeFajla = "obradjeni racuni/";
		imeFajla += std::to_string(i);
		imeFajla += ".txt";
		RacunUObradi.open(imeFajla.c_str());
		for (int j = 0; j < 5; j++)
			RacunUObradi.getline(buffer, 51);
		while (RacunUObradi.getline(buffer, 51))
			obradiArtikal(buffer, &niz, n, broj_artikala);
		RacunUObradi.close();
	}
	sortiraj(niz, broj_artikala);
	ispisi_artikle(niz, broj_artikala);
	delete[] niz;
}

void ispisUkupnogPoslovanja(){
	double ukupnoPoslovanje = 0;
	double pom;
	char buffer[50];
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
	std::ifstream RacunUObradi;
	std::string imeFajla;
	for (int i = 1; i <= brojRacuna; i++)
	{
		imeFajla = "obradjeni racuni/";
		imeFajla += std::to_string(i);
		imeFajla += ".txt";
		RacunUObradi.open(imeFajla.c_str());
		for (int j = 0; j < 4; j++)
			RacunUObradi.getline(buffer, 51);
		RacunUObradi >> pom;
		ukupnoPoslovanje += pom;
		RacunUObradi.close();
	}
	std::ifstream valuta("Valuta_sistema");
	if (!valuta.is_open()) {
		std::cout << std::endl << "Greska pri otvaranju fajla valute sistema" << std::endl;
		return;
	}
	
	std::string valuta_sistema;
	valuta >> valuta_sistema;
	valuta.close();
	std::cout << std::endl << "Dosadasnji ostvaren profit preduzeca je: " << ukupnoPoslovanje << valuta_sistema << std::endl;

}

Kupac::Kupac():ukupna_cijena(0){}

int is_exist_kupac(Kupac* niz,std::string& ime, int& broj_kupaca)
{
	for (int i = 0; i < broj_kupaca; i++)
		if (niz[i].naziv == ime)
			return i;
	return -1;
}

void sortiraj_i_ispisi(Kupac* niz,int broj_kupaca)
{
	Kupac pom;
	for (int i = 0; i < broj_kupaca - 1; i++)
	{
		for (int j = i + 1; j < broj_kupaca; j++)
		{
			if (niz[j].ukupna_cijena > niz[i].ukupna_cijena)
			{
				pom = niz[j];
				niz[j] = niz[i];
				niz[i] = pom;
			}
		}
	}
	std::ifstream valuta("Valuta_sistema");
	if (!valuta.is_open()) {
		std::cout << std::endl << "Greska pri otvaranju fajla valute sistema" << std::endl;
		return;
	}

	std::string valuta_sistema;
	valuta >> valuta_sistema;
	valuta.close();
	std::cout << std::endl << " ===Klijenti sortirani po ostvarenom profitu nad njima===" << std::endl;
	for (int i = 0; i < broj_kupaca; i++)
		std::cout << "    Naziv " << i + 1 << ". klijenta: " << niz[i].naziv << "=====ukupan profit: " << niz[i].ukupna_cijena <<valuta_sistema<< std::endl;

	
}

void sortirajKlijente()
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
	Kupac* niz = new Kupac[brojRacuna];
	std::ifstream RacunUObradi;
	std::string imeFajla;
	int broj_kupaca = 0;
	Kupac pom;
	char buffer[30];
	int indeks;
	for (int i = 1; i <= brojRacuna; i++)
	{
		imeFajla = "obradjeni racuni/";
		imeFajla += std::to_string(i);
		imeFajla += ".txt";
		RacunUObradi.open(imeFajla.c_str());
		RacunUObradi.getline(buffer, 30);
		pom.naziv = buffer;
		for(int j=0;j<3;j++)
			RacunUObradi.getline(buffer, 30);
		RacunUObradi.getline(buffer, 30);
		pom.ukupna_cijena = strtod(buffer,NULL);
		indeks = is_exist_kupac(niz,pom.naziv, broj_kupaca);
		if (indeks != -1)
			niz[indeks].ukupna_cijena =niz[indeks].ukupna_cijena+ pom.ukupna_cijena;
		else
			niz[broj_kupaca++] = pom;
		RacunUObradi.close();
	}
	sortiraj_i_ispisi(niz, broj_kupaca);
	delete[] niz;
}

void ispisRacunaGreska()
{
	std::ifstream brRac("Racuni sa greskom/brRac.txt");
	if(!brRac.is_open())
		{
		std::cout << std::endl << "Greska pri otvaranju racuna sa brojem error fajlova! " << std::endl;
		return;
	 }
	int broj_racuna;
	brRac >> broj_racuna;
	brRac.close();
	std::string nazivRacuna;
	for (int i = 1; i <= broj_racuna; ++i)
	{
		nazivRacuna = "Racuni sa greskom/" + std::to_string(i) + "_error.txt";
		std::cout << i << ". racun sa greskom: " << std::endl;
		ispisi_racun(nazivRacuna);
	}
}

void filtrirajpoArtiklu(std::string naziv)
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
	std::ifstream RacunUObradi;
	std::string imeFajla;
	Artikal prvi;
	prvi.ime = naziv;
	prvi.cijena =prvi.kolicina=prvi.ukupno=0;
	Artikal drugi;
	char buffer[40];
	int brojac = 0;
	char nazivv[20];
	char datum[12];

	for (int i = 1; i <= brojRacuna; i++)
	{
		imeFajla = "obradjeni racuni/";
		imeFajla += std::to_string(i);
		imeFajla += ".txt";
		RacunUObradi.open(imeFajla.c_str());
		RacunUObradi.getline(nazivv, 20);
		RacunUObradi.getline(datum, 12);
		for (int j = 0; j < 3; j++)
			RacunUObradi.getline(buffer, 40);
		while (RacunUObradi.getline(buffer, 40))
		{
			upisiUArtikal(buffer, drugi);
			if (prvi.ime == drugi.ime)
			{
				++brojac;
				prvi.cijena = drugi.cijena;
				prvi.kolicina += drugi.kolicina;
				prvi.ukupno += drugi.ukupno;
				std::cout << std::endl<< "Podaci o racunu " << brojac << ". u kom se artikal nalazi:" << std::endl;
				std::cout << " Naziv kupca: " << nazivv << std::endl;
				std::cout << "Datum izavanja racuna: " << datum << std::endl;
				std::cout << "Artikal:    "<<std::endl;
				std::cout << "Proizvod    -  kolicina  -  cijena  -  ukupno " << std::endl;
				ispisi_artikal(buffer);
				std::cout << std::endl;
			}

		}
		RacunUObradi.close();
	}
	
	std::cout <<std::endl << std::endl << "Ukupno se artikal nalazi u " << brojac << ". racuna" << std::endl;
	std::cout << "Ukupno je prodan " << prvi.kolicina << ". puta" << std::endl;
	std::cout << "Ukupan profitiran iznos nad njim je: " << prvi.ukupno << vratiValutu() << std::endl;
}