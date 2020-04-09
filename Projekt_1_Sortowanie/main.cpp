#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "mergesort.h"
#include "mergesort_reverse.h"
#include "heapsort.h"
#include "quicksort.h"
#include "introsort.h"
using namespace std;
// funkcja wypisujaca elementy tablicy:
template <typename typ>
void wypisz(typ A[], int N, string komentarz)
{
	cout << komentarz << endl;
	for (int i = 0; i < N; i++)
	{
		cout << A[i] << " ";
		if (i % 10 == 9)
			cout << endl;
	}
	cout << "\n\n";
}
// funkcja sluzaca do zweryfikowania poprawnosci wykonanego sortowania:
template <typename typ>
bool czyPosortowana(typ A, int N)
{
	bool czy = true;
	for (int i = 1; i < N; i++)
	{
		czy = czy && (A[i - 1] <= A[i]);
	}
	return czy;
}
template <typename typ>
void wstepne_sortowanie(typ A, int N, int ileJuzPosortowanych, bool czyOdwrotnaKolejnosc)
{
	if (czyOdwrotnaKolejnosc)
	{
		mergeSortRev(A, 0, ileJuzPosortowanych - 1);
	}
	else
	{
		mergeSort(A, 0, ileJuzPosortowanych - 1);
	}
}
// funkcja generujaca i sortujaca zadana liczbe tablic liczb calkowitych, zwracajaca sredni czas sortowania:
float sredniCzas(int N, int iloscPowtorzen, int algorytm, float stopienPosortowania, bool czyOdwrotnaKolejnosc = 0)
{
	int* A = new int[N]; // zaalokowanie miejsca w pamieci dla tablicy o zadanym rozmiarze
	float czas = 0; // zainicjowanie zmiennej zwracanej przez funkcje
	for (int i = 0; i < iloscPowtorzen; i++)
	{
		int t0 = 0;
		int t1 = 0;
		// wygenerowanie losowych elementow tablicy:
		for (int i = 0; i < N; i++)
			A[i] = rand() - RAND_MAX / 2;
		// przeliczenie wartosci procentowej na liczbe elemntow uporzadkowanych przed sortowaniem:
		int ileJuzPosortowanych = int(N * stopienPosortowania / 100);
		// wywolanie funkcji wykonujacej wstepne sortowanie (we wlasciwej lub odwrotnej kolejnosci):
		wstepne_sortowanie(A, N, ileJuzPosortowanych, czyOdwrotnaKolejnosc);
		// wywolanie wybranego algorytmu sortowania i pomiar czasu sortowania, czas sortowania jest sumowany po powtorzeniach wywolan algorytmu:
		switch (algorytm)
		{
			case 1:
				t0 = clock();
				mergeSort(A, 0, N - 1);
				t1 = clock();
				czas = czas + (t1 - t0) * float(0.001);
				break;
			case 2:
				t0 = clock();
				quickSort(A, 0, N - 1);
				t1 = clock();
				czas = czas + (t1 - t0) * float(0.001);
				break;
			case 3:
				t0 = clock();
				introSort(A, 0, N - 1);
				t1 = clock();
				czas = czas + (t1 - t0) * float(0.001);
				break;
		}
	}
	delete[] A; // wyczyszczenie zasobu pamieci
	return czas/iloscPowtorzen; // funkcja zwraca sredni czas (suma czasow podzielona przez ilosc powtorzen)
}
// funkcja generujaca i sortujaca pojedyncza tablice liczb calkowitych, wywoluje sprawdzenie sortowania oraz opcjonalnie wypisuje elementy
void jednoSortowanie(int N, int algorytm, bool czyWypisac, float stopienPosortowania, bool czyOdwrotnaKolejnosc = 0)
{
	int t0 = 0;
	int t1 = 0;
	int* A = new int[N]; // zaalokowanie miejsca w pamieci dla tablicy o zadanym rozmiarze
	// wygenerowanie losowych elementow tablicy:
	for (int i = 0; i < N; i++)
		A[i] = rand() - RAND_MAX / 2;
	// przeliczenie wartosci procentowej na liczbe elemntow uporzadkowanych przed sortowaniem:
	int ileJuzPosortowanych = int(N * stopienPosortowania / 100);
	// wywolanie funkcji wykonujacej wstepne sortowanie (we wlasciwej lub odwrotnej kolejnosci):
	wstepne_sortowanie(A, N, ileJuzPosortowanych, czyOdwrotnaKolejnosc);
	// opcjonalne wypisanie elementow przed sortowaniem:
	if (czyWypisac)
	{
		wypisz(A, N, "Przed sortowaniem:");
	}
	// wywolanie wybranego algorytmu sortowania i pomiar czasu pojedynczego sortowania:
	switch (algorytm)
	{
		case 1:
			t0 = clock();
			mergeSort(A, 0, N - 1);
			t1 = clock();
			break;
		case 2:
			t0 = clock();
			quickSort(A, 0, N - 1);
			t1 = clock();
			break;
		case 3:
			t0 = clock();
			introSort(A, 0, N - 1);
			t1 = clock();
			break;
	}
	// opcjonalne wypisanie elementow po sortowaniu:
	if (czyWypisac)
	{
		wypisz(A, N, "Po sortowaniu:");
	}
	// komunikat orzekujacy o poprawnosci (badz niepoprawnosci) wykonanego sortowania:
	if (czyPosortowana(A, N))
	{
		cout << "Tablica zostala prawidlowo posortowana.\n\n";
	}
	else
	{
		cout << "Tablicy nie udalo sie posortowac.\n\n";
	}
	// komunikat na temat czasu sortowania:
	cout << "Czas sortowania tablicy wyniosl\n" << (t1 - t0) * float(0.001) << " sekund.\n";
}
// Interfejs uzytkownika poprzez pytania prowadzi do wywolania funkcji jednoSortowanie() dla jednej tablicy lub sredniCzas() w przypadku wyboru wiekszej liczby tablic:
int main()
{
	srand(static_cast<int>(time(0)));
	int N, iloscPowtorzen, algorytm;
	float stopienPosortowania, sredni;
	bool czyWypisac, czyOdwrotnaKolejnosc = 0;
	cout << "Podaj rozmiar tablicy.\n";
	cin >> N;
	cout << endl << "Jaki algorytm zastosowac? ( 1 - mergesort, 2 - quicksort, 3 - introsort )\n";
	cin >> algorytm;
	cout << endl << "Podaj stopien wstepnego posortowania (w procentach).\n";
	cin >> stopienPosortowania;
	// Jesli uzytkownik zarzada aby czesc tablicy byla uporzadkowana przed sortowaniem, zadawane jest pytanie o kierunek uporzadkowania:
	if (stopienPosortowania != 0)
	{
		cout << endl << "Czy kolejnosc wstepnie posortowanych elementow ma byc odwrotna? ( 0 - nie, 1 - tak)\n";
		cin >> czyOdwrotnaKolejnosc;
	}
	cout << endl << "Ile powtorzen sortowania chcesz wykonac?\n";
	cin >> iloscPowtorzen;
	if (iloscPowtorzen == 1)
	{
		// opcja wypisania elementow jest oferowana wywlacznie w przypadku sortowania pojedynczej tablicy:
		cout << endl << "Czy chesz wypisac elementy tablicy przed i po sortowaniu? ( 0 - nie, 1 - tak )\n";
		cin >> czyWypisac;
		cout << endl;
		jednoSortowanie(N, algorytm, czyWypisac, stopienPosortowania, czyOdwrotnaKolejnosc);
	}
	else
	{
		sredni = sredniCzas(N, iloscPowtorzen, algorytm, stopienPosortowania, czyOdwrotnaKolejnosc);
		// w przypadkiu wyboru liczby tablic wiekszej od 1 wyswietlany jest komunikat o srednim czasie sortowania:
		cout << endl << "Sredni czas sortowania tablicy o rozmiarze " << N << " wyznaczony przez posortowanie " << iloscPowtorzen << " tablic wyniosl:\n" << sredni << " sekund.\n\n";
		// nastepnie zapisywany jest rekord w pliku txt (wydobyte w ten sposob dane sluza potem do stworzenia wykresow):
		ofstream myfile;
		myfile.open("wyniki.txt", ios::app);
		switch (algorytm)
		{
		case 1:
			myfile << "Algorytm: mergesort\t";
			break;
		case 2:
			myfile << "Algorytm: quicksort\t";
			break;
		case 3:
			myfile << "Algorytm: introsort\t";
			break;
		}
		myfile << "Ilosc powtorzen: " << iloscPowtorzen << endl << "Rozmiar tablicy: " << N << "\t" << "Sredni czas sortowania [s]: " << sredni;
		if (stopienPosortowania != 0)
		{
			myfile << endl << "Przed sortowaniem " << stopienPosortowania << " procent poczatkowych elementow bylo uporzadkowane ";
			if(czyOdwrotnaKolejnosc)
				myfile << "malejaco.";
			else
				myfile << "rosnaco.";
		}
		myfile << "\n\n";
		myfile.close();
		cout << "Zapisano wyniki do pliku wyniki.txt\n";
	}
	system("pause");
	return 0;
}
