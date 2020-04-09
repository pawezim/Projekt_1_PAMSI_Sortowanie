#pragma once
using namespace std;
#ifndef HEAPSORT_H
#define HEAPSORT_H
// Naprawa kopca po wstawieniu nowego elementu w miejsce korzenia:
template <typename typ>
void downHeap(typ A[], int ind, int heapSize, int k)
{
	// indeks w kopcu nie w tablicy, numeracja od 1 zamiast od 0:
	int left = 2 * ind; // lewy syn
	int right = 2 * ind + 1; // prawy syn
	int argmax = ind; // ojciec
	// Ze zbioru elementow {ojciec, lewy syn, prawy syn} wybierany jest element maksymalny:
	if (left <= heapSize && A[left - 1 + k] > A[argmax - 1 + k])
		argmax = left;
	if (right <= heapSize && A[right - 1 + k] > A[argmax - 1 + k])
		argmax = right;
	// sprawdzenie czy wciaz pozostaje naruszona wlasnosc kopca:
	if (argmax != ind)
	{
		swap(A[ind - 1 + k], A[argmax - 1 + k]); // zamiana miejscami ojca z synem, któwy ma wiêkszy klucz
		downHeap(A, argmax, heapSize, k); // naprawa kopca jest kontynuwana na podkopcu o korzeniu w synu, który zostal zamieniony miejscem z ojcem
	}
}
// Budowa kopca poprzez naprawe kopca w kierunku od korzenia do lisci:
template <typename typ>
void buildHeap(typ A[], int k, int l)
{
	// indeks w kopcu nie w tablicy, numeracja od 1 zamiast od 0:
	for (int ind = (l - k + 1) / 2; ind > 0; ind--) // naprawa jest wymagana jedynie dla elementow niebedacych lisciami
		downHeap(A, ind, l - k + 1, k);
}
//---------- Dodatkowa sekcja w ktorej znajduja sie funkcje uzywane tylko w implementacji upheap -----------------------
// Naprawa kopca po wstawieniu nowego elementu jako liscia:
template <typename typ>
void upHeap(typ A[], int ind, int k)
{
	int j = ind; // indeks w kopcu nie w tablicy, numeracja od 1 zamiast od 0
	while (j > 1 && A[j - 1 + k] > A[j / 2 - 1 + k]) // sprawdzenie czy wciaz pozostaje naruszona wlasnosc kopca
	{
		swap(A[j - 1 + k], A[j / 2 - 1 + k]); // zamina miejscem syna z ojcem
		j = j / 2; // przejscie od syna do ojca
	}
}
// Budowa kopca poprzez wstawianie elementow jako liscie (dodawanie do kolejki priorytetowej):
template <typename typ>
void buildHeap1(typ A[], int k, int l)
{
	// indeks w kopcu nie w tablicy, numeracja od 1 zamiast od 0:
	for (int ind = 2; ind <= l - k + 1; ind++) // naprawa jest wymagana dla kazdego elementu wstawionego jako lisc do kopca
		upHeap(A, ind, k);
}
//----------------------------------------------------------------------------------------------------------------------
// ALGORYTM SORTOWANIA PRZEZ KOPCOWANIE
template <typename typ>
void heapSort(typ A[], int k, int l)
{
	buildHeap(A, k, l); // OPCJA DOMYSLNA przeorganizowanie tablicy (w kierunku od korzenia do lisci - downheap) nadajace jej wlasnosc kopca
	//buildHeap1(A, k, l); // OPCJA ALTERNATYWNA przeorganizowanie tablicy (w kierunku od lisci do korzenia - upheap) nadajace jej wlasnosc kopca
	int heapSize = l - k + 1; // rozmiar kopca jest rozmiarem tablicy
	for (int i = l; i > k; i--) // w tej petli numeracja jak dla tablicy (od 0)
	{
		// zamiana miejscami elementu z konca tablicy o wlasnosci kopca z jego korzeniem, czyli wydobycie elementu maksymalnego z kolejki priorytetowej:
		swap(A[k], A[i]);
		heapSize--; // zmniejszenie rozmiaru rozpatrywanego kopca
		downHeap(A, 1, heapSize, k); // naprawa wlasnosci kopca po wstawieniu elementu w miejsce korzenia
	}
}
#endif