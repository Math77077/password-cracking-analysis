#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "oracle.h"

#define CACHE_SIZE 14776336

static bool increment_counter(int counter[], int base, int size, int left_boundary);
static void build_password_string(int counter[], int password_size, char alphabet[], char curr_password[]);
bool bruteForce(char alphabet[], int base, int counter[], int password_size, int start_idx, char* found_password);
static int get_cache_index(const int counter[]);
void solve_dynamic_programming_memoization(char alphabet[], int base, int password_size, char *found_password);

bool increment_counter(int counter[], int base, int size, int left_boundary) {
    int idx = size - 1;

    while (idx >= left_boundary) {
        if (counter[idx] < base - 1) {
            counter[idx] = counter[idx] + 1;
            return true;
        } else {
            counter[idx] = 0;
            idx = idx - 1;
        }
    }
    return false;
}

void build_password_string(int counter[], int password_size, char alphabet[], char curr_password[]) {
    for (int i = 0; i < password_size; i++) {
        curr_password[i] = alphabet[counter[i]];
    }
    curr_password[password_size] = '\0';
}

bool bruteForce(char alphabet[], int base, int counter[], int password_size, int start_idx, char* found_password) {
    bool has_next = true;
    char current_password[9];

    while (has_next == true) {
        build_password_string(counter, password_size, alphabet, current_password);
        if (check_full(current_password)) {
            strcpy(found_password, current_password);
            return true;
        } else {
            has_next = increment_counter(counter, base, password_size, start_idx);
        }
    }
    return false;
}

static int get_cache_index(const int counter[]) {
    int index = (counter[0] * 62 * 62 * 62) + (counter[1] * 62 * 62) + (counter[2] * 62) + (counter[3]);
    return index;
}

void solve_dynamic_programming_memoization(char alphabet[], int base, int password_size, char *found_password) {
    int counter[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    char current_password[9];

    bool *failed_prefixes = calloc(CACHE_SIZE, sizeof(bool));
    if (failed_prefixes == NULL) {
        perror("Failed to allocate memory for DP cache");
        return;
    }

    do {
        int idx = get_cache_index(counter);
        if (!failed_prefixes[idx]) {
            build_password_string(counter, 4, alphabet, current_password);
            current_password[4] = '\0';
            if (check_partial(current_password, 0)) {
                 if (bruteForce(alphabet, base, counter, password_size, 4, found_password)) {
                    free(failed_prefixes);
                    return;
                 };
            } else {
                failed_prefixes[idx] = true;
            }
        }
    } while (increment_counter(counter, base, 4, 0));
    found_password[0] = '\0';
    free(failed_prefixes);
    return;
}
