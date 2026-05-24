#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "oracle.h"

bool increment_counter(int counter[], int base, int size, int left_boundary);
void build_password_string(int counter[], char alphabet[], char curr_password[], int start_idx, int end_idx);
bool crack_sequential_halves(int counter[], int base, int size, char final_password[], char alphabet[]);


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

void build_password_string(int counter[], char alphabet[], char curr_password[], int start_idx, int end_idx) {
    for (int i = start_idx; i <= end_idx; i++) {
        curr_password[i] = alphabet[counter[i]];
    }
}

bool crack_sequential_halves(int counter[], int base, int size, char current_password[], char alphabet[]) {
    bool first_match_found = false;
    while (!first_match_found) {
        build_password_string(counter, alphabet, current_password, 0, 3);
        current_password[4] = '\0';

        if (check_partial(current_password, 0)) {
            first_match_found = true;
        } else {
            if (!increment_counter(counter, base, 4, 0)) {
                printf("Search complete for first half. All alphanumeric combinations exhausted. Target password not found.");
                return false;
            }
        }
    }

    bool second_match_found = false;
    while (!second_match_found) {
        build_password_string(counter, alphabet, current_password, 4, 7);

        if (check_partial(&current_password[4], 4)) {
            second_match_found = true;
        } else {
            if (!increment_counter(counter, base, 8, 4)) {
                printf("Search complete for second half. All alphanumeric combinations exhausted. Target password not found.");
                return false;
            };
        }
    }

    current_password[size] = '\0';
    return true;
}

void solve_divide_and_conquer(char alphabet[], int base, int password_size) {
    int counter[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    bool match_found = false;

    char current_password[9];

    if (crack_sequential_halves(counter, base, password_size, current_password, alphabet)) {
        printf("Password cracked! The password is: %s\n", current_password);
    }
}
