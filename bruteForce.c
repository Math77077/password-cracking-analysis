#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool increment_counter(int counter[], int base, int size);
void build_password_string(int counter[], int password_size, char alphabet[], char curr_password[]);

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

int main() {
    char alphabet[63] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int base = 62;
    int counter[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int password_size = 8;
    bool has_next = true;

    char target_password[9] = "aaaaabbc";
    bool match_found = false;

    char temp_current_password[9];

    while (has_next == true && match_found == false) {
        build_password_string(counter, password_size, alphabet, temp_current_password);
        if (!strcmp(temp_current_password, target_password)) {
            printf("Password cracked! The password is: %s\n", temp_current_password);
            match_found = true;
            return 0;
        } else {
            has_next = increment_counter(counter, base, password_size);
        }
    }
    printf("Search complete. All alphanumeric combinations exhausted. Target password not found.");
    return 0;
}