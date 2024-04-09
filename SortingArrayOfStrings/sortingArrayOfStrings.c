#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lexicographic_sort(const char* a, const char* b);
int lexicographic_sort_reverse(const char* a, const char* b);
int sort_by_number_of_distinct_characters(const char* a, const char* b);
int sort_by_length(const char* a, const char* b);
void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b));

int main() 
{
    int n;
    scanf("%d", &n);
  
    char** arr;
	arr = (char**)malloc(n * sizeof(char*));
  
    for(int i = 0; i < n; i++){
        *(arr + i) = (char*)malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = (char*)realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }

    printf("\n");
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");
    return 0;
}

// For all comparing functions, return 1 if you must switch characters, return 0 if you don't have to.

int lexicographic_sort(const char* a, const char* b) {
    int i, shortest = (strlen(a) > strlen(b)) ? strlen(b) : strlen(a);
    char a_copy, b_copy;
    for (i = 0; i < shortest; i++) {
        // Begin uppercasing
        // For a_copy
        if (a[i] >= 65 && a[i] <= 90) {
            a_copy = a[i];
        } else if (a[i] >= 97 && a[i] <= 122) {
            a_copy = a[i] - 32;
        }
        // For b_copy
        if (b[i] >= 65 && b[i] <= 90) {
            b_copy = b[i];
        } else if (b[i] >= 97 && b[i] <= 122) {
            b_copy = b[i] - 32;
        }
        // End uppercasing

        // Compare letters
        // If a_copy's value is higher on the ASCII table than b_copy's value, return 1
        if (a_copy > b_copy) {
            return 1;
        }
        /*
        Cases where this would run:
            1. If a_copy's value is lower on the ASCII table than b_copy's value, return 0
            2. If a_copy's value is equal to b_copy's value, continue to the next iteration
        */
        else if (a_copy < b_copy) {
            return 0;
        }
        // Continue to the next iteration
    }
    // Loop end

    // If the loop ends, check which string was shorter. If a was shorter than b, return 0; otherwise, return 1
    if (strlen(a) < strlen(b)) {
        return 0;
    } else {
        return 1;
    }
}

int lexicographic_sort_reverse(const char* a, const char* b) {
    int i, shortest = (strlen(a) > strlen(b)) ? strlen(b) : strlen(a);
    char a_copy, b_copy;
    for (i = 0; i < shortest; i++) {
        // Begin uppercasing
        // For a_copy
        if (a[i] >= 65 && a[i] <= 90) {
            a_copy = a[i];
        } else if (a[i] >= 97 && a[i] <= 122) {
            a_copy = a[i] - 32;
        }
        // For b_copy
        if (b[i] >= 65 && b[i] <= 90) {
            b_copy = b[i];
        } else if (b[i] >= 97 && b[i] <= 122) {
            b_copy = b[i] - 32;
        }
        // End uppercasing

        // Compare letters
        // If a_copy's value is higher on the ASCII table than b_copy's value, return 0
        if (a_copy > b_copy) {
            return 0;
        }
        /*
        Cases where this would run:
            1. If a_copy's value is lower on the ASCII table than b_copy's value, return 0
            2. If a_copy's value is equal to b_copy's value, continue to the next iteration
        */
        else if (a_copy < b_copy) {
            return 1;
        }
        // Continue to the next iteration
    }
    // Loop end

    // If the loop ends, check which string was shorter. If a was shorter than b, return 1; otherwise, return 0
    if (strlen(a) < strlen(b)) {
        return 1;
    } else {
        return 0;
    }
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    /* To determine the number of unique characters:
        1. Find how many unique characters each string has.
            a. Need to keep track of each unique character by storing them in an array.
            b. Along the way, count how many unique characters there are.
        2. After counting, compare the lengths.
            a. If a's length is greater than b's length, return 1 (to signal that b comes earlier than a, indicating a need to switch order). Else, return 0.
            b. If both their lengths are the same, rely on lexicographic sorting to order the items.
            c. If a's length is lesser than b's length, return 0 (to signal that the order of the items is already correct). */

    // Create arrays to store the unique characters for each string
    // Limit the size of the arrays to the length of the strings
    char a_unique_chars[strlen(a)], b_unique_chars[strlen(b)];
    // Create a variable to store the length of the unique characters; this is needed for iterating through the list of unique characters
    int a_unique_chars_len = 0, b_unique_chars_len = 0;
    // Begin finding unique characters; add a variable to keep track of uniqueness status
    int i, j, unique;
    // Find unique characters in a
    for (i = 0; i < strlen(a); i++) { // Limit to the length of the string, because there can only be a maximum number of unique characters equal to the length of the string
        unique = 1;
        // Check the array of unique characters to make sure that the current character is unique
        for (j = 0; j < a_unique_chars_len && unique; j++) { // Limit the loop to the length of the array of unique characters; the programme will only check for as many unique characters as the array has. The other condition is to check if the current character is unique.
            // If the current character is not unique (i.e. the current character is found in a_unique_chars), set unique to 0, ending the inner loop
            if (a[i] == a_unique_chars[j]) {
                unique = 0;
            }
        }
        if (!unique) {
            // If the current character is not unique, skip the rest of the loop and continue to the next iteration
            continue;
        }
        // If the current character is unique, add it to the array of unique characters
        // Add the character to the array, meanwhile incrementing the a_unique_chars_len
        a_unique_chars[a_unique_chars_len++] = a[i];
    }
    // Find unique characters in b
    for (i = 0; i < strlen(b); i++) {
        unique = 1;
        for (j = 0; j < b_unique_chars_len && unique; j++) {
            if (b[i] == b_unique_chars[j]) {
                unique = 0;
            }
        }
        if (!unique) {
            continue;
        }
        // If the current character is unique, add it to the array of unique characters
        // Add the character to the array, meanwhile incrementing the a_unique_chars_len
        b_unique_chars[b_unique_chars_len++] = b[i];
    }
    // End finding unique characters
    // a_unique_chars and b_unique_chars are no longer needed, so free them
    // If a has more unique characters than b
    if (a_unique_chars_len > b_unique_chars_len) {
        return 1;
    } else if (a_unique_chars_len == b_unique_chars_len) { // If both a and b have the same number of unique characters
        return lexicographic_sort(a, b); // Sort them lexicographically
    }
    // Else, if a has fewer unique characters than b
    return 0;
}

int sort_by_length(const char* a, const char* b) {
    // If a's string length is greater than b's string length
    if (strlen(a) > strlen(b)) {
        return 1;
    } else if (strlen(a) == strlen(b)) { // Else, if a's string length is equal to b's string length
        // Secondarily, sort the strings lexicographically
        return lexicographic_sort(a, b);
    } else { // Else, if a's string length is less than b's string length
        return 0;
    }
}

void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b)){
    int i, j, index;
    char *temp = (char*) malloc (strlen(arr[0]) + 1);
    // Begin sorting
    // Condition to end loop is len - 1; otherwise, the nested loop will cause segmentation fault
    for (i = 0; i < len - 1; i++) {
        // Reallocate memory for temp to handle the next string it will store
        temp = (char*) realloc (temp, strlen(arr[i]) + 1);
        // temp stores the next iteration's index
        strcpy(temp, arr[i]);
        // Reassign index with the iteration's current index
        index = i;
        // Begin sorting iteration
        // Loop requires initialisation of i + 1 to avoid unnecessary checks
        for (j = i + 1; j < len; j++) {
            // If the comparing function returns 1, temp stores the value of j's current array index
            if ((*cmp_func)(temp, arr[j])) {
                temp = (char*) realloc (temp, strlen(arr[j]) + 1);
                strcpy(temp, arr[j]);
                index = j;
            }
            // End if
        }
        // End loop
        // After loop ends, switch the value of array index i with the value of array index index
        strcpy(arr[index], arr[i]);
        strcpy(arr[i], temp);
    }
    // End loop
    // After loop ends, sorting should be finished. Free temp.
    free(temp);
}