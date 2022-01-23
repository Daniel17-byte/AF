#include <stdlib.h>
#include <stdio.h>
#include "Profiler.h"

Profiler profiler("avg");

enum { FREE, OCCUPIED, DELETED };//starea celulei in tabela

//structura pentru celule

typedef struct {
    int key;
    int status;
}Celule;

//initializare tabela de dispersie

void initHashTable(Celule* H, int dimHash)
{
    for (int i = 0; i < dimHash;i++)
    {
        H[i].status = FREE;
    }
}

//functii pentru quadratic probing

int h_prime(int k, int m)
{
    return k % m;
}


int quadratic_probing(int key, int dimHash, int index)
{
    return (h_prime(key, dimHash) + index + index * index) % dimHash;
}

//afisare tabela de dispersie

void printHashTable(Celule* H, int m)
{
    printf("\nHashTable: \n");
    for (int i = 0; i < m; i++)
    {
        if (H[i].status == OCCUPIED)
            printf("T[%d]=%d\n", i, H[i].key);
        else
            printf("T[%d]= --\n", i);
    }
}

//inserare in tabela de dispersie

void hashInsert(Celule* H, int key, int dimHash, int* flag)
{
    *(flag) = 0;
    int i = 0;
    int check = 0;
    do {
        int j = quadratic_probing(key, dimHash, i);
        if (H[j].status == FREE || H[j].status == DELETED)
        {
            H[j].key = key;
            H[j].status = OCCUPIED;
            check = 1;
            break;
        }
        else i++;
    } while (i <= dimHash - 1);

    if (check == 0)
    {
        printf("\nError->tabela este plina, nu s-a putut insera cheia:%d", key);
        *(flag) = 1;
    }
}

//cautare in tabela de dispersie

int hashSearch(Celule* H, int key, int dimHash, int* effort)
{
    int i = 0;
    int j;
    do {
        j = quadratic_probing(key, dimHash, i);
        (*effort)++;
        if (H[j].key == key)
        {
            return j;
            break;
        }
        else i++;

        if (H[j].status == FREE)
            return -1;
    } while (i <= dimHash - 1 && (H[j].status == DELETED || H[j].status == OCCUPIED));

    //printf("Cheia %d nu a fost gasita\n",key);
    return -1;

}

//stergere din tabela de dispersie

void hashDelete(Celule* H, int key, int dimHash)
{
    int i = 0, check = 0;

    do {
        int j = quadratic_probing(key, dimHash, i);
        if (H[j].key == key)
        {
            check = 1;
            H[j].status = DELETED;
            H[j].key = -INT_MAX;
            break;
        }
        else i++;
    } while (i <= dimHash - 1);

    if (check == 0)
        printf("Cheia %d nu a fost gasita\n", key);
}

//verifica daca exista in tabela

bool isNumberInVector(Celule* hashtable, int dimHash, int number)
{
    for (int i = 0;i < dimHash;i++)
    {
        if (hashtable->key == number)
            return true;
    }
    return false;
}

//genereaza o tabela de dispersie si face cazul mediu statistic

void generatorHashTables(int loadFactor)
{
    int dimHash = 9973;
    Celule* hashTable = (Celule*)malloc(dimHash * sizeof(Celule));
    initHashTable(hashTable, dimHash);

    int n = (loadFactor * dimHash) / 100;
    printf("Factor de umplere : %d  , %d elemente\n", loadFactor, n);

    //int *vectorElemente = (int *)malloc(sizeof(int) * 10007);
    int v[10007];

    FillRandomArray(v, 10006, 10, 25000, true, 0);

    int contor = 0;
    int i = 0;

    while (contor < n)
    {
        int flag;
        // printf("contor %d" , contor );
        hashInsert(hashTable, v[i], dimHash, &flag);
        if (flag == 0)
            contor++;
        i++;
    }
    //printf("contor %d" , i);

    int effortMaximum = -1;
    float effortMedium = 0;
    int effortTotal = 0;
    for (int i = 0; i < 1500; i++)
    {
        int effAux = 0;
        hashSearch(hashTable, v[i], dimHash, &effAux);
        effortTotal += effAux;
        effortMaximum = (effAux > effortMaximum) ? effAux : effortMaximum;
    }
    effortMedium = float(effortTotal / 1500.0);
    printf("Factor de umplere : %d - Efort mediu gasit: %.2f - Efort maxim gasit : %d ", loadFactor, effortMedium, effortMaximum);

    int v1[1500];
    FillRandomArray(v1, 1500, 25001, 50000, true, 0);

    int effortMaximumN = -1;
    float effortMediumN = 0;
    int effortTotalN = 0;

    int nbElem = 0;
    int j = 1;
    while (nbElem < 1500)
    {
        if (isNumberInVector(hashTable, dimHash, v1[j]) == false)
        {
            nbElem++;
            //printf("%d " ,isNumberInVector(hashTable,dimHash,v1[j]) );
            int effAux = 0;
            int x = hashSearch(hashTable, v1[j], dimHash, &effAux);
            //printf("%d " ,x );
            effortTotalN += effAux;
            effortMaximumN = (effAux > effortMaximumN) ? effAux : effortMaximumN;
            j++;
        }
        else {
            j++;
        }
    }
    // printf("j=%d nb=%d\n" , j , nbElem);
    effortMediumN = float(effortTotalN / 1500.0);

    //printf("%f " , effortMediumN);
    printf("\nFactor de umplere : %d - Efort mediu negasit: %.2f - Efort maxim negasit : %d ", loadFactor, effortMediumN, effortMaximumN);
    printf("\n\n");
}

//demo pentru stare curenta ,after insert,after search,after delete

void demo()
{
    int loadFactor = 95;
    int dimHash = 20;
    int n = 19;

    Celule* hashTable = (Celule*)malloc(dimHash * sizeof(Celule));
    initHashTable(hashTable, dimHash);

    int vector[21] = { 19, 29, 44, 13, 28, 17, 33, 18, 50, 34, 43, 27, 33, 14, 15, 30, 26, 45, 46 };
    //FillRandomArray(vector,21,10,50,true,0);
    int flag;
    int efort = 0;
    printf("Vector initial: \n");
    for (int i = 0; i < n; i++)
    {
        //   hashInsert(hashTable,vector[i],dimHash);
        printf("%d ", vector[i]);
    }

    for (int i = 0; i < n; i++)
    {
        hashInsert(hashTable, vector[i], dimHash, &flag);
        //printf("%d ", vector[i]);
    }

    printf("\nTabela de dispersie:\n");
    printHashTable(hashTable, dimHash);

    printf("Status Tabela:\n");
    for (int i = 0; i < dimHash;i++)
    {
        printf("%d ", hashTable[i].status);
    }

    hashDelete(hashTable, 33, dimHash);
    printf("\nDupa delete:-------\n");
    printHashTable(hashTable, dimHash);

    printf("Status Tabela:\n");
    for (int i = 0; i < dimHash;i++)
    {
        printf("%d ", hashTable[i].status);
    }

    printf("\nDupa cautare:-------\n");

    printf("Cheia 33 este la pozitia : %d \n", hashSearch(hashTable, 33, dimHash, &efort));
    printHashTable(hashTable, dimHash);

    printf("Status Tabela:\n");
    for (int i = 0; i < dimHash;i++)
    {
        printf("%d ", hashTable[i].status);
    }
    hashInsert(hashTable, 33, dimHash, &flag);
    printf("\nDupa insert 33:-------\n");
    printHashTable(hashTable, dimHash);
}

int main()
{
    printf("----------DEMO----------\n");
    demo();
    printf("\n----------AVG----------\n");

    generatorHashTables(80);
    generatorHashTables(85);
    generatorHashTables(90);
    generatorHashTables(95);
    generatorHashTables(99);


    return 0;
}