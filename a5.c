#include <stdio.h>  
#include <stdlib.h> 
#define INPUTMAX 100

int main(int argc, char * * argv)
    //argv[0]: ./a5
    //argv[1]: text file
{
    if (argc != 2) {
        printf("Incorrect number of arguments.\n");
        return EXIT_FAILURE;
    }

    int inputFlag;

    do {
      int xCent, yCent, radius;
      inputFlag = scanf("%d %d %d", &xCent, &yCent, &radius); 
      printf("x: %d, y: %d, radius: %d\n", xCent, yCent, radius);
    }while (inputFlag != EOF); //Checking if an EOF has been read

} 
