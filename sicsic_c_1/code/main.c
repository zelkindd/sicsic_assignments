//
// Created by danze on 16/05/2026.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STOCKS 10

//Stock struct
typedef struct {
    char name[21];
    float price;
} Stock;

// --- Function Prototype ---
int step_0_validate(char *input);
void printMenu();
int conv_selection_to_int(char *input);
void addStock(Stock **stocks, int* ptr_stock_count);
int isValidName(const char* str_buf);
int isValidPrice(const char *str_buf, float *ptr_price);
void printStocks(Stock **stocks, int stock_count);
void doubleStocks(Stock **stocks, int stock_count);
int isValidPercent(const char* str_buf, int* ptr_percent);
void dropStocks(Stock **stocks, int stock_count);
void findLessExpensive(Stock **stocks, int stock_count);
void sortByPrice(Stock **stocks, int stock_count);
void sortByName(Stock **stocks, int stock_count);
int asciiSum(const char* str);
void sortByAsciiSum(Stock **stocks, int stock_count);
int isPalindrome(const char* str);
void findPalindromes(Stock **stocks, int stock_count);

int main() {
    int tries = 5;
    int choice = -1;
    char buffer[5];
    int stock_count = 0;

    // 1. print menu
    printMenu();
    Stock **stocks = (Stock **) malloc(MAX_STOCKS * sizeof(Stock *));  // create the array of stocks

    // Initialize all pointers to NULL to prevent unallocated pointer issues
    for (int i = 0; i < MAX_STOCKS; i++) {
        stocks[i] = NULL;
    }

    while (tries && choice != 10) {
        // 2. fgets
        fgets(buffer, 5, stdin);
        buffer[strlen(buffer) - 1] = '\0';  // remove the \n

        // 3. validate
        int valid_input = step_0_validate(buffer);
        if (valid_input != 0) {
            tries--;
            if (tries == 0) { // The number of attempts has run out
                printf("You have exceeded the allowed number of attempts!");
            } else {
            printf("The input should be non negative upto 2 digits number, %d tries are left!\n", tries);
            }
        } else {
            tries = 5; // reset tries after a proper input
            choice = conv_selection_to_int(buffer);

            switch (choice) {
                case 1:
                    addStock(stocks, &stock_count);
                    break;
                case 2:
                    if (stock_count != 0) {
                        printStocks(stocks, stock_count); }
                    break;
                case 3:
                    if (stock_count != 0) {
                        doubleStocks(stocks, stock_count); }
                    break;
                case 4:
                    if (stock_count != 0) {
                        dropStocks(stocks, stock_count); }
                    break;
                case 5:
                    if (stock_count != 0) {
                        findLessExpensive(stocks, stock_count); }
                    break;
                case 6:
                    if (stock_count != 0) {
                        sortByPrice(stocks, stock_count); }
                    break;
                case 7:
                    if (stock_count != 0) {
                        sortByName(stocks, stock_count); }
                    break;
                case 8:
                    if (stock_count != 0) {
                        sortByAsciiSum(stocks, stock_count); }
                    break;
                case 9:
                    if (stock_count != 0) {
                        findPalindromes(stocks, stock_count); }
                    break;
                default:
                    break;
            }
            if (choice != 10) {
                printMenu(); }
        }
        // 4. if invalid → tries--
        // 5. if valid → convert, reset tries, handle choice
    }
    // Global Memory Cleanup
    // Free each dynamically allocated stock structure
    for (int i = 0; i < MAX_STOCKS; i++) {
        if (stocks[i] != NULL) {
            free(stocks[i]);
        }
    }
    free(stocks);
    return 0;
}


int step_0_validate (char *input) {
    // validates the input is non-negative 1-2 digit number.
    // this function has to be called 5 times as step 0 req.
    int number_max_digits = 2;
    int input_length = strlen(input);

    if (input_length > number_max_digits) return 1; // too long
    else {
        for (int i = input_length - 1; i >= 0; i--) {
            if (input[i] < '0' || input[i] > '9') return 2; // not a digit
        }
        return 0; // all good
    }
}

void addStock(Stock **stocks, int* ptr_stock_count) {
    int name_valid = 0;
    int price_valid = 0;
    char name_buffer[99];
    char price_buffer[99];

    do {
        printf("Enter stock name: ");
        fgets(name_buffer, 99, stdin);
        name_buffer[strlen(name_buffer) - 1] = '\0'; // remove \n
        name_valid = isValidName(name_buffer);
    } while (!name_valid);

    stocks[*ptr_stock_count] = (Stock *)malloc(sizeof(Stock));
    strcpy(stocks[*ptr_stock_count]->name, name_buffer);

    do {
        printf("Enter stock price: ");
        fgets(price_buffer, 99, stdin);
        price_buffer[strlen(price_buffer) - 1] = '\0'; // remove \n
        price_valid = isValidPrice(price_buffer, &stocks[*ptr_stock_count]->price);
    } while (!price_valid);

    (*ptr_stock_count)++;
    printf("Stock added.\n");
}

int conv_selection_to_int(char *input) {
    // converts the char* input to int
    int length = strlen(input);
    int buffer = 0;
    if (length == 1) return (input[0] - '0');
    // the digit value is 48 + digit so to get the actual digit I remove '0' which is 48 (ASCII)
    else return ((input[0] - '0') * 10 + (input[1] - '0') );
}

void printMenu() {
    printf ("=== Stock Management Menu ===\n"
                    "1. Add Stock\n"
                    "2. Print Stocks\n"
                    "3. Double All Stocks Price\n"
                    "4. Drop Stocks Price by x%\n"
                    "5. Find Less Expensive Stock\n"
                    "6. Sort Stocks by Price\n"
                    "7. Sort Stocks Alphabetically\n"
                    "8. Sort Stocks by ASCII Sum of Name\n"
                    "9. Check Palindromic Stock Names\n"
                    "10. Exit\n"
                    "Please enter a number between 0-99:");
}

int isValidName(const char* str_buf) {
    int max_len = 20; // can be changed!

    int str_len = strlen(str_buf);

    if (str_len > max_len) return 0; // cannot be longer than max_len

    for (int i = str_len - 1; i >= 0; i--) {
        int is_lowercase = (str_buf[i] >= 'a' && str_buf[i] <= 'z');
        int is_uppercase = (str_buf[i] >= 'A' && str_buf[i] <= 'Z');

        if (!is_lowercase && !is_uppercase) return 0; // invalid
    }
    return 1; // valid!
}

int isValidPrice(const char *str_buf, float *ptr_price) {
    int str_len = strlen(str_buf);

    // validate each char that is a digit
    for (int i = str_len - 1; i >= 0; i--) {
        int is_digit = (str_buf[i] >= '0' && str_buf[i] <= '9');
        if (!is_digit) return 0; // some char is not a digit
    }

    // convert to int and then cast to float
    int result = 0;
    for (int i = 0; i < str_len ; i++) {
        result = result * 10 + (str_buf[i] - '0');
    }
    *ptr_price = (float)result;
    return 1; // it's an int
}

void printStocks(Stock **stocks, int stock_count) {
    // prints all existing stocks (names and prices)
    for (int i = 0; i < stock_count; i++) {
        printf("%d. %s - $%.2f\n", i+1, stocks[i]->name,  stocks[i]->price); }
}

void doubleStocks(Stock **stocks, int stock_count) {
    // doubles the price of each stock in the array
    for (int i = 0; i < stock_count; i++) {
        stocks[i]->price *= 2; }
    printf("Stock prices have doubled.\n");
}

int isValidPercent(const char* str_buf, int* ptr_percent) {
    // validates if the input is a valid integer between 0 and 100
    int str_len = strlen(str_buf);

    // validate each char that is a digit
    for (int i = str_len - 1; i >= 0; i--) {
        int is_digit = (str_buf[i] >= '0' && str_buf[i] <= '9');
        if (!is_digit) return 0; // some char is not a digit
    }

    // convert to int
    int result = 0;
    for (int i = 0; i < str_len ; i++) {
        result = result * 10 + (str_buf[i] - '0');
    }
    // check if the percentage is between 0 and 100
    if (result < 0 || result > 100) return 0;

    *ptr_percent = result;
    return 1; // 1 means valid
}

void dropStocks(Stock **stocks, int stock_count) {
    // drops all stock prices by a user specified percentage
    char percent_buffer[99];
    int percent_value = 0;
    int is_valid = 0;

    do {
        printf("Enter x%%: ");
        fgets(percent_buffer, 99, stdin);
        percent_buffer[strlen(percent_buffer) - 1] = '\0';
        is_valid = isValidPercent(percent_buffer, &percent_value);
    } while (!is_valid);

    for (int i = 0; i < stock_count; i++) {
        stocks[i]->price = stocks[i]->price * (1.0 - (percent_value / 100.0));
    }

    printf("Stock prices has dropped by %d%%.\n", percent_value);
}

void findLessExpensive(Stock **stocks, int stock_count) {
    // finds and prints the stock with the lowest price
    int min_index = 0;
    for (int i = 0; i < stock_count; i++) {
        if (stocks[i]->price < stocks[min_index]->price) {
            min_index = i;
        }
    }
    printf("Less expensive stock: %s - $%.2f\n", stocks[min_index]->name, stocks[min_index]->price);
}

void sortByPrice(Stock **stocks, int stock_count) {
    // creates a temporary pointer array to sort and print stocks
    // by price without changing the original array
    Stock **temp_array = (Stock **) malloc(stock_count * sizeof(Stock *));

    // initialize the temporary array with the original pointers
    for (int i = 0; i < stock_count; i++) {
        temp_array[i] = stocks[i];
    }

    // bubble-sort to sort pointers based on stock prices
    for (int i = 0; i < stock_count - 1; i++) {
        for (int j = 0; j < stock_count - i - 1; j++) {
            if (temp_array[j]->price > temp_array[j + 1]->price) {
                Stock *temp = temp_array[j];
                temp_array[j] = temp_array[j + 1];
                temp_array[j + 1] = temp;
            }
        }
    }
    // print the sorted results
    for (int i = 0; i < stock_count; i++) {
        printf("%d. %s - $%.2f\n", i+1, temp_array[i]->name,  temp_array[i]->price); }
    printf("Sorted by price.\n");
    // free the temporary dynamic array
    free(temp_array);
}

void sortByName(Stock **stocks, int stock_count) {
    // creates a temporary pointer array to sort and print
    // stocks alphabetically without changing the original array
    Stock **temp_array = (Stock **) malloc(stock_count * sizeof(Stock *));

    // initialize the temporary array with the original pointers
    for (int i = 0; i < stock_count; i++) {
        temp_array[i] = stocks[i];
    }

    // bubble-sort to sort pointers alphabetically using strcmp
    for (int i = 0; i < stock_count - 1; i++) {
        for (int j = 0; j < stock_count - i - 1; j++) {
            // strcmp returns > 0 if the first string comes after the second alphabetically
            if (strcmp(temp_array[j]->name, temp_array[j + 1]->name) > 0) {
                // swap pointers in the temporary array only
                Stock *temp = temp_array[j];
                temp_array[j] = temp_array[j + 1];
                temp_array[j + 1] = temp;
            }
        }
    }

    // print the sorted results
    for (int i = 0; i < stock_count; i++) {
        printf("%d. %s - $%.2f\n", i + 1, temp_array[i]->name, temp_array[i]->price); }
    printf("Sorted by name.\n");
    // free the temporary dynamic array
    free(temp_array);
}

int asciiSum(const char* str) {
    // calc and returns the sum of ASCII values of a string
    int sum = 0;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        sum += str[i]; }
    return sum;
}

void sortByAsciiSum(Stock **stocks, int stock_count) {
    // creates a temporary pointer array to sort and print
    // stocks by their ASCII sum without changing the original array
    Stock **temp_array = (Stock **) malloc(stock_count * sizeof(Stock *));

    // initialize the temporary array with the original pointers
    for (int i = 0; i < stock_count; i++) {
        temp_array[i] = stocks[i];
    }

    // bubble-sort to sort pointers based on the ASCII sum of stock names
    for (int i = 0; i < stock_count - 1; i++) {
        for (int j = 0; j < stock_count - i - 1; j++) {
            // compare the ASCII sums of adjacent stock names
            if (asciiSum(temp_array[j]->name) > asciiSum(temp_array[j + 1]->name)) {
                // swap pointers in the temporary array only
                Stock *temp = temp_array[j];
                temp_array[j] = temp_array[j + 1];
                temp_array[j + 1] = temp;
            }
        }
    }

    // print the sorted results
    for (int i = 0; i < stock_count; i++) {
        printf("%d. %s - $%.2f\n", i + 1, temp_array[i]->name, temp_array[i]->price); }
    printf("Sorted by ASCII sum.\n");

    // free the temporary dynamic array
    free(temp_array);
}

int isPalindrome(const char* str) {
    // returns 1 if the string is a palindrome, and 0 otherwise
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right) {
        // if characters at current positions don't match, it's not a palindrome
        if (str[left] != str[right]) {
            return 0;
        }
        left++;  // move forward
        right--; // move backward
    }
    return 1; // all characters matched - palindrome
}

void findPalindromes(Stock **stocks, int stock_count) {
    // iterates through all stocks and prints those with palindromic names
    for (int i = 0; i < stock_count; i++) {
        if (isPalindrome(stocks[i]->name)) {
            printf("Palindrome stock: %s\n", stocks[i]->name);
        }
    }
}