#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define NUM_PREFIXES 4

bool check_partial(char prefix[], int start_pos);
bool check_password(char candidate[]);
bool increment_counter(int counter[], int base, int size, int left_boundary);
void build_password_string(int counter[], int password_size, char alphabet[], char curr_password[]);
int find_char_index(char target, char alphabet[]);
void pre_load_counter(char prefix[], int prefix_len, char alphabet[], int counter[]);
void bruteForce(char alphabet[], int base, int counter[], int password_size, int start_idx);
void solve_dynamic_programming(char alphabet[], int base, int counter[], int password_size);

bool check_partial(char prefix[], int start_pos) {
    char *true_password = "1234abcd";

    if (strncmp(true_password, prefix, strlen(prefix)) == 0) {
        return true;
    }
    return false;
}

bool check_password(char candidate[]) {
    char *true_password = "1234abcd";
    return strcmp(candidate, true_password) == 0;
}

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

int find_char_index(char target, char alphabet[]) {
    for (int i = 0; i < strlen(alphabet); i++) {
        if (alphabet[i] == target) {
            return i;
        }
    }
    return -1;
}

void pre_load_counter(char prefix[], int prefix_len, char alphabet[], int counter[]) {
    for (int i = 0; i < prefix_len; i++) {
        char curr_char = prefix[i];
        int alpha_idx = find_char_index(curr_char, alphabet);
        counter[i] = alpha_idx;
    }
};

void bruteForce(char alphabet[], int base, int counter[], int password_size, int start_idx) {
    bool has_next = true;
    bool match_found = false;
    char temp_current_password[9];

    while (has_next == true && match_found == false) {
        build_password_string(counter, password_size, alphabet, temp_current_password);
        if (check_password(temp_current_password)) {
            printf("Password cracked! The password is: %s\n", temp_current_password);
            match_found = true;
            return;
        } else {
            has_next = increment_counter(counter, base, password_size, start_idx);
        }
    }
    printf("Search complete. All alphanumeric combinations exhausted. Target password not found.");
    return;
}

void solve_dynamic_programming(char alphabet[], int base, int counter[], int password_size) {
    char *prefixes[] = {"admin", "1234", "pass", "user"};

    for (int i = 0; i < NUM_PREFIXES; i++) {
        if (check_partial(prefixes[i], 0)) {
            int prefix_len = strlen(prefixes[i]);

            pre_load_counter(prefixes[i], prefix_len, alphabet, counter);
            bruteForce(alphabet, base, counter, password_size, prefix_len);
            return;
        }
    }

    bruteForce(alphabet, base, counter, password_size, 0);
}

int main() {
    char alphabet[63] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int base = 62;
    int counter[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int password_size = 8;
    solve_dynamic_programming(alphabet, base, counter, password_size);

    return 0;
}