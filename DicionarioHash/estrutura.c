#include "stdio.h"
#include "stdlib.h"

typedef struct elem_hash t_elem_hash;
struct elem_hash{
    int chave;
    void* carga;
};

t_elem_hash* criar_elem_hash(int chave, void* carga){
    t_elem_hash* e = malloc(sizeof(t_elem_hash));
    e->chave = chave;
    e->carga = carga;

    return e;
}

typedef struct sensores{
    char tipo;
    char localizacao;
    char dadosHistoricos;
    char alarmes;
}t_sensores;

typedef struct equipamentos{
    char modelo;
    char fabricante;
    int dataDeInstalacao;
    char historico;
}t_equipamentos;

typedef struct materiais{
    int lote;
    char fornecedor;
    int dataValidade;
    char localizacao;
}t_materiais;