/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2020                           **/
/**   <2020204> - Prof. Luciano Antonio Digiampietri                **/
/**                                                                 **/
/**   EP1 - Fila de Prioridade                                      **/
/**                                                                 **/
/**   <Roberta Vitoria Borges>                   <11344811>         **/
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
//percorre o arranjo enquanto os elementos são válidos
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

// verifica posicao para ordenação em ordem decrescente
  while(insereElemento != f->fila && insereElemento->prioridade > prioridade){
    ant = insereElemento;
    insereElemento = insereElemento->prox;
  }

// aloca memoria para o elemento
    insereElemento = (PONT) malloc(sizeof(ELEMENTO)); 

// colocar o elemento no arranjo
    f->arranjo[id] = insereElemento;

// acerta os ponteiros e insere a respectiva prioridade e id do elemento
    insereElemento->ant = ant;
    insereElemento->prox = ant->prox;
    ant->prox = insereElemento;
    insereElemento->prox->ant = insereElemento;
    insereElemento->prioridade = prioridade;
    insereElemento->id = id;

// true
  return !resposta;
}

bool verificaPrioridade(PFILA f, PONT* ant, float novaPrioridade){

  bool resposta = false;
  PONT auxiliar = f->fila->prox;
  *ant = f->fila;
  f->fila->id = novaPrioridade;

//enquanto a prioridade antiga for maior que a nova - para reajustar o arranjo
    while(auxiliar->prioridade >= novaPrioridade){
    *ant = auxiliar;
    auxiliar = auxiliar->prox;
    }

//nova prioridade já é maior
  if(auxiliar->prioridade <= novaPrioridade){
      return !resposta;
    }

}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
  bool resposta = false;

//verificacoes de elementos validos
  if(id < 0 || id>=f->maxElementos || f->arranjo[id] == NULL){
    return resposta;
  }

  ELEMENTO* auxiliar;
  auxiliar = f->arranjo[id];
  PONT ant, prox;
  
//prioridade nova nao pode ser menor do que a antiga prioridade
  if(f->arranjo[id]->prioridade >= novaPrioridade){
    return resposta;
  }

  //limpa os elementos para uma nova ordenacao pela prioridade
  auxiliar->ant->prox = auxiliar->prox;
  auxiliar->prox->ant = auxiliar->ant;

//coloca a nova prioridade
    auxiliar->prioridade = novaPrioridade;

    verificaPrioridade(f,&ant,novaPrioridade);

    auxiliar->ant = ant;
    auxiliar->prox = ant->prox;
    ant->prox = auxiliar;
    auxiliar->prox->ant = auxiliar;

  return !resposta;
}

bool verificaPrioridade1(PFILA f, PONT* prox, float novaPrioridade){
//função para ordenar quando a prioridade for reduzida
  bool resposta = false;
  PONT auxiliar = f->fila->ant;
  *prox = f->fila;
  f->fila->id = novaPrioridade;

    while(auxiliar->prioridade <= novaPrioridade){
    *prox = auxiliar;
    auxiliar = auxiliar->ant;
    }

//nova prioridade já é maior
  if(auxiliar->prioridade <= novaPrioridade){
      return !resposta;
    }

}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
  bool resposta = false;

//verificacoes de elementos validos
  if(id < 0 || id>=f->maxElementos || f->arranjo[id] == NULL){
    return resposta;
  }

  ELEMENTO* auxiliar;
  auxiliar = f->arranjo[id];
  PONT ant, prox;
  
//prioridade nova nao pode ser maior do que a antiga prioridade
  if(f->arranjo[id]->prioridade <= novaPrioridade){
    return resposta;
  }

//limpa os elementos para uma nova ordenacao pela prioridade
  auxiliar->prox->ant = auxiliar->ant;
  auxiliar->ant->prox = auxiliar->prox;

//coloca a nova prioridade
    auxiliar->prioridade = novaPrioridade;

  verificaPrioridade1(f,&prox,novaPrioridade);

    auxiliar->prox = prox;
    auxiliar->ant = prox->ant;
    prox->ant = auxiliar;
    auxiliar->ant->prox = auxiliar;

  return !resposta;

}

PONT removerElemento(PFILA f){
  
  PONT resposta = NULL;
  ELEMENTO* elemento = f->fila->prox; // primeiro elemento
  int remover = elemento->id;

  if(f->fila == f->fila->ant && f->fila == f->fila->prox){
    return resposta;
  }

    f->fila->prox = elemento->prox;
    elemento->prox->ant = f->fila;
// remove o id
    f->arranjo[remover] = resposta;
    resposta = elemento;

//removido
    return resposta;

}

bool consultarPrioridade(PFILA f, int id, float* resposta){
  bool resp = false;

  if(id<0 || id>=f->maxElementos){
    return resp;
  }

// retorna a prioridade do elemento
  *resposta = f->arranjo[id]->prioridade;

  return !resp;
}