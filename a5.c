#include <stdio.h>  
#include <stdlib.h> 
#include <math.h>
#define INPUTMAX 100

void readFile(char * pointFile, int * xPoint, int * yPoint);
int calculateCirc(int, int, int, int, int);

int main(int argc, char * * argv)
    //argv[0]: ./a5
    //argv[1]: points.txt
{
    if (argc != 2) {
        printf("Incorrect number of arguments.\n");
        return EXIT_FAILURE;
    }

    int inputFlag; 

    do {
      int numCircPoint = 0;
      FILE * fptr = fopen(argv[1], "r");

      int xCent, yCent, radius, xPoint, yPoint;
      inputFlag = scanf("%d %d %d", &xCent, &yCent, &radius); 
    //   printf("x: %d, y: %d, radius: %d\n", xCent, yCent, radius);

      while ((fscanf(fptr, "%d", &xPoint) != EOF) && fscanf(fptr, "%d", &yPoint) != EOF) {
        // printf("x-coord: %d, y-coord: %d\n", xPoint, yPoint);
        
        if (calculateCirc(xPoint, yPoint, xCent, yCent, radius)) {
          numCircPoint++;
        }
      }
      printf("%d\n", numCircPoint);
      fclose(fptr);
    }while (inputFlag != EOF); //Checking if an EOF has been read

    return EXIT_SUCCESS;
} 

int calculateCirc(int xPoint, int yPoint, int xCent, int yCent, int radius) {
    if ((pow(xPoint - xCent, 2) + pow(yPoint - yCent, 2)) <= pow(radius, 2)) {
        return 1;
    }
    else {
        return 0;
    }
}

void readFile(char * pointFile, int * xPoint, int * yPoint) {
  FILE * fptr = fopen(pointFile, "r");
  if (fptr == NULL) {
    printf("Unable to open file");
    return;
  }
  
//   char sceneArray[INPUTMAX];
//   char * temp;

  fscanf(fptr, "%d", xPoint);
  fscanf(fptr, "%d", yPoint);

//   if (fgets(sceneArray, INPUTMAX, fptr) != NULL) {
//     strtol(sceneArray, &temp, 10);
//   }

  fclose(fptr);
}