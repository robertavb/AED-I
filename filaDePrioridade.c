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
  //guarda o tamanho da fila
  int tam = 0;
  //contador
  int i;
  PONT atual;
  //percorre os elementos do heap
  for (i = 0; i < f->elementosNoHeap; i++)
  {
    atual = f->heap[i];
    tam++;
  }
  return tam;
}

//posicao do pai no max heap - inicio no indice 0
int pai(int posicao, PONT atual)
{
  return (atual->posicao - 1) / 2;
}

//posicao do filho a esquerdo no max heap - inicio no indice 0
int esq(int posicao, PONT atual)
{
  return (2 * atual->posicao + 1);
}

//posicao do filho a direita no max heap - inicio no indice 0
int dir(int posicao, PONT atual)
{
  return (2 * atual->posicao + 2);
}

//funcao recursiva auxiliar utilizada na funcao inserir elemento e aumentar a prioridade - realoca os elementos mantendo a propriedade do max heap
void auxAumenta(PFILA f, int posicao, PONT atual)
{
  //posicao do pai
  int maior = pai(posicao, atual);
  //posicao do filho a esquerda
  int fEsq = esq(posicao, atual);
  //posicao do filho a direita
  int fDir = dir(posicao, atual);

  // ja eh o pai - esta na posicao 0 - eh a raiz
  if (atual->posicao == 0)
  {
    return;
  }

  if (atual->prioridade > f->heap[maior]->prioridade)
  {
    // variavel auxiliar para conseguir mudar a posicao de acordo com a prioridade
    PONT aux = f->heap[maior];

    // variavel auxiliar para atualizar a posicao no heap
    int auxP = atual->posicao;

    f->heap[maior] = atual;
    atual->posicao = maior;

    f->heap[auxP] = aux;
    aux->posicao = auxP;

    auxAumenta(f, maior, atual);
  }
}

//funcao recursiva auxiliar utilizada na funcao para diminuir a prioridade - realoca os elementos mantendo a propriedade do max heap
void auxReduz(PFILA f, int posicao, PONT atual)
{
  //posicao do pai
  int maior = pai(posicao, atual);
  //posicao do filho a esquerda
  int fEsq = esq(posicao, atual);
  //posicao do filho a direita
  int fDir = dir(posicao, atual);

  //verifica se os filhos sao validos - a esquerda ou a direita
  if (fDir >= f->elementosNoHeap)
  {
    return;
  }

  if (fEsq >= f->elementosNoHeap)
  {
    return;
  }

  //encontra a posicao onde esta o elemento maior entre o filho esquerdo, filho direito e a posicao atual
  if (fEsq < f->elementosNoHeap && f->heap[fEsq]->prioridade > atual->prioridade)
  {
    maior = fEsq;
  }

  else
  {
    maior = atual->posicao;
  }

  if (fDir < f->elementosNoHeap && f->heap[fDir]->prioridade > f->heap[maior]->prioridade)
  {
    maior = fDir;
  }

  //faz a troca de posicao
  if (maior != posicao)
  {
    // variavel auxiliar para conseguir mudar a posicao de acordo com a prioridade
    PONT aux = f->heap[maior];

    // variavel auxiliar para atualizar a posicao no heap
    int auxP = atual->posicao;

    f->heap[maior] = atual;
    atual->posicao = maior;

    f->heap[auxP] = aux;
    aux->posicao = auxP;

    auxReduz(f, maior, atual);
  }
}

void constroiHeap(PFILA f, int posicao, PONT atual)
{
  int aux = (atual->posicao / 2) - 1;
  for (int i = aux; i >= 0; i--)
  {
    auxReduz(f, posicao, atual);
  }
}

bool inserirElemento(PFILA f, int id, float prioridade)
{
  bool res = false;

  //verifica se o id eh valido ou se ja tem um elemento com esse id na fila
  if (id < 0 || id >= f->maxElementos || f->arranjo[id] != NULL)
  {
    return res;
  }

  ELEMENTO *insereElemento;
  int posicao;

  //aloca memoria para o elemento
  insereElemento = (PONT)malloc(sizeof(ELEMENTO));

  //o elemento inserido eh colocado no arranjo de elementos
  f->arranjo[id] = insereElemento;

  //atualiza a posicao, o id e a prioridade do elemento
  insereElemento->posicao = f->elementosNoHeap;
  insereElemento->id = id;
  insereElemento->prioridade = prioridade;

  //o elemento eh colocado no heap
  f->heap[f->elementosNoHeap] = insereElemento;

  //aumenta a quantidade de elementos no heap
  (f->elementosNoHeap)++;

  //reorganiza os elementos no heap de acordo com a prioridade
  auxAumenta(f, posicao, insereElemento);

  return !res;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade)
{
  bool res = false;

  int posicao;

  //verifica se o id eh valido e se ele esta na fila
  if (id < 0 || id >= f->maxElementos || f->arranjo[id] == NULL)
  {
    return res;
  }

  ELEMENTO *aux;
  aux = f->arranjo[id];

  //verifica se a prioridade ja existente eh maior ou igual a nova prioridade
  if (f->arranjo[id]->prioridade >= novaPrioridade)
  {
    return res;
  }

  //atualiza a prioridade
  aux->prioridade = novaPrioridade;

  //reorganiza o heap - funcao recursiva
  auxAumenta(f, posicao, aux);

  return !res;
}

bool reduzirPrioridade(PFILA f, int id, float novaPrioridade)
{
  bool res = false;

  int posicao;

  //verifica se o id eh valido e se ele esta na fila
  if (id < 0 || id >= f->maxElementos || f->arranjo[id] == NULL)
  {
    return res;
  }

  ELEMENTO *aux;
  aux = f->arranjo[id];

  //verifica se a prioridade ja existente eh menor ou igual a nova prioridade
  if (f->arranjo[id]->prioridade <= novaPrioridade)
  {
    return res;
  }

  //atualiza a prioridade
  aux->prioridade = novaPrioridade;

  //reorganiza o heap - funcao recursiva
  auxReduz(f, posicao, aux);

  return !res;
}

//funcao auxiliar para remover um elemento mantendo a propriedade do max heap
void auxRemove(PFILA f, int posicao, PONT atual)
{
  if (atual == NULL)
  {
    return;
  }

  //posicao do pai
  int maior = pai(posicao, atual);
  //posicao do filho a esquerda
  int fEsq = esq(posicao, atual);
  //posicao do filho a direita
  int fDir = dir(posicao, atual);

  //verifica se os filhos sao validos - a esquerda ou a direita
  if (fDir >= f->elementosNoHeap)
  {
    return;
  }

  if (fEsq >= f->elementosNoHeap)
  {
    return;
  }

  maior = fEsq;

  if (fDir >= 2)
  {
    if (f->heap[fEsq]->prioridade < f->heap[fDir]->prioridade)
    {
      maior = fDir;
    }
  }

  if (atual->prioridade < f->heap[maior]->prioridade)
  {
    // variavel auxiliar para conseguir mudar a posicao de acordo com a prioridade
    PONT aux = f->heap[maior];

    // variavel auxiliar para atualizar a posicao no heap
    int auxP = atual->posicao;

    f->heap[maior] = atual;
    atual->posicao = maior;

    f->heap[auxP] = aux;
    aux->posicao = auxP;

    auxRemove(f, maior, atual);
  }
}

PONT removerElemento(PFILA f)
{
  PONT res = NULL;
  int posicao;

  //verifica se o heap esta vazio
  if (f->elementosNoHeap == 0)
  {
    return res;
  }

  //primeiro elemento
  ELEMENTO *elemento;
  elemento = f->heap[0];
  res = elemento;
  elemento = f->heap[f->elementosNoHeap - 1];
  elemento->posicao = 0;

  f->heap[f->elementosNoHeap - 1] = NULL;
  (f->elementosNoHeap)--;
  f->arranjo[res->id] = NULL;

  //reorganiza o heap de forma recursiva mantendo a propriedade heap
  auxRemove(f, posicao, f->heap[0]);

  return res;
}

bool consultarPrioridade(PFILA f, int id, float *resposta)
{
  bool res = false;

  //verifica se o id eh valido e se existe um elemento na fila com esse id
  if (id < 0 || id >= f->maxElementos || f->arranjo[id] == NULL)
  {
    return res;
  }

  // valor da prioridade do elemento eh colocado na memoria apontada pela variavel resposta
  *resposta = f->arranjo[id]->prioridade;

  return !res;
}
