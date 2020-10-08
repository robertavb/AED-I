/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2020                           **/
/**   <turma> - Prof. Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   EP1 - Fila de Prioridade                                      **/
/**                                                                 **/
/**   <Roberta Vitoria Borges>                   <numero USP>          **/
/**                                                                 **/
/*********************************************************************/

#include "filaDePrioridade.h"

PFILA criarFila(int max){
  PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
  res->maxElementos = max;
  res->arranjo = (PONT*) malloc(sizeof(PONT)*max);
  int i;
  for (i=0;i<max;i++) res->arranjo[i] = NULL;
  PONT cabeca = (PONT) malloc(sizeof(ELEMENTO));
  res->fila = cabeca;
  cabeca->ant = cabeca;
  cabeca->prox = cabeca;
  cabeca->id = -1;
  cabeca->prioridade = 1000000;
  return res;
}

void exibirLog(PFILA f){
  printf("Log [elementos: %i (alem do no cabeca)]\n", tamanho(f));
  PONT atual = f->fila;
  printf("%p[%i;%f;%p]%p ", atual->ant, atual->id, atual->prioridade, atual, atual->prox);
  atual = atual->prox;
  while (atual != f->fila){
    printf("%p[%i;%f;%p]%p ", atual->ant, atual->id, atual->prioridade, atual, atual->prox);
    atual = atual->prox;
  }
  printf("\nElementos validos: ");
  atual = atual->prox;
  while (atual != f->fila){
    printf("[%i;%f;%p] ", atual->id, atual->prioridade, atual);
    atual = atual->prox;
  }

  printf("\nValores do arranjo:\n\[ ");
  int x;
  for (x=0;x<f->maxElementos;x++) printf("%p ",f->arranjo[x]);
  printf("]\n\n");
}

int tamanho(PFILA f){
  int tam = 0;
    PONT elementos = f->fila;
    elementos = elementos->prox;
    while(elementos != f->fila){
      tam++;
      elementos = elementos->prox;
    }
  return tam;
}

bool inserirElemento(PFILA f, int id, float prioridade){
  bool resposta = false;

  if(id < 0 || id>=f->maxElementos || f->arranjo[id] == f->fila->prox){
    return resposta;
  }

  ELEMENTO* insereElemento;
  PONT ant;

  ant = f->fila;
  insereElemento = ant->prox;

  while(insereElemento != f->fila && insereElemento->prioridade > prioridade){
    ant = insereElemento;
    insereElemento = insereElemento->prox;
  }
  
    insereElemento = (PONT) malloc(sizeof(ELEMENTO));

    f->arranjo[id] = insereElemento;

    insereElemento->ant = ant;
    insereElemento->prox = ant->prox;
    ant->prox = insereElemento;
    insereElemento->prox->ant = insereElemento;
    insereElemento->prioridade = prioridade;
    insereElemento->id = id;

  return !resposta;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
  bool resposta = false;
  float prioridade;
  ELEMENTO* elemento = f->fila->prox;
  PONT ant;
  

  if(id < 0 || id>=f->maxElementos || f->arranjo[id] == NULL){
    return resposta;
  }

  if(f->arranjo[id]->prioridade >= novaPrioridade){
    return resposta;
  }

  if(elemento->prioridade > novaPrioridade){
    elemento = elemento->prox;
  }

    f->arranjo[id]->prioridade = novaPrioridade;

  return !resposta;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
  bool resposta = false;

  ELEMENTO* elemento = f->fila->prox;

  if(id < 0 || id >= f->maxElementos || f->arranjo[id] == NULL){
    return resposta;
  }

  if(f->arranjo[id]->prioridade <= novaPrioridade){
    return resposta;
  }

    f->arranjo[id]->prioridade = novaPrioridade;

  return !resposta;

}

PONT removerElemento(PFILA f){
  
  PONT resposta = NULL;
  ELEMENTO* elemento = f->fila->prox;
  int remover = elemento->id;

  if(f->fila == f->fila->ant && f->fila == f->fila->prox){
    return resposta;
  }

    f->fila->prox = elemento->prox;
    elemento->prox->ant = f->fila;
    f->arranjo[remover] = resposta;
    resposta = elemento;

    return resposta;

}

bool consultarPrioridade(PFILA f, int id, float* resposta){
  bool resp = false;

  if(id<0 || id>=f->maxElementos){
    return resp;
  }

  *resposta = f->arranjo[id]->prioridade;

  return !resp;
}