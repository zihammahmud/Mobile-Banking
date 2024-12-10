#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Transaction {
    char type[20];
    float amount;
    struct Transaction* next;
} Transaction;

typedef struct User {
    char username[50];
    char password[50];
    float balance;
    Transaction* transactions;
    struct User* next;
} User;

User* head = NULL;
User* loggedInUser = NULL;

User* createUser(char* username, char* password) {
    User* newUser = (User*)malloc(sizeof(User));
    strcpy(newUser->username, username);
    strcpy(newUser->password, password);
    newUser->balance = 0.0;
    newUser->transactions = NULL;
    newUser->next = NULL;
    return newUser;
}

void addTransaction(User* user, char* type, float amount) {
    Transaction* newTransaction = (Transaction*)malloc(sizeof(Transaction));
    strcpy(newTransaction->type, type);
    newTransaction->amount = amount;
    newTransaction->next = user->transactions;
    user->transactions = newTransaction;
}

void registerAccount() {
    char username[50], password[50];
    printf("Enter a username: ");
    scanf("%s", username);
    printf("Enter a password: ");
    scanf("%s", password);

    User* newUser = createUser(username, password);
    newUser->next = head;
    head = newUser;

    printf("Account registered successfully!\n");
}

void login() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    User* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->username, username) == 0 && strcmp(temp->password, password) == 0) {
            loggedInUser = temp;
            printf("Logged in successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Invalid username or password.\n");
}

void accountDetails() {
    if (loggedInUser == NULL) {
        printf("No user is logged in.\n");
        return;
    }
    printf("Username: %s\n", loggedInUser->username);
    printf("Balance: $%.2f\n", loggedInUser->balance);
}

void depositMoney() {
    if (loggedInUser == NULL) {
        printf("No user is logged in.\n");
        return;
    }
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);
    loggedInUser->balance += amount;
    addTransaction(loggedInUser, "Deposit", amount);
    printf("Money deposited successfully!\n");
}

void sendMoney() {
    if (loggedInUser == NULL) {
        printf("No user is logged in.\n");
        return;
    }
    char recipientUsername[50];
    float amount;
    printf("Enter recipient's username: ");
    scanf("%s", recipientUsername);
    printf("Enter amount to send: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Amount should be greater than zero.\n");
        return;
    }

    if (loggedInUser->balance < amount) {
        printf("Insufficient balance.\n");
        return;
    }

    User* recipient = head;
    while (recipient != NULL) {
        if (strcmp(recipient->username, recipientUsername) == 0) {
            loggedInUser->balance -= amount;
            recipient->balance += amount;
            addTransaction(loggedInUser, "Send", -amount);
            addTransaction(recipient, "Receive", amount);
            printf("Money sent successfully!\n");
            return;
        }
        recipient = recipient->next;
    }
    printf("Recipient not found.\n");
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Register\n2. Login\n3. Account Details\n4. Deposit Money\n5. Send Money\n6. Logout\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                registerAccount();
                break;
            case 2:
                login();
                break;
            case 3:
                accountDetails();
                break;
            case 4:
                depositMoney();
                break;
            case 5:
                sendMoney();
                break;
            case 6:
                loggedInUser = NULL;
                printf("Logged out successfully.\n");
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}