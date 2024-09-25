#include <stdio.h>  
#include <stdlib.h> 

typedef struct tnode
{
  int value[2];
  struct tnode * left;
  struct tnode * right;
} TreeNode;

typedef struct trnode
{
  TreeNode * root;
} Tree;

Tree * buildTree(int, int, Tree *);
TreeNode * builderHelp (int, int, TreeNode *);
TreeNode * newNode(int, int);
void delTree(TreeNode * node);

int main(int argc, char * * argv)
    //argv[0]: ./a5
    //argv[1]: points.txt
{
    if (argc != 2) {
        printf("Incorrect number of arguments.\n");
        return EXIT_FAILURE;
    }

    FILE * fptr = fopen(argv[1], "r");
        if (fptr == NULL) {
        printf("Unable to open file");
        return EXIT_FAILURE;
    }
    
    int xPoint, yPoint;
    Tree * binaryTree = malloc(sizeof(Tree));
    binaryTree -> root = NULL;

    while ((fscanf(fptr, "%d", &xPoint) != EOF) && fscanf(fptr, "%d", &yPoint) != EOF) {
        binaryTree = buildTree(xPoint, yPoint, binaryTree);
    }
    fclose(fptr);

    TreeNode * treeRoot = binaryTree -> root;
    printf("%d \n", treeRoot -> right -> right -> left -> value[0]);

    // int inputFlag, xCent, yCent, radius;
    // int count;
    // do{
    //   count = 0;
    //   inputFlag = scanf("%d %d %d", &xCent, &yCent, &radius);
      
      
    //   if (inputFlag != EOF) {
    //     printf("%d\n", count);
    //   }

    // }while (inputFlag != EOF);

    delTree(treeRoot);
    free(binaryTree);
    return EXIT_SUCCESS;
} 

void delTree(TreeNode * node) {
    if (node == NULL) {
        return;
    }
    delTree(node -> left);
    delTree(node -> right);
    free(node);
}

Tree * buildTree(int xPoint, int yPoint, Tree * binaryTree) {
    binaryTree -> root = builderHelp(xPoint, yPoint, binaryTree -> root);
    return binaryTree;
}

TreeNode * builderHelp (int xPoint, int yPoint, TreeNode * node) {

    if (node == NULL) {
      return (newNode(xPoint, yPoint));
    }

    else if (node -> value[0] >= xPoint) {
        node -> left = builderHelp(xPoint, yPoint, node -> left);
    }

    else if (node -> value[0] < xPoint) {
        node -> right = builderHelp(xPoint, yPoint, node -> right);;
    }

    return (node);
}

TreeNode * newNode(int xPoint, int yPoint) {
    TreeNode * node = malloc(sizeof(TreeNode));

    node -> value[0] = xPoint;
    node -> value[1] = yPoint;

    node -> left = NULL;
    node -> right = NULL;
    return node;
}