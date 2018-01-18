#pragma once
#include <string>


class ObradjenRacun
{
public:
	std::string datum, kupac;
	double ukupno, pdv, ukupnoSaPdv;
};

struct Artikal
{
	std::string ime;
	int kolicina;
	double cijena;
	double ukupno;
};

int is_exist(Artikal&, Artikal*, int&);
void upisiUArtikal(char*, Artikal&);
Artikal* realociraj(Artikal*, int&);
void obradiArtikal(char*, Artikal**, int&, int&);
void sortiraj(Artikal*, int);
void ispisi_artikle(Artikal*, int);
void sortirajPoPrometu();
void ispisi_artikal(const char*);
void ispisi_racun(std::string);
void filtrirajPoKupcu(std::string);
void filtrirajPoMjesecu(int godina, int mjesec);
bool provjeriKupca(std::string, std::string);
int provjeraMjeseca(std::string nazivFajla, int godina, int mjesec);
int parseDate(const std::string &input);