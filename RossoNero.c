/*UNIVERSIDADE FEDERAL DA FRONTEIRA SUL
 *DISCENTE: FILIPE DOS REIS SANTOS - 1521100007
 *DOCENTE: RICARDO PARIZOTTO
 *DISCIPLINA: ESTRUTURAS DE DADOS II - 2017/2

 OBS: Professor eu utilizei o italiano para escrever esse código para fins de prática da língua, pois a estudo também.
 */

#include <stdio.h>
#include <stdlib.h>
#define ROSSO 1
#define NERO 0

//struttura principale
struct nodoDellAlbero {
		int colore;
		int informazioni;
		struct nodoDellAlbero *padre;
		struct nodoDellAlbero *sinistra;
		struct nodoDellAlbero *destra;
};
typedef struct nodoDellAlbero NodoDellAlbero;

//struttura ausiliaria
struct radiceDellAlbero {
		struct nodoDellAlbero *radice;
		struct nodoDellAlbero *nil;
};
typedef struct radiceDellAlbero RadiceDellAlbero;

//funzione per ricercare un elemento nell'albero
NodoDellAlbero *RicercareUnElementoNellAlbero(RadiceDellAlbero *radicePtr, NodoDellAlbero *alberoPtr, int informazioni){
		if(alberoPtr == radicePtr->nil || alberoPtr->informazioni == informazioni){
			return alberoPtr;
		}
		if(informazioni <= alberoPtr->informazioni){
			return RicercareUnElementoNellAlbero(radicePtr, alberoPtr->sinistra, informazioni);
		}

		return RicercareUnElementoNellAlbero(radicePtr, alberoPtr->destra, informazioni);
}

//funzione per ricercare il nodo più pìcollo
NodoDellAlbero *NodoPiuPiccolo(RadiceDellAlbero *radicePtr, NodoDellAlbero *alberoPtr){
		NodoDellAlbero *ausiliaria = alberoPtr;

		while(ausiliaria->sinistra != radicePtr->nil){
			ausiliaria = ausiliaria->sinistra;
		}

		return ausiliaria;
}

//il successore
NodoDellAlbero *AlberoSuccessore(RadiceDellAlbero *radicePtr, NodoDellAlbero *alberoPtr){
		if(alberoPtr->destra != radicePtr->nil){
			return NodoPiuPiccolo(radicePtr, alberoPtr->destra);
		}

		NodoDellAlbero *padre = alberoPtr->padre;
		while(padre != radicePtr->nil && alberoPtr == padre->destra){
			alberoPtr = padre;
			padre = padre->padre;
		}

		return padre;
}

//stampare in pre-ordine
void StampaPreOrdine(NodoDellAlbero *alberoPtr, NodoDellAlbero *nil){
		if(alberoPtr != nil){
				printf("%d\t", alberoPtr->informazioni);
				if(alberoPtr->colore == NERO){
					printf("NERO\n");
				}else{
					printf("ROSSO\n");
				}
				StampaPreOrdine(alberoPtr->sinistra, nil);
				StampaPreOrdine(alberoPtr->destra, nil);
		}
}

//stampare in in-ordine
void StampaInOrdine(NodoDellAlbero *alberoPtr, NodoDellAlbero *nil){
		if(alberoPtr != nil){
				StampaInOrdine(alberoPtr->sinistra, nil);
				printf("%d\t", alberoPtr->informazioni);
				if(alberoPtr->colore == NERO){
					printf("NERO\n");
				}else{
					printf("ROSSO\n");
				}
				StampaInOrdine(alberoPtr->destra, nil);
		}
}

//stampare in pos-ordine
void StampaPostOrdine(NodoDellAlbero *alberoPtr, NodoDellAlbero *nil){
		if(alberoPtr != nil){
				StampaPostOrdine(alberoPtr->sinistra,nil);
				StampaPostOrdine(alberoPtr->destra, nil);
				printf("%d\t", alberoPtr->informazioni);
				if(alberoPtr->colore == NERO){
					printf("NERO\n");
				}else{
					printf("ROSSO\n");
				}
		}
}

//funzione di inizializzazioni dell'albero
RadiceDellAlbero *InizializzazioniDellAlbero(void) {
		RadiceDellAlbero *nuovaRadice = (RadiceDellAlbero*)malloc(sizeof(RadiceDellAlbero));
		if(nuovaRadice == NULL){
			printf("insuccesso di segmentazioni\n");
			exit(3);
		}
		nuovaRadice->nil = (NodoDellAlbero*)malloc(sizeof(NodoDellAlbero));
		if(nuovaRadice->nil == NULL){
			printf("insuccesso di segmentazioni\n");
			exit(3);
		}
		nuovaRadice->nil->padre = nuovaRadice->nil->sinistra = nuovaRadice->nil->destra = NULL;
		nuovaRadice->nil->colore = NERO;

		nuovaRadice->radice = nuovaRadice->nil;
		return nuovaRadice;
}

//rotazione sinistra
void RotazioneSinistra(RadiceDellAlbero *radicePtr, NodoDellAlbero *x){
		NodoDellAlbero *y;
		y = x->destra;
		x->destra = y->sinistra;

		if(y->sinistra != radicePtr->nil){
			y->sinistra->padre = x;
		}
		y->padre = x->padre;
		if(x->padre == radicePtr->nil){
			radicePtr->radice = y;
		}else if(x == x->padre->sinistra){
			x->padre->sinistra = y;
		}else{
			x->padre->destra = y;
		}
			y->sinistra = x;
			x->padre = y;
}

//rotazione destra
void RotazioneDestra(RadiceDellAlbero *radicePtr, NodoDellAlbero *x){
		NodoDellAlbero *y;
		y = x->sinistra;
		x->sinistra = y->destra;

		if(y->destra != radicePtr->nil){
			y->destra->padre = x;
		}
		y->padre = x->padre;
		if(x->padre == radicePtr->nil){
			radicePtr->radice = y;
		}else if(x == x->padre->destra){
			x->padre->destra = y;
		}else{
			x->padre->sinistra = y;
		}
			y->destra = x;
			x->padre = y;
}

//funzione FixUp per immettere nell'albero
void ImmettereFixUp(RadiceDellAlbero *radicePtr, NodoDellAlbero *alberoPtr){
		NodoDellAlbero *y;

		while(alberoPtr->padre->colore == ROSSO){
			if(alberoPtr->padre == alberoPtr->padre->padre->sinistra){
				y = alberoPtr->padre->padre->destra;
				if(y->colore == ROSSO){
					alberoPtr->padre->colore = NERO;
					y->colore = NERO;
					alberoPtr->padre->padre->colore = ROSSO;
					alberoPtr = alberoPtr->padre->padre;
				}else{
					if(alberoPtr == alberoPtr->padre->destra){
						alberoPtr = alberoPtr->padre;
						RotazioneSinistra(radicePtr, alberoPtr);
						alberoPtr->padre->colore = NERO;
						alberoPtr->padre->padre->colore = ROSSO;
						RotazioneDestra(radicePtr, alberoPtr->padre->padre);
					}else{
						alberoPtr = alberoPtr->padre;
						RotazioneDestra(radicePtr, alberoPtr);
					}
				}
			}else{
				y = alberoPtr->padre->padre->sinistra;
				if(y->colore == ROSSO){
					alberoPtr->padre->colore = NERO;
					y->colore = NERO;
					alberoPtr->padre->padre->colore = ROSSO;
					alberoPtr = alberoPtr->padre->padre;
				}else{
					if(alberoPtr == alberoPtr->padre->sinistra){
						alberoPtr = alberoPtr->padre;
						RotazioneDestra(radicePtr, alberoPtr);
						alberoPtr->padre->colore = NERO;
						alberoPtr->padre->padre->colore = ROSSO;
						RotazioneSinistra(radicePtr, alberoPtr->padre->padre);
					}else{
						alberoPtr = alberoPtr->padre;
						RotazioneSinistra(radicePtr, alberoPtr);
					}
				}
			}
		}
		radicePtr->radice->colore = NERO;
}

//funzione immettere nell'albero
void ImmettereNellAlbero(RadiceDellAlbero *radicePtr, int informazioni){
		NodoDellAlbero *nuovoNodo = (NodoDellAlbero*)malloc(sizeof(NodoDellAlbero));
		if(nuovoNodo == NULL){
			printf("insuccesso di segmentazioni\n");
			exit(3);
		}
		nuovoNodo->padre = nuovoNodo->sinistra = nuovoNodo->destra = radicePtr->nil;
		nuovoNodo->colore = ROSSO;
		nuovoNodo->informazioni = informazioni;

		NodoDellAlbero *x, *y;
		x = radicePtr->radice;
		y = radicePtr->nil;

		while(x != radicePtr->nil){
			y = x;
			if(informazioni < x->informazioni){
				x = x->sinistra;
			}else{
				x = x->destra;
			}
		}

		nuovoNodo->padre = y;

		if(y == radicePtr->nil){
			radicePtr->radice = nuovoNodo;
		}else if(informazioni < y->informazioni){
			y->sinistra = nuovoNodo;
		}else{
			y->destra = nuovoNodo;
		}

		ImmettereFixUp(radicePtr, nuovoNodo);
}

//funzione FixUp per rimuovere dell'albero
void RimuovereFixUp(RadiceDellAlbero *radicePtr, NodoDellAlbero *x){
		NodoDellAlbero *y;

		while(x != radicePtr->radice && x->colore == NERO){
			if(x == x->padre->sinistra){
				y = x->padre->destra;
				if(y->colore == ROSSO){
					y->colore = NERO;
					x->padre->colore = ROSSO;
					RotazioneSinistra(radicePtr, x->padre);
					y = x->padre->destra;
				}
				if(y->sinistra->colore == NERO && y->destra->colore == NERO){
					y->colore = ROSSO;
					x = x->padre;
				}else if(y->destra->colore == NERO){
					y->sinistra->colore = NERO;
					y->colore = ROSSO;
					RotazioneDestra(radicePtr, y);
					y = x->padre->destra;
				}else{
					y->colore = y->padre->colore;
					x->padre->colore = NERO;
					y->destra->colore = NERO;
					RotazioneSinistra(radicePtr, x->padre);
					x = radicePtr->radice;
				}
			}else{
				y = x->padre->sinistra;
				if(y->colore == ROSSO){
					y->colore = NERO;
					x->padre->colore = ROSSO;
					RotazioneDestra(radicePtr, x->padre);
					y = x->padre->sinistra;
				}
				if(y->destra->colore == NERO && y->sinistra->colore == NERO){
					y->colore = ROSSO;
					x = x->padre;
				}else if(y->sinistra->colore == NERO){
					y->destra->colore = NERO;
					y->colore = ROSSO;
					RotazioneSinistra(radicePtr, y);
				}else{
					y->colore = y->padre->colore;
					x->padre->colore = NERO;
					y->sinistra->colore = NERO;
					RotazioneDestra(radicePtr, x->padre);
					x = radicePtr->radice;
				}
			}
		}

		x->colore = NERO;
}

//funzine per rimuovere dell'albero
NodoDellAlbero *RimuovereDellAlbero(RadiceDellAlbero *radicePtr, int informazioni){
		NodoDellAlbero *ausiliaria = RicercareUnElementoNellAlbero(radicePtr, radicePtr->radice, informazioni);
		NodoDellAlbero *x, *y;

		if(ausiliaria == radicePtr->nil){
			return ausiliaria;
		}
		if(ausiliaria->sinistra == radicePtr->nil || ausiliaria->destra == radicePtr->nil){
			y = ausiliaria;
		}else{
			y = AlberoSuccessore(radicePtr, ausiliaria);
		}
		if(y->sinistra != radicePtr->nil){
			x = y->sinistra;
		}else{
			x = y->destra;
		}

		x->padre = y->padre;

		if(y->padre == radicePtr->nil){
			radicePtr->radice = x;
		}else if(y == y->padre->sinistra){
			y->padre->sinistra = x;
		}else{
			y->padre->destra = x;
		}
		if(y != ausiliaria){
			ausiliaria->informazioni = y->informazioni;
		}
		if(y->colore == NERO){
			RimuovereFixUp(radicePtr, x);
		}

		return ausiliaria;
}

//il menu
int menu(void){
		int m;

		puts("============================");
		puts("ARN - Albero RossoNero");
		puts("Scegliere l'opzione desiderata:");
		puts("1 - Immettere");
		puts("2 - Rimuovere");
		puts("3 - Stampare");
		puts("0 - Finalizza l'esecuzione");
		puts("============================");
		scanf("%d", &m);

		return m;
}

//il programma principale
int main( void ){
		RadiceDellAlbero *radice;
		radice = InizializzazioniDellAlbero();
		int m = 5, valore;

		while(m != 0){
			m = menu();

			switch(m){
				case 1:
					puts("Immettere il valore per immettere nell'albero:");
					scanf("%d", &valore);
					printf("\n");
					ImmettereNellAlbero(radice, valore);
					break;

				case 2:
					puts("Immettere il valore per rimuovere dell'albero:");
					scanf("%d", &valore);
					printf("\n");
					radice->radice = RimuovereDellAlbero(radice, valore);
					break;

				case 3:
					printf("\n");
					puts("InOrdine");
					StampaInOrdine(radice->radice, radice->nil);
					printf("\n");
					puts("PostOrdine");
					StampaPostOrdine(radice->radice, radice->nil);
					printf("\n");
					puts("PreOrdine");
					StampaPreOrdine(radice->radice, radice->nil);
					printf("\n");
					break;

				case 0:
					puts("Grazie da usare. Arrivederci!!!");
					break;
			}
		}

		return 0;
}
