#pragma once
using namespace std;
#ifndef QICKSORT_H
#define QICKSORT_H
// procedura podzialu tablicy:
template <typename typ>
int partition(typ A[], int k, int l)
{
	typ x;
	if (A[(k + l) / 2] <= A[l]) // OPCJA 1: (DOMYSLNA) wybor granicy podzialu jako mediany ze srodka tablicy oraz jej lewego i prawego konca 
	{
		if (A[k] <= A[(k + l) / 2])
			x = A[(k + l) / 2];
		else if (A[k] <= A[l])
			x = A[k];
		else
			x = A[l];
	}
	else
	{
		if (A[(k + l) / 2] <= A[k])
			x = A[(k + l) / 2];
		else if (A[k] <= A[l])
			x = A[l];
		else
			x = A[k];
	}
	//x = A[(k + l) / 2]; // OPCJA 2: granica podzialu wybierana jest jako element o srodkowym indeksie
	//x = A[k + rand() % (l - k + 1)]; // OPCJA 3: losowy wybor elementu stanowiacego granice podzialu
	int i = k; // indeks przechodzacy od lewej do prawej
	int j = l; // indeks przechodzacy od prawej do lewej
	while (1)
	{
		// skanowanie od lewej az do znalezienia elementu do zamiany:
		while (A[i] < x)
			i++; 
		// skanowanie od prawej az do znalezienia elementu do zamiany:
		while (A[j] > x)
			j--;
		// Zamiana miejscami elementow ktore nie sa po wlasciwej stronie granicy podzialu:
		if (i < j)
		{
			swap(A[i], A[j]);
			i++;
			j--;
		}
		else
			return j; // jesli wszystkie elementy sa po wlasciwej stronie, podzial zostal ukonczony
	}
}
// ALGORYTM SORTOWANIA SZYBKIEGO:
template <typename typ>
void quickSort(typ A[], int k, int l)
{
	if (k < l) // sprawdzenie czy tablica ma co najmniej dwa elementy okreslajace warunek stopu dla rekurencji
	{
		// podzial tablicy za pomoca procedury partition():
		int m = partition(A, k, l);
		// sortowanie lewej i prawej podtablicy:
		quickSort(A, k, m);
		quickSort(A, m + 1, l);
	}
}
#endif

