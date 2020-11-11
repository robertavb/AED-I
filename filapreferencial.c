/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Seugndo Semestre de 2020                           **/
/**   <2020204> - Prof. Luciano Antonio Digiampietri                **/
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
        {
            return resposta;
        }
        verificaId = verificaId->prox;
    }

    PONT pessoa = (PONT)malloc(sizeof(ELEMENTO));

    pessoa->prox = NULL;
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

    if (pessoa->ehPreferencial)
    {
        PONT pessoaPreferencial = (PONT)malloc(sizeof(ELEMENTO));

        pessoaPreferencial->id = id;
        pessoaPreferencial->ehPreferencial = ehPreferencial;
        pessoaPreferencial->prox = NULL;

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

bool atenderPrimeiraDaFilaGeral(PFILA f, int *id)
{
    bool resposta = false;
    PONT aux = f->inicioGeral;
    int ehPreferencial;
    PONT apagar;

    if (f->inicioGeral == NULL)
    {
        return resposta;
    }

    if (f->inicioGeral->ehPreferencial)
    {
        *id = f->inicioGeral->id;

        PONT atenderFilaGeral = f->inicioGeral;
        PONT atenderFilaP = f->inicioPref;

        f->inicioGeral = f->inicioGeral->prox; /*primeira pessoa*/
        f->inicioPref = f->inicioPref->prox;   /*primeira pessoa*/

        free(atenderFilaGeral);
        free(atenderFilaP);

        if (f->inicioGeral == NULL)
        {
            f->fimGeral = NULL;
        }

        if (f->inicioPref == NULL)
        {
            f->fimPref = NULL;
        }
    }

    else
    {
        *id = f->inicioGeral->id;

        PONT atenderFilaGeral2 = f->inicioGeral;

        f->inicioGeral = f->inicioGeral->prox; /*primeira pessoa*/

        free(atenderFilaGeral2);

        if (f->inicioGeral == NULL)
        {
            f->fimGeral = NULL;
        }
    }

    return !resposta;
}

bool atenderPrimeiraDaFilaPreferencial(PFILA f, int *id)
{
    bool resposta = false;

    PONT aux = f->inicioGeral;

    if (f->inicioGeral == NULL)
    {
        return resposta;
    }

    if (f->inicioPref != NULL)
    {
        *id = f->inicioPref->id;

        PONT atenderPessoaPreferencial = f->inicioPref;

        f->inicioPref = f->inicioPref->prox;

        PONT apagar;

        if (f->inicioGeral->ehPreferencial) /* verifica a primeira posição */
        {
            apagar = f->inicioGeral;
            f->inicioGeral = f->inicioGeral->prox;
            free(apagar);
        }

        else
        {
            PONT ant = NULL;
            while (aux->id != atenderPessoaPreferencial->id)
            {
                ant = aux;
                aux = aux->prox;
            }
            if (aux->ehPreferencial)
            {
                ant->prox = aux->prox;
            }
            free(aux);
        }

        free(atenderPessoaPreferencial);

        if (f->inicioPref == NULL)
        {
            f->fimPref = NULL;
        }

        return !resposta;
    }

    return atenderPrimeiraDaFilaGeral(f, id);
}

bool desistirDaFila(PFILA f, int id)
{
    bool resposta = false;

    PONT verificaId = f->inicioGeral;
    PONT aux = f->inicioGeral;
    PONT auxiliar = f->inicioPref;
    PONT ant = NULL;
    PONT anterior = NULL;
    PONT atenderPessoaPreferencial = f->inicioPref;

    PONT atual = f->inicioGeral;
    while (atual)
    {
        if (atual->id != id)
            return resposta;
        atual = atual->prox;
        break;
    }

    while (verificaId->id)
    {
        if (verificaId->id == id)
        { /* a pessoa a desistir é a primeira da fila*/

            if (f->inicioGeral->ehPreferencial) /*primeira da fila e é preferencial*/
            {
                PONT atenderFilaGeral = f->inicioGeral;
                PONT atenderFilaP = f->inicioPref;

                f->inicioGeral = f->inicioGeral->prox; /*primeira pessoa*/
                f->inicioPref = f->inicioPref->prox;   /*primeira pessoa*/

                free(atenderFilaGeral);
                free(atenderFilaP);

                if (f->inicioGeral == NULL)
                {
                    f->fimGeral = NULL;
                }

                if (f->inicioPref == NULL)
                {
                    f->fimPref = NULL;
                }

                return !resposta;
            }

            if (f->inicioGeral->id == id) /*primeira da fila e não é preferencial*/
            {
                PONT atenderFilaGeral2 = f->inicioGeral;

                f->inicioGeral = f->inicioGeral->prox; /*primeira pessoa*/

                free(atenderFilaGeral2);

                if (f->inicioGeral == NULL)
                {
                    f->fimGeral = NULL;
                }

                return !resposta;
            }
        }

        else
        {
            while (aux)
            {

                if (auxiliar->id == f->fimPref->id)
                {

                    f->inicioPref = NULL;
                    free(auxiliar);

                    if (f->inicioPref = NULL)
                    {
                        f->fimPref = NULL;
                    }

                    return !resposta;
                }

                ant = aux;
                aux = aux->prox;

                if (aux || aux->id == id)
                {
                    ant->prox = aux->prox;

                    if (aux->ehPreferencial)
                    {

                        aux = auxiliar;

                        anterior = auxiliar;
                        auxiliar = auxiliar->prox;

                        if (auxiliar->id)
                        {
                            anterior->prox = auxiliar->prox;
                        }

                        free(auxiliar);

                        if (f->inicioPref == NULL)
                        {
                            f->fimPref = NULL;
                        }
                    }

                    free(aux);

                    if (f->inicioGeral == NULL)
                    {
                        f->fimGeral = NULL;
                    }

                    return !resposta;
                }
            }
        }
        verificaId = verificaId->prox;
    }

    return !resposta;
}