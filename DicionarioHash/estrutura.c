#include "stdio.h"
#include "stdlib.h"

typedef struct elem_hash{
    int chave;
    void* carga;
}t_elem_hash;

typedef struct hash{
    t_imprimir_hash impressora;
    t_lse* *vetor;
    int tamanho;
    double fc;
}t_hash;

t_elem_hash* criar_elem_hash(int chave, void* carga){
    t_elem_hash* e = malloc(sizeof(t_elem_hash));
    e->chave = chave;
    e->carga = carga;

    return e;
}

struct sensores{
    char tipo;
    char localizacao;
    char dadosHistoricos;
    char alarmes;
};

struct equipamentos{
    char modelo;
    char fabricante;
    int dataDeInstalacao;
    char historico;
};

struct materiais{
    int lote;
    char fornecedor;
    int dataValidade;
    char localizacao;
};
