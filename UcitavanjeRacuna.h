#pragma once
#include <vector>
#include <string>
using namespace std;

int tip_racuna(const char*); //std::string a; a.c_str()==const char* a;
void obradi_racun(const char*);
vector<string> imena_fajlova_u_folderu(string);
void ucitavanje_racuna();
inline bool ispravniPodaci(double cijena, double kolicina, double ukupno);
void provjeraRacuna(std::string);

