#include <stdio.h>
#include <string.h>

#define FILE_NAME "input.txt"
#define CITY_NAME_LENGTH 4  // Corrected the typo "LENGHT"
#define MAX_FLIGHTS 200

typedef struct {
    char partenza[CITY_NAME_LENGTH];
    char arrivo[CITY_NAME_LENGTH];
} Volo;

int load_data(FILE* file, Volo voli[], int* n_voli) {
    *n_voli = 0;
    while (*n_voli < MAX_FLIGHTS && fscanf(file, "%s %s", voli[*n_voli].partenza, voli[*n_voli].arrivo) == 2) 
        (*n_voli)++;
    

    if (*n_voli == MAX_FLIGHTS) 
        return 1; 
    

    return 0;
}

void tratte_andata_ritorno(Volo voli[], Volo tratte[], int n_voli, int* n_tratte) {
    int checks[MAX_FLIGHTS];
    *n_tratte = 0;

    for (int i = 0; i < n_voli; i++) 
        checks[i] = 0;
    
    for (int i = 0; i < n_voli; i++) 
        for (int j = 0; j < n_voli; j++) 
            if (i != j && checks[i] != 1 && checks[j] != 1) 
                if (strcmp(voli[i].partenza, voli[j].arrivo) == 0 && strcmp(voli[j].partenza, voli[i].arrivo) == 0) {
                    checks[i] = 1;
                    checks[j] = 1;
                    strcpy(tratte[*n_tratte].partenza, voli[i].partenza);
                    strcpy(tratte[*n_tratte].arrivo, voli[i].arrivo);
                    (*n_tratte)++;
                }
}

void visualizza_tratte(Volo tratte[], int n_tratte) {
    printf("Numero di tratte di andata e ritorno: %d\n", n_tratte);

    for (int i = 0; i < n_tratte; i++) 
        printf("%s %s\n", tratte[i].partenza, tratte[i].arrivo);
    
}

int main() {
    // Apertura file txt
    FILE* file = fopen(FILE_NAME, "r");

    if (file == NULL) {
        printf("Errore nell'apertura del file\n");
        return 1;
    }

    // Creazione array struct
    Volo voli[MAX_FLIGHTS];
    int n_voli;

    // Caricamento dei dati
    if (load_data(file, voli, &n_voli))
        printf("Sono presenti più di 200 voli\n");
    else
        printf("Sono presenti %d voli\n\n", n_voli);

    // Tratte andata ritorno
    Volo tratte[MAX_FLIGHTS];
    int n_tratte;
    tratte_andata_ritorno(voli, tratte, n_voli, &n_tratte);

    // Visualizzazione tratte di andata e ritorno
    visualizza_tratte(tratte, n_tratte);

    // Chiusura del file
    fclose(file);

    return 0;
}
