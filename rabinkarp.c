#include <stdio.h>
#include <string.h>
#include <math.h>

// A prime number to mod the hash values
#define q 101

void rabinKarpSearch(char pattern[], char text[]) {
    int d = 256; // Number of characters in the alphabet (ASCII)

    int M = strlen(pattern); // Length of pattern
    int N = strlen(text);    // Length of text
    int i, j;

    int p = 0; // hash value for pattern
    int t = 0; // hash value for current substring of text
    int h = 1;

    // Precompute h = (d^(M-1)) % q
    for (i = 0; i < M - 1; i++)
        h = (d * h) % q;

    // Calculate hash value for pattern and first window of text
    for (i = 0; i < M; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++) {
        // Check if hash values match
        if (p == t) {
            // Check characters one by one
            for (j = 0; j < M; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == M)
                printf("Pattern found at index %d\n", i);
        }

        // Calculate hash value for next window of text
        if (i < N - M) {
            t = (d * (t - text[i] * h) + text[i + M]) % q;

            // We might get negative value of t, convert to positive
            if (t < 0)
                t = t + q;
        }
    }
}

int main() {
    char text[] = "ABCCDDAEFGCC";
    char pattern[] = "CC";

    printf("Text: %s\n", text);
    printf("Pattern: %s\n", pattern);

    rabinKarpSearch(pattern, text);

    return 0;
}














// 1) Input:
// - pattern[]: the string to search for
// - text[]: the main text in which to search for the pattern

// 2) Algorithm:
// Rabin-Karp algorithm:
// - Precompute hash of pattern and each window of text
// - Use rolling hash to efficiently compute next window hash
// - Compare hash values first, then do character-by-character match if needed

// 3) Time Complexity:
// Best/Avg Case: O((N-M+1)*M) — worst-case same as naive search
// Worst Case: O(N*M), when all hash values match but characters don't (rare)
// Expected average case: O(N) with good hash function

// 4) Space Complexity:
// - O(1), constant extra space used (ignoring input strings)

// 5) Advantages / Disadvantages:
// + Efficient for multiple pattern searches in single pass
// + Fast when searching large texts for a few patterns
// - Worst-case performance matches naive approach
// - Hash collisions may cause unnecessary comparisons

// 6) Recurrence Relation:
// Rolling hash update:
// t[i+1] = (d * (t[i] - text[i] * h) + text[i + M]) % q
// where h = d^(M-1) mod q

// 7) Summary (2 lines):
// Uses hashing to speed up substring search.
// Fast in practice, especially with optimized hash functions.