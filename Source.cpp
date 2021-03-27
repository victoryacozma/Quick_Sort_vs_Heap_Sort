/*Graficul heap-sort-ului e caracterizat de o functie n*logn, 
ceea ce confirma complexitatea algoritmului
Quick-sortul face mai putine asignari decat heap-sortul si,
respectiv, efortul total este mai mic

*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

#include "Profiler.h"

Profiler profiler("Quick_vs_Heap");

void swap(int* a, int* b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}



int partition(int* a, int k, int left, int right, const char* Comp, const char* Asig)
{
	profiler.countOperation(Asig, k);
	int pivot = a[right];
	int sm = left - 1;

	for (int crt = left; crt < right; crt++)
	{
		profiler.countOperation(Comp, k);
		if (a[crt] <= pivot)
		{	
			sm++;
			swap(&a[sm], &a[crt]);
			profiler.countOperation(Asig, k, 3);
		}
	}
	sm++;
	swap(&a[sm], &a[right]);
	profiler.countOperation(Asig, k, 3);

	return sm;
}

void quickSort(int a[], int k, int left, int right, const char* Comp, const char* Asig)
{
	if (left < right)
	{
		/*srand(time(0));
		int p = left + rand() % (right-left);
		swap(&a[p], &a[right]);
		generare pivot random*/
		int q = partition(a, k, left, right, Comp, Asig);
		quickSort(a,k ,left, q-1, Comp, Asig);
		quickSort(a, k, q + 1, right, Comp, Asig);
	}
}

void reconstr_heap(int a[], int i, int n,int k, const char* typeComp, const char* typeAsig)
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int maxim;

	maxim = i;

	if (left <= n && a[left] > a[i])
	{
		profiler.countOperation(typeComp, k);
		maxim = left;
	}
	if (right <= n && a[right] > a[maxim])
	{
		profiler.countOperation(typeComp, k);
		maxim = right;
	}
	if (maxim != i)
	{
		profiler.countOperation(typeAsig, k, 3);
		swap(&a[i], &a[maxim]);
		reconstr_heap(a, maxim, n, k ,  typeComp, typeAsig);
	}

}

void constr_heap_bottomUp(int a[], int n, int k, const char* typeComp, const char* typeAsig)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		reconstr_heap(a, i, n, k, typeComp, typeAsig);
	}
}


void heapSort(int a[], int n, const char* comp, const char* asig)
{
	int k = n;
	constr_heap_bottomUp(a, n, k, comp, asig);
	
	for (int i = n - 1; i >= 0; i--)
	{
		profiler.countOperation(asig, k, 3);
		swap(&a[0], &a[i]);
		reconstr_heap(a, 0, i - 1, k, comp, asig);
	}
}

int main() {
	/*int n = 8;
	int arr[8] = {1,2,3,4,5,6,7,8};
	quickSort(arr, n, 0, n-1, "comp", "asig");
	
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	*/
	int a[10000];
	int b[10000];
	
	for (int m = 1; m <= 5; m++)
	{
		for (int n = 100; n < 1000; n += 100)
		{
			FillRandomArray(a, n, 0, 50000, true, 0);
			for (int k = 0; k < n; k++)
			{
				b[k] = a[k];
			}
			heapSort(a, n, "compHeap", "asigHeap");
			quickSort(b, n, 0, n - 1, "compQuick", "asigQuick");

		}
	}
	
	
		profiler.addSeries("totalEffHeap", "compHeap", "asigHeap");
		profiler.addSeries("totalEffQuick", "compQuick", "asigQuick");
		profiler.divideValues("totalEffHeap", 5);
		profiler.divideValues("totalEffQuick", 5);

		profiler.createGroup("Comparatii", "compHeap", "compQuick");
		profiler.createGroup("Asignari", "asigHeap", "asigQuick");
		profiler.createGroup("Efort", "totalEffHeap", "totalEffQuick");

	for (int n = 100; n <= 1000; n += 100)
	{
		FillRandomArray(a, n, 0, 50000, true, 1);
		quickSort(a, n, 0, n - 1, "compQuickFav", "asigQuickFav");

	}
	profiler.addSeries("totalEffQuickFav", "compQuickFav", "asigQuickFav");

	for (int n = 100; n <= 1000; n += 100)
	{
		FillRandomArray(a, n, 0, 50000, true, 2);
		quickSort(a, n, 0, n - 1, "compQuickDefav", "asigQuickDefav");

	}
	profiler.addSeries("totalEffQuickDefav", "compQuickDefav", "asigQuickDefav");

	profiler.createGroup("ComparatiiQuick", "compQuickDefav", "compQuickFav");
	profiler.createGroup("AsignariQuick", "asigQuickFav", "asigQuickDefav");
	profiler.createGroup("EfortQuick", "totalEffQuickDefav", "totalEffQuickFav");
	
	profiler.showReport();
	
	return 0;
}