#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 1500

// Helper function to check if a character is a delimiter or newline
int IsDelimiterCharacter(char c, const char* delimiter) {
    return (c == '\n' || strchr(delimiter, c) != NULL);
}

// Function to replace delimiters with commas in the input
void ReplaceDelimitersWithCommas(char* input, const char* delimiter) {
    while (*input) {
        if (IsDelimiterCharacter(*input, delimiter)) {
            *input = ',';
        }
        input++;
    }
}

// Function to initialize the default delimiter
void InitializeDefaultDelimiter(char* delimiter) {
    strcpy(delimiter, ",");
}

// Function to extract custom delimiter from input if present
int ExtractDelimiter(const char* input, char* delimiter, const char** numberSequence) {
    if (strncmp(input, "//", 2) == 0) {
        const char* delimiterPos = strchr(input, '\n');
        if (delimiterPos) {
            // Ensure the extracted delimiter fits within bounds
            size_t delimiterLength = delimiterPos - input - 2;
            if (delimiterLength >= MAX_STRING_LENGTH) {
                fprintf(stderr, "Delimiter too long\n");
                exit(1);
            }
            strncpy(delimiter, input + 2, delimiterLength);
            delimiter[delimiterLength] = '\0';  // Null-terminate
            *numberSequence = delimiterPos + 1;
            return 1; // Custom delimiter found
        }
    }
    return 0; // No custom delimiter
}

// Function to determine the delimiter and process the input numbers
void ParseDelimiterAndNumbers(const char* input, char* delimiter, const char** numberSequence) {
    InitializeDefaultDelimiter(delimiter);
    if (!ExtractDelimiter(input, delimiter, numberSequence)) {
        *numberSequence = input;
    }
    ReplaceDelimitersWithCommas((char*)*numberSequence, delimiter);
}

// Function to check for negative numbers and print an error if found
void ValidateForNegativeNumbers(const char* input) {
    char inputCopy[MAX_STRING_LENGTH];
    strncpy(inputCopy, input, MAX_STRING_LENGTH - 1);
    inputCopy[MAX_STRING_LENGTH - 1] = '\0';

    char* token = strtok(inputCopy, ",");
    while (token != NULL) {
        int number = atoi(token);
        if (number < 0) {
            fprintf(stderr, "Error: Negative numbers are not allowed (%d)\n", number);
            exit(1);
        }
        token = strtok(NULL, ",");
    }
}

// Function to calculate the sum, ignoring numbers greater than 1000
int SumNumbersIgnoringLarge(const char* input) {
    int sum = 0;
    char inputCopy[MAX_STRING_LENGTH];
    strncpy(inputCopy, input, MAX_STRING_LENGTH - 1);
    inputCopy[MAX_STRING_LENGTH - 1] = '\0';

    char* token = strtok(inputCopy, ",");
    while (token != NULL) {
        int number = atoi(token);
        if (number <= 1000) {
            sum += number;
        }
        token = strtok(NULL, ",");
    }
    return sum;
}

// Main function to add the numbers from the input string
int AddNumbers(const char* input) {
    if (*input == '\0') {
        return 0;
    }

    const char* numberSequence;
    char delimiter[MAX_STRING_LENGTH];

    ParseDelimiterAndNumbers(input, delimiter, &numberSequence);
    ValidateForNegativeNumbers(numberSequence);

    return SumNumbersIgnoringLarge(numberSequence);
}

int main() {
    const char* input = "//;\n1;2;1001;3";
    int result = AddNumbers(input);
    printf("Sum: %d\n", result);
    return 0;
}
