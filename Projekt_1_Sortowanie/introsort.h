#pragma once
using namespace std;
#include "heapsort.h"
#include "quicksort.h"
#ifndef INTROSORT_H
#define INTROSORT_H
// Algorytm sortowania przez wstawianie z wyszukiwaniem binarnym:
template <typename typ>
void insertionSort(typ A[], int k, int l)
{
	for (int i = k + 1; i <= l; i++)
	{
		typ x = A[i]; // brany jest pierwszy w kolejnosci element z nieposortowanej jeszcze czesci tablicy
		int mid, left = 0, right = i;
		while (left != right) // zawezenie poszukiwania do pojedynczego elementu jest warunkiem wyjscia zpetli
		{
			mid = (left + right) / 2;
			if (x < A[mid]) // sprawdzenie czy element nalezy wstawic na lewo czy na prawo od srodka obecnego obszaru poszukiwan
				right = mid;
			else left = mid + 1;
		}
		for (int j = i; j > left; j--)
		{
			A[j] = A[j - 1]; // przesuniecie w prawo elemntow pomiedzy nowym a starym miejscem elemntu x
		}
		A[left] = x; // wstawienie x w posortowana czesc tablicy
	}
}
// funkcja pomocnicza stanowiaca rekurencyjna procedure sortowania:
template <typename typ>
void introSortRecursion(typ A[], int k, int l, int recDepLim)
{
	if (k < l) // sprawdzenie czy tablica ma co najmniej dwa elementy okreslajace warunek stopu dla rekurencji
	{
		if (l - k + 1 < 10) // bardzo krotkie tablice sa sortowane przez wstawianie
		{
			insertionSort(A, k, l);
		}
		else
		if (recDepLim == 0) // sprawdzenie czy limit rekurencyjnych wywolan zostal wyczerpany, czyli wykrycie pesymistycznego przypadku algorytmu quickSort()
		{
			heapSort(A, k, l); // wywolanie sortowania przez kopcowanie
		}
		else
		{
			// podzial tablicy taki sam jak w algorytmie quickSort():
			int m = partition(A, k, l);
			// sortowanie lewej i prawej podtablicy, limit rekurencyjnych wywolan zmniejszany jest o jeden:
			introSortRecursion(A, k, m, recDepLim - 1);
			introSortRecursion(A, m + 1, l, recDepLim - 1);
		}
	}
}
// ALGORYTM SORTOWANIA INTROSPEKTYWNEGO:
template <typename typ>
void introSort(typ A[], int k, int l)
{
	// okreslany jest maksymalny stopien glebokosci rekurencji tj. liczba zagniezdzonych wywolan introSortRecursion(), po ktorej ma byc wywolany heapSort():
	int recDepLim = 2 * int(log2(l - k + 1));
	// pierwsze wywolanie wlasciwej procedury sortowania:
	introSortRecursion(A, k, l, recDepLim);
}
#endif
