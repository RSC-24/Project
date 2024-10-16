#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
struct Hint 
{
    char word[50];
    char hint[50];
};
void displayWord(char word[], bool guessed[])
{
    printf("Word: ");
    for (int i = 0; word[i] != '\0'; i++) 
    {
        if (guessed[word[i] - 'a']) 
            printf("%c ", word[i]);
        else 
            printf("_ ");
    }
    printf("\n");
}
void drawHangman(int tries)
{
    char* hangmanParts[] = { "     _________",    "    |         |", "    |        ( )","    |         |", "    |       -- --", "    |         |", "    |        / \\\n          \n\n      GAME OVER!!" };
    printf("\n");
    for (int i = 0; i <= tries; i++)
        printf("%s\n", hangmanParts[i]);
}
int main()
{
    struct Hint List[] = { { "beach", "Sandy shore by the sea" }, { "pds", "Coding" }, { "iit", "An esteemed engineering institution" }, { "pizza", "A popular Italian dish" }, {"math", "A dreaded subject"}, {"nitrogen","The largest percentage of air"} };
    srand(time(NULL));
    int wordIndex = rand() % 6;
    char* secretWord = List[wordIndex].word;
    char* hint = List[wordIndex].hint;
    int wordLength = strlen(secretWord);
    char guessedWord[50] = {0};
    bool guessedLetters[26] = {false};
    printf("Welcome to Hangman!\n");
    printf("Hint: %s\n", hint);
    int mistakes = 0;
    while (mistakes < 6) 
    {
        printf("\n");
        displayWord(guessedWord, guessedLetters);
        drawHangman(mistakes);
        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess);
        if (guessedLetters[guess - 'a']) 
        {
            printf("You've already guessed that letter. Try again.\n");
            continue;
        }
        guessedLetters[guess - 'a'] = true;
        bool found = false;
        for (int i = 0; i < wordLength; i++) 
        {
            if (secretWord[i] == guess) 
            {
                found = true;
                guessedWord[i] = guess;
            }
        }
        if (found) 
            printf("Good guess!\n");
        else 
        {
            printf("Sorry, the letter '%c' is not in the word.\n", guess);
            mistakes++;
        }
        if (strcmp(secretWord, guessedWord) == 0) 
        {
            printf("\nCongratulations! You've guessed the word: %s\n", secretWord);
            break;
        }
    }
    if (mistakes >= 6) 
    {
        drawHangman(mistakes);
        printf("\nSorry, you've run out of lives. The word was: %s\n", secretWord);
    }
    return 0;
}