#pragma once
#include <string>


struct ObradjenRacun
{
	std::string datum, kupac;
	double ukupno, pdv, ukupnoSaPdv;
};

struct Artikal
{
	std::string ime;
	double kolicina;
	double cijena;
	double ukupno;
};

struct Kupac
{
	std::string naziv;
	double ukupna_cijena;
	Kupac();
};

struct ModifikovanDatum
{
	int godina, mjesec;
	double ukupno;
	ModifikovanDatum();
	bool operator==(const ModifikovanDatum&)const noexcept;
	bool operator>(const ModifikovanDatum&)const noexcept;
};
void obradiRacuneIzIntervala(std::string, std::string);
int is_exist_datum(ModifikovanDatum*, ModifikovanDatum&, int);
void ispisiPoMjesecima();
int brojObradjenihRacuna();
void filtrirajpoArtiklu(std::string);
void ispisRacunaGreska();
void sortirajKlijente();
void sortiraj_i_ispisi(Kupac*, int);
void sortiraj_i_ispisi(ModifikovanDatum*, int);
int is_exist_kupac(Kupac*, std::string&, int&);
void ispisUkupnogPoslovanja();
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