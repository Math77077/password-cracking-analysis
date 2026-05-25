#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "src/oracle.h"

#define BENCHMARK_ROUNDS 13

void solve_brute_force(char alphabet[], int base, int password_size, char *found_password);
void solve_divide_and_conquer(char alphabet[], int base, int password_size, char *found_password);
void solve_dynamic_programming_memoization(char alphabet[], int base, int password_size, char *found_password);
void crack_password_genetic_algorithm(char alphabet[], char *found_password);

int main(int argc, char *argv[]) {
    char *algo = NULL;
    char *mode_str = NULL;
    char *secret_path = NULL;
    int mode_type = MODE_RANDOM;

    char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int base = 62;
    int password_size = 8;

    if (argc < 5) {
        fprintf(stderr, "Usage: %s --algo [brute|dnc|dp|genetic] --mode [random|file] [--path path_to_secret]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--algo") == 0 && i + 1 < argc) {
            algo = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "--mode") == 0 && i + 1 < argc) {
            mode_str = argv[i + 1];
            i++;
        } else if (strcmp(argv[i], "--path") == 0 && i + 1 < argc) {
            secret_path = argv[i + 1];
            i++;
        }
    }

    if (algo == NULL || mode_str == NULL) {
        fprintf(stderr, "Error: Missing required execution parameters. \n");
        return 1;
    }

    if (strcmp(mode_str, "file") == 0) {
        if (secret_path == NULL) {
            fprintf(stderr, "Error: Mode 'file' requires an explicit target path via --path.\n");
            return 1;
        }
        mode_type = MODE_FILE;
    }

    printf("Initializing Benchmark Suite: %s strategy across %d iterations...\n", algo, BENCHMARK_ROUNDS);
    printf("-----------------------------------------------------------------------\n");
    printf("Round\t| Status\t| Discovered Password\t| Oracle Hits\t| Time (ms)\n");
    printf("-----------------------------------------------------------------------\n");

    double total_time_ms = 0.0;
    long long total_hits = 0;

    for (int round = 1; round <= BENCHMARK_ROUNDS; round++) {
        char discovered_password[9] = {0};
        struct timespec start_time, end_time;

        oracle_init(mode_type, secret_path);

        clock_gettime(CLOCK_MONOTONIC, &start_time);

        if (strcmp(algo, "brute") == 0) {
            solve_brute_force(alphabet, base, password_size, discovered_password);
        } else if (strcmp(algo, "dnc") == 0) {
            solve_divide_and_conquer(alphabet, base, password_size, discovered_password);
        } else if (strcmp(algo, "dp") == 0) {
            solve_dynamic_programming_memoization(alphabet, base, password_size, discovered_password);
        } else if (strcmp(algo, "genetic") == 0) {
            crack_password_genetic_algorithm(alphabet, discovered_password);
        } else {
            fprintf(stderr, "Error: Unknown strategic execution target: '%s'\n", algo);
            return 1;
        }

        clock_gettime(CLOCK_MONOTONIC, &end_time);

        double elapsed_ms = (end_time.tv_sec - start_time.tv_sec) * 1000.0 + (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;

        long long current_hits = get_oracle_hits();

        total_time_ms += elapsed_ms;
        total_hits += current_hits;

        printf("%d\t| Success\t| %-19s\t| %-11lld\t| %.3f\n", round, discovered_password[0] != '\0' ? discovered_password : "FAILED", current_hits, elapsed_ms);
    }

    printf("-----------------------------------------------------------------------\n");
    printf("AVERAGE PERFORMANCE METRICS FOR ARTIFACT ANALYSIS:\n");
    printf("Average Core Processing Duration : %.3f ms\n", total_time_ms / BENCHMARK_ROUNDS);
    printf("Average Oracle Validation Weight : %.2f queries per run\n", (double)total_hits / BENCHMARK_ROUNDS);

    FILE *csv_file = fopen("results.csv", "a+");
    if (csv_file != NULL) {
        fseek(csv_file, 0, SEEK_END);
        long size = ftell(csv_file);
        
        if (size == 0) {
            fprintf(csv_file, "Algorithm,Mode,AvgTime_ms,AvgOracleHits\n");
        }

        fprintf(csv_file, "%s,%s,%.3f,%.2f\n", 
                algo, 
                mode_str, 
                total_time_ms / BENCHMARK_ROUNDS, 
                (double)total_hits / BENCHMARK_ROUNDS);
        
        fclose(csv_file);
        printf("Benchmark metrics successfully appended to results.csv!\n");
    } else {
        fprintf(stderr, "Warning: Unable to open results.csv for metrics archiving.\n");
    }
    return 0;
}