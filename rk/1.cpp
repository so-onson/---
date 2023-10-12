
#include <stdio.h>
#include <stdlib.h>
// #include <time.h>
#include <ctime>

void fill(int** mas, int row, int col){
    int i,j;
        for (i = 0; i < row; ++i) {
        // mas[i]
        for (j = 0; j < col; ++j) {
            mas[i][j] = rand() % 201 - 100;
        }
    }
}

int main() {
    int i, j, max = -101;
    srand(time(NULL));
    int nrow, ncol;
    printf("Enter number of rows: ");
    scanf("%d", &nrow);
    printf("Enter number of columns: ");
    scanf("%d", &ncol);
    // unsigned int start_time = clock();
    srand(time(0));
    int *b = (int *) malloc(sizeof(int) * nrow * ncol);
    // int **b = (int **) malloc(sizeof(int *) * nrow);
    // Initialize array with random values
fill(b, nrow, ncol);
    // Print initial array
    printf("Initial array:\n");
    for (i = 0; i < nrow; ++i) {
        for (j = 0; j < ncol; ++j) {
            printf("%6d   ", b[i][j]);
        }
        printf("\n");
    }
    // Find maximum value in each column
    for (i = 0; i < ncol; ++i) {
        for (j = 0; j < nrow; ++j) {
            if (b[j][i] > max) {
                max = b[j][i];
            }
        }
        printf("Max value in column %d is %d\n", i + 1, max);
        max = -101;
    }
    // Free allocated memory
    // free(a);
    free(b);
    // unsigned int end_time = clock();
    // unsigned int search_time = end_time - start_time;
    // printf("%d", search_time);
     printf("%f", clock()/1000.0);
    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <time.h>

// int main() {
//     int i, j, ncol, max = -101;
//     unsigned int seed = (unsigned int) time(NULL);
//     printf("Enter number of columns: ");
//     scanf("%d", &ncol);
//     // unsigned int start_time = clock();
//     srand(time(0));
//     int *a = (int *) malloc(sizeof(int) * ncol * ncol);
//     for (i = 0; i < ncol; ++i) {
//         for (j = 0; j < ncol; ++j) {
//             a[i * ncol + j] = -100 + rand_r(&seed) % 201;
//         }
//     }
//     printf("Initial array:\n");
//     for (i = 0; i < ncol; ++i) {
//         for (j = 0; j < ncol; ++j) {
//             printf("%6d   ", a[i * ncol + j]);
//         }
//         printf("\n");
//     }
//     for (i = 0; i < ncol; ++i) {
//         for (j = 0; j < ncol; ++j) {
//             if (a[j * ncol + i] > max) {
//                 max = a[j * ncol + i];
//             }
//         }
//         printf("Max value in column %d is %d\n", i + 1, max);
//         max = -101;
//     }
//     free(a);
//         // unsigned int end_time = clock();
//     // unsigned int search_time = end_time - start_time;
//     printf("%f", clock()/1000.0);
//     return 0;
// }