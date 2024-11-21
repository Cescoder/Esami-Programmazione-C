#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Definizione costanti
#define FILE_NAME   "tavola_elementi.txt"
#define LEN         100
#define BUFF_NAME   20
#define BUFF_ABB    5
#define MAX_ELEM    118

// Struttura degli elementi
typedef struct {
    int num_atom;
    char name[BUFF_NAME];
    char abbrev[BUFF_ABB];
    float mass_atom;
} Elem;

// Funzione per caricare gli elementi dal file
int load_elem(FILE* file, Elem* elementi, int* n) {
    *n = 0;
    while (*n < MAX_ELEM) {
        if (fscanf(file, "%d %19s %4s %f\n", 
                   &elementi[*n].num_atom, 
                   elementi[*n].name, 
                   elementi[*n].abbrev, 
                   &elementi[*n].mass_atom) != 4) {
            if (feof(file)) break; // Fine file raggiunta
            return -1; // Errore di formato
        }
        (*n)++;
    }
    return 0;
}

// Stampa della tavola periodica
void print_table(Elem* elementi, int n) {
    printf("Tavola degli elementi:\n\n");
    printf("%-15s %-20s %-15s %-10s\n", 
           "Numero Atomico", "Nome", "Abbreviazione", "Peso Atomico");
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-15d %-20s %-15s %-10.4f\n", 
               elementi[i].num_atom, 
               elementi[i].name, 
               elementi[i].abbrev, 
               elementi[i].mass_atom);
    }
}

// Funzione per cercare un elemento nella tavola periodica
float scan_table(char* element, Elem* elements, int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(elements[i].abbrev, element) == 0) {
            return elements[i].mass_atom;
        }
    }
    return -1;
}

// Validazione dell'input del composto
int validate_input(const char* composto) {
    for (int i = 0; i < strlen(composto); i++) {
        if (!isupper(composto[i]) && !islower(composto[i]) && !isdigit(composto[i])) {
            return 0; // Input non valido
        }
    }
    return 1; // Input valido
}

// Funzione per calcolare il peso di un composto
float scan_request(char* composto, Elem* elements, int n) {
    float sum_peso = 0;

    for (int i = 0; i < strlen(composto); i++) {
        if (isupper(composto[i])) {
            char element[4] = {0};
            int num = 0;

            element[0] = composto[i];

            // Legge il simbolo chimico completo
            if (i + 1 < strlen(composto) && islower(composto[i + 1])) {
                element[1] = composto[i + 1];
                i++;
            }

            // Legge il numero successivo (se presente)
            while (i + 1 < strlen(composto) && isdigit(composto[i + 1])) {
                num = num * 10 + (composto[i + 1] - '0');
                i++;
            }

            if (num == 0) num = 1; // Default a 1 se non specificato

            // Trova il peso atomico dell'elemento
            float peso = scan_table(element, elements, n);
            if (peso == -1) {
                printf("Errore: elemento '%s' non trovato nella tavola periodica...\n", element);
                return -1;
            }

            sum_peso += peso * num;
        }
    }

    return sum_peso;
}

int main() {
    // Apertura file
    FILE* file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Errore nell'apertura del file di input...\n");
        return -1;
    }

    // Caricamento elementi
    Elem elementi[MAX_ELEM];
    int n;
    if (load_elem(file, elementi, &n) == -1) {
        printf("Errore nel caricamento degli elementi dal file...\n");
        fclose(file);
        return -1;
    }

    // Chiusura file
    fclose(file);

    // Stampa tavola periodica
    print_table(elementi, n);

    // Richiesta composto
    char composto[LEN];
    printf("Scrivi un composto: ");
    scanf("%s", composto);

    // Validazione del composto
    if (!validate_input(composto)) {
        printf("Errore: il composto inserito contiene caratteri non validi...\n");
        return -1;
    }

    // Calcolo peso atomico
    float peso = scan_request(composto, elementi, n);
    if (peso == -1) {
        printf("Errore: composto non valido...\n");
        return -1;
    }

    // Stampa risultato
    printf("Il peso atomico del composto %s e' %.4f\n", composto, peso);

    return 0;
}
