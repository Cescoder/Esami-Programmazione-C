#include <stdio.h>
#include <string.h>

#define MIN_NQ 5
#define MAX_NQ 50
#define MAX_STUDENTS 1024
#define INPUT_FILE_NAME "examdat.txt"
#define OUTPUT_FILE_NAME "report.txt"


int fget_answer(FILE* input_file, int* nq, char* corr_answer, int* id_students, char answers[MAX_STUDENTS][MAX_NQ], int* n_students){
    //Lettura del numero di domande
    if(!fscanf(input_file, "%d", nq)){
        printf("\nErrore formato file: [errore nella lettura del numero di domande]");
        return -1;
    }

    if(*nq < MIN_NQ){
        printf("\nErrore formato file: [il numero di domande è inferiore al minimo: %d]", MIN_NQ);
        return -1;
    }

    if(*nq > MAX_NQ){
        printf("\nErrore formato file: [il numero di domande è superiore al massimo: %d]", MAX_NQ);
        return -1;
    }

    //Acquisizione delle domande corrette
    if(!fscanf(input_file, "%s", corr_answer)){
        printf("\nErrore formato file: [errore nella lettura delle risposte corrette]");
        return -1;
    }

    if(strlen(corr_answer) != *nq){
         printf("\nErrore formato file: [il numero di risposte corrette non corrisponde al numero di domande]");
        return -1;
    }

    *n_students = 0;
    while(!feof(input_file) && *n_students < MAX_STUDENTS){
        if(fscanf(input_file, "%d %s", &id_students[*n_students], &answers[*n_students]) != 2){
            printf("\nErrore formato file: [errore nella lettura della matricola e delle sue risposte][%d]", *n_students);
            return -1;
        }

        if(strlen(answers[*n_students]) != *nq){
            printf("\nErrore formato file: [le risposte della matricola non sono quante le domande][%d]", *n_students);
            return -1;
        }

        (*n_students)++;
    }
    return 1;
}

void get_wrong(int nq, int n_students, int* wrong, char* corr_answer, char answers[MAX_STUDENTS][MAX_NQ]){
    int conteggio_errori[nq];

    for(int i = 0; i< nq; i++){
        conteggio_errori[i] = 0;
    }
    
    for(int i = 0; i < n_students; i++){
        for(int j = 0; j < nq; j++){
            if(answers[i][j] != corr_answer[j]){
                conteggio_errori[j]++;
            }
        }
    }

    double percentuale;
    for(int i = 0; i<nq; i++){
        percentuale = (double)conteggio_errori[i]/n_students*100;
        wrong[i] = percentuale;
    }
}

void fwrite_report(FILE* output_file, char* corr_answer, int* wrong, int nq){
    fprintf(output_file, "Exam Report\n");
    fprintf(output_file, "Question\t");

    for(int i = 0; i <nq; i++){
        fprintf(output_file, "%d\t", i+1);
    }

    fprintf(output_file, "\nAnswer\t\t");

    for(int i = 0; i <nq; i++){
        fprintf(output_file, "%c\t", corr_answer[i]);
    }

    fprintf(output_file, "\nWrong\t\t");

    for(int i = 0; i <nq; i++){
        fprintf(output_file, "%d\t", wrong[i]);
    }
}

int main(){
    //Apertura file di input
    FILE* input_file = fopen(INPUT_FILE_NAME, "r");

    if(input_file == NULL){
        printf("Errore nell'apertura del file di input...");
        return -1;
    }

    //Variabili
    int nq;
    int n_students;
    char corr_answer[MAX_NQ];
    int id_students[MAX_STUDENTS];
    char answers[MAX_STUDENTS][MAX_NQ];

    //Funzione esercizio2
    if(!fget_answer(input_file, &nq, corr_answer, id_students, answers, &n_students)){
        printf("\nErrore nel caricamento dati...");
        return 1;
    }

    //Chiusura file di input
    fclose(input_file);

    //Funzione esercizio 3
    int wrong[MAX_NQ];
    get_wrong(nq, n_students, wrong, corr_answer, answers);

    //Apertura file in scrittura
    FILE* output_file = fopen(OUTPUT_FILE_NAME, "w");

    if(output_file == NULL){
        printf("Errore nell'apertura del file di output...");
        return -1;
    }

    //Esercizio 4
    fwrite_report(output_file, corr_answer, wrong, nq);

    //Chiusura file di output
    fclose(output_file);

    //Fine programma*/
    return 0;
}

