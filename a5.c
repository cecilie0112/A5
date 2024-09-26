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
void delTree(TreeNode *);
void findCount(TreeNode *, int, int, int, int *, int, int);

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

    TreeNode * treeRoot = binaryTree -> root;

    int inputFlag, xCent, yCent, radius, xMax, xMin;
    int count;
    do{
      count = 0;
      inputFlag = scanf("%d %d %d", &xCent, &yCent, &radius);

      xMax = xCent + radius;
      xMin = xCent - radius;
      int radiusSquared = radius * radius;
      
      findCount(treeRoot, xCent, yCent, radiusSquared, &count, xMax, xMin);

      if (inputFlag != EOF) {
        printf("%d\n", count);
      }

    }while (inputFlag != EOF);

    delTree(treeRoot);
    free(binaryTree);
    fclose(fptr);
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

void findCount(TreeNode * node, int xCent, int yCent, int radiusSquared, int * count, int xMax, int xMin) {
    if (node == NULL) {
        return;
    }
    
    if ((node -> value[0] >= xMin) && (node -> value[0] <= xMax)) {
        int xDistance = node -> value[0] - xCent;
        int yDistance = node -> value[1] - yCent;

        if ((xDistance * xDistance) + (yDistance * yDistance) <= radiusSquared) {
            (*count)++;
        }

        findCount(node -> left, xCent, yCent, radiusSquared, count, xMax, xMin);
        findCount(node -> right, xCent, yCent, radiusSquared, count, xMax, xMin);
    }

    else if (node -> value[0] < xMin) {
        findCount(node -> right, xCent, yCent, radiusSquared, count, xMax, xMin);
    }

    else if (node -> value[0] > xMax) {
        findCount(node -> left, xCent, yCent, radiusSquared, count, xMax, xMin);
    }
    
    return;
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