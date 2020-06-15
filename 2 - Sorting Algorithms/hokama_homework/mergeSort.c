/*
   Rodrigo Duarte Silva Luz - 2019003520
   Yasmin Karolyne Aniceto- 2018010440
   Matheus de Souza - 2019005909
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

//Definição do struct
typedef struct champion
{
    char *name;
    int tier;
} champion;

//Protótipos
void mergeSort(champion *C, int esq, int dir);

int min(int x, int y);

void mergeTier(champion *C, int esq, int mid, int dir);

void mergeChampionName(char meAjuda[], int esq, int mid, int dir);

void separateTiers(champion *C, int dir);

int main()
{
    //Número de linhas
    int n = 0;
    scanf("%d", &n);

    //Alocando espaço na memória para o struct champion
    champion *C = (champion *)calloc(n, sizeof(champion));

    //Pegar dados do usuário (um nome sem espaços e um inteiro)
    for (int i = 0; i < n; i++)
    {
        //Aloca espaço na memória para cada nome
        C[i].name = (char *)calloc(50, sizeof(char));
        scanf("%s %d", C[i].name, &(C[i].tier));
    }

    //Chamada da função para ordenar os números em estratos e os nomes entre eles em ordem alfabética
    mergeSort(C, 0, n - 1);

    // int tier_cont = C[0].tier, comeco = 0;

    // for (int i = 0; i <= n; i++)
    // {
    //     //procura posição em que muda o tier
    //     if (C[i].tier != tier_cont)
    //     {
    //         /* Devido ao tier trocar, encontra-se a posição final do tier atribuido ao tier_cont
    //         captura então o começo e o final do tier na lista
    //         como parametro é passado i-1 e começo, que representam a posição final e inicial do tier */
    //         mergeChampionName(C, 0, n / 2, n);
    //         //start recebe a posição inicial do novo tier
    //         comeco = i;
    //         //tier_cont pega o novo tier
    //         tier_cont = C[i].tier;
    //     }
    // }

    /*  int inicioSubvetor = 0;
    int cont = 0;
    champion subVetor[MAX];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            inicioSubvetor = i;
            if (C[i].tier == C[j].tier)
            {
                subVetor[cont] = C[j];
                cont++;
            }
        }
        mergeChampionName(subVetor, inicioSubvetor, (cont / 2), cont);
        cont = 0;
    } */

    //Imprimindo os valores de saída ordenados
    for (int i = 0; i < n; i++)
    {
        printf("%s %d\n", C[i].name, C[i].tier);
    }

    separateTiers(C, n - 1);

    for (int i = 0; i < n; i++)
    {
        printf("%s %d\n", C[i].name, C[i].tier);
    }
    //Libera espaço alocado na memória

    for (int i = 0; i < n; i++)
    {
        free(C[i].name);
    }

    free(C);

    return 0;
}

// Utility function to find minimum of two integers
int min(int x, int y)
{
    return (x < y) ? x : y;
}

void mergeSort(champion *C, int esq, int dir)
{
    int n = dir;
    int mid = (esq + dir) / 2;
    if (mid <= 8)
    {
        int curr_size;  // For current size of subarrays to be merged
                        // curr_size varies from 1 to n/2
        int left_start; // For picking starting index of left subarray
                        // to be merged

        // Merge subarrays in bottom up manner.  First merge subarrays of
        // size 1 to create sorted subarrays of size 2, then merge subarrays
        // of size 2 to create sorted subarrays of size 4, and so on.
        for (curr_size = 1; curr_size <= n; curr_size = 2 * curr_size)
        {
            // Pick starting point of different subarrays of current size
            for (left_start = 0; left_start < n; left_start += 2 * curr_size)
            {
                // Find ending point of left subarray. mid+1 is starting
                // point of right
                int mid = min(left_start + curr_size - 1, n);

                int right_end = min(left_start + 2 * curr_size - 1, n);

                // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
                mergeTier(C, left_start, mid, right_end);
                //mergeChampionName(C, left_start, mid, right_end);
            }
        }
    }
    else
    {
        if (esq < dir)
        {
            mergeSort(C, esq, mid);
            mergeSort(C, mid + 1, dir);
            mergeTier(C, esq, mid, dir);
            //mergeChampionName(C, esq, mid, dir);
        }
    }
}

void mergeTier(champion *C, int esq, int mid, int dir)
{
    int aux[MAX];
    int i = esq, j = mid + 1, k = 0;

    while (i <= mid && j <= dir)
        if (C[i].tier <= C[j].tier)
        {
            aux[k++] = C[i++].tier;
        }
        else
        {
            aux[k++] = C[j++].tier;
        }

    while (i <= mid)
        aux[k++] = C[i++].tier;
    while (j <= dir)
        aux[k++] = C[j++].tier;

    for (i = esq, k = 0; i <= dir; i++, k++)
        C[i].tier = aux[k];
}

void mergeChampionName(char meAjuda[], int esq, int mid, int dir)
{
    int nL = mid - esq + 1;
    int nR = dir - mid;

    //char **L = malloc(sizeof(char *) * nL);
    //char **R = malloc(sizeof(char *) * nR);
    char L[MAX];
    char R[MAX];
    int i;
    for (i = 0; i < nL; i++)
    {
        //L[i] = malloc(sizeof(meAjuda[esq + i]));
        strcpy(L[i], meAjuda[esq + i]);
    }
    for (i = 0; i < nR; i++)
    {

        //R[i] = malloc(sizeof(C[mid + i + 1]));
        strcpy(R[i], meAjuda[mid + i + 1]);
    }
    int j = 0, k;
    i = 0;
    k = esq;
    while (i < nL && j < nR)
    {
        if (strcmp(L[i], R[j]) < 0)
            strcpy(meAjuda[k++], L[i++]);

        else
            strcpy(meAjuda[k++], R[j++]);
    }

    while (i < nL)
        strcpy(meAjuda[k++], L[i++]);
    while (j < nR)
        strcpy(meAjuda[k++], R[j++]);
}

void separateTiers(champion *C, int dir)
{
    int help[MAX];
    char socorro[MAX];
    for (int k = 0; k <= dir; k++)
    {
        help[k] = C[k].tier;
        printf("%d\n", help[k]);
    }

    int ajuda = C[0].tier;

    int left = 0, right = 0, meio = 0;
    for (int i = 0; i <= dir; i++)
    {
        if (ajuda == help[i])
        {
            socorro[i] = help[i];
            printf("A\n");
            right++;
        }
    }
    ajuda = right;
    printf("%d\n", right);

    //printf("%d", ajuda);
    meio = right / 2;
    mergeChampionName(socorro, left, meio, right);
}