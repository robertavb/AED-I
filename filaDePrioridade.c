/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2020                           **/
/**   <2020204> - Prof. Luciano Antonio Digiampietri                **/
/**                                                                 **/
/**   EP3 - Fila de Prioridade (utilizando heap)                    **/
/**                                                                 **/
/**   <Roberta Vitoria Borges>                   <11344811>         **/
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
  int i;
  PONT atual;
  /* COMPLETAR */
  for (i = 0; i < f->elementosNoHeap; i++)
  {
    atual = f->heap[i];
    tam++;
  }
  return tam;
}

void heapMax(PFILA f, PONT maior, int posicao, int id)
{
  int pai = posicao / 2;
  int esq = 2 * posicao + 1;
  int dir = 2 * posicao + 2;
  maior = f->arranjo[pai];
  if (maior->prioridade > f->arranjo[id]->prioridade)
  {
    f->arranjo[id]->prioridade = f->heap[f->elementosNoHeap]->prioridade;
  }
  heapMax(f, maior, posicao, id);
}

bool inserirElemento(PFILA f, int id, float prioridade)
{
  bool res = false;

  /* COMPLETAR */

  if (id < 0 || id >= f->maxElementos - 1)
  {
    return res;
  }

  ELEMENTO *insereElemento;
  int posicao;

  insereElemento = (PONT)malloc(sizeof(ELEMENTO));

  f->arranjo[id] = insereElemento;

  insereElemento->id = id;
  insereElemento->prioridade = prioridade;
  insereElemento->posicao = posicao;

  f->heap[f->elementosNoHeap] = insereElemento;

  (f->elementosNoHeap)++;

  

  return !res;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade)
{
  bool res = false;

  /* COMPLETAR */

  if (id < 0 || id >= f->maxElementos - 1)
  {
    return res;
  }

  ELEMENTO *aux;
  aux = f->arranjo[id];

  if (f->arranjo[id]->prioridade >= novaPrioridade)
  {
    return res;
  }

  aux->prioridade = novaPrioridade;

  return !res;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade)
{
  bool res = false;

  /* COMPLETAR */

  if (id < 0 || id >= f->maxElementos - 1)
  {
    return res;
  }

  ELEMENTO *aux;
  aux = f->arranjo[id];

  if (f->arranjo[id]->prioridade <= novaPrioridade)
  {
    return res;
  }

  aux->prioridade = novaPrioridade;

  return !res;
}

PONT removerElemento(PFILA f)
{
  PONT res = NULL;

  /* COMPLETAR */

  return res;
}

bool consultarPrioridade(PFILA f, int id, float *resposta)
{
  bool res = false;

  /* COMPLETAR */

  if (id < 0 || id >= f->maxElementos - 1)
  {
    return res;
  }

  *resposta = f->arranjo[id]->prioridade;

  return !res;
}
