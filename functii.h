void clearScreen();
void wait(int seconds);
void afisareMeniu();
void drawHangman(int mistakes);
void rebuildWord(char c, const char* word, char* hiddenWord);
void freeWords(char** dictionar, int count);
char** loadWordsFromFile(const char* filename, int* count);
void playGame(int diff);