# Bank-System in C

> Console-based banking system written in C as the **final project for Programming Fundamentals**. Supports up to 20 users with full account management: registration, deposits, transfers, balance inquiry, PIN changes, and phone top-ups — all secured by phone number + PIN authentication.

---

## Features

| Feature | Description |
|---|---|
| User Registration | Stores name, phone number, PIN, and auto-generates a 16-digit card number |
| Deposit | Adds funds to the user's account balance |
| Balance Inquiry | Displays full name and current balance |
| Transfer | Sends funds to another card, with balance validation |
| PIN Change | Replaces the current PIN after authentication |
| Phone Top-Up | Sends credit to Movistar, Telcel, or AT&T numbers |

---

## Authentication

Every operation (except registration) requires the user to authenticate with:
- **10-digit phone number**
- **4-digit PIN**

The system validates credentials against all registered users before granting access.

---

## Data Structure

The system stores user data in parallel global arrays:

```c
char phones[MAX_USERS][11];         // Phone numbers
char pins[MAX_USERS][5];            // 4-digit PINs
char cards[MAX_USERS][17];          // Auto-generated 16-digit card numbers
char firstNames[MAX_USERS][20];
char firstLastNames[MAX_USERS][20];
char secondLastNames[MAX_USERS][20];
float balances[MAX_USERS];          // Account balances
```

> Maximum capacity: **20 users** (defined by `MAX_USERS`)

---

## How to Compile & Run

**Requirements:** GCC or any C99-compatible compiler

```bash
gcc -Wall -std=c99 -o banking_system banking_system.c
./banking_system
```

On Windows:
```bash
gcc -Wall -std=c99 -o banking_system.exe banking_system.c
banking_system.exe
```

---

## Menu

```
=== BANKING SYSTEM ===
1. Register
2. Deposit
3. Check balance
4. Transfer
5. Change PIN
6. Phone top-up
7. Exit
```

---

## Limitations

- Data is stored **in memory only** — all records are lost when the program exits (no file persistence).
- Transfers deduct from the sender's balance but do **not** credit an internal recipient account.
- `system("cls")` is Windows-specific — remove or replace with `system("clear")` on Linux/macOS.
- No encryption on PINs — this is an educational project, not production-ready.

---

## Concepts Applied

- Arrays and parallel data structures
- String manipulation without `<string.h>` comparisons (custom `stringsMatch`)
- Random number generation with `srand` / `rand`
- Input validation and control flow
- Modular programming with well-documented functions
- Console UI with `do-while` menu loop

---

*Final Project — Programming Fundamentals | C Language*
