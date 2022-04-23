#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

struct kolcsonzes
{
	char datum[12];   //a kölcsönzés napja
	char tipus[20]; //a kerékpár típusa
	int sorszam;    //a kerékpár sorszáma
	int ido;    //a kölcsönzés ideje
};
class kolcsonzo
{
private:
	kolcsonzes* k;
	int db;
public:
	kolcsonzo(char fnev[]);
	~kolcsonzo();
	int Getdb();
	int GetMagellan();
	int GetMedian();
	int MedianBevetel();
	int Osszbevetel();
	int LeghosszabbKolcsonzes();
	int LegtobbKolcsonzes();
	void Lista();
	void Kiir();
};
//kolcsonzo.dat beolvasasa
kolcsonzo::kolcsonzo(char fnev[])
{
	ifstream be(fnev, ios::binary);
	if (be.fail())
	{
		cerr << "Hiba a fajl megnyitasa kozben" << endl;
		system("pause");
		exit(-1);
	}
	// Meghatározzuk az állományban lévõ fileok számát
	//a seekg(0,ios::end)-el a file végére ugrunk
	be.seekg(0, ios::end);
	/*
	a tellg() - vel megmondjuk milyen pozícióban vagyunk pontosan,
	ezáltal meghatározzuk az egész fileba írt szöveget, majd azt
	elosztjuk a kolcsonzes struktura meretevel:
	*/
	db = be.tellg() / sizeof(kolcsonzes);
	//visszaugrunk a file elejére (be.seekg(0,ios::beg))
	be.seekg(0, ios::beg);
	/*
	tárterületet foglalunk le a kolcsonzesek adatait tartalmazo dinamikus tombnek,
	mivel megtudtuk hogy mekkora a lefoglalni kívánt terület a seekg és a tellg segítségével.
	*/
	k = new kolcsonzes[db];
	//ha a k 0-val egyenlo, akkor valami hiba tortent a beolvasas kozben
	if (k == 0)
	{
		cerr << "Hiba2" << endl;
		system("pause");
		exit(-2);
	}

	//Ebbe a címbe olvasunk, ennyi byte-ot
	be.read((char*)k, db * sizeof(kolcsonzes));
	be.close();
}
kolcsonzo::~kolcsonzo()
{
	if (k != 0)
	{
		delete[]k;
	}
}
int kolcsonzo::Getdb()
{
	return db;
}
int kolcsonzo::GetMagellan()
{
	int mdb = 0;
	for (int i = 0; i < db; i++)
	{
		//strcmp összehasonlít 2 stringet, és egy számot hoz vissza. Ha a szám "0", akkor tökéletes az egyezés.
		if (strcmp(k[i].tipus, "magellan") == 0)
		{
			mdb++;
		}
	}
	return mdb;
}
int kolcsonzo::GetMedian()
{
	int medb = 0;
	for (int i = 0; i < db; i++)
	{
		//strcmp összehasonlít 2 stringet, és egy számot hoz vissza. Ha a szám "0", akkor tökéletes az egyezés.
		if (strcmp(k[i].tipus, "median") == 0)
		{
			medb++;
		}
	}
	return medb;
}
int kolcsonzo::MedianBevetel()
{
	int mBevetel = 0;
	for (int i = 0; i < db; i++)
	{
		if (strcmp(k[i].tipus, "median") == 0)
		{
			mBevetel += k[i].ido * 1000;
		}
	}
	return mBevetel;
}
int kolcsonzo::Osszbevetel()
{
	int osszbevetel = 0;
	for (int i = 0; i < db; i++)
	{
		if (strcmp(k[i].tipus, "magellan") == 0)
		{
			osszbevetel += k[i].ido * 1200;
		}
		else
		{
			osszbevetel += k[i].ido * 1000;
		}
	}
	return osszbevetel;
}
int kolcsonzo::LeghosszabbKolcsonzes()
{
	int l = k[0].ido;
	for (int i = 0; i < db; i++)
	{
		if (k[i].ido > l)
		{
			l = k[i].ido;
		}
	}
	return l;
}
int kolcsonzo::LegtobbKolcsonzes()
{
	int max = 0, maxsorszam = 0, hanyszor = 0;
	for (int s = 20; s < 31; s++)
	{
		hanyszor = 0;
		for (int i = 0; i < db; i++)
		{
			if (k[i].sorszam == s)
			{
				hanyszor++;
			}
		}
		if (max < hanyszor)
		{
			maxsorszam = s;
			max = hanyszor;
		}
	}
	return maxsorszam;
}
void kolcsonzo::Lista()
{
	cout << setw(12) << "datum" << setw(20) << "tipus" << setw(10) << "sorszam" << setw(10) << "kolcsido" << endl;
	for (int i = 0; i < db; i++)
	{
		if (k[i].ido > 5)
		{
			cout << setw(12) << k[i].datum << setw(20) << k[i].tipus << setw(10) << k[i].sorszam << setw(10) << k[i].ido << endl;
		}
	}
}
void kolcsonzo::Kiir()
{
	cout << setw(14) << "datum" << setw(20) << "tipus" << setw(10) << "sorszam" << setw(10) << "kolcsido" << endl;
	for (int i = 0; i < db; i++)
	{
		cout << i + 1 << "." << setw(12) << k[i].datum << setw(20) << k[i].tipus << setw(10) << k[i].sorszam << setw(10) << k[i].ido << endl;
	}
}
int main(int argdb, char* argv[])
{
	if (argdb != 2)
	{
		cout << "hibas programinditas\n";
		system("pause");
		return 1;
	}
	kolcsonzo ketkerek(argv[1]);
	cout << "A kolcsonzesek szama: " << ketkerek.Getdb() << endl;
	cout << "A magellan kolcsonzesek szama: " << ketkerek.GetMagellan() << endl;
	cout << "A median kolcsonzesek szama: " << ketkerek.GetMedian() << endl;
	cout << "A median kerekparokkal szerzett bevetel: " << ketkerek.MedianBevetel() << endl;
	cout << "A kerekparokkal szerzett osszbevetel: " << ketkerek.Osszbevetel() << endl;
	cout << "A leghosszabb kolcsonzes ideje: " << ketkerek.LeghosszabbKolcsonzes() << endl;
	cout << "A legtobbszor kolcsonzott kerekpar sorszama: " << ketkerek.LegtobbKolcsonzes() << endl;
	cout << endl;
	cout << "Az 5 oranal hosszabb kolcsonzesek:\n";
	ketkerek.Lista();

	cout << endl << endl;
	cout << "***************** dinamikus objektum *****************\n\n";
	kolcsonzo* kektura = new kolcsonzo(argv[1]);
	if (kektura == 0)
	{
		cerr << "keves a memoria 2";
		return 2;
	}
	cout << "Az allomanyban levo adatok:\n";
	(*kektura).Kiir();
	cout << endl;
	cout << "A kolcsonzesek szama: " << kektura->Getdb() << endl;
	cout << "A magellan kolcsonzesek szama: " << kektura->GetMagellan() << endl;
	cout << "A median kolcsonzesek szama: " << kektura->GetMedian() << endl;
	cout << "A median kerekparokkal szerzett bevetel: " << kektura->MedianBevetel() << endl;
	cout << "A kerekparokkal szerzett osszbevetel: " << kektura->Osszbevetel() << endl;
	cout << "A leghosszabb kolcsonzes ideje: " << kektura->LeghosszabbKolcsonzes() << endl;
	cout << "A legtobbszor kolcsonzott kerekpar sorszama: " << kektura->LegtobbKolcsonzes() << endl;
	cout << endl;
	cout << "Az 5 oranal hosszabb kolcsonzesek:\n";
	kektura->Lista();
	delete kektura;

	system("pause");
	return 0;
}