#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "windows.h"
#include "time.h"
#include <conio.h>
#include <iomanip>
#define getch() _getch()

using namespace std;

enum Bolesti : int
{
	Tumori = 1, BolestiNervnogSistema = 2, DusevniPoremecaji = 3, BolestiDisanje = 4
};

struct podaciOdoktorima
{
	string ime;
	string prezime;
	string profesija;
};

struct lijek {
	string ime;
	string proizvodjac;
	int rokTrajanja;
	int rokIsteka;
	string odjeljenje;
};


void rasporedPosjeta()
{
	cout << endl;
	cout << "\t\t" << "===============================================================================" << endl;
	cout << "\t\t" << "Dobro dosli na informativni centar nase bolnice." << endl;
	cout << "\t\t" << "U ovome prozoru mozete vidjeti koji su termini posjeta:" << endl;
	cout << "\t\t" << "===============================================================================" << endl;
	cout << "\t\t" << "Odijeljenje 1: 10:00 - 12:00" << endl;
	cout << "\t\t" << "Odijeljenje 2: 12:30 - 14:30" << endl;
	cout << "\t\t" << "Odijeljenje 3: 15:00 - 17:00" << endl;
	cout << "\t\t" << "===============================================================================" << endl;
	cout << "\t\t" << "Molimo Vas da prilikom svake posjete obavijestite recepciju o vasoj posjeti." << endl;
	cout << "\t\t" << "Neka pravila ponasanja koje morate da postujete prilikom posjete pacijenata su: " << endl;
	cout << "\t\t" << "1. Posjetiocima je strogo zabranjeno sjedenje na bolesnickim krevetima." << endl;
	cout << "\t\t" << "2. Prilikom termina posjete pusenje nije dozvoljeno ni pacijentima ni posjetiocima." << endl;
	cout << "\t\t" << "3. Djeci mladjoj od 7 godina strogo je zabranjen dolazak u posjetu bolesnicima." << endl;
	cout << "\t\t" << "==============================================================================" << endl;
	cout << "\t\t" << "Pritisnite ENTER za nastavak..." << endl;
	getchar();
	getchar();

}


void upisUDatotekuPacijenata(string name, string prezime, string bolest, int brojKreveta, int brojDanaUBolnici, char izbor, char uputnica)
{
	ofstream out;
	ofstream pacijenti;
	pacijenti.open("Pacijenti.txt", ios::app);
	out.open("appointment.dat", ios::app);

	if (out) {
		out << izbor << ":" << name.c_str() << prezime.c_str() << bolest.c_str() << "\n";
		out.close();
		if (uputnica == 'Y' || uputnica == 'y')
		{
			cout << "---------------------------------------------" << endl;
			cout << "Termin koji je bio zakazan za : " << (izbor - 65) + 9 << " je obavljen uspjesno !!";
		}
		else if (uputnica == 'N' || uputnica == 'n')
		{
			cout << "------------------------------------------------------------------" << endl;
			cout << "\n Termin koji je bio zakazan za : " << (izbor - 65) + 9 + 2 << "  je obavljen uspjesno (bez uputnice termin koji ste zakazali ste morali naplatiti 10 KM)";
		}
			

	}
	if (pacijenti)
	{
		pacijenti << name.c_str() << " " << prezime.c_str() << " " << bolest.c_str() << " " << brojKreveta << " " << brojDanaUBolnici << "\n";
		pacijenti.close();
	}
	else
	{
		cout << "\n Greska tokom spremanja termina !";
	}
}

struct Pacijenti {
	string Ime;
	string Prezime;
	string Bolest;
	string odijeljenje;
	string lijek;
	int brojKreveta;
	int pretpostavka;

	void Ucitavanje(ifstream& datoteka, Pacijenti* p)
	{
		while (datoteka >> p->Ime >> p->Prezime >> p->Bolest >> p->brojKreveta >> p->pretpostavka) {
			p++;
		}
	}
	void IspisSvi(Pacijenti* p, int n) {
		cout << endl;
		cout << "\t\t\t\t\t";
		cout << "Detalji svih pacijenata u bolnici: " << endl;
		for (int i = 0; i < n; i++) {
			cout << "\t\t\t\t";
			cout << "--------------------------------------------------------" << endl;
			cout << "\t\t\t\t";
			cout << "Ime pacijenta: " << p[i].Ime << endl;
			cout << "\t\t\t\t";
			cout << "Prezime pacijenta: " << p[i].Prezime << endl;
			cout << "\t\t\t\t";
			cout << "Diagnosticirana bolest: " << p[i].Bolest << endl;
			if (p[i].Bolest == "Depresija") {
				cout << "\t\t\t\t";
				cout << "Pacijent se nalazi na odijeljenju za dusevne bolesti" << endl;
			}
			if (p[i].Bolest == "Nervna") {
				cout << "\t\t\t\t";
				cout << "Pacijent se nalazi na odijeljenju za nervne bolesti " << endl;
			}
			if (p[i].Bolest == "Tumor") {
				cout << "\t\t\t\t";
				cout << "Pacijent se nalazi na odijeljenju za radioterapiju " << endl;
			}
			cout << "\t\t\t\t";
			cout << "Broj kreveta: " << p[i].brojKreveta << endl;
			cout << "\t\t\t\t";
			cout << "Pretpostavlja se da ce ovaj pacijent boraviti u bolnici: " << p[i].pretpostavka << endl;
			cout << "\t\t\t\t";
			cout << "---------------------------------------------------------" << endl;
		}

	}

};

int BrojPacijenata(ifstream& datoteka)
{
	string temp;
	int brojLinija = 0;

	while (getline(datoteka, temp))
	{
		brojLinija++;
	}
	return brojLinija;
}
int BrojLijekovaDatoteke(ifstream& datoteka)
{
	string temp;
	int brojLinija = 0;

	while (getline(datoteka, temp))
	{
		brojLinija++;
	}
	return brojLinija;
}
Pacijenti ispisPacijenata() {
	int n = 0;
	ifstream datoteka;
	datoteka.open("Pacijenti.txt");
	if (datoteka.fail()) {
		cout << "Greska! " << endl;
	}
	Pacijenti* pd = 0;
	n = BrojPacijenata(datoteka);
	datoteka.clear();
	datoteka.seekg(ios::beg);
	pd = new Pacijenti[n];
	pd->Ucitavanje(datoteka, pd);
	pd->IspisSvi(pd, n);
	cout << "\t\t\t\t";
	cout << "Pritisnite ENTER za nastavak...";
	getchar();
	getchar();
	return *pd;
}


void unosLijeka() {
	lijek rez[100];
	int brojac = 0;
	cout << "\t\t\t\t\t\t";
	cout << "Koliko lijekova zelite unijeti" << endl;
	cout << "\t\t\t\t\t\t";
	cin >> brojac;
	cout << "\t\t\t\t\t\t";
	for (int i = 0; i < brojac; i++) {
		cout << endl;
		cout << "\t\t\t\t\t\t" <<"----------------------------" << endl;
		cout << "\t\t\t\t\t\t";
		cout << "Unesi ime lijeka:" << endl;
		cout << "\t\t\t\t\t\t";
		cin >> rez[i].ime;
		cout << "\t\t\t\t\t\t" << "----------------------------" << endl;
		cout << "\t\t\t\t\t\t";
		cout << "Unesi proivodjaca:" << endl;
		cout << "\t\t\t\t\t\t";
		cin >> rez[i].proizvodjac;
		cout << "\t\t\t\t\t\t" << "----------------------------" << endl;
		cout << "\t\t\t\t\t\t";
		cout << "Unesi rok trajanja:" << endl;
		cout << "\t\t\t\t\t\t";
		cin >> rez[i].rokTrajanja;
		cout << "\t\t\t\t\t\t" << "----------------------------" << endl;
		cout << "\t\t\t\t\t\t";
		cout << "Unesi datum isteka lijeka:" << endl;
		cout << "\t\t\t\t\t\t";
		cin >> rez[i].rokIsteka;
		cout << "\t\t\t\t\t\t" << "----------------------------" << endl;
		cout << "\t\t\t\t\t\t";
		cout << "Odjeljenja u bolnici:" << endl;
		cout << "\t\t\t\t\t\t" <<"1. Odjeljenje za radioterapiju (ORD)" << endl;
		cout << "\t\t\t\t\t\t" <<"2. Odjeljenje za nervne bolesti (ONB)" << endl;
		cout << "\t\t\t\t\t\t" <<"3. Odjeljenje za dusevne bolesti (ODB)" << endl;
		cout << "\t\t\t\t\t\t" << "Za koje odjeljenje je ovaj lijek potreban (upisite skracenicu odjeljenja): ";
		cout << "\t\t\t\t\t\t";
		cin >> rez[i].odjeljenje;
		cout << "\t\t\t\t\t\t";
	}

	ofstream fout("lijekovi.txt", ios::app);

	if (fout.fail())
	{
		cout << "Ne postojeca datoteka";
		exit(1);
	}
	else {
		for (int i = 0; i < brojac; i++) {
			fout << rez[i].ime << " " << rez[i].proizvodjac << " " << rez[i].rokTrajanja << " " << rez[i].rokIsteka << " " << rez[i].odjeljenje << endl;
		}
	}
	cout << "Pritisnite ENTER za izlazak...";
	getchar();
	getchar();

}
lijek pregled_lijekova() {
	int brojlijekova = 0;
	int noviBrojLijekova = 0;
	int broj_isteknutog_roka = 0;
	ifstream fin("lijekovi.txt");
	ifstream novi("brojlijekova.txt");
	int n = BrojLijekovaDatoteke(fin);
	lijek* var = 0;
	lijek noviBrojLijeka[100];
	fin.clear();
	fin.seekg(ios::beg);
	var = new lijek[n];
	if (fin.fail())
	{
		cout << "Ne postojeca datoteka";
		exit(1);
	}
	else {
	
		while (fin >> var[brojlijekova].ime >> var[brojlijekova].proizvodjac >> var[brojlijekova].rokTrajanja >> var[brojlijekova].rokIsteka >> var[brojlijekova].odjeljenje) {
			brojlijekova++;
		}
		cout << "\t\t\t\t\t\t";
		for (int i = 0; i < 30; i++) {
			cout << char(223);
		}
		cout << endl;
		cout << "\t\t\t\t\t\t";
		cout << "Lijekovi koje bolnica posjeduje su:" << brojlijekova << endl;
		cout << "\t\t\t\t\t\t";
		for (int i = 0; i < brojlijekova; i++) {
			cout << "Ime lijeka: " << var[i].ime << endl;
			cout << "\t\t\t\t\t\t";
			cout << "Proizvodjac lijeka: " << var[i].proizvodjac << endl;
			cout << "\t\t\t\t\t\t";
			cout << "Rok trajanja lijeka: " << var[i].rokTrajanja << endl;
			cout << "\t\t\t\t\t\t";
			cout << "Rok isteka lijeka: " << var[i].rokIsteka << endl;
			cout << "\t\t\t\t\t\t";
			cout << "Odjeljenje za koje je ovaj lijek potreban: ";
			if (var[i].odjeljenje == "ORD")
			{
				cout <<"Odjeljenje za radioterapiju" << endl;
			}
			else if (var[i].odjeljenje == "ONB")
			{
				cout << "Odjeljenje za nervne bolesti" << endl;
			}
			else if (var[i].odjeljenje == "ODB")
			{
				cout << "Odjeljenje za dusevne bolesti" << endl;
			}
			cout << "\t\t\t\t\t\t";
		}

		for (int i = 0; i < brojlijekova; i++) {
			if (var[i].rokIsteka >= 4 && var[i].rokIsteka <= 5) {
				broj_isteknutog_roka++;
			}
		}
		cout << "Isteknutih ima: " << broj_isteknutog_roka << endl;
	}
	cout << "\t\t\t\t\t\t";
	for (int i = 0; i < 30; i++) {
		cout << char(223);
	}
	cout << endl;
	cout << "\t\t\t\t\t\t";
	cout << "Pritisnite ENTER za izlazak...";
	getchar();
	getchar();
	return *var;
}

void meniLijekova()
{
	int odabir;
	lijek meni;
	cout << endl;
	cout << "\t\t\t\t\t\t";
	cout << "1. Unesi lijek" << endl;
	cout << "\t\t\t\t\t\t";
	cout << "2. Pregled lijekova" << endl;
	cout << "\t\t\t\t\t\t";
	cout << "Odaberi MENI: ";
	cin >> odabir;


	switch (odabir) {
	case 1: {
		unosLijeka();
		break;
	}
	case 2: {
		pregled_lijekova();
		break;
	}
	}
}

int upisLijekovaDoktori(int count)
{
	string ime;
	int karakterPassworda = 0;
	string sifra = "";
	if (count == 3)
	{
		cout << endl;
		cout << "\t\t\t\t";
		cout << "--------------------------------------------------" << endl;
		cout << "\t\t\t\t";
		cout << "   Dobrodosli u sistem za unos lijekova, doktore" << endl;
		cout << "\t\t\t\t";
		cout << "--------------------------------------------------" << endl;
		cout << "\t\t";
		cout << "Prije nego sto zapocnete sa procesom unosa lijekova, molimo Vas unesite vase podatke" << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "\t\t\t\t\t\t";
		for (int i = 0; i < 20; i++) {
			cout << char(95);
		}
		cout << endl;
		cout << "\t\t\t\t\t\t";
		cout << "Unesite Vas username: " << endl;
		cout << "\t\t\t\t\t\t";
		cin >> ime;
		cout << "\t\t\t\t\t\t";
		for (int i = 0; i < 20; i++) {
			cout << char(95);
		}
		cout << "\t\t\t\t\t\t";
		cout << endl;
		cout << "\t\t\t\t\t\t";
		cout << "Vasa sifra je: " << endl;
		cout << "\t\t\t\t\t\t";
	}
	else if (count == 2 || count == 1)
	{
		int karakterPassworda = 0;
		cout << "\t\t\t\t\t\t";
		cout << "Ukucajte ponovo svoje ime: ";
		cin >> ime;
		cout << "\t\t\t\t\t\t";
		cout << "Ukucajte ponovo svoju sifru: ";

	}
	if (count == 0)
	{
		cout << "\t\t\t\t\t\t";
		cout << "Pogrijesili ste vise nego sto treba, program se gasi" << endl;
		cout << "\t\t\t\t\t\t";
		cout << "Pritisnite ENTER za izlazak...";
		getchar();
		getchar();
		return 0;
	}
	else
	{
		while (karakterPassworda = getch())
		{
			if (karakterPassworda == 13)
			{

				if ((sifra == "meris" || sifra == "samed" || sifra == "ahmed") && (ime == "Meris123" || ime == "Samed123" || ime == "Ahmed123")) {
					cout << endl;
					cout << "\t\t\t\t\t" << " ======================================" << endl;
					cout << "\t\t\t\t\t\t\t" << endl;
					system("cls");
					cout << "\t\t\t\t\t";
					cout << "	5. Pregled lijekova			" << endl;
					cout << "\t\t\t\t\t";
					for (int i = 0; i < 35; i++) { cout << char(254); }
					cout << endl;
					cout << "\t\t\t\t\t" << "        Dobrodosli " << ime << endl;
					cout << "\t\t\t\t\t" << "      -----------------------" << endl;
					meniLijekova();
					break;
				}
				else
				{
					cout << endl;
					cout << "\t\t\t\t";
					cout << "  Pogresno unesen username i sifra, pokusajte ponovo! \n\n";
					cout << "\t\t\t\t\t\t";
					cout << "Imate " << count - 1 << " pokusaja" << endl;
					sifra = "";
					upisLijekovaDoktori(count - 1);
					break;

				}

			}
			else if (karakterPassworda == 8) { //provjera karaktera ako je korisnik pritisnuo BACKSPACE 
				if (sifra.length() > 0) {
					cout << "\b \b"; //brisanje duzine maske
					sifra.erase(sifra.length() - 1);
				}
			}
			else {
				cout << "*";
				sifra += karakterPassworda; //svi karakteri dodjeljeni varijabli sifra
			}
		}

	}
	return 0;
}


struct knjizica
{
	string ime;
	string prezime;
	long long int JMBG;
	string mjesto;
};

void zdrastvenaKnjizica()
{
	system("cls");
	ofstream upisKnjizica("knjizica.txt", ios::app);
	knjizica upis[100];
	cout << "\t\t\t\t\t";
	for (int i = 0; i < 40; i++) {
		cout << char(254);
	}
	cout << endl;
	for (int i = 0; i < 1; i++)
	{
		cout << "\t\t\t\t\t\t";
		cout << "Unesite svoje ime: " << endl;
		cout << "\t\t\t\t\t\t";
		cin >> upis[i].ime;
		cout << "\t\t\t\t\t\t";
		cout << endl;
		cout << "\t\t\t\t\t";
		for (int i = 0; i < 40; i++) {
			cout << char(254);
		}cout << endl;
		cout << "\t\t\t\t\t\t";
		cout << "Unesite svoje prezime: " << endl;
		cout << "\t\t\t\t\t\t";
		cin >> upis[i].prezime;
		cout << "\t\t\t\t\t\t";
		cout << endl;
		cout << "\t\t\t\t\t";
		for (int i = 0; i < 40; i++) {
			cout << char(254);
		}cout << endl;
		cout << "\t\t\t\t\t\t";
		cout << "Unesite svoj JMBG: " << endl;
		cout << "\t\t\t\t\t\t";
		cin >> upis[i].JMBG;
		cout << "\t\t\t\t\t";
		for (int i = 0; i < 40; i++) {
			cout << char(254);
		}cout << endl;
		cout << "\t\t\t\t\t\t";
		cout << "Unesite mjesto rodjenja: " << endl;
		cout << "\t\t\t\t\t\t";
		cin >> upis[i].mjesto;
		cout << "\t\t\t\t\t";
		for (int i = 0; i < 40; i++) {
			cout << char(254);
		}cout << endl;
		cout << endl;


	}

	for (int i = 0; i < 1; i++)
	{
		cout << endl;
		upisKnjizica << upis[i].ime << " " << upis[i].prezime << " " << upis[i].JMBG << " " << upis[i].mjesto << endl;

	}
	cout << "\t\t\t\t\t";
	cout << "	 Pritisnite ENTER za nastavak...";
	getchar();
	getchar();
}

int detaljiODoktorima()
{
	system("cls");
	ifstream citanjeDoktora;

	citanjeDoktora.open("citanjedoktora.txt");

	if (citanjeDoktora.fail())
	{
		cout << "Nepostojeca datoteka";
		exit(1);
	}
	knjizica knjizicePacijenata[100];
	podaciOdoktorima doktori[100];
	int brojDoktora = 0;
	int brojKnjizica = 0;

	while (citanjeDoktora >> doktori[brojDoktora].ime >> doktori[brojDoktora].prezime >> doktori[brojDoktora].profesija)
	{
		brojDoktora++;
	}

	cout << "\t\t\t\t\t";
	cout << "----- Imena doktora i njihove profesije -----" << endl;
	cout << "\t\t\t\t\t";
	for (int i = 0; i < 45; i++) {
		cout << char(254);
	}
	cout << endl;

	citanjeDoktora.seekg(0);
	for (int i = 0; i < brojDoktora; i++)
	{
		cout << "\t\t\t\t\t\t";
		cout << "Ime " << i + 1 << ". doktora: " << doktori[i].ime << endl;
		cout << "\t\t\t\t\t\t";
		cout << "Prezime " << i + 1 << ". doktora: " << doktori[i].prezime << endl;
		cout << "\t\t\t\t\t\t";
		cout << "Profesija " << i + 1 << ". doktora: " << doktori[i].profesija << endl;
		cout << "\t\t\t\t\t";
		cout << "--------------------------------------------" << endl;
		cout << endl;
	}
	cout << "\t\t\t\t\t";
	for (int i = 0; i < 45; i++) {
		cout << char(254);
	}
	cout << endl;
	cout << "\t\t\t\t\t\t";
	cout << "Pritisnite ENTER za nastavak..";

	getchar();
	getchar();

	return 0;
}
int zakazatiTermin()
{
	cout << endl;
	cout << "\t\t\t\t\t";
	cout << "----- Molimo da zakazete Vas termin ---- \n";
	cout << "\t\t\t\t\t";
	cout << "     ----- Slobodni termini ---- \n";


	ifstream citanje;
	ofstream pisanje;
	pisanje.open("appointment.dat", ios::trunc);
	char slova[13] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M'};
	char novaSlova[13];

	int i = 0;
	while (i < 13) {
		int temp = rand() % 13 + 3;
		novaSlova[i] = slova[temp];
		i++;
	}

	for (i = 0; i < 6; i++)
	{
			pisanje << novaSlova[i] << endl;
		    
	}
	citanje.open("appointment.dat");

	int arr[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
	int pronadjenTermin = 0;

	if (citanje)
	{
		string linija;
		char termin = 'A';
		int i = 9;

		while (getline(citanje, linija)) {
			char temp = linija[0];
			int index = (temp - 65);
			arr[index] = 1;
			pronadjenTermin = 1;
		}
		if (pronadjenTermin == 1)
		{
			cout << "\t\t\t\t\t";
			cout << "    Termini sortirani po satima :" << endl;
			char termin = 'A';
			int sati = 9;
			for (int i = 0; i <= 12; i++)
			{
				if (i == 0) {
					if (arr[i] == 0) {
						cout << "\t\t\t\t\t\t";
						cout << termin << "-> 0" << sati << " - Slobodan" << endl;
					}

					else {
						cout << "\t\t\t\t\t\t";
						cout << termin << "-> 0" << sati << " - Zauzet" << endl;
					}

				}

				else
				{
					if (arr[i] == 0) {
						cout << "\t\t\t\t\t\t";
						cout <<  termin << "->" << sati << " - Slobodan" << endl;
					}

					else {
						cout << "\t\t\t\t\t\t";
						cout <<  termin << "->" << sati << " - Zauzet" << endl;
					}

				}
				sati++; termin++;
			}

		}

		citanje.close();
	}
	if (pronadjenTermin == 0) { 
		cout << "\t\t\t\t\t";
		cout << "  Svi termini su slobodni za iduce sate :";
		char termin = 'A';
		cout << "\t\t\t\t\t\t";
		for (int i = 9; i <= 21; i++)
		{
			if (i == 9) {
				cout << "\t\t\t\t\t\t";
				cout << termin << "   -> 0" << i << "   - Slobodan";
			}
			else {
				cout << "\t\t\t\t\t" << endl;
				cout << "\t\t\t\t\t\t" << termin << "   -> " << i << "   - Slobodan";
			}
			termin++;

		}

	}

	char izbor;
	cout << "\n\n Molimo Vas upisite naziv termina koji je oznacen sa velikim slovom abecede : ";
	cin >> izbor;
	cout << "--------------------------------------------------" << endl;
	if (!(izbor >= 'A' && izbor <= 'Z'))
	{
		cout << "\n Greska! Pogresan odabir";
		cout << "\n Molimo odaberite isparavan termin iz menija A-Z";
		cout << "\n Pritisnite ENTER za nastavak";
		getchar();
		getchar();
		system("cls");
		zakazatiTermin();
	}

	int index = (izbor - 65);
	int zakazan = 1;
	if (arr[index] == 0)
		zakazan = 0;

	if (zakazan == 1)
	{
		cout << "\n Greska! Termin je vec zakazan u tom vremenskom periodu.";
		cout << "\n Molimo odaberite drugi termin !!";
		cout << "\n Pritisnite ENTER za nastavak !!";
		getchar();
		getchar();
		system("cls");
		zakazatiTermin();
	}
	ifstream citanjeKnjizica;
	ifstream citanje1;
	ifstream fin;
	fin.open("lijekovi.txt");
	citanjeKnjizica.open("knjizica.txt");
	citanje1.open("citanjedoktora.txt");
	int brojDoktora = 0;
	int brojKnjizica = 0;
	int brojlijekova = 0;
	lijek var[100];
	podaciOdoktorima doktoriNovi[100];
	knjizica knjizicePacijenata[100];
	int j = 0;
	while (citanje1 >> doktoriNovi[brojDoktora].ime >> doktoriNovi[brojDoktora].prezime >> doktoriNovi[brojDoktora].profesija)
	{
		brojDoktora++;
	}
	while (citanjeKnjizica >> knjizicePacijenata[brojKnjizica].ime >> knjizicePacijenata[brojKnjizica].prezime >> knjizicePacijenata[brojKnjizica].JMBG >> knjizicePacijenata[brojKnjizica].mjesto)
	{
		brojKnjizica++;

	}
	while (fin >> var[brojlijekova].ime >> var[brojlijekova].proizvodjac >> var[brojlijekova].rokTrajanja >> var[brojlijekova].rokIsteka >> var[brojlijekova].odjeljenje) {
		brojlijekova++;
	}
	string name, prezime;
	string ime1, prezime1;
	Bolesti TumorBolesti;
	TumorBolesti = Tumori;
	Bolesti NervnogSistema;
	NervnogSistema = BolestiNervnogSistema;
	Bolesti Dusevni;
	Dusevni = DusevniPoremecaji;
	Bolesti BolestiSistemaZaDisanje;
	BolestiSistemaZaDisanje = BolestiDisanje;
	int odabranaBolest;
	char uputnica;
	char knjizicaValidnost;
	char sistem;
	cout << "\n Upisite svoje ime: ";
	cin >> name;
	cout << "--------------------------" << endl;
	cout << "\n Upisite svoje prezime: ";
	cin >> prezime;
	cout << "-------------------------------------------------------------------------" << endl;
	cout << "Da li imate uputnicu ? (Y - ako imate, N - ako nemate): ";
	cin >> uputnica;
	cout << "-------------------------------------------------------------------------" << endl;
	cout << "Da li imate knjizicu? (Y - ako imate , N - ako nemate): ";
	cin >> knjizicaValidnost;
	cout << "-------------------------------------------------------------------------" << endl;
	if (knjizicaValidnost == 'Y' || knjizicaValidnost == 'y')
	{
		string ime2;
		string prezime2;
		long long int JMBG2;
		string mjesto;
		cout << "Da li ste unijeli prethodno svoju knjizicu u nas elektronski sistem (Y - ako jeste , N - ako niste): ";
		cin >> sistem;
		cout << endl;
		if (sistem == 'Y' || sistem == 'y')
		{
			cout << "---- Sada cemo provjeriti Vasu knjizicu, molimo pricekajte par trenutaka ----" << endl;
			Sleep(5000);
			system("cls");
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "Molimo Vas, unesite ponovo svoje podatke kako bi provjerili vjerodostojnost istih " << endl;
			cout << "--------------------------------" << endl;
			cout << "Unesite Vase ime: ";
			cin >> ime2;
			cout << "--------------------------------" << endl;
			cout << "Unesite Vase prezime: ";
			cin >> prezime2;
			cout << "--------------------------------" << endl;
			cout << "Unesite Vas JMBG: ";
			cin >> JMBG2;
			cout << "--------------------------------" << endl;
			cout << "Unesite Vase mjesto rodjenja: ";
			cin >> mjesto;
			bool success1 = false;
			do
			{
				success1 = find_if(knjizicePacijenata, knjizicePacijenata + brojKnjizica,
					[&](const knjizica& d)
					{
						return d.ime == ime2 && d.prezime == prezime2 && d.JMBG == JMBG2 && d.mjesto == mjesto;
					}) != knjizicePacijenata + brojKnjizica;

				if (not success1)
				{
					cout << "Vasi unijeti podaci nisu validni i ne poklapaju se sa nasim podacima iz sistema ! " << endl;
					cout << "\n Pritisnite ENTER za nastavak...";
					getchar();
					getchar();
					return 0;
				}
			} while (not success1);
		}
		else
		{
			cout << "Molimo vas unesite podatke o Vasoj knjizici u nas elektorniski sistem" << endl;
			zdrastvenaKnjizica();
			cout << "\n Pritisnite ENTER za nastavak..";
            
			getchar();
			getchar();

			return 0;
		}

	}
	else if (knjizicaValidnost == 'N' || knjizicaValidnost == 'n')
	{
		cout << "Bez knjizice ne mozete zakazati termin kod doktora. zao nam je." << endl;
		cout << "\n Pritisnite ENTER za nastavak..";

		getchar();
		getchar();

		return 0;
	}
	cout << "\t\t\t\t" << "--------------------------------" << endl;
	cout << "\t\t\t\t" <<"       Molimo sacekajte" << endl;
	cout << "\t\t\t\t" <<"---------------------------------" << endl;
	Sleep(5000);
	system("cls");
	cout << "Vasi podaci se poklapaju sa podacima koji ste unijeli u sistem. Mozete nastaviti dalje" << endl;
	cout << "--------------------------------------------------------------------------------------" << endl;
	cout << "Na osnovu primjecenih simptoma, odaberite grupu za vasu bolest: " << endl;
	cout << TumorBolesti << ". Tumori" << endl;
	cout << NervnogSistema << ". Bolesti nervnog sistema " << endl;
	cout << Dusevni << ". Dusevni " << endl;
	cout << BolestiSistemaZaDisanje << ". Bolesti sistema za disanje " << endl;
	cout << "----------------------------------------------------------" << endl;
	cout << "Odaberite grupu: ";
	cin >> odabranaBolest;
	if (odabranaBolest == TumorBolesti)
	{
		cout << "\nIme i prezime dostupnih doktora na osnovu grupe: " << endl;
		cout << "--------------------------------------" << endl;
		string temp1;
		string temp2;
		citanje1.clear();
		citanje1.seekg(0);
		for (int i = 0; i < brojDoktora; i++)
		{

			if (doktoriNovi[i].profesija == "Hirurg")
			{
				cout << "Ime " << i + 1 << ". doktora: " << doktoriNovi[i].ime << endl;
				cout << "Prezime " << i + 1 << ". doktora: " << doktoriNovi[i].prezime << endl;
				cout << "Profesija " << i + 1 << ". doktora: " << doktoriNovi[i].profesija << endl;
				cout << "------------------------------------------" << endl;
				cout << endl;
			}

		}

		cout << "Unesite ime doktora koji zeli da Vas lijeci: ";
		cin >> ime1;
		cout << "-------------------------------------------" << endl;
		cout << "Unesite prezime doktora koji zeli da Vas lijeci: ";
		cin >> prezime1;
		cout << "-------------------------------------------" << endl;
		bool success = false;
		do
		{
			success = find_if(doktoriNovi, doktoriNovi + brojDoktora,
				[&](const podaciOdoktorima d)
				{
					return d.ime == ime1 && d.prezime == prezime1;
				}) != doktoriNovi + brojDoktora;

			if (not success)
			{
				cout << "Ne postoji unijeto ime i prezime doktora. Ukucajte ponovo: ";
				cin >> ime1 >> prezime1;
			}
		} while (not success);
		system("cls");
		int brojDana;
		char prijavaDoktora;
		char stanje;
		char simptomi;
		cout << "----------------------------------------------------------------------------" << endl;
		cout << "Sada cemo Vam postaviti nekoliko pitanja vezanih za Vase primjecene simptome" << endl;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "1. Koliko dana primjecujete svoje simptome:  ";
		cin >> brojDana;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "2. Da li ste se javili doktoru kada ste primjetili simptome tumora (Y - za da || N - za ne): ";
		cin >> prijavaDoktora;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "3. Da li je Vase stanje pogorsano sto se tice problema sa tumorom u zadnjih par dana (Y - za da || N - za ne): ";
		cin >> stanje;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "4. Da li ste imali problema sa gutanjem, mokrenjem, cirom, ili nekom ranom koja ne zacjeljuje (Y - za da || N - za ne):";
		cin >> simptomi;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << endl;
		cout <<"\t\t\t\t" << "Molimo sacekajte rezultate nalaza" << endl;
		Sleep(5000);
		string bolest = "Tumor";
		int brojDanaUBolnici = rand() % 10 + 1;
		int brojKreveta = rand() % 100 + 1;
		if (prijavaDoktora == 'Y' && stanje == 'Y' && simptomi == 'Y')
		{ 
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "Na osnovu analize doktora procjenili smo da je potrebno da ostanete " << brojDanaUBolnici << ". dana u bolnici" << endl;
			cout << "Vas broj kreveta u Odjeljenju za radioterapiju je " << brojKreveta;
			cout << "-------------------------------------------------------------------------" << endl;
			upisUDatotekuPacijenata(name, prezime, bolest, brojKreveta, brojDanaUBolnici, izbor, uputnica);
		}
		else
		{
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "Na osnovu analize doktora procjenili smo da Vas boravak u nasoj bolnici nije potreban, te da cemo Vam preporuciti da samo pijete lijekove ";
			cout << "Lijekove koje morate koristiti su: ";
			for (int i = 0; i < brojlijekova; i++)
			{
				if (var[i].odjeljenje == "ORD")
					cout << var[i].ime << endl;
			}

		}

	}
	else if (odabranaBolest == NervnogSistema)
	{
		cout << "\nIme i prezime dostupnih doktora na osnovu grupe: " << endl;
		cout << "--------------------------------------" << endl;
		string temp1;
		string temp2;
		citanje1.clear();
		citanje1.seekg(0);
		for (int i = 0; i < brojDoktora; i++)
		{
			if (doktoriNovi[i].profesija == "Neurohirurg")
			{
				cout << "Ime " << i + 1 << ". doktora: " << doktoriNovi[i].ime << endl;
				cout << "Prezime " << i + 1 << ". doktora: " << doktoriNovi[i].prezime << endl;
				cout << "Profesija " << i + 1 << ". doktora: " << doktoriNovi[i].profesija << endl;
				cout << "------------------------------------------" << endl;
				cout << endl;
			}

		}
		cout << "-----------------------------------------------" << endl;
		cout << "Unesite ime doktora koji zeli da Vas lijeci: ";
		cin >> ime1;
		cout << "-----------------------------------------------" << endl;
		cout << "Unesite prezime doktora koji zeli da Vas lijeci: ";
		cin >> prezime1;
		cout << "-----------------------------------------------" << endl;
		bool success = false;
		do
		{
			success = find_if(doktoriNovi, doktoriNovi + brojDoktora,
				[&](const podaciOdoktorima d)
				{
					return d.ime == ime1 && d.prezime == prezime1;
				}) != doktoriNovi + brojDoktora;

			if (not success)
			{
				cout << "Ne postoji unijeto ime i prezime doktora. Ukucajte ponovo: ";
				cin >> ime1 >> prezime1;
			}
		} while (not success);
		system("cls");
		int brojDana;
		char prijavaDoktora;
		char stanje;
		char simptomi;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "Sada cemo Vam postaviti nekoliko pitanja vezanih za Vase primjecene simptome" << endl;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "1. Koliko dana primjecujete svoje simptome:  ";
		cin >> brojDana;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "2. Da li ste se javili doktoru kada ste primjetili simptome bolesti nervnog sistema (Y - za da || N - za ne): ";
		cin >> prijavaDoktora;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "3. Da li se Vase stanje pogorsalo u zadnjih par dana (Y - za da || N - za ne): ";
		cin >> stanje;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "4. Da li ste imali problema sa osjetljivosti na svjetlost, nemirom, bolom u vratu, poremacaju govora ili slicno (Y - za da || N - za ne): ";
		cin >> simptomi;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "\t\t\t\t\t" << "Molimo sacekajte za rezultat nalaza" << endl;
		cout << endl;
		Sleep(5000);
		string bolest = "Nervna";
		int brojDanaUBolnici = rand() % 10 + 1;
		int brojKreveta = rand() % 100 + 1;
		if (prijavaDoktora == 'Y' && stanje == 'Y' && simptomi == 'Y')
		{
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "Na osnovu analize doktora procjenili smo da je potrebno da ostanete " << brojDanaUBolnici << ". dana" << endl;
			cout << "Vas broj kreveta u Odjeljenju za nervne bolesti je " << brojKreveta;
			cout << "-------------------------------------------------------------------------" << endl;
			upisUDatotekuPacijenata(name, prezime, bolest, brojKreveta, brojDanaUBolnici, izbor, uputnica);
		}
		else
		{
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "Na osnovu analize doktora procjenili smo da Vas boravak u nasoj bolnici nije potreban, te da cemo Vam preporuciti da samo pijete lijekove ";
			cout << "Lijekove koje morate koristiti su: ";
			for (int i = 0; i < brojlijekova; i++)
			{
				if (var[i].odjeljenje == "ONB")
				{
					cout << var[i].ime << endl;
				
				}
			
			}

		}
	}
	else if (odabranaBolest == Dusevni)
	{
		cout << "\nIme i prezime dostupnih doktora na osnovu grupe: " << endl;
		cout << "--------------------------------------" << endl;
		string temp1;
		string temp2;
		citanje1.clear();
		citanje1.seekg(0);
		for (int i = 0; i < brojDoktora; i++)
		{
			if (doktoriNovi[i].profesija == "Psiholog")
			{
				cout << "Ime " << i + 1 << ". doktora: " << doktoriNovi[i].ime << endl;
				cout << "Prezime " << i + 1 << ". doktora: " << doktoriNovi[i].prezime << endl;
				cout << "Profesija " << i + 1 << ". doktora: " << doktoriNovi[i].profesija << endl;
				cout << "------------------------------------------" << endl;
				cout << endl;
			}

		}
		cout << "------------------------------------------------" << endl;
		cout << "Unesite ime doktora koji zeli da Vas lijeci: ";
		cin >> ime1;
		cout << "------------------------------------------------" << endl;
		cout << "Unesite prezime doktora koji zeli da Vas lijeci: ";
		cin >> prezime1;
		cout << "-----------------------------------------------" << endl;
		bool success = false;
		do
		{
			success = find_if(doktoriNovi, doktoriNovi + brojDoktora,
				[&](const podaciOdoktorima d)
				{
					return d.ime == ime1 && d.prezime == prezime1;
				}) != doktoriNovi + brojDoktora;

			if (not success)
			{
				cout << "Ne postoji unijeto ime i prezime doktora. Ukucajte ponovo: ";
				cin >> ime1 >> prezime1;
			}
		} while (not success);
		system("cls");
		int brojDana;
		char prijavaDoktora;
		char stanje;
		char simptomi;
		char pomoc;
		ifstream fin;
		fin.open("lijekovi.txt");
		int brojlijekova = 0;
		lijek var[100];
		while (fin >> var[brojlijekova].ime >> var[brojlijekova].proizvodjac >> var[brojlijekova].rokTrajanja >> var[brojlijekova].rokIsteka) {
			brojlijekova++;
		}
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "Sada cemo Vam postaviti nekoliko pitanja vezanih za Vase primjecene simptome" << endl;
		cout << "1. Koliko dana primjecujete svoje simptome:  ";
		cin >> brojDana;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "2. Da li ste se javili doktoru kada ste primjetili simptome depresije (Y - za da || N - za ne): ";
		cin >> prijavaDoktora;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "3. Da li se Vasa depresija pogorsala u zadnjih par dana (Y - za da || N - za ne): ";
		cin >> stanje;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "4. Da li ste primjetili promjene u ponasanju tokom depresije (Y - za da || N - za ne):  ";
		cin >> simptomi;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "5. Jeste li pronasli pomoc u krugu porodice (Y - za da || N - za ne): ";
		cin >> pomoc;
		cout << "-------------------------------------------------------------------------" << endl;
		cout << "\t\t\t\t" <<"Molimo sacekajte za rezultat nalaza" << endl;
		Sleep(5000);
		string bolest = "Depresija";
		int brojDanaUBolnici = rand() % 30 + 1;
		int brojKreveta = rand() % 100 + 1;
		Sleep(5000);
		if (brojDana > 1 && prijavaDoktora == 'Y' && stanje == 'Y' && simptomi == 'Y' && pomoc == 'Y' || pomoc == 'N')
		{
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "Na osnovu analize doktora procjenili smo da je potrebno da ostanete " << brojDanaUBolnici << ". dana u bolnici" << endl;
			cout << "Vas broj kreveta u Odjeljenju za nervne bolesti je " << brojKreveta;
			cout << "-------------------------------------------------------------------------" << endl;
			ofstream out;
			ofstream pacijenti;
			pacijenti.open("Pacijenti.txt", ios::app);
			out.open("appointment.dat", ios::app);
			upisUDatotekuPacijenata(name, prezime, bolest, brojKreveta, brojDanaUBolnici, izbor, uputnica);

		}
		else
		{
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "Na osnovu analize doktora procjenili smo da Vas boravak u nasoj bolnici nije potreban, te da cemo Vam preporuciti da samo pijete lijekove ";
			cout << "Lijekove koje morate koristiti su: ";
			cout << "-------------------------------------------------------------------------" << endl;
			for (int i = 0; i < brojlijekova; i++)
			{
				if (var[i].odjeljenje == "ODB")
					cout << var[i].ime << endl;
			}

		}
	}



	cout << "\n Pritisnite ENTER za nastavak...";
	getchar();
	getchar();
	return 0;
}




int main()
{
	int count = 3;
	while (true)
	{
		system("cls");
		cout << "\t\t\t\t\t";
		cout << char(218);
		for (int i = 0; i < 25; i++)
		{
			cout << char(196);
		}
		cout << char(191) << endl;
		system("color f4"); // Bijela pozadina i crveni tekst 
		cout << "\t\t\t\t\t" << char(179) << "         MENU            " << char(179) << endl;
		cout << "\t\t\t\t\t" << char(192);
		for (int i = 0; i < 25; i++) { cout << char(196); }
		cout << char(217) << endl;
		cout << "\t\t\t\t\t";
		cout << char(218);
		for (int i = 0; i < 25; i++) { cout << char(196); }
		cout << char(191) << endl;
		cout << "\t\t\t\t\t" << char(179) << "1. Prijavi pacijenta     " << char(179) << endl;
		cout << "\t\t\t\t\t" << char(192);
		for (int i = 0; i < 25; i++) { cout << char(196); }
		cout << char(217) << endl;
		cout << "\t\t\t\t\t";
		cout << char(218);
		for (int i = 0; i < 25; i++) { cout << char(196); }
		cout << char(191) << endl;
		cout << "\t\t\t\t\t" << char(179) << "2. Detalji o pacijentima " << char(179) << endl;
		cout << "\t\t\t\t\t" << char(192);
		for (int i = 0; i < 25; i++) { cout << char(196); }
		cout << char(217) << endl;
		cout << "\t\t\t\t\t";
		cout << char(218);
		for (int i = 0; i < 25; i++) { cout << char(196); }
		cout << char(191) << endl;
		cout << "\t\t\t\t\t" << char(179) << "3. Detalji o doktorima   " << char(179) << endl;
		cout << "\t\t\t\t\t" << char(192);
		for (int i = 0; i < 25; i++) { cout << char(196); }
		cout << char(217) << endl;
		cout << "\t\t\t\t\t";
		cout << char(218);
		for (int i = 0; i < 25; i++) { cout << char(196); }
		cout << char(191) << endl;
		cout << "\t\t\t\t\t" << char(179) << "4. Raspored posjeta      " << char(179) << endl;
		cout << "\t\t\t\t\t" << char(192);
		for (int i = 0; i < 25; i++) { cout << char(196); }
		cout << char(217) << endl;
		cout << "\t\t\t\t\t";
		cout << char(218);
		for (int i = 0; i < 25; i++) { cout << char(196); }
		cout << char(191) << endl;
		cout << "\t\t\t\t\t" << char(179) << "5. Pregled lijekova      " << char(179) << endl;
		cout << "\t\t\t\t\t" << char(192);
		for (int i = 0; i < 25; i++) { cout << char(196); }
		cout << char(217) << endl;
		cout << "\t\t\t\t\t";
		cout << char(218);
		for (int i = 0; i < 25; i++) { cout << char(196); }
		cout << char(191) << endl;
		cout << "\t\t\t\t\t" << char(179) << "6. Dodaj knjizicu        " << char(179) << endl;
		cout << "\t\t\t\t\t" << char(192);
		for (int i = 0; i < 25; i++) { cout << char(196); }
		cout << char(217) << endl;
		cout << "\t\t\t\t\t";
		cout << char(218);
		for (int i = 0; i < 25; i++) { cout << char(196); }
		cout << char(191) << endl;
		cout << "\t\t\t\t\t" << char(179) << "        7. IZLAZ         " << char(179) << endl;
		cout << "\t\t\t\t\t" << char(192);
		for (int i = 0; i < 25; i++) { cout << char(196); }
		cout << char(217) << endl;


		int choice;
		cout << "\t\t\t\t\t";
		cout << "Unesite broj koji zelite: ";
		cin >> choice;

		switch (choice)
		{
		case 1: {
			cout << char(254);
			for (int i = 0; i < 34; i++)
			{
				cout << char(254);
			}
			system("cls");
			cout << endl;
			cout << "\t\t\t\t\t";
			cout << "	1. Prijava pacijenta 		" << endl;
			cout << "\t\t\t\t\t";
			for (int i = 0; i < 35; i++) { cout << char(254); }
			zakazatiTermin();
			break;
		}

		case 2: {
			cout << char(254);
			for (int i = 0; i < 34; i++)
			{
				cout << char(254);
			}
			system("cls");
			cout << endl;
			cout << "\t\t\t\t\t";
			cout << "     2. Detalji o pacijentima 		" << endl;
			cout << "\t\t\t\t\t";
			for (int i = 0; i < 35; i++) { cout << char(254); }
			ispisPacijenata();
			break;
		}

		case 3: {
			cout << char(254);
			for (int i = 0; i < 34; i++)
			{
				cout << char(254);
			}
			system("cls");
			cout << endl;
			cout << "\t\t\t\t\t";
			cout << "	3. Detalji o doktorima		" << endl;
			cout << "\t\t\t\t\t";
			for (int i = 0; i < 35; i++) { cout << char(254); }
			detaljiODoktorima();
			break;
		}

		case 4: {
			cout << char(254);
			for (int i = 0; i < 34; i++)
			{
				cout << char(254);
			}
			system("cls");
			cout << endl;
			cout << "\t\t\t\t\t" << "	4. Raspored posjeta		 " << endl;
			cout << "\t\t\t\t\t";
			for (int i = 0; i < 35; i++) { cout << char(254); }
			rasporedPosjeta();
			break;
		}


		case 5: {
			cout << char(254);
			for (int i = 0; i < 34; i++)
			{
				cout << char(254);
			}
			system("cls");

			cout << endl;
			cout << "\t\t\t\t\t";
			cout << "	5. Pregled lijekova			" << endl;
			cout << "\t\t\t\t\t";
			for (int i = 0; i < 35; i++) { cout << char(254); }
			upisLijekovaDoktori(count);
			break;
		}

		case 6: {
			cout << char(254);
			for (int i = 0; i < 34; i++)
			{
				cout << char(254);
			}
			system("cls");
			cout << endl;
			cout << "\t\t\t\t\t";
			cout << "6. Dodavanje zdrastvene knjizice " << endl;
			cout << "\t\t\t\t\t";
			for (int i = 0; i < 35; i++) { cout << char(254); }
			zdrastvenaKnjizica();
			break;
		}
		case 7: {

			while (true)
			{

				system("cls");
				cout << "\t\t\t\t\t";
				for (int i = 0; i < 44; i++) {
					cout << char(254);
				}
				cout << endl;
				cout << "\t\t\t\t\t";
				cout << " Da li ste sigurni da zelite izaci ? y | n \n";
				char ex;
				cout << " \t\t\t\t\t";
				cin >> ex;

				for (int i = 0; i < 44; i++) {
					cout << char(254);
				}
				cout << endl;
				if (ex == 'y' || ex == 'Y')
					exit(0);
				else if (ex == 'n' || ex == 'N')
				{
					break;
				}
				else {
					cout << "\n Pogresan odabir !!!";
					getchar();
				}
			}	break;


		default: cout << "\n Pogresan odabir, pokusajte ponovo ";
			getchar();

		}

		}

	}
}
