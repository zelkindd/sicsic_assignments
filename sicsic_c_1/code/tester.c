#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE       2048
#define MAIN_EXE       "./main"
#define INPUT_FILE     "../assignment_details/input.txt"
#define EXPECTED_FILE  "../assignment_details/output.txt"
#define ACTUAL_FILE    "./actual_output.txt"

int main() {
    // Run main.exe, feed input.txt via stdin, capture stdout to actual_output.txt
    int ret = system(MAIN_EXE " < " INPUT_FILE " > " ACTUAL_FILE);
    if (ret != 0) {
        printf("ERROR: Failed to run main.exe (exit code %d)\n", ret);
        return 1;
    }

    FILE *expected = fopen(EXPECTED_FILE, "r");
    FILE *actual   = fopen(ACTUAL_FILE,   "r");

    if (!expected) { printf("ERROR: Cannot open expected output: %s\n", EXPECTED_FILE); return 1; }
    if (!actual)   { printf("ERROR: Cannot open actual output: %s\n",   ACTUAL_FILE);   return 1; }

    char exp_line[MAX_LINE];
    char act_line[MAX_LINE];
    int  line_num   = 0;
    int  mismatches = 0;

    while (1) {
        char *exp_read = fgets(exp_line, MAX_LINE, expected);
        char *act_read = fgets(act_line, MAX_LINE, actual);
        line_num++;

        // Both files exhausted — done
        if (!exp_read && !act_read) break;

        // Actual has extra lines
        if (!exp_read) {
            act_line[strcspn(act_line, "\n")] = '\0';
            printf("[LINE %d] EXTRA in actual:   \"%s\"\n", line_num, act_line);
            mismatches++;
            while (fgets(act_line, MAX_LINE, actual)) {
                act_line[strcspn(act_line, "\n")] = '\0';
                printf("[LINE %d] EXTRA in actual:   \"%s\"\n", ++line_num, act_line);
                mismatches++;
            }
            break;
        }

        // Actual is missing lines
        if (!act_read) {
            exp_line[strcspn(exp_line, "\n")] = '\0';
            printf("[LINE %d] MISSING in actual: \"%s\"\n", line_num, exp_line);
            mismatches++;
            while (fgets(exp_line, MAX_LINE, expected)) {
                exp_line[strcspn(exp_line, "\n")] = '\0';
                printf("[LINE %d] MISSING in actual: \"%s\"\n", ++line_num, exp_line);
                mismatches++;
            }
            break;
        }

        // Compare lines
        if (strcmp(exp_line, act_line) != 0) {
            char exp_display[MAX_LINE], act_display[MAX_LINE];
            strcpy(exp_display, exp_line);
            strcpy(act_display, act_line);
            exp_display[strcspn(exp_display, "\n")] = '\0';
            act_display[strcspn(act_display, "\n")] = '\0';
            printf("[LINE %d] MISMATCH:\n  Expected: \"%s\"\n  Actual:   \"%s\"\n\n",
                   line_num, exp_display, act_display);
            mismatches++;
        }
    }

    fclose(expected);
    fclose(actual);

    printf("----------------------------------------\n");
    if (mismatches == 0) {
        printf("ALL LINES MATCH! Output is correct.\n");
    } else {
        printf("Total mismatches: %d\n", mismatches);
    }

    return mismatches > 0 ? 1 : 0;
}
