#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "oracle.h"

#define CACHE_SIZE 14776336

bool increment_counter(int counter[], int base, int size, int left_boundary);
void build_password_string(int counter[], int password_size, char alphabet[], char curr_password[]);
bool bruteForce(char alphabet[], int base, int counter[], int password_size, int start_idx);
void solve_dynamic_programming_memoization(char alphabet[], int base, int password_size);

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

bool bruteForce(char alphabet[], int base, int counter[], int password_size, int start_idx) {
    bool has_next = true;
    char current_password[9];

    while (has_next == true) {
        build_password_string(counter, password_size, alphabet, current_password);
        if (check_full(current_password)) {
            printf("Password cracked! The password is: %s\n", current_password);
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

void solve_dynamic_programming_memoization(char alphabet[], int base, int password_size) {
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
                 if (bruteForce(alphabet, base, counter, password_size, 4)) {
                    free(failed_prefixes);
                    return;
                 };
            } else {
                failed_prefixes[idx] = true;
            }
        }
    } while (increment_counter(counter, base, 4, 0));
    printf("Search complete. All alphanumeric combinations exhausted. Target password not found.");
    free(failed_prefixes);
    return;
}
