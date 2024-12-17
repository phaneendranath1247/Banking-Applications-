#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Structure for bank using required data items
struct bank {
    char name[100];
    int number;
    int balance;
    struct bank *next;
};

typedef struct bank Bank;

Bank *first = NULL;
Bank *last = NULL;

// Function declarations
void read();
void display();
void balance();
void withdraw();
void search();
void deposit();
void update();
void transfer();
void load_from_file();
void save_to_file();

// Global variables
int acc_num;
int count = 0;

// Main function
int main() {
    int choice;

    load_from_file(); // Load account details from the file at the start

    for (;;) {
        printf("\nBanking System Menu:\n");
        printf("1. Enter Account Details\n");
        printf("2. Display All Accounts\n");
        printf("3. Check Balance\n");
        printf("4. Withdraw Money\n");
        printf("5. Search Account\n");
        printf("6. Deposit Money\n");
        printf("7. Update Account\n");
        printf("8. Transfer Money\n");
        printf("9. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                read();
                break;
            case 2:
                display();
                break;
            case 3:
                balance();
                break;
            case 4:
                withdraw();
                break;
            case 5:
                search();
                break;
            case 6:
                deposit();
                break;
            case 7:
                update();
                break;
            case 8:
                transfer();
                break;
            case 9:
                save_to_file(); // Save all updates to the file before exiting
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// Load account details from file
void load_from_file() {
    FILE *file = fopen("bank_accounts.txt", "r");
    if (file == NULL) {
        printf("No existing account data found. Starting fresh.\n");
        return;
    }

    while (!feof(file)) {
        Bank *new = (Bank *)malloc(sizeof(Bank));
        if (fscanf(file, "%99[^,],%d,%d\n", new->name, &new->number, &new->balance) == 3) {
            new->next = NULL;
            if (first == NULL) {
                first = last = new;
            } else {
                last->next = new;
                last = new;
            }
            count++;
        }
    }
    fclose(file);
}

// Save all account details to file in tabular format
void save_to_file() {
    FILE *file = fopen("bank_accounts.txt", "w");
    if (file == NULL) {
        printf("Error: Unable to save account data.\n");
        return;
    }

    // Write the table header
    fprintf(file, "%-25s %-20s %-10s\n", "Account Holder Name", "Account Number", "Balance");

    Bank *temp = first;
    while (temp != NULL) {
        // Write the account details in a tabular format
        fprintf(file, "%-25s %-20d %-10d\n", temp->name, temp->number, temp->balance);
        temp = temp->next;
    }
    fclose(file);
}

// Function to read account details
void read() {
    Bank *new = (Bank *)malloc(sizeof(Bank));
    count++;

    printf("Enter the account holder name:\n");
    getchar();
    scanf("%[^\n]s", new->name);
    printf("Enter the account number:\n");
    scanf("%d", &new->number);
    printf("Enter the initial balance:\n");
    scanf("%d", &new->balance);

    new->next = NULL;
    if (first == NULL) {
        first = last = new;
    } else {
        last->next = new;
        last = new;
    }

    save_to_file(); // Save after adding a new account
}

// Display all accounts
void display() {
    printf("We have %d records in the bank:\n", count);

    Bank *temp = first;
    while (temp != NULL) {
        printf("Account Holder Details:\n");
        printf("Name: %s\n", temp->name);
        printf("Account Number: %d\n", temp->number);
        printf("Balance: %d\n", temp->balance);
        printf("-------------------------------\n");
        temp = temp->next;
    }
}

// Check account balance
void balance() {
    printf("Enter the account number to check balance:\n");
    scanf("%d", &acc_num);
    Bank *temp = first;
    while (temp != NULL) {
        if (acc_num == temp->number) {
            printf("The balance in account %d is: %d\n", temp->number, temp->balance);
            return;
        }
        temp = temp->next;
    }
    printf("Account not found.\n");
}

// Withdraw money
void withdraw() {
    int amt;
    printf("Enter the account number to withdraw from:\n");
    scanf("%d", &acc_num);
    Bank *temp = first;

    while (temp != NULL) {
        if (acc_num == temp->number) {
            printf("Enter the amount to withdraw:\n");
            scanf("%d", &amt);
            if (amt > temp->balance) {
                printf("Insufficient balance.\n");
            } else {
                temp->balance -= amt;
                printf("Withdrawal successful. New balance is: %d\n", temp->balance);
                save_to_file(); // Update file after withdrawal
            }
            return;
        }
        temp = temp->next;
    }
    printf("Account not found.\n");
}

// Deposit money
void deposit() {
    int amount;
    printf("Enter the account number to deposit into:\n");
    scanf("%d", &acc_num);

    Bank *temp = first;
    while (temp != NULL) {
        if (acc_num == temp->number) {
            printf("Enter the amount to deposit:\n");
            scanf("%d", &amount);
            if (amount > 0) {
                temp->balance += amount;
                printf("Deposit successful. New balance is: %d\n", temp->balance);
                save_to_file(); // Update file after deposit
            } else {
                printf("Invalid amount.\n");
            }
            return;
        }
        temp = temp->next;
    }
    printf("Account not found.\n");
}

// Search for an account
void search() {
    printf("Enter the account number to search:\n");
    scanf("%d", &acc_num);
    Bank *temp = first;

    while (temp != NULL) {
        if (acc_num == temp->number) {
            printf("Account Found!\n");
            printf("Name: %s\n", temp->name);
            printf("Account Number: %d\n", temp->number);
            printf("Balance: %d\n", temp->balance);
            return;
        }
        temp = temp->next;
    }
    printf("Account not found.\n");
}

// Update account holder name
void update() {
    char name[100];
    printf("Enter the account number to update:\n");
    scanf("%d", &acc_num);

    Bank *temp = first;
    while (temp != NULL) {
        if (acc_num == temp->number) {
            printf("Enter the new name:\n");
            getchar();
            scanf("%[^\n]s", name);
            strcpy(temp->name, name);
            printf("Name updated successfully.\n");
            save_to_file(); // Update file after modification
            return;
        }
        temp = temp->next;
    }
    printf("Account not found.\n");
}

// Transfer money between accounts
void transfer() {
    int source, destination, credit;
    printf("Enter the amount to transfer:\n");
    scanf("%d", &credit);

    printf("Enter the account number to debit from:\n");
    scanf("%d", &source);

    printf("Enter the account number to credit to:\n");
    scanf("%d", &destination);

    Bank *temp = first;
    Bank *debit_account = NULL, *credit_account = NULL;

    while (temp != NULL) {
        if (temp->number == source) debit_account = temp;
        if (temp->number == destination) credit_account = temp;
        temp = temp->next;
    }

    if (debit_account && credit_account) {
        if (debit_account->balance >= credit) {
            debit_account->balance -= credit;
            credit_account->balance += credit;
            printf("Transfer successful!\n");
            save_to_file(); // Update file after transfer
        } else {
            printf("Insufficient balance in source account.\n");
        }
    } else {
        printf("Account not found.\n");
    }
}
