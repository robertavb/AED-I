/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Seugndo Semestre de 2020                           **/
/**   <turma> - Prof. Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   EP2 - Fila Preferencial                                       **/
/**                                                                 **/
/**   <Roberta Vitoria Borges>                   <11344811>         **/
/**                                                                 **/
/*********************************************************************/

#include "filapreferencial.h"

PFILA criarFila()
{
  PFILA res = (PFILA)malloc(sizeof(FILAPREFERENCIAL));
  res->inicioPref = NULL;
  res->fimPref = NULL;
  res->inicioGeral = NULL;
  res->fimGeral = NULL;
  return res;
}

int tamanho(PFILA f)
{
  PONT atual = f->inicioGeral;
  int tam = 0;
  while (atual)
  {
    atual = atual->prox;
    tam++;
  }
  return tam;
}

int tamanhoFilaPreferencial(PFILA f)
{
  PONT atual = f->inicioPref;
  int tam = 0;
  while (atual)
  {
    atual = atual->prox;
    tam++;
  }
  return tam;
}

PONT buscarID(PFILA f, int id)
{
  PONT atual = f->inicioGeral;
  while (atual)
  {
    if (atual->id == id)
      return atual;
    atual = atual->prox;
  }
  return NULL;
}

void exibirLog(PFILA f)
{
  int numElementos = tamanho(f);
  printf("\nLog fila geral [elementos: %i] - Inicio:", numElementos);
  PONT atual = f->inicioGeral;
  while (atual)
  {
    printf(" [%i;%i]", atual->id, atual->ehPreferencial);
    atual = atual->prox;
  }
  printf("\n");
  numElementos = tamanhoFilaPreferencial(f);
  printf("\nLog fila preferencial [elementos: %i] - Inicio:", numElementos);
  atual = f->inicioPref;
  while (atual)
  {
    printf(" [%i;%i]", atual->id, atual->ehPreferencial);
    atual = atual->prox;
  }
  printf("\n\n");
}

bool inserirPessoaNaFila(PFILA f, int id, int ehPreferencial)
{
  bool resposta = false;

  if (id < 0)
  {
    return resposta;
  }

  PONT verificaId = f->inicioGeral;
  while (verificaId)
  {
    if (verificaId->id == id)
      return resposta;
    verificaId = verificaId->prox;
  }

  PONT pessoa = (PONT)malloc(sizeof(ELEMENTO));

  pessoa->id = id;
  pessoa->ehPreferencial = ehPreferencial;

  if (f->fimGeral == NULL || f->inicioGeral == NULL)
  {
    f->inicioGeral = pessoa;
    f->fimGeral = f->inicioGeral;
  }

  else
  {
    f->fimGeral->prox = pessoa;
    f->fimGeral = pessoa;
  }

  if (pessoa->ehPreferencial == true)
  {
    PONT pessoaPreferencial = (PONT)malloc(sizeof(ELEMENTO));

    pessoaPreferencial->id = id;
    pessoaPreferencial->ehPreferencial = ehPreferencial;

    if (f->fimPref == NULL || f->inicioPref == NULL)
    {
      f->inicioPref = pessoaPreferencial;
      f->fimPref = f->inicioPref;
    }

    else
    {
      f->fimPref->prox = pessoaPreferencial;
      f->fimPref = pessoaPreferencial;
    }
  }

  return !resposta;
}

bool atenderPrimeiraDaFilaPreferencial(PFILA f, int *id)
{
  bool resposta = false;

  /* COMPLETAR */

  int ehPreferencial;
  int i = 0;
  PONT percorre = f->inicioGeral->prox;
  PONT segundaPosicao = f->inicioGeral;

  if (f->inicioGeral == NULL && f->fimGeral == NULL)
  {
    return resposta;
  }

  if (f->fimPref != NULL && f->inicioPref != NULL)
  {

    *id = f->inicioPref->id;

    PONT atenderPessoaPreferencial = f->inicioPref;

    f->inicioPref = f->inicioPref->prox;

    if (f->inicioGeral->ehPreferencial == true) // verifica a primeira posição
    {
      f->inicioGeral = f->inicioGeral->prox;
    } // mantem isso aqui heim

    else
    {
      /*while (atual->ehPreferencial)
      {
        if (atual->ehPreferencial == true)
        {
          atual = atual->prox;
          i++;
          printf("O tamanho do i: %i.\n", i);
          printf("\n");
        }
        atual->prox;
      }*/

      while (percorre->prox)
      {
        if (percorre->ehPreferencial == true)
        {
          percorre = percorre->prox;
        }
        if (percorre->prox->ehPreferencial == true)
        {
          percorre->prox = percorre->prox->prox;
        }
        break;
      }

      while (segundaPosicao)
      {
        if (segundaPosicao->ehPreferencial == true)
        {
          segundaPosicao = segundaPosicao->prox;
        }
        if (segundaPosicao->prox->ehPreferencial == true)
        {
          segundaPosicao->prox = segundaPosicao->prox->prox;
        }
        break;
      }
    }

    printf("O tamanho do i: %i.\n", i);
    printf("\n");

    free(atenderPessoaPreferencial);

    return !resposta;
  }

  /*if (f->fimPref == NULL && f->inicioPref == NULL && f->fimGeral != NULL && f->inicioGeral != NULL)
  {

    *id = f->inicioGeral->id;

    PONT atenderPessoa = f->inicioGeral;

    f->inicioGeral = f->inicioGeral->prox;

    free(atenderPessoa);

    if (f->inicioGeral == NULL)
    {
      f->fimGeral = NULL;
    }

    return !resposta;
  }*/

  return !resposta;
}

bool atenderPrimeiraDaFilaGeral(PFILA f, int *id)
{
  bool resposta = false;

  /* COMPLETAR */

  PONT pessoa;

  if (f->fimGeral == NULL || f->inicioGeral == NULL)
  {
    return resposta;
  }

  /*if (f->inicioGeral->ehPreferencial == true)
  {

    *id = f->inicioGeral->ehPreferencial;

    PONT atenderFilaGeral = f->inicioGeral;

    f->inicioGeral = f->inicioGeral->prox;

    free(atenderFilaGeral);

    if (f->inicioGeral == NULL)
    {
      f->fimGeral = NULL;
    }

    return !resposta;
  }*/

  /*if (f->fimGeral != NULL && f->inicioGeral != NULL)
  {

    *id = f->inicioGeral->id;

    PONT atenderPessoa = f->inicioGeral;

    f->inicioGeral = f->inicioGeral->prox;

    free(atenderPessoa);

    if (f->inicioGeral == NULL)
    {
      f->fimGeral = NULL;
    }
  }*/

  return resposta;
}

bool desistirDaFila(PFILA f, int id)
{
  bool resposta = false;

  /* COMPLETAR */

  PONT pessoa;

  if (id != f->fimGeral->id && id != f->inicioGeral->id)
  {
    return resposta;
  }

  /*if(pessoa->ehPreferencial == true){

  }*/

  return resposta;
}

/* while (f->inicioGeral->prox)
    {
      //if (f->inicioGeral->prox->ehPreferencial == true)
      f->inicioGeral->prox = f->inicioGeral->prox->prox;
      i++;
    } */