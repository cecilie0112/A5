#include <stdio.h>  
#include <stdlib.h> 
#include <math.h>

#define COL 2
#define ROW 100

int readFile(char * pointFile, int(**)[COL], int, int *);
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

    int inputFlag, xCent, yCent, radius;
    int col = 0;
    int count;
    int flag = 0;
    do{
      count = 0;
      inputFlag = scanf("%d %d %d", &xCent, &yCent, &radius);
      int rowIndx = readFile(argv[1], &pointArray, radius, &flag);
      if (!flag) {
        printf("No points in the given circle!\n");
        free(pointArray);
        return EXIT_FAILURE;
      }

    //   for (int i = 0; i < 8; i++) {
    //     for (int j = 0; j < 2; j++) {
    //         printf("%d ", pointArray[i][j]);
    //     }
    //     printf("\n");
    //   }
      
      int radiusSquared = radius * radius;
      for (int row = 0; row < rowIndx; row++) {
        if (calculateCirc(pointArray[row][col], pointArray[row][col + 1], xCent, yCent, radiusSquared)) {
          count++;
        }
      }
      
      if (inputFlag != EOF) {
        printf("%d\n", count);
      }

    }while (inputFlag != EOF);


    free(pointArray);

    return EXIT_SUCCESS;
} 


int readFile(char * pointFile, int(**pointArray)[COL], int radius, int * flag) {
  FILE * fptr = fopen(pointFile, "r");
  if (fptr == NULL) {
    printf("Unable to open file");
    return EXIT_FAILURE;
  }
  int currentIndx = 0;
  int currentSize = ROW;
  int xPoint, yPoint;
  
  while ((fscanf(fptr, "%d", &xPoint) != EOF) && fscanf(fptr, "%d", &yPoint) != EOF) {
    if (currentIndx >= currentSize) {
        int (*tempArray)[COL] = realloc(*pointArray, (currentIndx * 2) * sizeof(**pointArray));
        if (tempArray == NULL) {
            printf("Memory allocation failed.");
            return EXIT_FAILURE;
        } else {
          *pointArray = tempArray;
          currentSize = currentIndx * 2;
        }
    }

    if (abs(xPoint) <= radius && abs(yPoint) <= radius){
        *flag = 1;
        (*pointArray)[currentIndx][0] = xPoint;
        (*pointArray)[currentIndx][1] = yPoint;
        ++currentIndx;
    }
  }

  fclose(fptr);
  return (currentIndx);
}

int calculateCirc(int xPoint, int yPoint, int xCent, int yCent, int radiusSquared) {
    int xDistance = xPoint - xCent;
    int yDistance = yPoint - yCent; 

    return ((xDistance * xDistance) + (yDistance * yDistance) <= radiusSquared);
}