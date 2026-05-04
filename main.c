#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("      JOC SPANZURATOAREA      \n");
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

void rebuildWord(char c, char* word, char* hiddenWord) {
    int length = strlen(word);
    for (int i=0; i<length; i++)
        if (c == word[i])
            hiddenWord[i] = c;
}

void playGame() {
    char secretWord[] = "joc";
    int length = strlen(secretWord);
    char* hiddenWord = malloc((length+1)*sizeof(char));
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
        printf("Greseli: %d / %d\n\n", mistakes, maxMistakes);

        printf("Cuvantul: ");
        for(int i = 0; i < length; i++) {
            printf("%c ", hiddenWord[i]);
        }
        printf("\n\n");

        printf("Litere gresite incercate: ");
        for (int i=0; i<mistakes; i++)
            printf("%c ", wrongLetters[i]);
        printf("\n\n");

        char guess;
        printf("Introdu o litera: ");
        scanf(" %c", &guess);
        printf("\n\n");
        if (strchr(hiddenWord, guess)) {
            printf("Ai ghicit deja aceasta litera!\n");
            wait(2);
        }
        else if (strchr(secretWord, guess)) {
            rebuildWord(guess, secretWord, hiddenWord);
        }
        else
            if (strchr(wrongLetters,guess)) {
                printf("Ai incercat deja aceasta litera!");
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
        printf("\nFELICITARI! Ai ghicit cuvantul: %s\n", secretWord);
        wait(2);
    }
    else {
        printf("\nAI PIERDUT! Cuvantul corect era: %s\n", secretWord);
        wait(2);
    }
    free(hiddenWord);
}

int main() {
    int optiune;

    do {
        clearScreen();
        afisareMeniu();

        if (scanf("%d", &optiune) != 1) {
            optiune = -1;
        }
        while (getchar() != '\n');

        switch(optiune) {
            case 1:
                printf("\n---> Incepem un joc nou!\n");
                wait(2);
                playGame();
                optiune = 0;
                break;
            case 2:
                printf("\n---> REGULI: Ai 6 incercari sa ghicesti cuvantul ascuns. Succes!\n");
                break;
            case 0:
                printf("\n---> Iesire din joc. La revedere!\n");
                wait(2);
                break;
            default:
                printf("\n---> Optiune invalida! Te rog alege 1, 2 sau 0.\n");
        }

        if (optiune != 0) {
            printf("\nApasa tasta ENTER pentru a te intoarce la meniu...");
            while (getchar() != '\n');
        }

    } while (optiune != 0);

    return 0;
}