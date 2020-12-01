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

int pai(int posicao)
{
  return (posicao / 2);
}

int esq(int posicao)
{
  return (posicao * 2);
}

int dir(int posicao)
{
  return (posicao * 2 + 1);
}

void refazHeapMaximo(PFILA f, PONT atual)
{
  if (atual->posicao == 0)
  {
    return;
  }

  int pai;
  pai = (atual->posicao) / 2;

  if (atual->prioridade > f->heap[pai]->prioridade)
  {
    PONT aux = f->heap[pai];

    int aux2 = atual->posicao;

    f->heap[pai] = atual;

    atual->posicao = pai;

    f->heap[aux2] = aux;

    aux->posicao = aux2;

    refazHeapMaximo(f, atual);
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

  ELEMENTO *insereId;
  insereId = (PONT)malloc(sizeof(ELEMENTO));

  insereId->id = id;
  insereId->prioridade = prioridade;
  insereId->posicao = f->elementosNoHeap;

  f->arranjo[id] = insereId;
  f->heap[f->elementosNoHeap] = insereId;
  (f->elementosNoHeap)++;

  refazHeapMaximo(f, insereId);

  return !res;
}

void aumentarPrioridadeAux(PFILA f, int posicao)
{
  int j = pai(posicao);
  if (j >= 0)
  {
    if (f->heap[f->elementosNoHeap]->prioridade > f->arranjo[j]->prioridade)
    {
      int temp = f->heap[posicao];
      f->heap[posicao] = f->arranjo[posicao];
      f->arranjo[posicao] = temp;
      aumentarPrioridadeAux(f, posicao);
    }
  }
}

void aumentarPrioridadeAux2(PFILA f, PONT atual);

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade)
{
  bool res = false;

  /* COMPLETAR */

  ELEMENTO *aux;
  aux = f->arranjo[id];

  if (id < 0 || id >= f->maxElementos || f->arranjo[id] == NULL)
  {
    return res;
  }

  if (aux->prioridade >= novaPrioridade)
  {
    return res;
  }

  aux->id = novaPrioridade;

  aumentarPrioridadeAux(f, id);

  return !res;
}

void reduzPrioridadeAux(PFILA f, int posicao, PONT atual, int aux, int id)
{
  atual = f->arranjo[id];
  int e = esq(posicao);
  int d = dir(posicao);
  int maior = posicao;
  if (e <= aux && f->heap[e] > f->heap[posicao])
  {
    maior = e;
  }
  if (d <= aux && f->heap[d] > f->heap[maior])
  {
    maior = d;
  }
  if (maior != posicao)
  {
    int temp = f->heap[posicao];
    f->heap[posicao] = f->heap[maior];
    f->heap[maior] = temp;
    reduzPrioridadeAux(f, maior, atual, aux, id);
  }
}

void reduzirPrioridadeAux2(PFILA f, PONT atual)
{
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade)
{
  bool res = false;

  /* COMPLETAR */

  ELEMENTO *aux;
  aux = f->arranjo[id];

  if (id < 0 || id >= f->maxElementos || f->arranjo[id] == NULL)
  {
    return res;
  }

  if (aux->prioridade <= novaPrioridade)
  {
    return res;
  }

  aux->id = novaPrioridade;

  refazHeapMaximo(f, aux);

  return !res;
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

  // fila vazia
  if (f->arranjo == NULL || f->heap[f->elementosNoHeap] == NULL)
  {
    return res;
  }

  /* deverá retirar o primeiro elemento do heap máximo; reorganizar o heap (acertando os elementos - isto é, o campo posicao dos respectivos elementos - e ponteiros necessários; colocar NULL na posicao correspondente desse elemento no arranjo arranjo, acertar o valor do campo elementosNoHeap e retornar o endereço do respectivo elemento.*/

  int id, posicao;

  ELEMENTO *atual; // primeiro elemento
  f->heap[0] = f->heap[f->elementosNoHeap];
  (f->elementosNoHeap)--;

  f->heap = (int)realloc(f->heap, sizeof(int));

  refazHeapMaximo(f, atual);

  return res;
}

bool consultarPrioridade(PFILA f, int id, float *resposta)
{

  bool res = false;

  if (id < 0 || id >= f->maxElementos)
  {
    return res;
  }

  *resposta = f->arranjo[id]->prioridade;

  return !res;
}
