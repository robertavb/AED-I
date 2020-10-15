#include <stdio.h>
#include <malloc.h>

typedef struct {
  int linhas;
  int colunas;
  int** M;
}MATRIZ;

MATRIZ* inicializarMatriz(int linhas, int colunas){
  if (linhas<=0 || colunas<=0) return NULL;
  int i;
  MATRIZ* mat = (MATRIZ*) malloc(sizeof(MATRIZ));
  mat->M = (int**)malloc(sizeof(int*)*linhas);
  for (i=0; i<linhas; i++){
      mat->M[i] = (int*)malloc(sizeof(int)*colunas);
  }
  mat->linhas = linhas;
  mat->colunas = colunas;
  return mat;
}

void imprimirMatriz(MATRIZ* mat){
  int i,j;
  printf("Matriz %i x %i:\n", mat->linhas, mat->colunas);
  for (i=0; i<mat->linhas; i++){
    for (j=0; j<mat->colunas; j++) printf("%i ", mat->M[i][j]);
    printf("\n");
  }
  printf("\n");
}
      
MATRIZ* multiplicarMatrizes(MATRIZ* m1, MATRIZ* m2){
  if (m1->colunas != m2->linhas) return NULL;
  MATRIZ* res = inicializarMatriz(m1->linhas,m2->colunas);
  int i,j,k;
  int valor = 0;

    //a multiplicação de matrizes é, tipicamente, implementada utilizando três laços _for_ encadeado
    
    /* Multiplicação de matrizes:
        linha 0 de A * coluna 0 de B + linha 1 de A * coluna 0 e linha 1 de B */

        for(i = 0; i < m1->linhas; i++){
            for(j = 0; j < m2->colunas; j++)
              for(k =0; k < m1->linhas; k++)
                printf("%i ",  m1->M[i][j]);
                printf("\n");
              
            
        }

        /*valor = (m1->M[0][0] * m2->M[0][0]) + (m1->M[0][1] * m2->M[1][0]);*/
    
    

  /* COMPLETAR */


  return m1;
}
      

int main(){
  
  MATRIZ* m1 = inicializarMatriz(3, 2);
  int i,j;
  int cont = 1;
  for (i=0; i<m1->linhas; i++)
    for (j=0; j<m1->colunas; j++) {
        m1->M[i][j] = cont;
        cont++;
    }

  imprimirMatriz(m1);

  MATRIZ* m2 = inicializarMatriz(2, 3);
  for (i=0; i<m2->linhas; i++)
    for (j=0; j<m2->colunas; j++) {
        m2->M[i][j] = cont;
        cont++;
    }

  imprimirMatriz(m2); 

  MATRIZ* m3 = multiplicarMatrizes(m1, m2);
  
  imprimirMatriz(m3);


  char c1;
  printf("Pressione ENTER para terminar.\n");
  scanf("%c", &c1);

  return 0;
}