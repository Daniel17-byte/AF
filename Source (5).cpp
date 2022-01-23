#include <iostream>
using namespace std;

int parrentArray[11] = { 0, 2, 7, 5, 2, 7, 7, -1, 5,2 };

//pretty print R1
void prettyPrintR1(int parrentArray[], int elem, int root, int lvl, int* visited)
{
	for (int i = 1; i <= lvl; i++)
	{
		printf("   ");
	}
	printf("%d\n", root);

	visited[root] = 1;
	
	for (int i = 1; i < elem; i++)
	{
		if (visited[i] == 0 && parrentArray[i] == root)
		{
			prettyPrintR1(parrentArray, elem, i, lvl + 1, visited);
		}
	}
}
//pretty print R1



/////////////////////////transformare 1
typedef struct nodeR2 {
	int key;
	int numberOfChildren;
	struct nodeR2* childrenArray[10];
}nodeR2;

nodeR2* rootR2 = NULL;
nodeR2* nodesArrayR2[11];

// de la parrentArray la arbore multicai
void T1(int* parrentArray, int n) {

	// initializam nodurile noii reprezentari
	for (int i = 1; i <= n; i++) {

		nodesArrayR2[i] = (nodeR2*)malloc(sizeof(nodeR2));
		nodesArrayR2[i]->key = i;
		nodesArrayR2[i]->numberOfChildren = 0;

		// initializam copii cu NULL
		for (int j = 0; j < 10; j++) {
			nodesArrayR2[i]->childrenArray[j] = NULL;
		}
	}

	for (int i = 1; i < n; i++) {

		// gasim radacina noii reprezentari
		if (parrentArray[i] == -1) {
			rootR2 = nodesArrayR2[i];
		}

		else {

			// este copilul unui nod
			nodeR2* child = nodesArrayR2[i];

			// ii gasim parintele
			nodeR2* parrent = nodesArrayR2[parrentArray[i]];

			//adaugam fiul in linsta copiilor parintelui
			parrent->childrenArray[parrent->numberOfChildren++] = child;
		}
	}
}

void prettyPrintR2(nodeR2* root, int level) {

	if (root != NULL) {
		for (int i = 1; i <= level; i++)
			printf("   ");
		printf("%d\n", root->key);
		for (int i = 0; i < root->numberOfChildren; i++) {
			prettyPrintR2(root->childrenArray[i], level + 1);
		}
	}

}
/////////////////////////transformare 1




/////////////////////////transformare 2
typedef struct nodeR3 {
	int key;
	struct nodeR3* child;
	struct nodeR3* sibling;
}nodeR3;

nodeR3* createNodeR3(int key) {
	nodeR3* node = (nodeR3*)malloc(sizeof(nodeR3));
	node->key = key;
	node->child = NULL;
	node->sibling = NULL;
	return node;
}

// de la multicai la binar
nodeR3* T2(nodeR2* root) {

	if (root == NULL) {
		return NULL;
	}
	else {

		nodeR3* node = createNodeR3(root->key);

		int nrOfChildren = root->numberOfChildren;
		node->child = T2(root->childrenArray[0]);

		nodeR3* siblingsList;

		siblingsList = node->child;

		int i = 1; 
		while (i < nrOfChildren) {
			siblingsList->sibling = T2(root->childrenArray[i]);

			if (siblingsList != NULL)
				siblingsList = siblingsList->sibling;

			i++;
		}
		return node;
	}
}

void prettyPrintR3(nodeR3* root, int level) {

	if (root != NULL) {
		for (int i = 0; i < level; i++)
			printf("   ");
		printf("%d\n", root->key);
		prettyPrintR3(root->child, level + 1);
		prettyPrintR3(root->sibling, level);
	}

}
/////////////////////////transformare 2



int main()
{
	int length = 10;
	int* vizitat = (int*)calloc(length, sizeof(int));
	int i;

	printf("****Parrent Array****\n");
	for (i = 0; i < length; i++) {
		printf(" %d  ", i);
	}
	printf("\n");
	for (i = 0; i < length; i++) {
		printf("%d   ", parrentArray[i]);
	}
	printf("\n");

	printf("\nPRETTY PRINT 1\n");
	prettyPrintR1(parrentArray, length, 7, 0, vizitat);

	printf("\nTRANSFORMAREA 1 \n");
	T1(parrentArray, 10);
	prettyPrintR2(rootR2, 0);

	printf("\nTRANSFORMAREA 2 \n");
	nodeR3* binaryRoot = T2(rootR2);
	prettyPrintR3(binaryRoot, 0);

	return 0;
}