#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool increment_counter(int counter[], int base, int size, int left_boundary);
void build_password_string(int counter[], char alphabet[], char curr_password[], int start_idx, int end_idx);
bool validate_password(char curr_password[], int start_idx, int end_idx);
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

bool validate_password(char curr_password[], int start_idx, int end_idx) {
    char target_password[9] = "zzzzbbbc";

    for (int i = start_idx; i <= end_idx; i++) {
        if (curr_password[i] != target_password[i]) {
            return false;
        }
    }
    return true;
}

bool crack_sequential_halves(int counter[], int base, int size, char final_password[], char alphabet[]) {
    bool first_match_found = false;
    while (!first_match_found) {
        build_password_string(counter, alphabet, final_password, 0, 3);

        if (validate_password(final_password, 0, 3)) {
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
        build_password_string(counter, alphabet, final_password, 4, 7);

        if (validate_password(final_password, 4, 7)) {
            second_match_found = true;
        } else {
            if (!increment_counter(counter, base, 8, 4)) {
                printf("Search complete for second half. All alphanumeric combinations exhausted. Target password not found.");
                return false;
            };
        }
    }

    final_password[size] = '\0';
    return true;
}


int main() {
    char alphabet[63] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int base = 62;
    int counter[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int password_size = 8;
    bool match_found = false;

    char temp_current_password[9];

    if (crack_sequential_halves(counter, base, password_size, temp_current_password, alphabet)) {
        printf("Password cracked! The password is: %s\n", temp_current_password);
    }

    return 0;
}