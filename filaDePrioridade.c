/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2020                           **/
/**   <turma> - Prof. Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   EP3 - Fila de Prioridade (utilizando heap)                    **/
/**                                                                 **/
/**   <nome do(a) aluno(a)>                   <numero USP>          **/
/**                                                                 **/
/*********************************************************************/

#include "filaDePrioridade.h"

PFILA criarFila(int max)
{
  PFILA res = (PFILA)malloc(sizeof(FILADEPRIORIDADE));
  res->maxElementos = max;
  res->arranjo = (PONT *)malloc(sizeof(PONT) * max);
  res->heap = (PONT *)malloc(sizeof(PONT) * max);
  int i;
  for (i = 0; i < max; i++)
  {
    res->arranjo[i] = NULL;
    res->heap[i] = NULL;
  }
  res->elementosNoHeap = 0;
  return res;
}

void exibirLog(PFILA f)
{
  printf("Log [elementos: %i]\n", f->elementosNoHeap);
  PONT atual;
  int i;
  for (i = 0; i < f->elementosNoHeap; i++)
  {
    atual = f->heap[i];
    printf("[%i;%f;%i] ", atual->id, atual->prioridade, atual->posicao);
  }
  printf("\n\n");
}

int tamanho(PFILA f)
{
  int tam = 0;

  /* COMPLETAR */

  PONT atual;
  int i; /*contador*/
  for (i = 0; i < f->elementosNoHeap; i++)
  {
    atual = f->heap[i];
    tam++;
  }

  return tam;
}

PONT buscarChave(PONT posicao, int id)
{
}

void refazHeapMaximo(PFILA f, PONT atual, int id)
{
  int i;
  PONT pai = i/2;
  PONT dir = 2*i + 1;
  PONT esq = 2*i;
    if(f->arranjo[id] >= f->heap[f->elementosNoHeap]){
      pai = f->heap[f->elementosNoHeap];
    }

}

bool inserirElemento(PFILA f, int id, float prioridade)
{
  bool res = false;

  /* COMPLETAR */

  PONT atual;
  int i;
  for (i = 0; i < f->elementosNoHeap; i++)
  {
    atual = f->arranjo[i];
    if (id < 0 || id >= f->maxElementos)
    {
      return res;
    }
  }

  ELEMENTO *insereId;
  insereId = (PONT)malloc(sizeof(ELEMENTO));

  insereId->id = id;
  insereId->prioridade = prioridade;
  insereId->posicao = f->elementosNoHeap;

  f->arranjo[id] = insereId;
  f->heap[f->elementosNoHeap] = insereId;
  (f->elementosNoHeap)++;

  return !res;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade)
{
  bool res = false;

  /* COMPLETAR */

  return res;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade)
{
  bool res = false;

  /* COMPLETAR */

  return res;
}

PONT removerElemento(PFILA f)
{
  PONT res = NULL;

  /*ELEMENTO *insereId;
  insereId = (PONT)malloc(sizeof(ELEMENTO));

  insereId->id = id;
  insereId->prioridade = prioridade;
  insereId->posicao = f->elementosNoHeap;

  f->arranjo[id] = insereId;
  f->heap[f->elementosNoHeap] = insereId;
  (f->elementosNoHeap)++;*/

  /* COMPLETAR */
  int id;
  ELEMENTO *elemento = f->arranjo[id];
  int apagar = elemento->id;
  f->arranjo[apagar] = res;
  f->heap[apagar] = res;
  (f->elementosNoHeap)--;

  return res;
}

bool consultarPrioridade(PFILA f, int id, float *resposta)
{

  bool res = false;

  /* COMPLETAR */

  return res;
}
