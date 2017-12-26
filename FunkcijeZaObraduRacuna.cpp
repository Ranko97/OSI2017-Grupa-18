#include "FunkcijeZaObraduRacuna.h"
#include <iostream>
#include <string>

char* formatiraj124(char* buffer) {
	int i = 0;
	bool prekidac = true;
	char* novi = new char[100];
	while (prekidac) {
		novi[i] = buffer[i];
		i++;
		if ((buffer[i] == ' ' && (buffer[i + 1] == ' ' || buffer[i + 1] == '-')) || buffer[i] == '-')
			prekidac = false;
	}
	int k = i;
	while (buffer[i] != '\0') {
		if (buffer[i] > 44 && buffer[i] < 58 && buffer[i] != 47)
			novi[k++] = buffer[i];
		i++;
	}
	novi[k] = '\0';
	return novi;

}

void obradi_racun1(std::string puniNaziv2, std::string puniNaziv) {
	std::ifstream neobradjeniRacun(puniNaziv2.c_str());
	std::ofstream racunPoslijeObrade(puniNaziv.c_str());
	char buffer[100];
	neobradjeniRacun.get(buffer, 8);
	neobradjeniRacun.getline(buffer, 100);
	racunPoslijeObrade << buffer << "\n";
	neobradjeniRacun.get(buffer, 8);
	neobradjeniRacun.getline(buffer, 100);
	racunPoslijeObrade << buffer << "\n";
	/*
	Upisemo prve dve linije racuna(samo podatke od znacaja), odnosno ime i datum.
	*/
	int i = 0;
	while (neobradjeniRacun.getline(buffer, 100))
		i++;
	neobradjeniRacun.close();
	neobradjeniRacun.open(puniNaziv2.c_str());
	i = i + 2;
	std::cout << i << std::endl;
	/*
	Odredimo ukupan broj linija racuna koji se obradjuje
	*/
	for (int j = 0; j<i - 3; j++)
		neobradjeniRacun.getline(buffer, 100);
	/*
	Pozicioniramo se na pocetak trece otpozadi linije racuna
	se obradjuje, odnosno prije rijeci "Ukupno"
	*/
	neobradjeniRacun.get(buffer, 9);
	neobradjeniRacun.getline(buffer, 100);
	racunPoslijeObrade << buffer << "\n";
	neobradjeniRacun.get(buffer, 6);
	neobradjeniRacun.getline(buffer, 100);
	racunPoslijeObrade << buffer << "\n";
	neobradjeniRacun.get(buffer, 21);
	neobradjeniRacun.getline(buffer, 100);
	racunPoslijeObrade << buffer << "\n";
	/*
	Stavljamo posljednje tri linije racuna koji se obradjuje u obradjeni fajl
	Samo podaci od znacaja.Artikle zbog nepoznatog broja stavljamo posljednje
	u obradjeni racun.
	*/
	neobradjeniRacun.close();
	neobradjeniRacun.open(puniNaziv2.c_str());
	for (int j = 0; j<6; j++)
		neobradjeniRacun.getline(buffer, 100);
	i = i - 10;                             //Vrijednost je broj artikala
	char* pom;
	for (int j = 0; j<i; j++) {
		neobradjeniRacun.getline(buffer, 100);
		pom = formatiraj124(buffer);
		racunPoslijeObrade << pom << "\n";
		delete[] pom;

	}
}

void obradi_racun2(std::string stari_naziv, std::string novi_naziv) {
	std::ifstream racun(stari_naziv.c_str());
	std::ofstream obradjeni_racun(novi_naziv.c_str());
	char buffer[100];
	for (int i = 0; i < 5; i++)
		racun.getline(buffer, 100);
	racun.get(buffer, 8);
	racun.getline(buffer, 100);
	obradjeni_racun << buffer << "\n";
	int i = 0;
	while (racun.getline(buffer, 100))
		i++;
	i = i + 6;
	char buffer2[100];
	char buffer3[100];
	char buffer4[100];
	racun.close();
	racun.open(stari_naziv.c_str());
	for (int j = 0; j < i - 4; j++)
		racun.getline(buffer, 100);

	racun.get(buffer2, 9);
	racun.getline(buffer2, 100);
	racun.get(buffer3, 6);
	racun.getline(buffer3, 100);
	racun.get(buffer4, 21);
	racun.getline(buffer4, 100);
	racun.get(buffer, 8);
	racun.getline(buffer, 100);
	obradjeni_racun << buffer << "\n";
	obradjeni_racun << buffer2 << "\n";
	obradjeni_racun << buffer3 << "\n";
	obradjeni_racun << buffer4 << "\n";
	racun.close();
	racun.open(stari_naziv.c_str());
	for (int j = 0; j < 9; j++)
		racun.getline(buffer, 100);

	char* pom;
	for (int j = 9; j < i - 6; j++) {
		racun.getline(buffer, 100);
		pom = formatiraj124(buffer);
		obradjeni_racun << pom << '\n';
		delete[] pom;
	}

}
// OVO STO TREBA POPRAVITI JE DOLE U KOMENTARU

void obradi_racun4(std::string stari_naziv, std::string novi_naziv) {


std::ifstream racun(stari_naziv.c_str());
std::ofstream obradjeni_racun(novi_naziv.c_str());
char buffer[100];

racun.get(buffer, 8);
racun.getline(buffer, 100);
obradjeni_racun << buffer << '\n';
racun.get(buffer, 8);
racun.getline(buffer, 100);
obradjeni_racun << buffer << '\n';

int i = 0;
while (racun.getline(buffer, 100))
i++;
i = i + 2;
racun.close();
racun.open(stari_naziv.c_str());
for (int j = 0; j < i - 6; j++)
racun.getline(buffer, 100);
racun.get(buffer, 9);
racun.getline(buffer, 100);
obradjeni_racun << buffer << '\n';
racun.get(buffer, 6);
racun.getline(buffer, 100);
obradjeni_racun << buffer << '\n';
racun.getline(buffer, 100);
racun.get(buffer, 21);
racun.getline(buffer, 100);
obradjeni_racun << buffer << '\n';
racun.close();
racun.open(stari_naziv.c_str());
for (int j = 0; j < 7; j++)
racun.getline(buffer, 100);

char* pom;
for (int j = 9; j < i - 6; j++) {
racun.getline(buffer, 100);
pom = formatiraj124(buffer);
obradjeni_racun << pom << '\n';
delete[] pom;
}
}


void obradi_racun3(std::string stari_naziv, std::string novi_naziv) {
std::ifstream racun(stari_naziv.c_str());
std::ofstream obradjeni_racun(novi_naziv.c_str());
char buffer[100];
for (int i = 0; i < 2; i++)
racun.getline(buffer, 100);
racun.get(buffer, 8);
racun.getline(buffer, 100);
obradjeni_racun << buffer << "\n";
int i = 0;
racun.get(buffer, 8);
racun.getline(buffer, 100);
obradjeni_racun << buffer << "\n";

while (racun.getline(buffer, 100))
i++;
i = i + 4;

racun.close();
racun.open(stari_naziv.c_str());
for (int j = 0; j < i - 3; j++)
racun.getline(buffer, 100);
racun >> buffer;
racun >> buffer;
obradjeni_racun << buffer<<'\n';
racun >> buffer;
racun >> buffer;
obradjeni_racun << buffer<<'\n';
racun >> buffer;
racun >> buffer;
racun >> buffer;
racun >> buffer;
obradjeni_racun << buffer << '\n';


racun.close();
racun.open(stari_naziv.c_str());

for (int j = 0; j < 9; j++)
racun.getline(buffer, 100);
char pom[100];
int l, k = 0;
for (int j = 9; j < i - 5; j++) {
	//obradjeni_racun << "ala";
	racun.getline(pom, 100);
	//obradjeni_racun << pom<<'\n';
l = 0;
	//obradjeni_racun << "druze";
k = 0;
while (pom[l] != '\0') {
	if (pom[l] != '=') {
		if (pom[l - 1] == '=')buffer[k++] = '-';
		buffer[k++] = pom[l];
	}
l++;
}
buffer[k] = '\0';
	//obradjeni_racun << "je";
obradjeni_racun << buffer << '\n';

}
}
