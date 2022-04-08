#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"



struct elemento{
 int lin,col, info;
 Elem *pcol, *plin;
};

struct matriz{
  Elem **lin, **col;
  int nlin,ncol;
};

Matriz *cria_matriz(int nlinhas, int ncolunas){
	Matriz *m = (Matriz*) malloc(sizeof(Matriz));
	m->nlin= nlinhas;
	m->ncol=ncolunas;

	m->lin = (Elem **) malloc(sizeof(Elem*)*nlinhas);
	m->col = (Elem **) malloc(sizeof(Elem*)*ncolunas);

	for(int i=0;i<nlinhas;i++){
		m->lin[i]=NULL;
	}
	for(int i=0;i<ncolunas;i++){
		m->col[i]=NULL;
	}
	return m;
}
//assume-se que o no na linha e coluna nao existe...
void insere_cordenada(Matriz *m, int linha, int coluna, int info){
    if(linha>m->nlin-1 || linha<0 || coluna>m->ncol-1 || coluna<0){
        printf("\nEstá linha ou coluna não existem\n");
        return;
    }
	Elem *p=(Elem*) malloc(sizeof(Elem));
	p->lin= linha;
	p->col= coluna;
	p->info= info;
	p->pcol=NULL;
	p->plin=NULL;

	Elem *aux = m->lin[linha];
	Elem *ant= NULL;
	while(aux!=NULL && aux->col < coluna){
		ant= aux;
		aux=aux->pcol;
	}
	if(ant==NULL){//insere no inicio
		if(aux!=NULL){ // lista ja tem pelo menos 1 eleme
			p->pcol=aux;
			m->lin[linha] = p;
		}else{//lista vazia
			m->lin[linha] =p;
		}
	}else{//inserção no meio ou no fim da lista
		ant->pcol = p;
		p->pcol = aux;
	}
	aux = m->col[coluna];
	ant= NULL;
	while(aux!=NULL && aux->lin < linha){
		ant= aux;
		aux=aux->plin;
	}
	if(ant==NULL){//insere no inicio
		if(aux!=NULL){ // lista ja tem pelo menos 1 eleme
			p->plin=aux;
			m->col[coluna] = p;
		}else{//lista vazia
			m->col[coluna] =p;
		}
	}else{//inserção no meio ou no fim da lista
		ant->plin = p;
		p->plin = aux;
	}
	printf("\nValor inserido com sucesso!\n");
}
//imprime os elementos diferentes de zero
void imprime_alocados(Matriz *m){
	for(int i=0;i<m->nlin;i++){
		Elem *aux = m->lin[i];
		while(aux!=NULL){
		 	printf("Linha: %d Coluna: %d Valor: %d\n", aux->lin, aux->col, aux->info);
			aux=aux->pcol;
		}
	}
}

void imprime_completo(Matriz *m){
	for(int i=0; i < m->nlin;i++){
		Elem *aux = m->lin[i];
		for(int j=0; j<m->ncol;j++){
			if(aux == NULL){
				printf("0");
			}else{
				if(aux->col == j){
					printf("%d", aux->info);
					aux=aux->pcol;
				}else{
					printf("0");
				}
			}
			if(j<m->ncol-1)printf("\t");
		}
        printf("\n");
	}
}

void libera_matriz(Matriz *m){
	Elem *aux2;
	for(int i=0; i<m->nlin; i++){
		Elem *aux= m->lin[i];
		while(aux!=NULL){
			aux2=aux;
			aux= aux->pcol;
			free(aux2);
		}
	}
	free(m->lin);
	free(m->col);
	free(m);
	printf("\nMatriz liberada com sucesso!\n");
}
void remove_cordenada(Matriz *m,int linha, int coluna){
    if(linha>m->nlin-1 || linha<0 || coluna>m->ncol-1 || coluna<0){
        printf("\nEstá linha ou coluna não existem\n");
        return;
    }
    Elem *aux= m->lin[linha];
    Elem *ant= NULL;
    while(aux!=NULL && aux->col != coluna){
        ant=aux;
        aux=aux->pcol;
    }
    if(aux==NULL){
            printf("\nValor já não existe\n");
            return;
    }
    if(ant==NULL){
        m->lin[linha]=aux->pcol;
    }else{
        ant->pcol = aux->pcol;
    }
    aux= m->col[coluna];
    ant= NULL;
    while(aux!=NULL && aux->lin != linha){
        ant=aux;
        aux=aux->plin;
    }
    if(aux==NULL){
            printf("\nValor já não existe\n");
            return;
    }
    if(ant==NULL){
        m->col[coluna]=aux->plin;
    }else{
        ant->plin = aux->plin;
    }
    free(aux);
    printf("\nValor removido com sucesso!\n");
}
void soma_em_cordenada(Matriz *m, int linha, int coluna, int info){
        if(linha>m->nlin-1 || linha<0 || coluna>m->ncol-1 || coluna<0){
        printf("\nEstá linha ou coluna não existem\n");
        return;
        }
        Elem *aux= m->lin[linha];
        if(aux==NULL){
            insere_cordenada(m,linha, coluna, info);
            printf("\nValor inserido com sucesso!\n");
            return ;
        }
        while(aux!=NULL){
            if(coluna == aux->col){
                aux->info += info;
                if(aux->info==0){
                    remove_cordenada(m,linha,coluna);
                }
                printf("\nValor inserido com sucesso!\n");
                return;
            }
            if(coluna < aux->col){
                insere_cordenada(m,linha,coluna,info);
                printf("\nValor inserido com sucesso!\n");
                return ;
            }
            aux=aux->pcol;
        }
        insere_cordenada(m,linha,coluna,info);
}

void somalinha(Matriz *m, int linha, int info){
        if(linha>m->nlin-1 || linha<0){
            printf("\nEsta linha não existe\n");
        }
        for(int i=0 ; i<m->ncol;i++){
            soma_em_cordenada(m,linha,i,info);
        }
}

void somacoluna(Matriz *m, int coluna, int info){
        if(coluna>m->ncol-1 || coluna<0){
            printf("\nEsta coluna não existe\n");
        }
        for(int i=0; i<m->nlin; i++){
            soma_em_cordenada(m,i,coluna,info);
        }
}
void consultaposi(Matriz *m, int linha, int coluna){
        if(linha>m->nlin-1 || linha<0 || coluna>m->ncol-1 || coluna<0){
        printf("\nEstá linha ou coluna não existem\n");
        return;
    }
        Elem *auxl= m->lin[linha];
        Elem *auxc= m->col[coluna];
        while(auxl!=NULL && auxl->col!=coluna){
            auxl=auxl->pcol;
        }
        while(auxc!=NULL && auxc->lin!=linha){
            auxc=auxc->plin;
        }
            if(auxl==NULL || auxc == NULL){
            printf("\n O valor buscado na matriz é 0\n");
            return;
            }
            if(auxl->col == coluna && auxc->lin==linha)
                printf("\n O valor buscado na matriz é %d\n", auxc->info);
}
void buscar_valor(Matriz *m, int valor){
        if(valor==0){
            printf("\nO valor é NULL\n");
            return;
        }
        for(int i=0; i< m->nlin;i++){
		Elem *aux = m->lin[i];
		for(int j=0; j<m->ncol;j++){
			if(aux == NULL){
			}else{
				if(aux->col == j){
					if(aux->info==valor)
                        printf("\nPodemos localizar o valor %d na posição\nLinha: %d\nColuna:%d", aux->info, aux->lin,aux->col);
					aux=aux->pcol;
				}
			}
		}
        printf("\n");
	}
}
void imprimir_vizinhos(Matriz *m, int linha, int coluna){
        if(linha>m->nlin-1 || linha<0 || coluna>m->ncol-1 || coluna<0){
        printf("\nEstá linha ou coluna não existem\n");
        return;
    }
        Elem *aux = m->lin[linha];
        Elem *ant = NULL;
        Elem *prox = NULL;
        while(aux!=NULL && aux->col<coluna){
            if(aux->col==coluna-1){
            ant=aux;
            }
            aux=aux->pcol;
        }

        if(aux==NULL)
            prox=NULL;
        if(aux!=NULL && aux->pcol!=NULL && aux->pcol->col==coluna+1){
                prox=aux->pcol;
        }
        if(aux!=NULL && aux->col==coluna+1){
            prox=aux;
        }
         if(prox==NULL)
            printf("\nO valor a direira é : NULL \n");
         else
            printf("\nO valor a direita é : %d\n",prox->info);
         if(ant==NULL)
            printf("\nO valor a esquerda é : NULL\n");
         else
            printf("\nO valor a esquerda é : %d\n", ant->info);

        aux = m->col[coluna];
        ant = NULL;
        prox = NULL;
        while(aux!=NULL && aux->lin<linha){
            if(aux->lin==linha-1){
            ant=aux;
            }
            aux=aux->plin;
        }

        if(aux==NULL)
            prox=NULL;
        if(aux!=NULL && aux->plin!=NULL && aux->plin->lin==linha+1){
                prox=aux->plin;
        }
        if(aux!=NULL && aux->lin==linha+1){
            prox=aux;
        }
         if(prox==NULL)
            printf("\nO valor abaixo é : NULL \n");
         else
            printf("\nO valor abaixo é : %d\n",prox->info);
         if(ant==NULL)
            printf("\nO valor acima é : NULL\n");
         else
            printf("\nO valor acima é : %d\n", ant->info);
}
