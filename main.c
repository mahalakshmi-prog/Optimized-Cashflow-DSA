#include <stdio.h>
#include "cashflow.h"

int main() {
    printf("Cashflow Minimizer\n");

    inputPeople();
    inputTransactions();
    minimizeCashFlow();

    return 0;
}
