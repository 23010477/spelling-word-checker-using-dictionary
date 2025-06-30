#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Colored output
#define RED "\033[0;91m"
#define ORANGE "\033[38;5;214m"
#define YELLOW "\033[0;93m"
#define GREEN "\033[0;92m"
#define BLUE "\033[0;94m"
#define PURPLE "\033[35m"
#define PINK "\033[38;5;200m"
#define RESET "\033[0m"

// Node structure for a BST holding words
typedef struct Node {
    char word[100];
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    int height;
} Node;

// Create a new node with a given word
Node* createNode(char* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->word, value);
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    newNode->height = 1;
    return newNode;
}

// Get height of a node (handles NULL nodes)
int getHeight(Node* node) {
    if (node == NULL) return 0;
    return node->height;
}

// Calculate and update the height of a node based on its children
void updateHeight(Node* node) {
    if (node == NULL) return;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Get balance factor of a node
int getBalance(Node* node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Find the height of the tree
int height(Node* root) {
    if (root == NULL) return 0;
    return root->height;
}

// Check if the tree is balanced
int isBalanced(Node* root) {
    if (root == NULL) return 1;
    int balance = getBalance(root);
    if (abs(balance) > 1) {
        return 0;
    }
    return isBalanced(root->left) && isBalanced(root->right);
}

// Left rotation with proper parent pointer updates
Node* leftRotate(Node* x) {
    if (x == NULL || x->right == NULL) return x;
    
    Node* y = x->right;
    Node* T2 = y->left;
    Node* parent = x->parent;
    
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    // Update parent pointers
    x->parent = y;
    y->parent = parent;
    if (T2 != NULL) {
        T2->parent = x;
    }
    
    // Update heights
    updateHeight(x);
    updateHeight(y);
    
    return y;  // new root
}

// Right rotation with proper parent pointer updates
Node* rightRotate(Node* y) {
    if (y == NULL || y->left == NULL) return y;
    
    Node* x = y->left;
    Node* T2 = x->right;
    Node* parent = y->parent;
    
    // Perform rotation
    x->right = y;
    y->left = T2;
    
    // Update parent pointers
    y->parent = x;
    x->parent = parent;
    if (T2 != NULL) {
        T2->parent = y;
    }
    
    // Update heights
    updateHeight(y);
    updateHeight(x);
    
    return x;  // new root
}

// Insert a word into the AVL tree
Node* insert(Node* root, char* value) {
    // Standard BST insertion
    if (root == NULL) {
        return createNode(value);
    }
    
    int cmp = strcasecmp(value, root->word);
    if (cmp < 0) {
        Node* leftChild = insert(root->left, value);
        root->left = leftChild;
        leftChild->parent = root;
    } else if (cmp > 0) {
        Node* rightChild = insert(root->right, value);
        root->right = rightChild;
        rightChild->parent = root;
    } else {
        // Duplicate value, just return the existing node
        return root;
    }
    
    // Update height of current node
    updateHeight(root);
    
    // Get balance factor to check if node became unbalanced
    int balance = getBalance(root);
    
    // Left-Left Case
    if (balance > 1 && strcasecmp(value, root->left->word) < 0) {
        return rightRotate(root);
    }
    
    // Right-Right Case
    if (balance < -1 && strcasecmp(value, root->right->word) > 0) {
        return leftRotate(root);
    }
    
    // Left-Right Case
    if (balance > 1 && strcasecmp(value, root->left->word) > 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    // Right-Left Case
    if (balance < -1 && strcasecmp(value, root->right->word) < 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    // Return the unchanged node pointer
    return root;
}

// Search for a word in the BST
Node* search(Node* root, char* value, Node** last) {
    Node* current = root;
    *last = NULL;
    while (current != NULL) {
        int cmp = strcasecmp(value, current->word);
        *last = current;          // update last visited node
        if (cmp == 0) {
            return current;       // found node
        } else if (cmp < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL;  // word not found
}

// Load words from a file into the BST
Node* input_dictionary(Node* root, int* count) {
    FILE* fptr = fopen("D:\\programming\\projects\\C\\Data Structure\\assign 5\\Dictionary.txt", "r");
    if (fptr == NULL) {
        printf(RED "Error: Could not open the 'Dictionary.txt'\n" RESET);
        return NULL;
    }

    char buffer[150];  // Holds the line from the file
    char word[100];    // Extracted word
    *count = 0;

    int lineNumber = 0;
    while (fgets(buffer, sizeof(buffer), fptr)) {
        lineNumber++;

        // Remove newline
        buffer[strcspn(buffer, "\r\n")] = 0;

        // Use sscanf to extract word
        if (sscanf(buffer, "%99s", word) == 1) {
            root = insert(root, word);
            (*count)++;
        } else {
            printf(RED "Warning: Skipping invalid line %d\n" RESET, lineNumber);
        }
    }

    fclose(fptr);
    return root;
}

// Inorder traversal (prints words alphabetically)
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%s ", root->word);
        inorder(root->right);
    }
}

// Count nodes
int countNodes(Node* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Find minimum node starting from given node
Node* tree_minimum(Node* node) {
    if (node == NULL) return NULL;
    
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Find maximum node starting from given node
Node* tree_maximum(Node* node) {
    if (node == NULL) return NULL;
    
    while (node->right != NULL) {
        node = node->right;
    }
    return node;
}

// Find the successor of a given node
Node* tree_successor(Node* x) {
    if (x == NULL) return NULL;
    
    if (x->right != NULL) {
        return tree_minimum(x->right);
    }

    Node* y = x->parent;
    while (y != NULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

// Find the predecessor of a given node
Node* tree_predecessor(Node* x) {
    if (x == NULL) return NULL;
    
    if (x->left != NULL) {
        return tree_maximum(x->left);
    }
    Node* y = x->parent;
    while (y != NULL && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

// Print suggestions for a word not found in the dictionary
void print_suggestions(Node* lastVisited) {
    printf("Suggestions:\n");

    if (lastVisited != NULL) {
        printf("1) Closest node visited: %s\n", lastVisited->word);

        Node* succ = tree_successor(lastVisited);
        if (succ != NULL)
            printf("2) Successor: %s\n", succ->word);
        else
            printf("2) Successor: (none)\n");

        Node* pred = tree_predecessor(lastVisited);
        if (pred != NULL)
            printf("3) Predecessor: %s\n", pred->word);
        else
            printf("3) Predecessor: (none)\n");
    } else {
        printf("No suggestions available.\n");
    }
}

int main() {
    Node* root = NULL;
    int word_count = 0;
    
    root = input_dictionary(root, &word_count);
    
    if (root != NULL) {
        printf("Dictionary loaded successfully\n");
        printf(YELLOW "Total words: %d\n" RESET, word_count);
        printf(YELLOW "Tree height: %d\n" RESET, height(root));
    } else {
        printf(RED "Failed to load dictionary\n" RESET);
        return 1;
    }
    
    char sentence[500];
    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = '\0'; // remove trailing newline
    
    char* token = strtok(sentence, " ");
    while (token != NULL) {
        Node* lastVisited = NULL;
        Node* found = search(root, token, &lastVisited);
        if (found != NULL) {
            printf(GREEN "'%s' found in dictionary.\n" RESET, token);
        } else {
            printf(RED "'%s' NOT found in dictionary.\n" RESET, token);
            print_suggestions(lastVisited);
        }
        token = strtok(NULL, " ");
    }
    
    return 0;
}