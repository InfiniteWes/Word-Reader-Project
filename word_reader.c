#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "word_reader.h"

// Define the global variables
int TOT_COUNT = 0;
int CHAR_COUNT = 0;

void word_count() {
    TOT_COUNT++;
}

void addCharCount(int n) {
    CHAR_COUNT += n;
}

void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int main() {
    FILE *file;
    char words[100];
    char search_word[100];
    char low[100]; // Temporary variable to store the lowercase version of words read from the file
    int wordFound = 0;
    char userResponse;

    file = fopen("puzzle.txt", "r");
    if (file == NULL) {
        printf("The file could not be opened.\n");
        return 1;
    }

    do {
        printf("Please enter a word to see if it is within the document.\n");
        scanf("%99s", search_word);
        toLowerCase(search_word); // Convert the search word to lowercase

        // Reset word count and char count for each new search
        TOT_COUNT = 0;
        CHAR_COUNT = 0;
        fseek(file, 0, SEEK_SET); // Reset file pointer to the beginning for a new search

        while (fscanf(file, "%99s", words) == 1) {
            strcpy(low, words); // Copy words into temp
            toLowerCase(low); // Convert temp to lowercase for comparison
            if (strcmp(low, search_word) == 0) {
                word_count();
                addCharCount(strlen(words));
                wordFound = 1;
            }
        }

        if (!wordFound) {
            printf("The word '%s' was not found in the document.\n", search_word);
            printf("Do you want to try another word? (Y/N): ");
            scanf(" %c", &userResponse); // Note the space before %c to consume any leftover newline character
            if (userResponse == 'N' || userResponse == 'n') {
                break; // Exit the loop if the user doesn't want to continue
            }
        } else {
            printf("The word '%s' is in the document %d times.\n", search_word, TOT_COUNT);
            printf("While the total character count is: %d\n", CHAR_COUNT);
            break; // Word found, exit the loop
        }

        wordFound = 0; // Reset the word found flag for the next iteration
    } while (1); // Infinite loop, exit controlled by break statements

    fclose(file);

    return 0;
}
