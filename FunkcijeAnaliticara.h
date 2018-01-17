#pragma once
#include <string>


class ObradjenRacun
{
public:
	std::string datum, kupac;
	double ukupno, pdv, ukupnoSaPdv;
};

void ispisi_artikal(char*);
void ispisi_racun(std::string);
void filtrirajPoKupcu(std::string);
void filtrirajPoMjesecu(int godina, int mjesec);
bool provjeriKupca(std::string, std::string);
int provjeraMjeseca(std::string nazivFajla, int godina, int mjesec);
int parseDate(const std::string &input);