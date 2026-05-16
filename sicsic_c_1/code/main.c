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


//Function Prototype
int step_0_validate(char *input);
void printMenu();
int conv_selection_to_int(char *input);
void addStock(Stock **stocks, int* ptr_stock_count);
int isValidName(const char* str_buf);
int isValidPrice(const char *str_buf, float *ptr_price);

int main() {
    int tries = 5;
    int choice = -1;
    char buffer[5];
    int stock_count = 0;

    // 1. print menu
    printMenu();
    Stock **stocks = (Stock **) malloc(MAX_STOCKS * sizeof(Stock *));  // create the array of stocks


    while (tries && choice != 10) {
        // 2. fgets
        fgets(buffer, 5, stdin);
        buffer[strlen(buffer) - 1] = '\0';  // remove the \n

        // 3. validate
        int valid_input = step_0_validate(buffer);
        if (valid_input != 0) {
            tries--;
            printf("The input should be non negative upto 2 digits number, %d tries are left!\n", tries);
        } else {
            tries = 5; // reset tries after a proper input
            int choise = conv_selection_to_int(buffer);
        }

        // 4. if invalid → tries--
        // 5. if valid → convert, reset tries, handle choice
    }
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
                    "Please enter a number between 0-99:  ");
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