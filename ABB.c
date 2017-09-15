/*UNIVERSIDADE FEDERAL DA FRONTEIRA SUL
 *DISCENTE: FILIPE DOS REIS SANTOS - 1521100007
 *DOCENTE: RICARDO PARIZOTTO
 *DISCIPLINA: ESTRUTURAS DE DADOS II - 2017/2

 OBS: Professor eu utilizei o espanhol para escrever esse código para fins de prática da língua, pois a estudo também.
 */

#include <stdio.h>
#include <stdlib.h>

//estrutura principal
struct nodoDelArbol {
	int informacion;
	struct nodoDelArbol *izquierda;
	struct nodoDelArbol *derecha;
};
typedef struct nodoDelArbol NodoDelArbol;

//estrutura auxiliar
struct raizDelArbol {
	struct nodoDelArbol *raiz;
};
typedef struct raizDelArbol RaizDelArbol;

//función que busca un elemento en el árbol
NodoDelArbol *BuscarElementoEnElArbol(NodoDelArbol *arbolPtr, int informacion){
		if(arbolPtr == NULL){
				return NULL;
		}else if(arbolPtr->informacion > informacion){
				return BuscarElementoEnElArbol(arbolPtr->izquierda, informacion);
		}else if(arbolPtr->informacion < informacion){
				return BuscarElementoEnElArbol(arbolPtr->derecha, informacion);
		}else{
				return arbolPtr;
		}
}

//impression pre-orden
void ImpressionPreOrden(NodoDelArbol *arbolPtr){
		if(arbolPtr != NULL){
				printf("%d\n", arbolPtr->informacion);
				ImpressionPreOrden(arbolPtr->izquierda);
				ImpressionPreOrden(arbolPtr->derecha);
		}
}

//impression en-order
void ImpressionEnOrden(NodoDelArbol *arbolPtr){
		if(arbolPtr != NULL){
				ImpressionEnOrden(arbolPtr->izquierda);
				printf("%d\n", arbolPtr->informacion);
				ImpressionEnOrden(arbolPtr->derecha);
		}
}

//impression Pos-orden
void ImpressionPosOrden(NodoDelArbol *arbolPtr){
		if(arbolPtr != NULL){
				ImpressionPosOrden(arbolPtr->izquierda);
				ImpressionPosOrden(arbolPtr->derecha);
				printf("%d\n", arbolPtr->informacion);
		}
}

//función que inicializa a estrutura auxiliar
RaizDelArbol *InicializacionDelArbol(void) {
	RaizDelArbol *nuevaRaiz = (RaizDelArbol*)malloc(sizeof(RaizDelArbol));
	nuevaRaiz->raiz = NULL;

	return nuevaRaiz;
}

//función que crea un nuevo nodo del arbol
NodoDelArbol *CreacionDeUnNuevoNodoDelArbol(int informacion){
	NodoDelArbol *nuevoNodo = (NodoDelArbol*)calloc(1, sizeof(NodoDelArbol));
	nuevoNodo->informacion = informacion;
	nuevoNodo->izquierda = nuevoNodo->derecha = NULL;

	return nuevoNodo;
}

//función que hace la inserción
NodoDelArbol *InsercionEnElArbol(NodoDelArbol *arbolPtr, int informacion){
	if(arbolPtr == NULL){
		return CreacionDeUnNuevoNodoDelArbol(informacion);
	}
	if(informacion < arbolPtr->informacion){
		arbolPtr->izquierda = InsercionEnElArbol(arbolPtr->izquierda, informacion);
	}else if(informacion > arbolPtr->informacion){
		arbolPtr->derecha = InsercionEnElArbol(arbolPtr->derecha, informacion);
	}

	return arbolPtr;
}

//función que hace la exclusión
NodoDelArbol *RetirarUnElementoDelArbol(NodoDelArbol *arbolPtr, int informacion){
		if(arbolPtr == NULL){
				return NULL;
		}else if(arbolPtr->informacion > informacion){
				arbolPtr->izquierda = RetirarUnElementoDelArbol(arbolPtr->izquierda, informacion);
		}else if(arbolPtr->informacion < informacion){
				arbolPtr->derecha = RetirarUnElementoDelArbol(arbolPtr->derecha, informacion);
		}else{//encontraste el elemento para remoción
				if(arbolPtr->izquierda == NULL && arbolPtr->derecha == NULL){
						free(arbolPtr);
						arbolPtr = NULL;
				}else if( arbolPtr->izquierda == NULL){
						NodoDelArbol *temp = arbolPtr;
						arbolPtr = arbolPtr->derecha;
						free(temp);
				}else if(arbolPtr->derecha){
						NodoDelArbol *temp = arbolPtr;
						arbolPtr = arbolPtr->izquierda;
						free(temp);
				}else{
						NodoDelArbol *temp = arbolPtr->izquierda;
						while(temp->derecha != NULL){
								temp = temp->derecha;
						}
						arbolPtr->informacion = temp->informacion;
						temp->informacion = informacion;
						arbolPtr->izquierda = RetirarUnElementoDelArbol(arbolPtr->izquierda, informacion);
				}
		}
	return arbolPtr;
}

//El menú del código
void menu(void){
		puts("============================");
		puts("ABB Arbol");
		puts("Escoja la opción deseada:");
		puts("1 - Inserir");
		puts("2 - Retirar");
		puts("3 - Imprimir");
		puts("0 - Cerrar la execución");
		puts("============================");
}

//el programa principal
int main( void ){
		RaizDelArbol *raiz;
		raiz = InicializacionDelArbol();
		int controlar = -1, valor;
		
		do{
			menu();
			scanf("%d", &controlar);
			
			switch(controlar){
				case 1:
					puts("Insira el valor:");
					scanf("%d", &valor);
					printf("\n");
					raiz->raiz = InsercionEnElArbol(raiz->raiz, valor);
					break;
					
				case 2:
					puts("Insira el valor:");
					scanf("%d", &valor);
					printf("\n");
					raiz->raiz = RetirarUnElementoDelArbol(raiz->raiz, valor);
					break;
					
				case 3:
					printf("\n");
					puts("EnOrden");
					ImpressionEnOrden(raiz->raiz);
					printf("\n");
					puts("PosOrden");
					ImpressionPosOrden(raiz->raiz);
					printf("\n");
					puts("PreOrden");
					ImpressionPreOrden(raiz->raiz);
					printf("\n");
					puts("Insira un opción válida");
					scanf("%d", &controlar);
					printf("\n");
					break;
				
				case 0:
					puts("Gracias por la utilización. Hasta luego!!!");
					break;
				
				default:
					puts("Valor inválido");
					puts("Insira un valor válido");
					scanf("%d", &controlar);
					printf("\n");
			}
		}while(controlar != 0);
		
		return 0;
}
