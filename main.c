#include "functii.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int optiune, diff, mod;

    do {
        clearScreen();
        afisareMeniu();

        if (scanf("%d", &optiune) != 1) {
            optiune = -1;
        }
        if (getchar() != '\n') {
            optiune = -1;
            while (getchar() != '\n');
        }

        switch(optiune) {
            case 1:
                do {
                    clearScreen();
                    printf("---> Alegeti modul de joc:\n\n");
                    printf("1. Single-player\n2. Multiplayer\n\nAlege o optiune:");
                    if (scanf("%d", &mod) != 1) {
                        mod = -1;
                    }
                    if (getchar() != '\n') {
                        printf("\n---> Optiune invalida! Te rog alege 1 sau 2.\n");
                        mod = -1;
                    }
                } while (mod < 0);
                if (mod == 1) {
                    do {
                        clearScreen();
                        printf("---> Alegeti nivelul de dificultate:\n\n");
                        printf("1. Usor\n2. Mediu\n3. Greu\n\nAlege o optiune:");
                        if (scanf(" %d", &diff) != 1) {
                            diff = -1;
                        }
                        if (getchar() != '\n') {
                            diff = -1;
                            while (getchar() != '\n');
                        }
                        switch (diff) {
                            case 1:
                                playGame(1);
                                break;
                            case 2:
                                playGame(2);
                                break;
                            case 3:
                                playGame(3);
                                break;
                            default:
                                printf("\n---> Optiune invalida! Te rog alege 1, 2 sau 3.\n");
                                diff = -1;
                                wait(2);
                        }
                    } while (diff < 0);
                }
                else {
                    clearScreen();
                    playGame(4);
                }
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