#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "Profiler.h"

Profiler profiler("DOS_Trees");

int number_op_sel = 0;
int number_op_del = 0;
int number_op_bld = 0;

//structura pentru arbore

struct Node
{
	int key;
	Node* left;
	Node* right;
	int size;
};

//Construieste arborele

Node* buildTree(int left, int right)
{
	struct Node* pNew = (struct Node*)malloc(sizeof(struct Node));
	number_op_bld++;
	if (left <= right)
	{
		int mid = (left + right) / 2;

		number_op_bld += 2;
		pNew->key = mid;
		pNew->size = 1;

		number_op_bld += 2;
		pNew->left = buildTree(left, mid - 1);
		pNew->right = buildTree(mid + 1, right);


		number_op_bld++;
		if (pNew->left != NULL)
		{
			number_op_bld++;
			pNew->size = pNew->size + pNew->left->size;
		}

		number_op_bld++;
		if (pNew->right != NULL)
		{
			number_op_bld++;
			pNew->size = pNew->size + pNew->right->size;
		}

		return pNew;
	}
	else return NULL;
}

void printTree(struct Node* root, int level)
{
	if (root == NULL) return;

	printTree(root->right, level + 1);
	printf("%*s(%d,%d)\n\n", 7 * level, "", root->key, root->size);
	printTree(root->left, level + 1);

}

//OS Select

Node* OS_Select(struct Node* root, int i)
{
	number_op_sel++;
	if (root != NULL)
	{
		int r;
		number_op_sel++;
		if (root->left != NULL)  r = root->left->size + 1;
		else r = 1;
		if (i == r) return root;
		else
		{
			if (i < r) return OS_Select(root->left, i);
			else return OS_Select(root->right, i - r);
		}
	}
	else return NULL;

}

//gasire minim

struct Node* findMin(struct Node* pNode)
{
	number_op_del++;
	if (pNode == NULL) return NULL;
	number_op_del++;
	if (pNode->left != NULL) return findMin(pNode->left);
	else
		return pNode;

}

//OS delete

struct Node* OS_delete_node(struct Node* pNode, int x)
{
	number_op_del++;
	if (pNode == NULL)
	{
		printf("\nElement %c negasit.\n", x);
	}
	else
	{
		number_op_del++;
		if (x < pNode->key)
		{
			pNode->left = OS_delete_node(pNode->left, x);
			pNode->size--;
			number_op_del++;
		}
		else
		{
			number_op_del++;
			if (x > pNode->key)
			{
				pNode->right = OS_delete_node(pNode->right, x);
				pNode->size--;
				number_op_del++;
			}
			else
			{
				number_op_del += 2;
				if (pNode->right != NULL && pNode->left != NULL)
				{
					pNode->size--;
					number_op_del++;
					struct Node* temp = findMin(pNode->right);
					pNode->key = temp->key;
					number_op_del++;
					pNode->right = OS_delete_node(pNode->right, temp->key);
				}
				else
				{
					struct Node* temp = pNode;
					number_op_del++;
					if (pNode->left == NULL)
					{
						pNode = pNode->right;
					}
					else
					{
						number_op_del++;

						if (pNode->right == NULL)
						{
							pNode = pNode->left;
						}
					}
					free(temp);
				}
			}
		}
	}
	return pNode;
}

int main()
{

	printf("1 pentru demo , 2 pentru grafice .\n");
	int demo;
	scanf("%d", &demo);

	if (demo == 1)
	{
		struct Node* root = NULL;
		int n = 11;
		root = buildTree(1, n);
		printf("TREE : \n");
		printTree(root, 0);

		printf("\n");
		srand(time(NULL));

		// random select & delete
		int a = 2;// rand() % (n) + 1;
		printf("Gasim al %d-lea cel mai mic ! \n", a);
		if (OS_Select(root, a) != NULL) printf("Am gasit %d , acum il vom sterge ! \n", OS_Select(root, a)->key);
		root = OS_delete_node(root, OS_Select(root, a)->key);
		printTree(root, 0);
		n--;

		int b = 3; //rand() % (n - 1) + 1;
		printf("\nGasim al %d-lea cel mai mic ! \n", b);
		if (OS_Select(root, b) != NULL) printf("Am gasit %d , acum il vom sterge ! \n", OS_Select(root, b)->key);
		root = OS_delete_node(root, OS_Select(root, b)->key);
		printTree(root, 0);
		n--;

		int c = 4; //rand() % (n - 1) + 1;
		printf("\nGasim al %d-lea cel mai mic ! \n", c);
		if (OS_Select(root, c) != NULL) printf("Am gasit %d , acum il vom sterge ! \n", OS_Select(root, c)->key);
		root = OS_delete_node(root, OS_Select(root, c)->key);
		printTree(root, 0);
		n--;

	}
	else
	{
		int n;
		for (n = 100; n <= 10000; n += 100)
		{

			number_op_sel = 0;
			number_op_del = 0;
			number_op_bld = 0;
			struct Node* root = NULL;
			root = buildTree(1, n);

			int i;
			srand(time(NULL));
			int nnn = n;
			for (i = 0; i < n; i++)
			{
				int xth_smallest = rand() % (nnn)+1;
				struct Node* val = OS_Select(root, xth_smallest);

				root = OS_delete_node(root, val->key);
				nnn--;
			}

			profiler.countOperation("nbOp_SEL", n, number_op_sel);
			profiler.countOperation("nbOp_DEL", n, number_op_del);
			profiler.countOperation("nbOp_BLD", n, number_op_bld);
			//profiler.countOperation("sumOps", n, number_op_sel + number_op_del + number_op_bld);

			profiler.createGroup("ops", "nbOp_SEL", "nbOp_DEL", "nbOp_BLD");
			profiler.addSeries("opsSelDel", "nbOp_SEL", "nbOp_DEL");
			profiler.addSeries("TotalOps", "opsSelDel", "nbOp_BLD");
		}
		profiler.showReport();
	}

	return 0;
}