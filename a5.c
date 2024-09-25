#include <stdio.h>  
#include <stdlib.h> 
#include <math.h>

#define INPUTMAX 100
#define COL 2
#define ROW 100

void readFile(char * pointFile, int(**)[COL]);
int calculateCirc(int, int, int, int, int);

int main(int argc, char * * argv)
    //argv[0]: ./a5
    //argv[1]: points.txt
{
    if (argc != 2) {
        printf("Incorrect number of arguments.\n");
        return EXIT_FAILURE;
    }

    // int inputFlag; 
    int (*pointArray)[COL];
    pointArray = malloc(sizeof(*pointArray) * ROW);
    readFile(argv[1], &pointArray);

    // int xCent, yCent, radius;
    // int inputFlag = scanf("%d %d %d", &xCent, &yCent, &radius);

    // // while (inputFlag != EOF) {
    // //     printf("Hello");
    // //     inputFlag = scanf("%d %d %d", &xCent, &yCent, &radius);
    // // }

    free(pointArray);

    return EXIT_SUCCESS;
} 


void readFile(char * pointFile, int(**pointArray)[COL]) {
  FILE * fptr = fopen(pointFile, "r");
  if (fptr == NULL) {
    printf("Unable to open file");
    return;
  }
  int currentIndx = 0;
  int currentSize = ROW;
  int xPoint, yPoint;
  
  while ((fscanf(fptr, "%d", &xPoint) != EOF) && fscanf(fptr, "%d", &yPoint) != EOF) {
    if (currentIndx >= currentSize) {
        int (*tempArray)[COL] = realloc(*pointArray, (currentIndx * 2) * sizeof(**pointArray));
        if (tempArray == NULL) {
            printf("Memory allocation failed.");
            return;
        } else {
          *pointArray = tempArray;
          currentSize = currentIndx * 2;
        }
    }
    (*pointArray)[currentIndx][0] = xPoint;
    (*pointArray)[currentIndx][1] = yPoint;
    ++currentIndx;
  }

  fclose(fptr);
}

int calculateCirc(int xPoint, int yPoint, int xCent, int yCent, int radius) {
    if ((pow(xPoint - xCent, 2) + pow(yPoint - yCent, 2)) <= pow(radius, 2)) {
        return 1;
    }
    else {
        return 0;
    }
}