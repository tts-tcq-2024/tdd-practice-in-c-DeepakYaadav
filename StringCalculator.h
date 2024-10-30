#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>

int is_empty_string(const char* input) {
    return (input == NULL || input[0] == '\0');
}

void extract_custom_delimiter(const char* input, char* delimiter) {
    int i = 2;     // Start after the initial //
    delimiter[0] = '\0';
    while (input[i] != '\0' && input[i] != '\n') {
        strncat(delimiter, &input[i], 1);
        i++;
    }
}
void has_custom_delimiter(const char* input, char* delimiter) {
    if (input[0] == '/' && input[1] == '/')
        extract_custom_delimiter(input, delimiter);
    else
         strcpy(delimiter, ",\n");
}


int value_less_than_thousand(const char *input_segment) {
    int value_check = atoi(input_segment);
    return (value_check < 1000) ? value_check : 0;
}

void contains_negative(const char* input, const char* delimiter) {
    char* duplicate_input = strdup(input);
    char* input_segment = strtok(duplicate_input, delimiter);
    while (input_segment != NULL) {
        int value_check = atoi(input_segment);
        if (value_check < 0) {
          throw std::runtime_error("negatives not allowed");
         }
        input_segment = strtok(NULL, delimiter);
    }
    free(duplicate_input);
}

int calculate_sum(const char* input, const char* delimiter) {
    int sum = 0;
    char* input_copy = strdup(input); 
    char* input_segment = strtok(input_copy, delimiter);
    while (input_segment != NULL) {
        sum += value_less_than_thousand(input_segment);
        input_segment = strtok(NULL, delimiter);
    }
    free(input_copy); 
    return sum;
}

int add(const char* input) {
    char delimiter[20];
    if (is_empty_string(input)) {
        return 0;
    }
    has_custom_delimiter(input, delimiter);
    contains_negative(input, delimiter);
    return calculate_sum(input, delimiter);
}
