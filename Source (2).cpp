#include <iostream>
#include <limits>
#include "Profiler.h"

using namespace std;

Profiler profiler("Heap");

void max_heapify(int array[], int n, int i)
{
	Operation atribuiri = profiler.createOperation("Atribuiri_bottomup", n);
	Operation comparari = profiler.createOperation("Comparari_bottomup", n);
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int largest = i;
	comparari.count();
	if (l<n && array[l]>array[largest])
	{
		largest = l;
	}
	comparari.count();
	if (r<n && array[r]>array[largest])
		largest = r;
	if (largest != i)
	{
		atribuiri.count(3);
		swap(array[i], array[largest]);
		max_heapify(array, n, largest);
	}
}

void build_max_heap_bottomup(int array[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		max_heapify(array, n, i);
}

void heapsort(int array[], int n)
{
	build_max_heap_bottomup(array, n);
	for (int i = n - 1; i >= 0; i--)
	{

		swap(array[0], array[i]);
		n--;
		max_heapify(array, i, 0);
	}
}


void heap_increase_key(int array[], int i, int key, int n)
{
	Operation atribuiri = profiler.createOperation("Atribuiri_topdown", n);
	Operation comparari = profiler.createOperation("Comparari_topdown", n);

	comparari.count();
	if (key < array[i]) {
		return;
	}
	atribuiri.count();
	array[i] = key;
	if (array[(i - 1) / 2] >= array[i])
	{
		comparari.count();
	}
	while (i > 0 && array[(i - 1) / 2] < array[i])
	{
		comparari.count();
		atribuiri.count(3);
		swap(array[i], array[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

void max_heap_insert(int array[], int& size, int key, int n)
{
	size++;
	array[size] = -INFINITY;
	heap_increase_key(array, size, key, n);
}

void build_max_heap_topdown(int array[], int n)
{
	int size = 0;
	for (int i = 1; i < n; i++)
	{
		max_heap_insert(array, size, array[i], n);
	}
}

void printArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << ' ';
	}
	cout << endl;
}


void demo()
{
	int arr1[] = { 12, 16, 13, 91, 85 ,6, 7 };
	int arr2[] = { 12, 16, 13, 91, 85 ,6, 7 };
	int n = sizeof(arr1) / sizeof(arr1[0]);
	int n2 = n;
	heapsort(arr1, n);
	printArray(arr1, n);
	build_max_heap_bottomup(arr1, n);
	printArray(arr1, n);
	build_max_heap_topdown(arr2, n2);
	printArray(arr1, n2);
}

int main()
{
	demo();

	int arr1[10000];
	int arr2[10000];

	for (int x = 0; x < 5; x++)
	{
		for (int i = 100; i <= 2000; i += 100)
		{

			FillRandomArray(arr1, i, 10, 2000, false,UNSORTED);
			CopyArray(arr2, arr1, i);
			build_max_heap_bottomup(arr1, i);
			build_max_heap_topdown(arr2, i);
		}
	}

	profiler.divideValues("Atribuiri_bottomup", 5);
	profiler.divideValues("Comparari_bottomup", 5);

	profiler.addSeries("Total_bottomup", "Atribuiri_bottomup", "Comparari_bottomup");

	profiler.divideValues("Atribuiri_topdown", 5);
	profiler.divideValues("Comparari_topdown", 5);

	profiler.addSeries("Total_topdown", "Atribuiri_topdown", "Comparari_topdown");


	profiler.createGroup("Caz_mediu_Atribuiri", "Atribuiri_bottomup", "Atribuiri_topdown");
	profiler.createGroup("Caz_mediu_Comparatii", "Comparari_bottomup", "Comparari_topdown");
	profiler.createGroup("Caz mediu total", "Total_bottomup", "Total_topdown");

	profiler.showReport();

	return 0;
}