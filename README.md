# CashFlow Minimizer (C | DSA Project)

## Project Overview
CashFlow Minimizer is a C-based program that minimizes the number of transactions required to settle debts among a group of people.

The project models transactions as a directed graph using an adjacency matrix and applies a greedy cashflow minimization algorithm to compute simplified settlements efficiently.

---

## Problem Statement
In group expense scenarios such as trips, events,or shared spending, multiple transactions between people make final settlement complex and error-prone.

This project simplifies the settlement process by:
- Calculating the net balance for each participant
- Reducing multiple real-world transactions into the minimum number of required transfers
- Ensuring correctness using a greedy algorithm

---

## Key Features
- Uses numeric **IDs instead of names** for faster and simpler transaction input
- Case-insensitive name handling during registration
- Transaction graph representation using:
  - Adjacency Matrix
  - Adjacency List
- Net balance computation for each participant
- Greedy algorithm for minimizing cashflow
- Floating-point precision handling
- Clear and user-friendly console interaction

---

## Validation Rules
- Number of people must be within the allowed limit
- Names must be unique (case-insensitive)
- Sender and receiver IDs cannot be the same
- Transaction amount must be positive
- Invalid formats are detected and re-prompted

---

## Algorithm Used
1. Store all transactions in an adjacency matrix
2. Compute net balance for each person:
   - Net Balance = Incoming − Outgoing
3. Identify:
   - Maximum creditor (highest positive balance)
   - Maximum debtor (most negative balance)
4. Transfer the minimum possible amount between them
5. Repeat until all balances become zero

This greedy approach minimizes the total number of transactions.

---

## Data Structures Used
- Arrays
- Adjacency Matrix
- Adjacency List

---

## Project Structure
```CashFlow_Minimizer/
├── main.c // Program entry point
├── cashflow.c // Core cashflow minimization logic
├── cashflow.h // Function declarations and constants
└── README.md // Project documentation ```
