#ifndef CASHFLOW_H
#define CASHFLOW_H

#define MAX_PEOPLE 10
#define MAX_NAME_LEN 50

// Global variables
extern int n;
extern float adjMatrix[MAX_PEOPLE][MAX_PEOPLE];
extern char names[MAX_PEOPLE][MAX_NAME_LEN];

// Function declarations
void trimSpaces(char *str);

int findPersonIndexByName(const char *name);
int isDuplicateName(const char *name, int uptoIndex);

void inputPeople(void);
void inputTransactions(void);
void minimizeCashFlow(void);
int fixed_budget(void);

#endif
