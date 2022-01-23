#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Profiler.h"

#define NR_TESTE 5

using namespace std;

Profiler prof("Merge_kLists");

int totalOperatii = 0;

//liste

typedef struct node
{
	int key;
	struct node* next;

}NodeT;

typedef struct list
{
	NodeT* first;
	NodeT* last;

}ListT;

ListT* initialize_List()
{
	ListT* new_list = (ListT*)malloc(sizeof(ListT));
	new_list->first = NULL;
	new_list->last = NULL;

	return new_list;
}

void insert_last(ListT* L, int givenKey)
{
	NodeT* p = (NodeT*)malloc(sizeof(NodeT));
	p->key = givenKey;
	p->next = NULL;

	if (L->first == NULL)
	{
		L->first = p;
		L->last = p;
	}
	else
	{
		L->last->next = p;
		L->last = p;
	}
}

NodeT* delete_first(ListT* L)
{
	if (L->first != NULL)
	{
		NodeT* p = L->first;
		if (L->first->next == NULL)
		{
			L->first = NULL;
			L->last = NULL;
		}
		else
		{
			L->first = L->first->next;
			p->next = NULL;
		}
		return p;
	}
	return NULL;
}

//printare lista

void print_list(ListT* L, int givenList)
{
	NodeT* p;
	p = L->first;
	cout << "Lista " << givenList << " contine: ";
	while (p != NULL)
	{
		cout << p->key << " ";
		p = p->next;
	}
	cout << "\n";
}

//printare lista interclasata

void print_merge_list(ListT* mergeList)
{
	NodeT* p;
	p = mergeList->first;
	cout << "Lista interclasata este: \n";
	while (p != NULL)
	{
		cout << p->key << " ";
		p = p->next;
	}
	cout << "\n";
}

ListT* L[500];

void heapify(int k, int root)
{
	ListT* aux;
	int min_one = root;
	int left = 2 * root + 1;
	int right = 2 * root + 2;

	if (left < k)
	{
		totalOperatii++;
		if (L[left]->first->key < L[min_one]->first->key)
			min_one = left;
	}

	if (right < k)
	{
		totalOperatii++;
		if (L[right]->first->key < L[min_one]->first->key)
			min_one = right;
	}

	if (min_one != root)
	{
		totalOperatii += 3;
		aux = L[root];
		L[root] = L[min_one];
		L[min_one] = aux;


		heapify(k, min_one);
	}
}

void buildHeap_BottomUp(int k)
{
	int index;

	index = (k / 2) - 1;
	for (int i = index; i >= 0; i--)
		heapify(k, i);
}

ListT* interclasare(int k)
{
	ListT* mergeList, * aux;
	mergeList = initialize_List();

	NodeT* p;

	int heapsize = k;
	buildHeap_BottomUp(heapsize);

	while (heapsize > 1)
	{
		totalOperatii += 3;
		p = delete_first(L[0]);
		insert_last(mergeList, p->key);

		if (L[0]->first == NULL)
		{
			totalOperatii += 3;
			aux = L[0];
			L[0] = L[heapsize - 1];
			L[heapsize - 1] = aux;
			heapsize--;
		}

		heapify(heapsize, 0);
	}

	while (L[0]->first != NULL)
	{
		totalOperatii += 3;
		p = delete_first(L[0]);
		insert_last(mergeList, p->key);
	}
	totalOperatii++;

	return mergeList;

}

void perf()
{
	//n elemente, k liste
	int n, k;
	int n1 = 10000;
	int k1 = 5, k2 = 10, k3 = 100;
	int size_list;
	int intermediar;
	int* array;
	ListT* mergeList;

	for (int teste = 0; teste < NR_TESTE; teste++)
	{
		//pt K1=5;
		for (n = 100; n <= 10000; n += 100)
		{
			Operation K1_OppTotal = prof.createOperation("K1_OperatiiTotale", n);
			totalOperatii = 0;
			intermediar = 0;
			for (int i = 0; i < k1 - 1; i++)
			{
				size_list = n / (2 * k1) + rand() % (n / (2 * k1) + 1);
				intermediar += size_list;
				L[i] = initialize_List();
				array = (int*)malloc(size_list * sizeof(int));
				FillRandomArray(array, size_list, 10, 50000, false, 1);
				for (int j = 0; j < size_list; j++)
					insert_last(L[i], array[j]);
			}
			size_list = n - intermediar;
			L[k1 - 1] = initialize_List();
			array = (int*)malloc(size_list * sizeof(int));
			FillRandomArray(array, size_list, 10, 50000, false, 1);
			for (int j = 0; j < size_list; j++)
				insert_last(L[k1 - 1], array[j]);

			mergeList = interclasare(k1);
			K1_OppTotal.count(totalOperatii);
		}
	}

	for (int teste = 0; teste < NR_TESTE; teste++)
	{
		//pt K2=10;
		for (n = 100; n <= 10000; n += 100)
		{
			Operation K2_OppTotal = prof.createOperation("K2_OperatiiTotale", n);
			totalOperatii = 0;
			intermediar = 0;
			for (int i = 0; i < k2 - 1; i++)
			{
				size_list = n / (2 * k2) + rand() % (n / (2 * k2) + 1);
				intermediar += size_list;
				L[i] = initialize_List();
				array = (int*)malloc(size_list * sizeof(int));
				FillRandomArray(array, size_list, 10, 50000, false, 1);
				for (int j = 0; j < size_list; j++)
					insert_last(L[i], array[j]);
			}
			size_list = n - intermediar;
			L[k2 - 1] = initialize_List();
			array = (int*)malloc(size_list * sizeof(int));
			FillRandomArray(array, size_list, 10, 50000, false, 1);
			for (int j = 0; j < size_list; j++)
				insert_last(L[k2 - 1], array[j]);

			mergeList = interclasare(k2);
			K2_OppTotal.count(totalOperatii);
		}
	}

	for (int teste = 0; teste < NR_TESTE; teste++)
	{
		//pt K3=100;
		for (n = 100; n <= 10000; n += 100)
		{
			Operation K3_OppTotal = prof.createOperation("K3_OperatiiTotale", n);
			totalOperatii = 0;
			intermediar = 0;
			if (n == 100)
			{
				for (int i = 0; i < k3; i++)
				{
					size_list = 1;
					L[i] = initialize_List();
					array = (int*)malloc(size_list * sizeof(int));
					FillRandomArray(array, size_list, 10, 50000, false, 1);
					for (int j = 0; j < size_list; j++)
						insert_last(L[i], array[j]);
				}
			}
			else
			{
				for (int i = 0; i < k3 - 1; i++)
				{
					size_list = n / (2 * k3) + rand() % (n / (2 * k3) + 1);
					intermediar += size_list;
					L[i] = initialize_List();
					array = (int*)malloc(size_list * sizeof(int));
					FillRandomArray(array, size_list, 10, 50000, false, 1);
					for (int j = 0; j < size_list; j++)
						insert_last(L[i], array[j]);
				}
				size_list = n - intermediar;
				L[k3 - 1] = initialize_List();
				array = (int*)malloc(size_list * sizeof(int));
				FillRandomArray(array, size_list, 10, 50000, false, 1);
				for (int j = 0; j < size_list; j++)
					insert_last(L[k3 - 1], array[j]);
			}


			mergeList = interclasare(k3);
			K3_OppTotal.count(totalOperatii);
		}
	}

	for (int teste = 0; teste < NR_TESTE; teste++)
	{
		//pt n1=10000
		for (k = 10; k <= 500; k += 10)
		{
			Operation N1_OppTotal = prof.createOperation("N_10000_OperatiiTotale", k);
			totalOperatii = 0;
			intermediar = 0;

			for (int i = 0; i < k - 1; i++)
			{
				size_list = n1 / (2 * k) + rand() % (n / (2 * k) + 1);
				intermediar += size_list;
				L[i] = initialize_List();
				array = (int*)malloc(size_list * sizeof(int));
				FillRandomArray(array, size_list, 10, 50000, false, 1);
				for (int j = 0; j < size_list; j++)
					insert_last(L[i], array[j]);
			}
			size_list = n1 - intermediar;
			L[k - 1] = initialize_List();
			array = (int*)malloc(size_list * sizeof(int));
			FillRandomArray(array, size_list, 10, 50000, false, 1);
			for (int j = 0; j < size_list; j++)
				insert_last(L[k - 1], array[j]);

			mergeList = interclasare(k);
			N1_OppTotal.count(totalOperatii);
		}
	}

	prof.divideValues("K1_OperatiiTotale", NR_TESTE);
	prof.divideValues("K2_OperatiiTotale", NR_TESTE);
	prof.divideValues("K3_OperatiiTotale", NR_TESTE);
	prof.divideValues("N_10000_OperatiiTotale", NR_TESTE);

	prof.createGroup("K_LISTE_OperatiiTotale", "K1_OperatiiTotale", "K2_OperatiiTotale", "K3_OperatiiTotale");

	prof.showReport();
}

void demo()
{
	int* array;
	int size_list;
	int n = 30, intermediar = 0;
	int k = 5;
	ListT* mergeList;

	for (int i = 0; i < k - 1; i++)
	{

		size_list = n / (2 * k) + rand() % (n / (2 * k) + 1);
		intermediar += size_list;
		L[i] = initialize_List();
		array = (int*)malloc(size_list * sizeof(int));
		FillRandomArray(array, size_list, 10, 100, false, 1);
		for (int j = 0; j < size_list; j++)
			insert_last(L[i], array[j]);
		print_list(L[i], i);

	}
	size_list = n - intermediar;
	L[k - 1] = initialize_List();
	array = (int*)malloc(size_list * sizeof(int));
	FillRandomArray(array, size_list, 10, 100, false, 1);
	for (int j = 0; j < size_list; j++)
		insert_last(L[k - 1], array[j]);
	print_list(L[k - 1], k - 1);
	cout << "\n";

	mergeList = interclasare(k);

	print_merge_list(mergeList);

}

int main()
{
	//demo();
	perf();
}

/*

-Complexitate(O[n * log k]);
-acest algoritm combina k liste sortate intr-o lista cu n elemente
-de la un anumit k se aplatizeaza cresterea operatiilor
-numarul total de elemente(n) afecteaza mai mult performanta 
algoritmului decat numarul de liste(k);

*/