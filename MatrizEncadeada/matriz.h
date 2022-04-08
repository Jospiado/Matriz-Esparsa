typedef struct matriz Matriz;
typedef struct elemento Elem;


Matriz *cria_matriz(int nlinhas, int ncolunas);

void insere_cordenada(Matriz *m, int linha, int coluna, int val);

void imprime_alocados(Matriz *m);

void imprime_completo(Matriz *m);

void libera_matriz(Matriz *m);

void remove_cordenada(Matriz *m,int linha, int coluna);

void soma_em_cordenada(Matriz *m, int linha, int coluna , int val);

void somalinha(Matriz *m, int linha, int val);

void somacoluna(Matriz *m, int coluna, int val);

void consultaposi(Matriz *m, int linha, int coluna);

void buscar_valor(Matriz *m, int valor);

void imprimir_vizinhos(Matriz *m, int linha, int coluna);
