#include "functii.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_RESET   "\033[0m"

#define CHUNK 50

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void wait(int seconds) {
    #ifdef _WIN32
    Sleep(seconds*1000);
    #else
    sleep(seconds);
    #endif
}

void afisareMeniu() {
    printf("==============================\n");
    printf(COLOR_CYAN"      JOC SPANZURATOAREA      \n"COLOR_RESET);
    printf("==============================\n");
    printf(" 1. Joaca\n");
    printf(" 2. Reguli\n");
    printf(" 0. Iesire\n");
    printf("==============================\n");
    printf("Alege o optiune: ");
}

void drawHangman(int mistakes) {
    printf("\n");
    switch (mistakes) {
        case 0:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 1:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 2:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf("  |   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 3:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 4:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 5:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf(" /    |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 6:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf(" / \\  |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        default:
            printf("Eroare la numararea greselilor!\n");
    }
}

void rebuildWord(char c, const char* word, char* hiddenWord) {
    int length = strlen(word);
    for (int i=0; i<length; i++)
        if (c == word[i])
            hiddenWord[i] = c;
}

void freeWords(char** dictionar, int count) {
    for (int i=0; i<count; i++)
        free(dictionar[i]);
}

char** loadWordsFromFile(const char* filename, int* count) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("eroare la deschiderea fisierului!");
        exit(-1);
    }

    int size = CHUNK;
    char** dictionar = malloc(size*sizeof(char*));
    if (!dictionar) {
        printf("Memorie insuficienta!");
        fclose(f);
        exit(-1);
    }
    *count = 0;
    char line[100] = "";
    while (fgets(line, sizeof(line), f)) {
        if (*count == size) {
            size += CHUNK;
            char** temp = realloc(dictionar, size*sizeof(char*));
            if (!temp) {
                printf("Memorie insuficienta!");
                fclose(f);
                freeWords(dictionar, *count);
                free(dictionar);
                exit(-1);
            }
            dictionar = temp;
        }
        char* start = strchr(line, '"');
        if (start) {
            start++;
            char word[100] = "";
            int i=0;
            while (*start != '"') {
                word[i++] = (*start);
                start++;
            }
            word[i] = '\0';
            dictionar[*count] = malloc((strlen(word)+1) * sizeof(char));
            if (!dictionar[*count]) {
                printf("Memorie insuficienta!");
                fclose(f);
                freeWords(dictionar, *count);
                free(dictionar);
                exit(-1);
            }
            strcpy(dictionar[(*count)++], word);
        }
    }
    if (fclose(f) != 0) {
        printf("Eroare inchidere fisier!");
        freeWords(dictionar, *count);
        free(dictionar);
        exit(-1);
    }
    return dictionar;
}

void playGame(int diff) {
    char** dictionar; int count, length, index;
    char* hiddenWord;
    char* secretWord;
    switch (diff) {
        case 1:
            dictionar = loadWordsFromFile("../usor.json", &count);
            index = rand() % count;
            secretWord = dictionar[index];
            break;
        case 2:
            dictionar = loadWordsFromFile("../mediu.json", &count);
            index = rand() % count;
            secretWord = dictionar[index];
            break;
        case 3:
            dictionar = loadWordsFromFile("../greu.json", &count);
            index = rand() % count;
            secretWord = dictionar[index];
            break;
        case 4:
            secretWord = malloc(21 * sizeof(char));
            if (!secretWord) {
                printf("Memorie insuficienta!");
                exit(-1);
            }

            int validWord = 0;
            do {
                printf("---> Jucator 1, introdu cuvantul secret (doar litere, maxim 20): ");
                fgets(secretWord, 21, stdin);

                if (strchr(secretWord, '\n') == NULL) {
                    printf("\n" COLOR_YELLOW "EROARE: Cuvantul este prea lung! Maxim 20 de litere." COLOR_RESET "\n\n");
                    while (getchar() != '\n');
                    continue;
                }

                secretWord[strcspn(secretWord, "\n")] = '\0';

                if (strlen(secretWord) == 0) {
                    printf("\n" COLOR_YELLOW "EROARE: Nu ai introdus niciun cuvant!" COLOR_RESET "\n\n");
                    continue;
                }

                validWord = 1;
                for (int i = 0; secretWord[i] != '\0'; i++) {
                    if (!isalpha(secretWord[i])) {
                        validWord = 0;
                        break;
                    }
                }

                if (validWord == 0) {
                    printf("\n" COLOR_YELLOW "EROARE: Cuvantul trebuie sa contina DOAR litere (fara cifre, spatii sau simboluri)!" COLOR_RESET "\n\n");
                }

            } while (validWord == 0);

            for(int i = 0; secretWord[i] != '\0'; i++) {
                secretWord[i] = tolower(secretWord[i]);
            }
            break;
        default:
            printf("eroare dificultate");
            exit(-1);
    }
    printf("\n---> Incepem un joc nou!\n");
    wait(2);
    length = strlen(secretWord);
    hiddenWord = malloc((length+1)*sizeof(char));
    if (!hiddenWord) {
        printf("Memorie insuficienta!");
        freeWords(dictionar, count);
        free(dictionar);
        exit(-1);
    }
    char wrongLetters[7] = "";

    for(int i = 0; i < length; i++) {
        hiddenWord[i] = '_';
    }
    hiddenWord[length] = '\0';

    int mistakes = 0;
    int maxMistakes = 6;
    int win = 0;

    while (mistakes < maxMistakes && win == 0) {
        clearScreen();
        drawHangman(mistakes);
        printf(COLOR_RED"Greseli: %d / %d" COLOR_RESET "\n\n", mistakes, maxMistakes);

        printf("Cuvantul: ");
        for(int i = 0; i < length; i++) {
            printf("%c ", hiddenWord[i]);
        }
        printf("\n\n");

        printf(COLOR_RED "Litere gresite incercate: ");
        for (int i=0; i<mistakes; i++)
            printf("%c ", wrongLetters[i]);
        printf(COLOR_RESET"\n\n");

        char guess;
        int valid;
        do {
            printf("Introdu o litera: ");
            scanf(" %c", &guess);
            char nextchar = getchar();
            if (nextchar != '\n') {
                printf("\n" COLOR_YELLOW "EROARE: Te rog sa introduci O SINGURA litera!" COLOR_RESET "\n\n");
                while (getchar() != '\n');
                valid = 0;
            }
            else if (!isalpha(guess)) {
                printf("\n" COLOR_YELLOW "EROARE: Ai introdus o cifra sau un simbol! Te rog introdu doar litere (a-z)." COLOR_RESET "\n\n");
                valid = 0;
            }
            else {
                guess = tolower(guess);
                valid = 1;
            }
        } while (valid == 0);
        printf("\n\n");
        if (strchr(hiddenWord, guess)) {
            printf(COLOR_YELLOW"Ai ghicit deja aceasta litera!" COLOR_RESET "\n");
            wait(2);
        }
        else if (strchr(secretWord, guess)) {
            rebuildWord(guess, secretWord, hiddenWord);
        }
        else
            if (strchr(wrongLetters,guess)) {
                printf(COLOR_YELLOW"Ai incercat deja aceasta litera!" COLOR_RESET);
                wait(2);
            }
            else {
                mistakes++;
                wrongLetters[mistakes - 1] = guess;
                wrongLetters[mistakes] = '\0';
            }

        if (strcmp(hiddenWord, secretWord) == 0) {
            win = 1;
        }
    }

    clearScreen();
    drawHangman(mistakes);
    if (win == 1) {
        clearScreen();
        printf("\n" COLOR_GREEN "FELICITARI! Ai ghicit cuvantul: %s" COLOR_RESET "\n", secretWord);
        wait(2);
        clearScreen();
    }
    else {
        printf("\n" COLOR_RED "AI PIERDUT! Cuvantul corect era: %s" COLOR_RESET "\n", secretWord);
        wait(2);
        clearScreen();
    }
    free(hiddenWord);
    if (diff == 4)
        free(secretWord);
    else {
        freeWords(dictionar, count);
        free(dictionar);
    }
}
