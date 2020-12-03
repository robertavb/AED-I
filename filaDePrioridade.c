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

int pai(int posicao)
{
  return (posicao - 1) / 2;
}

int esq(int posicao)
{
  return (2 * posicao + 1);
}

int dir(int posicao)
{
  return (2 * posicao + 2);
}

void heapAumenta(PFILA f, int posicao, PONT atual)
{
  int maior = pai(posicao);

  if (atual->posicao == 0)
  {
    return;
  }

  if (atual->prioridade > f->heap[maior]->prioridade)
  {
    /*PONT aux = atual;
    int auxP = atual->posicao;

    atual = f->heap[maior];
    f->heap[maior] = aux;*/

    PONT aux = atual;
    int auxP = atual->posicao;

    f->heap[maior] = atual;
    atual->posicao = maior;

    f->heap[auxP] = aux;
    aux->posicao = auxP;

    heapAumenta(f, maior, aux);
  }
}

bool inserirElemento(PFILA f, int id, float prioridade)
{
  bool res = false;

  /* COMPLETAR */

  if (id < 0 || id >= f->maxElementos)
  {
    return res;
  }

  ELEMENTO *insereElemento;
  int posicao;

  insereElemento = (PONT)malloc(sizeof(ELEMENTO));

  f->arranjo[id] = insereElemento;

  insereElemento->posicao = posicao;
  insereElemento->id = id;
  insereElemento->prioridade = prioridade;

  f->heap[f->elementosNoHeap] = insereElemento;

  (f->elementosNoHeap)++;

  heapAumenta(f, posicao, insereElemento);

  return !res;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade)
{
  bool res = false;

  /* COMPLETAR */

  int posicao;

  if (id < 0 || id >= f->maxElementos || f->arranjo[id] == NULL)
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

  heapAumenta(f, posicao, aux);

  return !res;
}

void heapReduz(PFILA f, int posicao, PONT atual)
{
  int filhoEsq = esq(posicao);
  int filhoDir = dir(posicao);

  int maior = posicao;

  if (atual->posicao == -1 || atual->posicao == 0 || atual == NULL)
  {
    return;
  }

  if (filhoDir >= f->elementosNoHeap)
  {
    filhoDir = -1;
  }

  if (filhoEsq >= f->elementosNoHeap)
  {
    filhoEsq = -1;
  }

  if (filhoEsq <= f->elementosNoHeap && f->heap[filhoEsq]->prioridade > atual->prioridade)
  {
    maior = filhoEsq;
  }

  if (filhoDir <= f->elementosNoHeap && f->heap[filhoDir]->prioridade > f->heap[maior]->prioridade)
  {
    maior = filhoDir;
  }

  if (maior != posicao)
  {
    PONT aux = f->heap[maior];
    int auxP = atual->posicao;

    f->heap[maior] = atual;
    atual->posicao = maior;

    f->heap[auxP] = aux;
    aux->posicao = auxP;

    heapReduz(f, maior, aux);
  }
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade)
{
  bool res = false;

  /* COMPLETAR */
  int posicao;

  if (id < 0 || id >= f->maxElementos || f->arranjo[id] == NULL)
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

  heapReduz(f, posicao, aux);

  return !res;
}

PONT removerElemento(PFILA f)
{
  PONT res = NULL;
  int posicao;

  /* COMPLETAR */

  ELEMENTO *elemento = f->heap[0];
  int remove = elemento->id;

  f->arranjo[remove] = res;
  res = elemento;
  (f->elementosNoHeap)--;

  heapReduz(f, f->elementosNoHeap, elemento);

  return res;
}

bool consultarPrioridade(PFILA f, int id, float *resposta)
{
  bool res = false;

  /* COMPLETAR */

  if (id <= 0 || id >= f->maxElementos || f->arranjo[id] == NULL)
  {
    return res;
  }

  *resposta = f->arranjo[id]->prioridade;

  return !res;
}
