#include "oracle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char secret_password[9];
static long long oracle_hits = 0;
static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

void oracle_init(int mode, const char* path) {
    oracle_hits = 0;
    if (mode == MODE_FILE) {
        FILE *f = fopen(path, "r");
        if (!f) {
            perror("Error opening password file");
            exit(1);
        }
        if (fscanf(f, "%s", secret_password) != 1) {
            fprintf(stderr, "Error reading password from file.\n");
            exit(1);
        }
        fclose(f);
    } else {
        srand(time(NULL));
        for (int i = 0; i < 8; i++) {
            secret_password[i] = charset[rand() % 62];
        }
        secret_password[8] = '\0';
    }
}

bool check_full(const char* attempt) {
    oracle_hits++;
    return strcmp(secret_password, attempt) == 0;
}

bool check_partial(const char* part, int start_pos) {
    oracle_hits++;
    int len = strlen(part);
    if (start_pos + len > 8) return false;
    for (int i = 0; i < len; i++) {
        if (secret_password[start_pos + i] != part[i]) return false;
    }
    return true;
}

int get_fitness(const char* attempt) {
    oracle_hits++;
    int score = 0;
    for (int i = 0; i < 8; i++) {
        if (secret_password[i] == attempt[i]) score++;
    }
    return score;
}

long long get_oracle_hits() {
    return oracle_hits;
}