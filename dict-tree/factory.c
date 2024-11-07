#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "factory.h"

// Função para criar uma nova árvore AVL
AVLTree* create_avl_tree() {
    AVLTree* tree = (AVLTree*)malloc(sizeof(AVLTree));
    tree->root = NULL;
    return tree;
}

// Função para criar um novo nó com os dados de um elemento
Node* create_node(int barcode, ElementData data) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->barcode = barcode;
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return node;
}

int get_height(Node* node) {
	return node ? node->height : 0;
}

int get_balance_factor(Node* node) {
	return node ? get_height(node->left) - get_height(node->right) : 0;
}

Node* right_rotate(Node* y) {
	Node* x = y->left;
	Node* T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = 1 + (get_height(y->left) > get_height(y->right) ? get_height(y->left) : get_height(y->right));
	x->height = 1 + (get_height(x->left) > get_height(x->right) ? get_height(x->left) : get_height(x->right));

	return x;
}

Node* left_rotate(Node* x) {
	Node* y = x->right;
	Node* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = 1 + (get_height(x->left) > get_height(x->right) ? get_height(x->left) : get_height(x->right));
	y->height = 1 + (get_height(y->left) > get_height(y->right) ? get_height(y->left) : get_height(y->right));

	return y;
}

// Função para inserir um novo elemento na árvore AVL
Node* insert_node_rec(Node* node, int barcode, ElementData data) {
	if (!node) return create_node(barcode, data);

	if (barcode < node->barcode) {
		node->left = insert_node_rec(node->left, barcode, data);
	} else if (barcode > node->barcode) {
		node->right = insert_node_rec(node->right, barcode, data);
	} else {
		printf("Erro: Código de barras %d já existe.\n", barcode);
		return node;
	}

	node->height = 1 + (get_height(node->left) > get_height(node->right) ? get_height(node->left) : get_height(node->right));

	int balance_factor = get_balance_factor(node);

	if (balance_factor > 1 && barcode < node->left->barcode) return right_rotate(node);
	if (balance_factor < -1 && barcode > node->right->barcode) return left_rotate(node);
	if (balance_factor > 1 && barcode > node->left->barcode) {
		node->left = left_rotate(node->left);
		return right_rotate(node);
	}
	if (balance_factor < -1 && barcode < node->right->barcode) {
		node->right = right_rotate(node->right);
		return left_rotate(node);
	}

	return node;
}

Node* insert_node(AVLTree* tree, int barcode, ElementData data) {
	tree->root = insert_node_rec(tree->root, barcode, data);
	return tree->root;
}

// Função para buscar um nó na árvore AVL pelo código de barras
Node* search_node(AVLTree* tree, int barcode) {
	Node* current = tree->root;
	while (current != NULL) {
		if (barcode < current->barcode) {
			current = current->left;
		} else if (barcode > current->barcode) {
			current = current->right;
		} else {
			return current;
		}
	}
	return NULL;
}

// Função para encontrar o menor valor de um nó (para remoção)
Node* get_min_node(Node* node) {
	Node* current = node;
	while (current->left != NULL) {
		current = current->left;
	}
	return current;
}

// Função de remoção recursiva
Node* delete_node_rec(Node* root, int barcode) {
	if (!root) return NULL;

	if (barcode < root->barcode) {
		root->left = delete_node_rec(root->left, barcode);
	} else if (barcode > root->barcode) {
		root->right = delete_node_rec(root->right, barcode);
	} else {
		if (!root->left) {
			Node* temp = root->right;
			free(root);
			return temp;
		} else if (!root->right) {
			Node* temp = root->left;
			free(root);
			return temp;
		}
		Node* temp = get_min_node(root->right);
		root->barcode = temp->barcode;
		root->data = temp->data;
		root->right = delete_node_rec(root->right, temp->barcode);
	}

	root->height = 1 + (get_height(root->left) > get_height(root->right) ? get_height(root->left) : get_height(root->right));

	int balance_factor = get_balance_factor(root);

	if (balance_factor > 1 && get_balance_factor(root->left) >= 0) return right_rotate(root);
	if (balance_factor < -1 && get_balance_factor(root->right) <= 0) return left_rotate(root);
	if (balance_factor > 1 && get_balance_factor(root->left) < 0) {
		root->left = left_rotate(root->left);
		return right_rotate(root);
	}
	if (balance_factor < -1 && get_balance_factor(root->right) > 0) {
		root->right = right_rotate(root->right);
		return left_rotate(root);
	}

	return root;
}

Node* delete_node(AVLTree* tree, int barcode) {
	tree->root = delete_node_rec(tree->root, barcode);
	return tree->root;
}

// Funções de cálculo de média, máximo e mínimo
void calculate_mean_rec(Node* node, float* total_temperature, float* total_vibration, float* total_pressure, int* count) {
	if (!node) return;

	*total_temperature += node->data.temperature;
	*total_vibration += node->data.vibration;
	*total_pressure += node->data.pressure;
	(*count)++;

	calculate_mean_rec(node->left, total_temperature, total_vibration, total_pressure, count);
	calculate_mean_rec(node->right, total_temperature, total_vibration, total_pressure, count);
}

void calculate_mean(Node* node) {
	float total_temperature = 0, total_vibration = 0, total_pressure = 0;
	int count = 0;

	calculate_mean_rec(node, &total_temperature, &total_vibration, &total_pressure, &count);

	if (count > 0) {
		printf("Média - Temperature: %.2f, Vibration: %.2f, Pressure: %.2f\n",
		total_temperature / count,
		total_vibration / count,
		total_pressure / count);
	}
}

void calculate_max_rec(Node* node, float* max_temperature, float* max_vibration, float* max_pressure) {
	if (!node) return;

	if (node->data.temperature > *max_temperature) *max_temperature = node->data.temperature;
	if (node->data.vibration > *max_vibration) *max_vibration = node->data.vibration;
	if (node->data.pressure > *max_pressure) *max_pressure = node->data.pressure;

	calculate_max_rec(node->left, max_temperature, max_vibration, max_pressure);
	calculate_max_rec(node->right, max_temperature, max_vibration, max_pressure);
}

void calculate_max(Node* node) {
	if (!node) return;

	float max_temperature = node->data.temperature;
	float max_vibration = node->data.vibration;
	float max_pressure = node->data.pressure;

	calculate_max_rec(node, &max_temperature, &max_vibration, &max_pressure);

	printf("Máximo - Temperature: %.2f, Vibration: %.2f, Pressure: %.2f\n",
					max_temperature, max_vibration, max_pressure);
}

void calculate_min_rec(Node* node, float* min_temperature, float* min_vibration, float* min_pressure) {
	if (!node) return;

	if (node->data.temperature < *min_temperature) *min_temperature = node->data.temperature;
	if (node->data.vibration < *min_vibration) *min_vibration = node->data.vibration;
	if (node->data.pressure < *min_pressure) *min_pressure = node->data.pressure;

	calculate_min_rec(node->left, min_temperature, min_vibration, min_pressure);
	calculate_min_rec(node->right, min_temperature, min_vibration, min_pressure);
}

void calculate_min(Node* node) {
	if (!node) return;

	float min_temperature = node->data.temperature;
	float min_vibration = node->data.vibration;
	float min_pressure = node->data.pressure;

	calculate_min_rec(node, &min_temperature, &min_vibration, &min_pressure);

	printf("Mínimo - Temperature: %.2f, Vibration: %.2f, Pressure: %.2f\n",
					min_temperature, min_vibration, min_pressure);
}

void free_tree_rec(Node* node) {
	if (node != NULL) {
			free_tree_rec(node->left);
			free_tree_rec(node->right);
			free(node);
	}
}

void free_tree(AVLTree* tree) {
	free_tree_rec(tree->root);
	free(tree);
}
