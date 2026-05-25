#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "oracle.h"

static bool increment_counter(int counter[], int base, int size);
static void build_password_string(int counter[], int password_size, char alphabet[], char curr_password[]);
void solve_brute_force(char alphabet[], int base, int password_size, char *found_password);

bool increment_counter(int counter[], int base, int size) {
    int idx = size - 1;

    while (idx >= 0) {
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

void solve_brute_force(char alphabet[], int base, int password_size, char *found_password) {
    int counter[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    bool has_next = true;
    char current_password[9];

    while (has_next == true) {
        build_password_string(counter, password_size, alphabet, current_password);
        if (check_full(current_password)) {
            strcpy(found_password, current_password);
            return;
        } else {
            has_next = increment_counter(counter, base, password_size);
        }
    }
    found_password[0] = '\0';
    return ;
}