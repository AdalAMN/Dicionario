#include "factory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_file(const char *filename, AVLTree *tree) {
	FILE *file = fopen(filename, "r");
	if (!file) {
		fprintf(stderr, "Erro ao abrir o arquivo: %s\n", filename);
		exit(1);
	}

	char command[10];
	while (fscanf(file, "%s", command) != EOF) {
		if (strcmp(command, "ADD") == 0) {
			int barcode, class_id, maintenance_flag;
			float temperature, vibration, pressure, flow_rate, rpm, operational_hours;

			fscanf(file, "%d %d %f %f %f %f %f %f %d",
				&barcode, &class_id, &temperature, &vibration, &pressure,
				&flow_rate, &rpm, &operational_hours, &maintenance_flag);

			ElementData data;
			data.class_id = class_id;
			data.temperature = temperature;
			data.vibration = vibration;
			data.pressure = pressure;
			data.flow_rate = flow_rate;
			data.rpm = rpm;
			data.operational_hours = operational_hours;
			data.maintenance_flag = maintenance_flag;

			insert_node(tree, barcode, data);
			printf("Medida adicionada para o código de barras: %d\n", barcode);

		} else if (strcmp(command, "SEARCH") == 0) {
			int barcode;
			fscanf(file, "%d", &barcode);
			Node *result = search_node(tree, barcode);
			if (result) {
					printf("Medições para código de barras %d:\n", barcode);
					printf("Temperature: %.2f, Vibration: %.2f, Pressure: %.2f, Flow Rate: %.2f, RPM: %.2f, Operational Hours: %.2f, Maintenance Flag: %d\n",
									result->data.temperature, result->data.vibration, result->data.pressure,
									result->data.flow_rate, result->data.rpm, result->data.operational_hours,
									result->data.maintenance_flag);
			} else {
					printf("Código de barras %d não encontrado.\n", barcode);
			}

		} else if (strcmp(command, "REPORT") == 0) {
			char report_type[10];
			int barcode;
			fscanf(file, "%s %d", report_type, &barcode);

			Node *node = search_node(tree, barcode);
			if (node == NULL) {
					printf("Código de barras %d não encontrado para relatório.\n", barcode);
					continue;
			}

			if (strcmp(report_type, "MEAN") == 0) {
					calculate_mean(node);
			} else if (strcmp(report_type, "MAX") == 0) {
					calculate_max(node);
			} else if (strcmp(report_type, "MIN") == 0) {
					calculate_min(node);
			}

		} else if (strcmp(command, "REMOVE") == 0) {
			int barcode;
			fscanf(file, "%d", &barcode);
			Node *result = delete_node(tree, barcode);
			if (result) {
					printf("Medições removidas para o código de barras %d\n", barcode);
			} else {
					printf("Código de barras %d não encontrado para remoção.\n", barcode);
			}

		} else if (strcmp(command, "END") == 0) {
			printf("Encerrando processamento.\n");
			break;
		}
	}

	fclose(file);
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "Uso: %s <arquivo_de_entrada>\n", argv[0]);
		return 1;
	}

	AVLTree *tree = create_avl_tree();

	// Processa o arquivo de entrada passado como argumento
	process_file(argv[1], tree);

	// Libera a memória ao final
	free_tree(tree);

	return 0;
}
