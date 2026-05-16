#include <stdio.h>
#include <stdbool.h>

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

int main() {
    char alphabet[4] = "abc";
    int base = 3;
    int counter[3] = {0, 0, 0};
    bool has_next = true;

    while (has_next == true) {
        for (int i = 0; i < 3; i++) {
            printf("%c", alphabet[counter[i]]);
        }
        printf("\n");
        has_next = increment_counter(counter, base, 3);
    }
    return 0;
}