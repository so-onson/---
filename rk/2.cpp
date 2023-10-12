#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <ctime>

int main()
{
    
    int N , i, j, max = -101;
    srand(time(NULL));
    printf("Введите количество элементов: ");
    scanf("%d",&N);
    unsigned int start_time = clock();
    int** a = (int**)malloc(sizeof(int*) * N);
    for(i = 0; i < N; i++)
        a[i] = (int*)malloc(sizeof(int*) * N);
    for (i = 0; i<N; i++){
        for (j = 0; j<N; j++){
            a[i][j] = - 100 + rand()%(100 + 100 + 1);
        }
    }
    printf("Исходный массив: \n");
    for (i = 0; i<N; i++){
        for (j = 0; j<N; j++){
            printf("%6d   ", a[i][j]);
        }
        printf("\n");
    }
     for (i = 0; i<N; i++){
        for (j = 0; j<N; j++){
            if (a[j][i]>max) max = a[j][i];
        }
        printf("В столбце %d максимум равен %d\n",i+1, max);
        max = -101;
    }
        unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    printf("%d", search_time);
    return 0;
}
