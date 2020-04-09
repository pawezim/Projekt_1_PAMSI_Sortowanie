#pragma once
using namespace std;
#ifndef MERGESORT_REV_H
#define MERGESORT_REV_H
// Procedura scalania dwoch posortowanych podtablic (W ODWROTNEJ KOLEJNOSCI):
template <typename typ>
void mergeRev(typ A[], int k, int m, int l)
{
	int i = 0;
	int j = 0;
	typ* temp = new typ[l - k + 1];
	while (i + j < l - k + 1)
	{
		if (j == l - m)
		{
			temp[i + j] = A[k + i];
			i++;
		}
		else if (i == m - k + 1)
		{
			break;
		}
		else if (A[k + i] > A[m + 1 + j]) // jedyna linia, wktorej algorytm rozni sie od sortujacego we wlasciwej kolejnosci
		{
			temp[i + j] = A[k + i];
			i++;
		}
		else
		{
			temp[i + j] = A[m + 1 + j];
			j++;
		}
	}
	for (int v = 0; v < i + j; v++)
		A[v + k] = temp[v];
	delete[] temp;
}
// algorytm sortowania przez scalanie (W ODWROTNEJ KOLEJNOSCI):
template <typename typ>
void mergeSortRev(typ A[], int k, int l)
{
	if (k < l)
	{
		int m = (k + l) / 2;
		mergeSortRev(A, k, m);
		mergeSortRev(A, m + 1, l);
		mergeRev(A, k, m, l);
	}
}
#endif