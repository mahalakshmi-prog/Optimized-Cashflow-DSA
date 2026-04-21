#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "cashflow.h"

int n;
float adjMatrix[MAX_PEOPLE][MAX_PEOPLE];
char names[MAX_PEOPLE][MAX_NAME_LEN];

/* ---------------- Utility Functions ---------------- */

// Trim leading and trailing spaces
void trimSpaces(char *str) {
    char *start = str;
    while (isspace(*start)) start++;
    if (start != str)
        memmove(str, start, strlen(start) + 1);

    int end = strlen(str) - 1;
    while (end >= 0 && isspace(str[end]))
        str[end--] = '\0';
}

// Check duplicate names
int isDuplicateName(const char *name, int uptoIndex) {
    for (int i = 0; i < uptoIndex; i++)
        if (strcasecmp(names[i], name) == 0)
            return 1;
    return 0;
}

/* ---------------- Input People ---------------- */

void inputPeople() {
    memset(adjMatrix, 0, sizeof(adjMatrix));
    memset(names, 0, sizeof(names));

    printf("Enter number of people (max %d): ", MAX_PEOPLE);
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        printf("\nEnter name of person %d:\n", i + 1);

        while (1) {
            printf("Name: ");
            fgets(names[i], MAX_NAME_LEN, stdin);
            names[i][strcspn(names[i], "\n")] = '\0';
            trimSpaces(names[i]);

            if (strlen(names[i]) == 0) {
                printf("Name cannot be blank.\n");
                continue;
            }
            if (isDuplicateName(names[i], i)) {
                printf("This name is already registered!\n");
                continue;
            }
            break;
        }
    }
}

/* ---------------- Input Transactions (ID-BASED) ---------------- */

void inputTransactions() {
    int m;
    printf("\nEnter number of ACTUAL transactions that occurred: ");
    scanf("%d", &m);

    printf("\nRegistered people (use IDs for transactions):\n");
    for (int i = 0; i < n; i++)
        printf("  %d -> %s\n", i + 1, names[i]);

    printf("\nNOTE:\n");
    printf("Enter transactions using numeric IDs.\n");
    printf("Format: <payerID> <receiverID> <amount>\n");
    printf("Example: 1 2 500 means Person 1 pays Person 2 amount 500\n");

    for (int i = 0; i < m; i++) {
        int fromID, toID;
        float amount;

        printf("\nTransaction %d: ", i + 1);

        if (scanf("%d %d %f", &fromID, &toID, &amount) != 3) {
            printf("Invalid input format!\n");
            i--;
            while (getchar() != '\n');
            continue;
        }

        if (fromID < 1 || fromID > n || toID < 1 || toID > n) {
            printf("Invalid ID! Use IDs between 1 and %d\n", n);
            i--;
            continue;
        }

        if (fromID == toID) {
            printf("Sender and receiver cannot be the same!\n");
            i--;
            continue;
        }

        if (amount <= 0) {
            printf("Amount must be positive!\n");
            i--;
            continue;
        }

        adjMatrix[fromID - 1][toID - 1] += amount;
    }

    /* ----- Print Adjacency Matrix ----- */
    printf("\nTransaction Graph (Adjacency Matrix)\n");
    printf("%15s", "");
    for (int i = 0; i < n; i++)
        printf("%15s", names[i]);
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%15s", names[i]);
        for (int j = 0; j < n; j++)
            printf("%15.2f", adjMatrix[i][j]);
        printf("\n");
    }

    /* ----- Print Adjacency List ----- */
    printf("\nTransaction Graph (Adjacency List)\n");
    for (int i = 0; i < n; i++) {
        printf("%s -> ", names[i]);
        int has = 0;
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i][j] > 0.001) {
                printf("%s(%.2f) ", names[j], adjMatrix[i][j]);
                has = 1;
            }
        }
        if (!has) printf("No transactions");
        printf("\n");
    }
}

/* ---------------- Minimize Cash Flow ---------------- */

void minimizeCashFlow() {
    float balance[MAX_PEOPLE] = {0};

    for (int p = 0; p < n; p++)
        for (int q = 0; q < n; q++)
            balance[p] += adjMatrix[q][p] - adjMatrix[p][q];

    printf("\nSimplified Transactions\n");

    while (1) {
        int credit = 0, debit = 0;
        for (int i = 1; i < n; i++) {
            if (balance[i] > balance[credit]) credit = i;
            if (balance[i] < balance[debit]) debit = i;
        }

        if (fabs(balance[credit]) < 1e-6 &&
            fabs(balance[debit]) < 1e-6)
            break;

        float minAmt = fmin(fabs(balance[credit]), fabs(balance[debit]));

        balance[credit] -= minAmt;
        balance[debit] += minAmt;

        printf("%s should pay %.2f to %s\n",
               names[debit], minAmt, names[credit]);
    }

    printf("\nAll debts settled successfully!\n");
}

/* ---------------- Fixed Budget Check ---------------- */

int fixed_budget() {
    printf("\nFixed Budget Validation (Total = 1000)\n");

    float outgoing[MAX_PEOPLE] = {0};
    float total = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            outgoing[i] += adjMatrix[i][j];
            total += adjMatrix[i][j];
        }

    if (fabs(total - 1000) > 0.001) {
        printf("ERROR: Total spending = %.2f (must be exactly 1000)\n", total);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (fabs(outgoing[i] - 1000) < 0.001) {
            printf("ERROR: %s alone spent entire budget\n", names[i]);
            return 0;
        }
    }

    printf("Budget validation successful!\n");
    return 1;
}
