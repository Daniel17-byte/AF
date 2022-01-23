#include <stdio.h>
#include "Profiler.h"

Profiler p("sort");

#define MAX_SIZE 10000
#define STEP_SIZE 100
#define NR_TESTS 5

//bubble sort
void bubblesort(int arr[],int n) {
    int ok, aux;
    Operation opComp = p.createOperation("comp-elem-bubble", n);
    Operation opAttr = p.createOperation("atr-elem-bubble", n);
    do {
        ok = 0;
        for (int i = 0;i < n - 1;i++)
        {
            opComp.count();
            if (arr[i] > arr[i + 1])
            {
                opAttr.count(3);
                aux = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = aux;
                ok = 1;
            }
        }
    } while (ok == 1);
}

void selectionsort(int arr[],int n) {
    Operation opComp = p.createOperation("comp-elem-selection", n);
    Operation opAttr = p.createOperation("atr-elem-selection", n);
    int min,aux;
    for (int i = 0; i < n - 1;i++) {
        min = i;
        for (int j = i + 1; j < n;j++) {
            opComp.count();
            if (arr[j] < arr[min]) {
                min = j;
                opAttr.count();
            }
        }
        if (i != min) {
            aux = arr[i];
            arr[i] = arr[min];
            arr[min] = aux;
            opAttr.count(3);
        }
    }
}
void insertionsort(int arr[], int n) {
    Operation opComp = p.createOperation("comp-elem-insertion", n);
    Operation opAttr = p.createOperation("atr-elem-insertion", n);
    int x, j;
    for (int i = 1; i < n; i++)
    {
        opAttr.count();
        x = arr[i];
        j = i - 1;
        if (arr[j] <= x) {
            opComp.count();
        }
        
        while (j >= 0 && arr[j] > x)
        {
            opComp.count();
            arr[j + 1] = arr[j];
            j = j - 1;
            opAttr.count();
        }
        if (j != i) {
            opAttr.count();
            arr[j + 1] = x;
        }
    }
}
void printArr(int arr[],int n) {
    for (int i = 0;i < n;i++)
        printf("%d ", arr[i]);
    printf("\n");

}

void corectitudine(int arr[], int n) {
    int a[10], b[10];
    CopyArray(a, arr, n);
    CopyArray(b, arr, n);

    bubblesort(arr, n);
    insertionsort(a, n);
    selectionsort(b, n);

    printf("Bubble:");
    printArr(arr,n);
    printf("Selection:");
    printArr(a,n);
    printf("Insertion:");
    printArr(b,n);

}

int main()
{
    int arr[10] = { 17,49,19,88,63,24,7,18,10,35 };
    //corectitudine(arr, 10);
    //perf();
    int  a[10000], b[10000], c[10000];

    //caz favorabil
  
    for (int i = 100;i <= 1500;i += 100) {
        FillRandomArray(a, i, 0, 1000, false, 1);
        CopyArray(b, a, i);
        CopyArray(c, a, i);
        bubblesort(a, i);
        insertionsort(b, i);
        selectionsort(c, i);
    }
    p.addSeries("total-bubble", "atr-elem-bubble", "comp-elem-bubble");
    p.addSeries("total-insertion", "atr-elem-insertion", "comp-elem-insertion");
    p.addSeries("total-selection", "atr-elem-selection", "comp-elem-selection");
    
    p.createGroup("Caz favorabil atribuiri", "atr-elem-bubble", "atr-elem-insertion","atr-elem-selection");
    p.createGroup("Caz favorabil comparari", "comp-elem-bubble", "comp-elem-insertion","comp-elem-selection");
    p.createGroup("Caz favorabil total", "total-bubble", "total-insertion", "total-selection");
        

    //caz defavorabil
    p.reset("Caz defavorabil");
    for (int i = 100;i <= 1500;i += 100) {
        FillRandomArray(a, i, 0, 1000, false, 2);
        CopyArray(b, a, i);
        CopyArray(c, a, i);
        bubblesort(a, i);
        insertionsort(b, i);
        selectionsort(c, i); // sirul dat e de forma {n, 1, 2, 3, ... , n - 1} 
    }
    p.addSeries("total-bubble", "atr-elem-bubble", "comp-elem-bubble");
    p.addSeries("total-insertion", "atr-elem-insertion", "comp-elem-insertion");
    p.addSeries("total-selection", "atr-elem-selection", "comp-elem-selection");

    p.createGroup("Caz defavorabil atribuiri", "atr-elem-bubble", "atr-elem-insertion", "atr-elem-selection");
    p.createGroup("Caz defavorabil comparari", "comp-elem-bubble", "comp-elem-insertion", "comp-elem-selection");
    p.createGroup("Caz defavorabil total", "total-bubble", "total-insertion", "total-selection");

    //caz mediu
    p.reset("Caz mediu statistic");
  
    for (int test = 0; test < NR_TESTS; test++) {
        for (int i = STEP_SIZE;i <= 2000; i += STEP_SIZE) {
            {
                FillRandomArray(a, i);
                CopyArray(b, a, i);
                CopyArray(c, a, i);
                bubblesort(a, i);
                insertionsort(b, i);
                selectionsort(c, i);
            }
        }
    }
    p.divideValues("atr-elem-bubble", NR_TESTS);
    p.divideValues("atr-elem-insertion", NR_TESTS);
    p.divideValues("atr-elem-selection", NR_TESTS);

    p.divideValues("comp-elem-bubble", NR_TESTS);
    p.divideValues("comp-elem-insertion", NR_TESTS);
    p.divideValues("comp-elem-selection", NR_TESTS);

    p.addSeries("total-bubble", "atr-elem-bubble", "comp-elem-bubble");
    p.addSeries("total-insertion", "atr-elem-insertion", "comp-elem-insertion");
    p.addSeries("total-selection", "atr-elem-selection", "comp-elem-selection");

    p.createGroup("Caz mediu atribuiri", "atr-elem-bubble", "atr-elem-insertion", "atr-elem-selection");
    p.createGroup("Caz mediu comparari", "comp-elem-bubble", "comp-elem-insertion", "comp-elem-selection");
    p.createGroup("Caz mediu total", "total-bubble", "total-insertion", "total-selection");

    p.showReport();
    return 0;
}