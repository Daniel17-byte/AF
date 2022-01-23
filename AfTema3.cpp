# include <stdio.h>
# include "Profiler.h"

Profiler profiler("Quicksort");

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high,int n)
{
    Operation atribuiri = profiler.createOperation("Atribuiri_quicksort", n);
    Operation comparari = profiler.createOperation("Comparari_quicksort", n);
    atribuiri.count(2);
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        comparari.count();
        if (arr[j] <= pivot)
        {
            atribuiri.count(4);
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    atribuiri.count(3);
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void quicksort(int a[], int p, int r,int n)
{
    if (p < r)
    {
        int q;
        q = partition(a, p, r,n);
        quicksort(a, p, q - 1,n);
        quicksort(a, q + 1, r,n);
    }
}

void printArray(int a[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

/*
void demo(){
}
*/
int main()
{
    //demo();
    int arr1[10000];
    int arr2[10000];

    for (int x = 0; x < 5; x++)
    {
        for (int i = 100; i <= 2000; i += 100)
        {

            FillRandomArray(arr1, i, 10, 10000, false, UNSORTED);
            CopyArray(arr2, arr1, i);
            quicksort(arr1, 0,i-1,i);
        }
    }

    int arr[] = { 9, 7, 5, 11, 12, 2, 14, 3, 10, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);

    quicksort(arr, 0, n - 1, n);

    printf("Vector sortat: \n");
    printArray(arr, n);

    profiler.divideValues("Atribuiri_quicksort", 5);
    profiler.divideValues("Comparari_quicksort", 5);

    profiler.addSeries("Total_quicksort", "Atribuiri_quicksort", "Comparari_quicksort");

    profiler.createGroup("Caz_mediu_Atribuiri", "Atribuiri_quicksort", "Atribuiri_quicksort");
    profiler.createGroup("Caz_mediu_Comparatii", "Comparari_quicksort", "Comparari_quicksort");

    profiler.showReport();
    return 0;
}