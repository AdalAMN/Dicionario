#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lse.h"
#include "estrutura.h"

//Area da Hash

typedef struct imprimir t_imprimir_hash;
typedef struct hash{
    t_imprimir_hash* impressora;
    t_lse* *vetor;
    int tamanho;
    double fc;
}t_hash;

t_hash* criar_hash(double fc){
    t_hash* nova = malloc(sizeof(t_hash));

    nova->fc = fc;
    nova->tamanho = 7;
    nova->vetor = malloc(sizeof(t_lse*)*nova->tamanho);
    for(int i=0;i<nova->tamanho;i++){
        nova->vetor[i] = criar_lse(imprimir_elem_hash, comparar_elem_hash);
    }
    
    return nova;
}

int comparar_elem_hash(void* e1, void* e2){
    t_sensores* ee1 = e1;
    t_sensores* ee2 = e2;
    return (ee1->Pump_ID - ee2->Pump_ID);
}

int funcao_hashing(t_hash* t, int chave){
    int pos = chave % t->tamanho;

    return pos;
}

void inserir_hash(t_hash* t, t_sensores* sensor){
    int pos = funcao_hashing(t, sensor->Pump_ID);

    t_lse* colisoes = t->vetor[pos];
    t_sensores* novo = criar_elem_hash(sensor->Pump_ID);
    inserir_inicio_lse(colisoes, novo );
}

void* buscar_hash(t_hash* t, int chave){
    int pos = funcao_hashing(t, chave);

    t_lse* colisoes = t->vetor[pos];
    t_sensores* e = acessar_conteudo_lse(colisoes, &chave);
    if (e!=NULL)
        return e;
    else
        return NULL;
}

void* buscar_report(t_hash* t, int chave){
    int pos = funcao_hashing(t, chave);

    t_lse* colisoes = t->vetor[pos];
    t_sensores* e = acessar_conteudo_lse(colisoes, &chave);
    if (e!=NULL)
        return imprimir_report;
    else
        return NULL;
}

void* remover_hash(t_hash* t, int chave){
    void* carga =NULL;
    int pos = funcao_hashing(t, chave);

    t_lse* colisoes = t->vetor[pos];

    t_sensores* e = remover_conteudo_lse(colisoes, &chave);
    if (e != NULL){
        carga = e->Pump_ID;
        destroy_elem_hash(e); 
    }
    return carga;
}

void imprimir_hash(t_hash* t){
   int K =  t->tamanho;
   for (int k=0;k<K;k++){
        t_lse* colisoes = t->vetor[k];
        imprimir_lse(colisoes); // potencial 
   }
}

void imprimir_elem_hash(void* ee){
    t_sensores* e = ee;

    printf("%d\n", e->Pump_ID);
}

//Area dos elementos da Hash
t_sensores* criar_sensores(int Pump_ID, float Class_ID, float Temperatura, float Vibrations, float Pressure, float Flow_Rate, float RPM, float Operational_Hours, float Maintaince_Flag){
    t_sensores* S = malloc(sizeof(t_sensores));
        S->Pump_ID = Pump_ID;
        S-> Class_ID = Class_ID;
        S-> Temperatura = Temperatura;
        S-> Vibrations = Vibrations;
        S-> Pressure = Pressure;
        S-> Flow_Rate = Flow_Rate;
        S-> RPM = RPM;
        S-> Operational_Hours = Operational_Hours;
        S-> Maintaince_Flag = Maintaince_Flag;

    return S;
}

typedef struct sensores{
    int Pump_ID;
    float Class_ID;
    float Temperatura;
    float Vibrations;
    float Pressure;
    float Flow_Rate;
    float RPM;
    float Operational_Hours;
    float Maintaince_Flag;
}t_sensores;

void imprimir_sensor(t_sensores* sensor){
    printf("%d\n%f\n%f\n%f\n%f\n%f\n%f\n%f\n%f\n", sensor->Pump_ID, sensor->Class_ID, sensor->Temperatura, sensor->Vibrations, sensor->Pressure, sensor->Flow_Rate, sensor->RPM, sensor->Operational_Hours, sensor->Maintaince_Flag);
}
void imprimir_report(t_sensores* sensor){
    printf("%f\n%f\n%f\n", sensor->Temperatura, sensor->Vibrations, sensor->Pressure);
}
