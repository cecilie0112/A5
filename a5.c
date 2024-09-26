#include <stdio.h>  
#include <stdlib.h> 

typedef struct tnode
{
  int value[2];
  struct tnode * left;
  struct tnode * right;
  int height; //Keep track of the height of the tree to make it balanced
} TreeNode;

typedef struct trnode
{
  TreeNode * root;
} Tree;
//For this program, I'm creating an AVL tree instead of a regular binary tree to keep it balanced and reduce the time complexity to O(n)

Tree * buildTree(int, int, Tree *);
TreeNode * builderHelp (int, int, TreeNode *);
TreeNode * newNode(int, int);
void delTree(TreeNode *);
void findCount(TreeNode *, int, int, int, int *, int, int);

int findMax(int, int);
int getNodeHeight(TreeNode *);
int findBalanceFactor(TreeNode *);
TreeNode * leftRotation (TreeNode *);
TreeNode * rightRotation(TreeNode *);

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

int findMax(int x, int y) {
    if (x > y) {return x;}
    else {return y;}
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

    else if (node -> value[0] > xPoint) {
        node -> left = builderHelp(xPoint, yPoint, node -> left);
    }
    else if (node -> value[0] < xPoint) {
        node -> right = builderHelp(xPoint, yPoint, node -> right);
    }
    else {
        if (node -> value[1] > yPoint) {
            node -> left = builderHelp(xPoint, yPoint, node -> left);
        }
        else {
            node -> right = builderHelp(xPoint, yPoint, node -> right);
        }
    }

    //Finding the max height of the left and right sub tree. Adding 1 to account for the root. 
    node -> height = 1 + findMax(getNodeHeight(node -> left), getNodeHeight(node -> right)); 
    int balanceFactor = findBalanceFactor(node); //Finding the balance factor

    //Left rotation 
    if ((balanceFactor <= -2) && (xPoint > node -> right -> value[0])) {
        return (leftRotation(node));
    }
    //Right rotation
    if ((balanceFactor >= 2) && (xPoint < node -> left -> value[0])) {
        return (rightRotation(node));
    }
    //First left rotation --> then right rotation
    if ((balanceFactor >= 2) && (xPoint > node -> left -> value[0])) {
        node -> left = leftRotation(node -> left);
        return (rightRotation(node));
    }
    //First right rotation --> then left rotation
    if ((balanceFactor <= -2) && (xPoint < node -> right -> value[0])) {
        node -> right = rightRotation(node -> right);
        return (leftRotation(node));
    }

    return (node);
}

TreeNode * leftRotation (TreeNode * node) {
    TreeNode * newRoot = node -> right;
    TreeNode * tempLeft = newRoot -> left;

    newRoot -> left = node;
    node -> right = tempLeft;

    node -> height = findMax(getNodeHeight(node -> left), getNodeHeight(node -> right)) + 1;
    newRoot -> height = findMax(getNodeHeight(newRoot -> left), getNodeHeight(newRoot -> right)) + 1; 

    return newRoot;
}

TreeNode * rightRotation(TreeNode * node) {
    TreeNode * newRoot = node -> left;
    TreeNode * tempRight = newRoot -> right;

    newRoot -> right = node;
    node -> left = tempRight;

    node -> height = findMax(getNodeHeight(node -> left), getNodeHeight(node -> right)) + 1;
    newRoot -> height = findMax(getNodeHeight(newRoot -> left), getNodeHeight(newRoot -> right)) + 1; 

    return newRoot;
}

int findBalanceFactor(TreeNode * node) {
    if (node == NULL) {
        return 0;
    }
    else {
        return (getNodeHeight(node -> left) - getNodeHeight(node -> right));
    }
}

int getNodeHeight(TreeNode * node) {
    if (node == NULL) {
        return 0;
    }
    return (node -> height);
}

TreeNode * newNode(int xPoint, int yPoint) {
    TreeNode * node = malloc(sizeof(TreeNode));

    node -> value[0] = xPoint;
    node -> value[1] = yPoint;

    node -> left = NULL;
    node -> right = NULL;
    node -> height = 1; //Initializing the height of the node to be 1 for the calculation of the balacing factor later
    return node;
}