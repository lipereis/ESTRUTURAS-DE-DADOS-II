/*UNIVERSIDADE FEDERAL DA FRONTEIRA SUL
 *DISCENTE: FILIPE DOS REIS SANTOS - 1521100007
 *DOCENTE: RICARDO
 *DISCIPLINA: ESTRUTURAS DE DADOS II
 */

#include <stdio.h>
#include <stdlib.h>

struct treeNode{
	int key, heightOfNode, levelOfNode;
	int rightHeight, leftHeight;
	struct treeNode *left, *right, *father;
};
typedef struct treeNode TreeNode;

struct tree{
	struct treeNode *root;
};
typedef struct tree Tree;


/*Testanto o maior de dois inteiros*/
int moreThan(int c, int d){
		return (c > d) ? c:d;
}

//Testanto altura
int TreeHeight(TreeNode *treePtr){
		return (treePtr != NULL) ? treePtr->heightOfNode:0;
}

//inicializando árvore
Tree *InitializeTree( void ){
	Tree *newNode = (Tree*)malloc(sizeof(Tree));
	newNode->root = NULL;
	
	return newNode;		
}

//criando novo nó
TreeNode *CreatingNewNode (int value, int level){
	TreeNode *newNode = (TreeNode*)calloc(1, sizeof(TreeNode));
	newNode->key = value;
	newNode->father = newNode->right = newNode->left = NULL;
	newNode->heightOfNode = newNode->rightHeight = newNode->leftHeight = 1;
	newNode->levelOfNode = 0;
	
	return newNode;
}

//atualizando altura
TreeNode *RefreshHeight(TreeNode *treePtr){
		if(treePtr->right != NULL){
				treePtr->right->heightOfNode = TreeHeight(treePtr->right);
		}else{
				treePtr->rightHeight = 0;
		}
		
		if(treePtr->left != NULL){
				treePtr->left->heightOfNode = TreeHeight(treePtr->left);			
		}else{
				treePtr->leftHeight = 0;
		}
		
		
		treePtr->rightHeight = TreeHeight(treePtr->right);
		treePtr->leftHeight = TreeHeight(treePtr->left);
		treePtr->heightOfNode = 1 + moreThan(treePtr->leftHeight, treePtr->rightHeight);
		
		return treePtr;
}

//rotacionando a esquerda
TreeNode *LeftRotation(TreeNode *treePtr){
		TreeNode *x, *y;
		x = treePtr->right;
		y = x->left;
		
		x->left = treePtr;
		treePtr->right = y;
		
		x->father = treePtr->father;
		treePtr->father = x;
		
		treePtr = RefreshHeight(treePtr);
		x = RefreshHeight(x);
		
		return x;
}

//rotacionando a direita
TreeNode *RightRotation(TreeNode *treePtr){
		TreeNode *x, *y;
		x = treePtr->left;
		y = x->right;
		
		x->right = treePtr;
		treePtr->left = y;
		
		x->father = treePtr->father;
		treePtr->father = x;
		
		treePtr = RefreshHeight(treePtr);
		x = RefreshHeight(x);
		
		return x;
}

//inserindo nó
TreeNode *InsertTreeNode (TreeNode *treePtr, int value, int level){
	int choice;
	
	if(treePtr == NULL){
			return CreatingNewNode(value, level);
	}
	if(value < treePtr->key){
			treePtr->left = InsertTreeNode(treePtr->left, value, level+1);
	}else if(value > treePtr->key){
			treePtr->right = InsertTreeNode(treePtr->right, value, level+1);
	}else{
			puts("This value is already in the tree");
			puts("Insert a number different than 0 to continue");
			scanf("%d", &choice);
			
			return treePtr;
	}
	
	treePtr->leftHeight = TreeHeight(treePtr->left);
	treePtr->rightHeight = TreeHeight(treePtr->right);
	
	treePtr->levelOfNode = 1 + moreThan(treePtr->leftHeight, treePtr->rightHeight);
	treePtr->heightOfNode = 1 + moreThan(treePtr->leftHeight, treePtr->rightHeight);
	
	int balance = treePtr->leftHeight - treePtr->rightHeight;
	
	if(balance > 1 && value < treePtr->left->key){
			return RightRotation(treePtr);
	}
	
	if(balance < -1 && value > treePtr->right->key){
			return LeftRotation(treePtr);
	}
	
	if(balance > 1 && value > treePtr->left->key){
			treePtr->left = LeftRotation(treePtr->left);
			return RightRotation(treePtr);
	}
	
	if(balance < -1 && value < treePtr->right->key){
			treePtr->right = RightRotation(treePtr->right);
			return LeftRotation(treePtr);
	}
	
	return treePtr;
}

//nós pais
TreeNode *Parents (TreeNode *treePtr){
		if(treePtr->left != NULL){
				treePtr->left->father = treePtr;
				treePtr->left = Parents(treePtr->left);
		}
		
		if(treePtr->right != NULL){
				treePtr->right->father = treePtr;
				treePtr->right = Parents(treePtr->right);
		}
		
		return treePtr;
}

//nível
TreeNode *TreeLevel(TreeNode *treePtr){
		if(treePtr->father == NULL){
				treePtr->levelOfNode = 0;
		}else{
				treePtr->levelOfNode = treePtr->father->levelOfNode + 1;
		}
		
		if(treePtr->left != NULL){
				treePtr->left = TreeLevel(treePtr->left);
		}
		
		if(treePtr->right != NULL){
				treePtr->right = TreeLevel(treePtr->right);
		}
		
		return treePtr;
}

//menu
void menu(void){
		puts("AVL TREE");
		puts("Choose the option:");
		puts("1 - Insert");
		puts("2 - Show Nodes");
		puts("0 - Finishing the Program");
}

//imprimindo árvore
void PrintTree(TreeNode *treePtr){
		if(treePtr != NULL){
				PrintTree(treePtr->left);
				(treePtr->father != NULL) ? printf("%d\tLevel: %d\tFather Key: %d\n", treePtr->key, treePtr->levelOfNode, treePtr->father->key) : printf("%d\tLevel: %d\tFather Key: Root\n", treePtr->key, treePtr->levelOfNode);
				PrintTree(treePtr->right);
		}
}

//função principal
int main( void ){
		Tree *root = (Tree*)malloc(sizeof(Tree));
		root = InitializeTree();
		int choice = -1, value;
		
		do{
			menu();
			scanf("%d", &choice);
			
			switch(choice){
				case 1:
					puts("Insert new value:");
					scanf("%d", &value);
					root->root = InsertTreeNode(root->root, value, 0);
					root->root = Parents(root->root);
					root->root = TreeLevel(root->root);
					break;
					
				case 2:
					puts("Showing InOrder Mode");
					printf("Root: %d\n", root->root->key);
					PrintTree(root->root);
					puts("Insert 1 or 2 to continue");
					scanf("%d", &choice);
					break;
				
				case 0:
					puts("Thank You for use this program. Until next time!!!");
					break;
				
				default:
					puts("Invalid value");
					puts("Insert 1 or 2 to continue");
					scanf("%d", &choice);
			}
		}while(choice != 0);
		
		return 0;
}
