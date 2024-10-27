#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FILE_NAME "punti.txt"
#define N 10
#define lower_a 97
#define lower_z 122
#define max_name_size 20

typedef struct {
    float x;
    float y;
    float z;
    char nome[max_name_size];
} Point3D;

// Funzione per la stampa della matrice
void stampa(float **distances, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%.6f", distances[i][j]);
            if (j != size - 1) printf("; ");
        }
        printf("\n");
    }
}

// Funzione per il calcolo delle distanze
void calcola_distanze(Point3D *points, int size, char c, float **matrix, int *param) {
    *param = 0;
    Point3D selected[N];
    
    for (int i = 0; i < size; i++) {
        if (strchr(points[i].nome, c) != NULL) {
            selected[*param] = points[i];
            (*param)++;
        }
    }

    for (int i = 0; i < *param; i++) {
        for (int j = 0; j < *param; j++) {
            if (i == j) {
                matrix[i][j] = 0.0;
            } else {
                float dx = selected[i].x - selected[j].x;
                float dy = selected[i].y - selected[j].y;
                float dz = selected[i].z - selected[j].z;
                matrix[i][j] = sqrt(dx * dx + dy * dy + dz * dz);
            }
        }
    }
}

// Funzione per il caricamento dati dal file
int carica_dati(FILE *file, Point3D *points, int n) {
    if (file == NULL)
        return -1;

    int count = 0;
    while (count < n && fscanf(file, "%f %f %f %s", &points[count].x, &points[count].y, &points[count].z, points[count].nome) == 4) {
        count++;
    }

    return count;
}

// Funzione Main
int main() {
    Point3D points[N];
    FILE *file = fopen(FILE_NAME, "r");

    // Caricamento dei dati
    int n_records = carica_dati(file, points, N);
    if (n_records == -1) {
        printf("Errore nel caricamento dati ...\n");
        return 1;
    }
    fclose(file);
    printf("Numero di punti caricati: %d\n", n_records);

    for (int i = 0; i < n_records; i++) {
        printf("X: %.2f\tY: %.2f\tZ: %.2f\tNome: %s\n", points[i].x, points[i].y, points[i].z, points[i].nome);
    }

    // Allocazione della memoria per la matrice
    float **matrix = malloc(N * sizeof(float *));
    for (int i = 0; i < N; i++) {
        matrix[i] = malloc(N * sizeof(float));
    }

    // Input della lettera e verifica
    char c;
    do {
        printf("Inserisci una lettera (a-z): ");
        scanf(" %c", &c);
    } while (!(c >= lower_a && c <= lower_z));

    // Calcolo delle distanze e matrice quadrata
    int param;
    calcola_distanze(points, n_records, c, matrix, &param);

    // Stampa della matrice delle distanze
    if (param > 0) {
        printf("\nMatrice delle distanze:\n");
        stampa(matrix, param);
    } else {
        printf("Nessun punto trovato con il carattere '%c' nel nome.\n", c);
    }

    // Deallocazione della matrice
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
