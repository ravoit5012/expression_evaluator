# Expression Evaluator for Rationals in E++

This project implements an **Expression Evaluator for Rationals** using expression trees, a symbol table, and unlimited precision arithmetic in C++.

## 💡 Key Functionalities

- **UnlimitedInt Class**
  - Handles arbitrarily large integers
  - Supports: Addition, Subtraction, Multiplication, Division, Modulus

- **UnlimitedRational Class**
  - Represents rational numbers as a pair of `UnlimitedInt` numerator and denominator
  - Supports arithmetic operations on rational numbers
  - Maintains simplified and canonical rational forms

- **Expression Tree**
  - Parses fully parenthesized infix expressions using recursive descent
  - Constructs a binary expression tree
  - Nodes can be: `ADD`, `SUB`, `MUL`, `DIV`, `VAL`, `VAR`

- **Symbol Table**
  - Implemented using an unbalanced Binary Search Tree (BST)
  - Stores variable names and their evaluated `UnlimitedRational` values
  - Supports: `insert`, `search`, `remove`, `get_size`

- **Evaluator**
  - Parses E++ style statements (e.g., `x := (a + b)`)
  - Builds expression trees and evaluates them
  - Maintains state via the symbol table

## 🗂️ Project Structure

```
.
├── ulimitedint.cpp          # Arbitrary precision integer arithmetic
├── ulimitedrational.cpp     # Rational arithmetic using UnlimitedInt
├── exprtreenode.cpp         # Node class for expression tree
├── symtable.cpp             # BST implementation for symbol table
├── evaluator.cpp            # Parser and evaluator logic
├── entry.cpp                # (Optional) Main file for running tests
```

## 🚀 How to Compile and Run

### Compile

```bash
g++ -std=c++17 -o program entry.cpp evaluator.cpp exprtreenode.cpp main.cpp symtable.cpp ulimitedint.cpp ulimitedrational.cpp
```

### Run

```bash
./program
```

Provide E++ style statements as input in main.cpp. For example:

```
// Test 1: x = (5 + 3)
    vector<string> code1 = {"x", "=", "(", "5", "+", "3", ")"};
    evaluator.parse(code1);
    evaluator.eval();
```

### Output

- Evaluated values are stored in the symbol table and displayed as defined in main.cpp

---

> Data Structures and Algorithms Project.