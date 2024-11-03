#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 50
#define FILE_NAME "diz.txt"

typedef struct {
    char testo[MAX_LENGTH];
    int lunghezza;
} Parola;

int carica_dizionario(FILE *file, Parola *dizionario, int *n) {
    *n = 0;
    char buffer[MAX_LENGTH];

    while (fscanf(file, "%s", buffer) != EOF) {
        strcpy(dizionario[*n].testo, buffer);
        dizionario[*n].lunghezza = strlen(buffer);
        (*n)++;  
    }

    return 1;
}

void stampa_dizionario(Parola *dizionario, int n) {
    printf("Dizionario: ");

    int char_count = 0;

    for (int i = 0; i < n; i++) {
        printf("\n%d: %s", i, dizionario[i].testo);
        char_count += dizionario[i].lunghezza;
    }

    printf("\nTotale caratteri: %d", char_count);
}

void componi_frase(Parola *dizionario, int n, Parola *frase, int *m) {
    int num;
    *m = 0;

    do {
        printf("\nInserisci indice: ");
        scanf("%d", &num);

        if (num >= n)
            printf("Indice al di fuori del dizionario...\n");

        else if (num >= 0) {
            frase[*m] = dizionario[num];
            (*m)++; 
        }

    } while (num >= 0 && *m < MAX_LENGTH);
}

Parola* trova_parola_lunga(Parola *frase, int m) {
    int max = 0;

    for (int i = 1; i < m; i++)
        if (frase[i].lunghezza > frase[max].lunghezza)
            max = i;

    return &frase[max];
}

int main() {
    FILE *file = fopen(FILE_NAME, "r");

    if (file == NULL) {
        printf("Errore nell'apertura del file.\n");
        return -1;
    }

    int n;
    int m;
    Parola dizionario[MAX_LENGTH];
    Parola frase[MAX_LENGTH];

    printf("DEBUG 1\n");

    if (!carica_dizionario(file, dizionario, &n)) {
        printf("Errore nel caricamento del dizionario.\n");
        return -1;
    }

    fclose(file);

    stampa_dizionario(dizionario, n);

    componi_frase(dizionario, n, frase, &m);

    printf("\nFrase composta: ");

    for (int i = 0; i < m; i++)
        printf("%s ", frase[i].testo);


    Parola *parola_lunga = trova_parola_lunga(frase, m);
    printf("\nParola più lunga: %s", parola_lunga->testo);

    return 0;
}
