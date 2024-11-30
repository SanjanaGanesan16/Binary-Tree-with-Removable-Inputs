#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;



struct Node* createNode(int data, struct Node* parent){
    struct Node* new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = parent;

    return new_node;
}


void insertNode(struct Node** tree, int data, struct Node* parent){
    if (*tree == NULL){
        struct Node* new_node = createNode(data, parent);
        *tree = new_node;
    }
    else{
        int root_value = (*tree)->data;
        if (data < root_value){
            insertNode(&(*tree)->left, data, *tree);
        }
        else{
            insertNode(&(*tree)->right, data, *tree);
        }
    }
}



void freeNode(struct Node* node){
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    free(node);
}



void replaceNode(struct Node* current_node, struct Node* new_node){
    if (current_node->parent){
        if (current_node->data == current_node->parent->left->data){
            current_node->parent->left = new_node;
        }
        else if (current_node->data == current_node->parent->right->data){
            current_node->parent->right = new_node;
        }
    }

    if (new_node){
        new_node->parent = current_node->parent;
    }
}



struct Node* findMinimum(struct Node* tree){
    if (tree == NULL){
        return NULL;
    }
    if (tree->left){
        findMinimum(tree->left);
    }
    else{
        return tree;
    }
}



void removeNode(struct Node* target_node){
    if (target_node->left && target_node->right){
        struct Node* minimum = findMinimum(target_node->right);
        target_node->data = minimum->data;
        removeNode(minimum);
    }


    else if (target_node->left){
        replaceNode(target_node, target_node->left);
        freeNode(target_node);
    }

    else if (target_node->right){
        replaceNode(target_node, target_node->right);
        freeNode(target_node);
    }

    else{
        replaceNode(target_node, NULL);
        freeNode(target_node);
    }
}



void deleteNode(struct Node* tree, int data){
    if (tree == NULL){
        return;
    }

    else if (data < tree->data){
        deleteNode(tree->left, data);
    }

    else if( data > tree->data){
        deleteNode(tree->right, data);
    }

    else{
        removeNode(tree);
    }

}




void printTree(struct Node* tree, int counter){
    if (tree == NULL){
        return;
    }
    else{
        printTree(tree->right, counter + 1);
        for (int i = 0; i < counter; ++i){
            printf("     ");
        }
        printf("(%d)\n", tree->data);
        
        printTree(tree->left, counter + 1);
        
    }
}


bool search(struct Node* tree, int data){
    if (tree == NULL){
        return false;
    }
    else if (tree->data == data){
        return true;
    }
    else if (data < tree->data){
        search(tree->left, data);
    }
    else{
        search(tree->right, data);
    }
}


int main() {
    struct Node* root = NULL;
    int counter = 0;
    insertNode(&root, 30, NULL);
    insertNode(&root, 10, NULL);
    insertNode(&root, 5, NULL);
    insertNode(&root, 20, NULL);
    insertNode(&root, 15, NULL);
    insertNode(&root, 14, NULL);
    insertNode(&root, 16, NULL);
    insertNode(&root, 25, NULL);
    insertNode(&root, 22, NULL);
    insertNode(&root, 23, NULL);
    insertNode(&root, 27, NULL);
    insertNode(&root, 40, NULL);
    insertNode(&root, 37, NULL);
    insertNode(&root, 32, NULL);
    insertNode(&root, 38, NULL);




    
    // int value = 20;
    // printTree(root, counter);
    
    // if (search(root, value)){
    //     printf("value [%d] has been found!", value);
    // }
    // else{
    //     printf("value [%d] has not been found!", value);

    // }
    deleteNode(root, 30);
    printTree(root, counter);

    return 0;
}
