//Librerie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Costanti
#define TLEN 50
#define PLEN 4
#define MAX_STR 100
#define FILE_NAME "input.txt"
#define PATTERN "ABCD"

//Struttura statistica
typedef struct{
    char testo[TLEN];
    int freq[PLEN];
    int occur;
}Statistica;

//Funzione per leggere la sequenza
int leggi_seq(FILE* file, char* pattern, char* testo, int* lenght, int matrix[PLEN][TLEN]){
    //Leggo la stringa
    if(!fscanf(file, "%s", testo))
        return 0;
    

    *lenght = strlen(testo);
    int pattern_lenght = strlen(pattern);

    //Riempio la matrice
    for(int i = 0; i <*lenght; i++){
        for(int j = 0; j<pattern_lenght;j++){
            if(testo[i] == pattern[j])
                matrix[j][i] = 1;
            else
                matrix[j][i] = 0;
        }
    }

    return 1;
}

//Funzione per calcolare le statistiche
void calcola_stat(int matrix[PLEN][TLEN], int lenght, Statistica* statistica){

    //Inizializzo la frequenza
    for(int i = 0; i<PLEN; i++)
        statistica->freq[i] = 0;
    
    //Conteggio delle occorrenze
    for(int i = 0; i<PLEN; i++)
        for(int j = 0; j<lenght; j++)
            if(matrix[i][j] == 1)
                statistica->freq[i]++;

    //Controllo se tutte le lettere sono presenti    
    statistica->occur = 1;
    for(int i = 0; i<PLEN; i++){
        if(statistica->freq[i] == 0){
            statistica->occur = 0;
            return;
        }
    }
        

}

//Funzione per stampare le statistiche
void stampa_stat(Statistica statistica, char* pattern){
    printf("\nStatistiche per la sequenza: %s\n", statistica.testo);

    for(int i = 0; i < PLEN; i++){
        printf("la frequenza di %c e': %d\n", pattern[i], statistica.freq[i]);
    }
}

int main(){
    //Apro il file
    FILE* file = fopen(FILE_NAME, "r");

    if(file == NULL){
        printf("Errore nell'apertura del file\n");
        return -1;
    }

    //Leggo il numero di stringhe
    int n;
    if(!fscanf(file, "%d", &n)){
        printf("Errore nel formato file\n");
        return -1;
    }

    if(n < 1){
        printf("Numero negativo\n");
        return -1;
    }

    if(n > MAX_STR) n = MAX_STR;

    
    char pattern[] = "ABCD";
    Statistica statistiche[MAX_STR];
    int lenght;
    int matrix[PLEN][TLEN];

    //Gestione delle statistiche
    for(int i = 0; i<n; i++){
        if(!leggi_seq(file, pattern, statistiche[i].testo, &lenght, matrix)){
            printf("Errore nella lettura della stringa [%d]...", i);
            return -1;
        }

        calcola_stat(matrix, lenght, &statistiche[i]);
        stampa_stat(statistiche[i], pattern);
    }

    fclose(file);
    return 0;
}