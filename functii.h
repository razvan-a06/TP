#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_RESET   "\033[0m"

void clearScreen();
void wait(int seconds);
void afisareMeniu();
void drawHangman(int mistakes);
void rebuildWord(char c, const char* word, char* hiddenWord);
void freeWords(char** dictionar, int count);
char** loadWordsFromFile(const char* filename, int* count);
void playGame(int diff);