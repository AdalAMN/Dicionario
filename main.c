#include "stdio.h"
#include "stdlib.h"
#include "estrutura.h"
#include "lse.h"
#include "string.h"
#include <limits.h>

#define MAX_DATA 1000

int data[MAX_DATA];
int data_count = 0;


void add(t_hash* fabrica, t_sensores* value) {
    if (data_count < MAX_DATA) {
        data[data_count++] = value;
        inserir_hash(fabrica, value);
    } else {
        printf("Erro: capacidade máxima atingida.\n");
    }
}

void search(t_hash* fabrica ,int value) {
    print(buscar_hash(fabrica, value));
}

void remove_value(t_hash* fabrica, int value) {
    printf("removido %d", remover_hash(fabrica, value));
    
}

void report_mean(t_hash* fabrica, int sensor) {

    buscar_hash(fabrica, sensor);
    
}

void report_max(t_hash* fabrica, int sensor) {
    buscar_hash(fabrica, sensor);
}

void report_min(t_hash* fabrica ,int sensor) {
    buscar_hash(fabrica, sensor);
}

void process_batch(t_hash* fabrica, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char command[20];
    while (fscanf(file, "%s", command) != EOF) {
        if (strcmp(command, "ADD") == 0) {
            t_sensores* value;
            fscanf(file, "%d", &value);
            add(fabrica, value);
        } else if (strcmp(command, "SEARCH") == 0) {
            int value;
            fscanf(file, "%d", &value);
            search(fabrica, value);
        } else if (strcmp(command, "REMOVE") == 0) {
            int value;
            fscanf(file, "%d", &value);
            remove_value(fabrica, value);
        } else if (strcmp(command, "REPORT") == 0) {
            char subcommand[10];
            int id;
            fscanf(file, "%s %d", subcommand, id);
            if (strcmp(subcommand, "MEAN") == 0) {
                report_mean(fabrica, id);
            } else if (strcmp(subcommand, "MAX") == 0) {
                report_max(fabrica, id);
            } else if (strcmp(subcommand, "MIN") == 0) {
                report_min(fabrica, id);
            } else {
                printf("Subcomando de REPORT desconhecido: %s\n", subcommand);
            }
        } else if (strcmp(command, "END") == 0) {
            printf("Finalizando processamento.\n");
            break;
        } else {
            printf("Comando desconhecido: %s\n", command);
        }
    }

    fclose(file);
}

int main() {
    t_hash* fabrica = criar_hash(0.7);
    char cmd[15];
    process_batch(fabrica, scanf("%s", cmd));
    return 0;
}
