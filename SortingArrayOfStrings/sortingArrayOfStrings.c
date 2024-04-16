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
    for (i = 0; i < shortest; i++) {// Compare letters
        // If a_copy's value is higher on the ASCII table than b_copy's value, return 1
        if (a[i] > b[i]) {
            return 1;
        }
        else if (a[i] < b[i]) {
            return 0;
        }
        // Continue to the next iteration
    }
    // Loop end

    // If the loop ends, check which string was shorter. If a was shorter than b, return 0; otherwise, return 1
    if (strlen(a) > strlen(b)) {
        return 1;
    }
    return 0;
}

int lexicographic_sort_reverse(const char* a, const char* b) {
    return lexicographic_sort(b, a);
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    /* 
    i: string length of a;
    j: string length of b;
    k: unique characters in a;
    l: unique characters in b
    */
    int i = strlen(a), j = strlen(b), k = 0, l = 0;
    // There are only 26 letters in the alphabet, so we can use the ASCII values of 'a' and 'z' to iterate through the alphabet
    for (int y = 'a'; y <= 'z'; y++) {
        // Iterate through the string to find the unique characters
        for (int x = 0; x < i; x++) {
            // If the current character is equal to the current letter in the alphabet, increment k and break the loop
            if (a[x] == (char) y) {
                k++;
                break;
                /* The first version of this code that was used had another (useless) condition and used the "and" boolean operator. However, instead of using the double ampersand (&&), it used a single ampersand (&). This makes sense because C doesn't really return the boolean values true and false but only returns 1 and 0, and binary operands can thus still work. */
            }        
        }
    }
    /* Note on the algorithm: if the character a[x] is equal to the current letter, e.g. 'a', then the number of unique characters will go up and the loop will break. The computer does not need to be wary of repeated characters in the string, because the conditional statement can no longer become true with repeated characters in the string, e.g. 'a', once the outer loop changes the integer y to another character, e.g. 'b'. Hence, if 'a' appears in the string again, the conditional won't be true anymore because the variable y is now 'b'.
    
    Also, the number of unique characters won't become inaccurate because the loop will break at the first instance of that character. */

    for (int y = 'a'; y <= 'z'; y++) {
        for (int x = 0; x < j; x++) {
            if (b[x] == (char) y) {
                l++;
                break;
            }       
        }
    }

    // Else statements are not necessary because the function will return if a conditional statement is true, so the subsequent code will not run.
    if (k == l) {
        return lexicographic_sort(a, b);
    }
}

// My original implementation
/* int sort_by_number_of_distinct_characters(const char* a, const char* b) {

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
    return k > l;
}*/

// Implementation adapted from the discussion board
int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    /* 
    i: string length of a;
    j: string length of b;
    k: unique characters in a;
    l: unique characters in b
    */
    int i = strlen(a), j = strlen(b), k = 0, l = 0;
    // There are only 26 letters in the alphabet, so we can use the ASCII values of 'a' and 'z' to iterate through the alphabet
    for (int y = 'a'; y <= 'z'; y++) {
        // Iterate through the string to find the unique characters
        for (int x = 0; x < i; x++) {
            // If the current character is equal to the current letter in the alphabet, increment k and break the loop
            if (a[x] == (char) y) {
                k++;
                break;
                /* The first version of this code that was used had another (useless) condition and used the "and" boolean operator. However, instead of using the double ampersand (&&), it used a single ampersand (&). This makes sense because C doesn't really return the boolean values true and false but only returns 1 and 0, and binary operands can thus still work. */
            }        
        }
    }
    /* Note on the algorithm: if the character a[x] is equal to the current letter, e.g. 'a', then the number of unique characters will go up and the loop will break. The computer does not need to be wary of repeated characters in the string, because the conditional statement can no longer become true with repeated characters in the string, e.g. 'a', once the outer loop changes the integer y to another character, e.g. 'b'. Hence, if 'a' appears in the string again, the conditional won't be true anymore because the variable y is now 'b'.
    
    Also, the number of unique characters won't become inaccurate because the loop will break at the first instance of that character. */

    for (int y = 'a'; y <= 'z'; y++) {
        for (int x = 0; x < j; x++) {
            if (b[x] == (char) y) {
                l++;
                break;
            }       
        }
    }

    // Else statements are not necessary because the function will return if a conditional statement is true, so the subsequent code will not run.
    if (k == l) {
        return lexicographic_sort(a, b);
    }
    return k > l;
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
    // Begin sorting
    // Condition to end loop is len - 1; otherwise, the nested loop will cause segmentation fault
    for (i = 0; i < len - 1; i++) {
        // Reassign index with the iteration's current index
        index = i;
        // Begin sorting iteration
        // Loop requires initialisation of i + 1 to avoid unnecessary checks
        for (j = i + 1; j < len; j++) {
            // If the comparing function returns 1, temp stores the value of j's current array index
            if ((*cmp_func)(arr[index], arr[j])) {
                index = j;
            }
            // End if
        }
        // End loop
        // After loop ends, switch the value of array index i with the value of array index index
        char *temp = arr[index];
        arr[index] = arr[i];
        arr[i] = temp;
    }
    // End loop
}
