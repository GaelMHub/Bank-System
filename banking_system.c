/*
 * banking_system.c
 * Final Project - Programming Fundamentals
 *
 * A simple console-based banking system supporting up to 20 users.
 * Each user has a name, phone number, PIN, auto-generated card number,
 * and an account balance.
 *
 * Features:
 *   - User registration
 *   - Balance deposit
 *   - Balance inquiry
 *   - Fund transfer
 *   - PIN change
 *   - Phone credit top-up
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Maximum number of users the system can hold */
#define MAX_USERS 20

/* ---------- Global user data ---------- */
char phones[MAX_USERS][11];       /* 10-digit phone number + null terminator */
char pins[MAX_USERS][5];          /* 4-digit PIN + null terminator */
char cards[MAX_USERS][17];        /* 16-digit card number + null terminator */
char firstNames[MAX_USERS][20];
char firstLastNames[MAX_USERS][20];
char secondLastNames[MAX_USERS][20];
float balances[MAX_USERS];
int totalUsers = 0;

/* ---------- Helper functions ---------- */

/*
 * generateCardNumber
 * Fills `card` with a random 16-digit card number string.
 * The first digit is always 1-9; the rest are 0-9.
 */
void generateCardNumber(char card[]) {
    int i;
    card[0] = (rand() % 9) + 1 + '0';
    for (i = 1; i < 16; i++) {
        card[i] = (rand() % 10) + '0';
    }
    card[16] = '\0';
}

/*
 * stringsMatch
 * Returns 1 if strings a and b are equal up to `len` characters, 0 otherwise.
 */
int stringsMatch(char a[], char b[], int len) {
    int i;
    for (i = 0; i < len; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

/*
 * authenticate
 * Prompts for phone number and PIN, searches for a matching user,
 * and returns that user's index. Returns -1 if no match is found.
 */
int authenticate() {
    char phoneInput[11], pinInput[5];
    int i;

    printf("Phone number: ");
    scanf("%10s", phoneInput);
    printf("PIN: ");
    scanf("%4s", pinInput);

    for (i = 0; i < totalUsers; i++) {
        if (stringsMatch(phoneInput, phones[i], 11) &&
            stringsMatch(pinInput, pins[i], 5)) {
            return i;
        }
    }

    printf("Incorrect credentials. Please try again.\n");
    return -1;
}

/* ---------- Menu operations ---------- */

/*
 * registerUser
 * Collects name, last names, PIN, and phone number for a new user.
 * Validates that the PIN is exactly 4 digits and the phone number
 * is exactly 10 digits. On success, assigns a random card number
 * and sets the initial balance to 0.
 */
void registerUser() {
    int index, i, pinLen = 0, phoneLen = 0;

    if (totalUsers >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return;
    }

    index = totalUsers;

    printf("First name: ");
    scanf("%19s", firstNames[index]);

    printf("First last name: ");
    scanf("%19s", firstLastNames[index]);

    printf("Second last name: ");
    scanf("%19s", secondLastNames[index]);

    printf("PIN (4 digits): ");
    scanf("%4s", pins[index]);

    printf("Phone number (10 digits): ");
    scanf("%10s", phones[index]);

    /* Validate lengths */
    for (i = 0; pins[index][i] != '\0'; i++) pinLen++;
    for (i = 0; phones[index][i] != '\0'; i++) phoneLen++;

    if (pinLen != 4 || phoneLen != 10) {
        printf("Invalid data. Please try again.\n");
        return;
    }

    generateCardNumber(cards[index]);
    balances[index] = 0.0f;
    totalUsers++;

    printf("Registration complete. Your card number is: %s\n", cards[index]);
}

/*
 * checkBalance
 * Authenticates the user and displays their full name and current balance.
 */
void checkBalance() {
    int user = authenticate();
    if (user == -1) return;

    printf("=== ACCOUNT INFORMATION ===\n");
    printf("Name   : %s %s %s\n",
        firstNames[user], firstLastNames[user], secondLastNames[user]);
    printf("Balance: $%.2f\n", balances[user]);
}

/*
 * deposit
 * Authenticates the user and adds a positive amount to their balance.
 */
void deposit() {
    float amount;
    int user = authenticate();
    if (user == -1) return;

    printf("Amount to deposit: $");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount.\n");
        return;
    }

    balances[user] += amount;
    printf("Deposit successful. New balance: $%.2f\n", balances[user]);
}

/*
 * transfer
 * Authenticates the user, asks for a destination card number and amount,
 * and deducts the amount from the sender's balance if funds are sufficient.
 * Note: this version does not credit another internal account.
 */
void transfer() {
    char destinationCard[17];
    float amount;
    int user = authenticate();
    if (user == -1) return;

    printf("=== ACCOUNT INFORMATION ===\n");
    printf("Name   : %s %s %s\n",
        firstNames[user], firstLastNames[user], secondLastNames[user]);
    printf("Balance: $%.2f\n", balances[user]);
    printf("===========================\n");

    printf("Destination card number: ");
    scanf("%16s", destinationCard);

    printf("Amount to transfer: $");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount.\n");
        return;
    }

    if (amount > balances[user]) {
        printf("Insufficient funds.\n");
        return;
    }

    balances[user] -= amount;
    printf("Transfer of $%.2f completed successfully.\n", amount);
    printf("Remaining balance: $%.2f\n", balances[user]);
}

/*
 * changePin
 * Authenticates the user and replaces their current PIN with a new one.
 */
void changePin() {
    char newPin[5];
    int user, i;

    user = authenticate();
    if (user == -1) return;

    printf("Enter new PIN (4 digits): ");
    scanf("%4s", newPin);

    for (i = 0; i < 5; i++) {
        pins[user][i] = newPin[i];
    }

    printf("PIN updated successfully.\n");
}

/*
 * topUp
 * Authenticates the user and performs a phone credit top-up.
 * Deducts the specified amount from the user's balance.
 */
void topUp() {
    char destination[11];
    float amount;
    int carrier;
    int user = authenticate();
    if (user == -1) return;

    printf("=== ACCOUNT INFORMATION ===\n");
    printf("Name   : %s %s %s\n",
        firstNames[user], firstLastNames[user], secondLastNames[user]);
    printf("Balance: $%.2f\n", balances[user]);
    printf("===========================\n");

    printf("Select carrier:\n");
    printf("  1. Movistar\n");
    printf("  2. Telcel\n");
    printf("  3. AT&T\n");
    printf("Choice: ");
    scanf("%d", &carrier);

    if (carrier < 1 || carrier > 3) {
        printf("Invalid carrier option.\n");
        return;
    }

    printf("Phone number to top up: ");
    scanf("%10s", destination);

    printf("Amount: $");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount.\n");
        return;
    }

    if (amount > balances[user]) {
        printf("Insufficient funds.\n");
        return;
    }

    balances[user] -= amount;
    printf("Top-up of $%.2f sent to %s successfully.\n", amount, destination);
    printf("Remaining balance: $%.2f\n", balances[user]);
}

/* ---------- Entry point ---------- */

int main() {
    int option;
    srand((unsigned int)time(NULL));

    do {
        printf("\n=== BANKING SYSTEM ===\n");
        printf("1. Register\n");
        printf("2. Deposit\n");
        printf("3. Check balance\n");
        printf("4. Transfer\n");
        printf("5. Change PIN\n");
        printf("6. Phone top-up\n");
        printf("7. Exit\n");
        printf("Option: ");
        scanf("%d", &option);

        switch (option) {
            case 1: system("cls"); registerUser(); break;
            case 2: system("cls"); deposit();      break;
            case 3: system("cls"); checkBalance(); break;
            case 4: system("cls"); transfer();     break;
            case 5: system("cls"); changePin();    break;
            case 6: system("cls"); topUp();        break;
            case 7: printf("Goodbye.\n");          break;
            default: printf("Invalid option. Please enter 1-7.\n"); break;
        }

    } while (option != 7);

    return 0;
}