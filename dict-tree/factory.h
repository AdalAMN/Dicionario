#ifndef FACTORY_H
#define FACTORY_H

typedef struct ElementData {
    int class_id;
    float temperature;
    float vibration;
    float pressure;
    float flow_rate;
    float rpm;
    float operational_hours;
    int maintenance_flag;
} ElementData;

typedef struct Node {
    int barcode;
    ElementData data;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

typedef struct AVLTree {
    Node* root;
} AVLTree;

// Funções de árvore AVL
AVLTree* create_avl_tree();
Node* insert_node(AVLTree* tree, int barcode, ElementData data);
Node* search_node(AVLTree* tree, int barcode);
Node* delete_node(AVLTree* tree, int barcode);
void generate_report(AVLTree* tree);
void calculate_mean(Node* node);
void calculate_max(Node* node);
void calculate_min(Node* node);
void free_tree(AVLTree* tree);

#endif
