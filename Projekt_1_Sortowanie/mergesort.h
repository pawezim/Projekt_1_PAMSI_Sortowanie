#pragma once
using namespace std;
#ifndef MERGESORT_H
#define MERGESORT_H
// Procedura scalania dwoch posortowanych podtablic:
template <typename typ>
void merge(typ A[], int k, int m, int l)
{
	int i = 0;
	int j = 0;
	typ* temp = new typ[l - k + 1]; // tworzona jest tablica pomocnicza do przechowania posortowanych elementow
	// petla przechodzi w kierunku rosnacego indeksu tablicy jednoczesnie po lewej i prawej podtablicy:
	while (i + j < l - k + 1)
	{
		// jesli prawa podtablica zostala wyczerpana, pozostale elementy lewej podtablicy sa przepisywane na koncu tablicy pomocniczej:
		if (j == l - m)
		{
			temp[i + j] = A[k + i];
			i++;
		}
		// jesli lewa podtablica zostala wyczerpana, pozostale elementy prawej podtablicy sa juz na wlasciwej pozycji:
		else if (i == m - k + 1)
		{
			break;
		}
		// Jesli zadna z podtablic nie zostala jeszcze wyczerpana, znajdowany jest element najmniejszy i zapisywany w tablicy pomocniczej: 
		else if (A[k+i] < A[m+1+j])
		{
			temp[i+j] = A[k+i];
			i++;
		}
		else
		{
			temp[i+j] = A[m+1+j];
			j++;
		}
	}
	for (int v = 0; v < i+j; v++)
		A[v+k] = temp[v];
	delete[] temp; // wyczyszczenie zasobu pamieci
}
// ALGORYTM SORTOWANIA PRZEZ SCALANIE:
template <typename typ>
void mergeSort(typ A[], int k, int l)
{
	if (k < l) // sprawdzenie czy tablica ma co najmniej dwa elementy okreslajace warunek stopu dla rekurencji
	{
		int m = (k + l) / 2; // podzial tablicy na rowne czesci
		mergeSort(A, k, m); // sortowanie lewej podtablicy
		mergeSort(A, m + 1, l); // sortowanie prawej podtablicy
		merge(A, k, m, l); // wywolanie procedury scalania ze soba posortowanych podtablic
	}
}
#endif