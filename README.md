# Expression Parser and Evaluator in C++

## Overview
A C++ implementation of a Recursive Descent Parser that performs lexical analysis, syntax analysis, parse tree generation, expression evaluation, and symbol table management for arithmetic expressions.

## Features
- Lexical Analysis (Tokenization)
- Recursive Descent Parsing
- Parse Tree Generation
- Expression Evaluation
- Variable Assignment Support
- Symbol Table Management
- Operator Precedence Handling
- Syntax Error Detection

## Supported Operations
- Addition (`+`)
- Subtraction (`-`)
- Multiplication (`*`)
- Division (`/`)
- Assignment (`=`)

## Grammar

```text
Statement  → ID = Expression | Expression
Expression → Term { (+|-) Term }
Term       → Factor { (*|/) Factor }
Factor     → NUMBER | ID | ( Expression )
```

## Technologies Used
- C++
- STL (Vector, String, Unordered Map)
- Recursive Descent Parsing
- Tree Data Structures

## Example

### Input
```text
x = 5
y = 10
z = x + y * 2
```

### Output
```text
x = 5
y = 10
z = 25
```

## Project Workflow
1. Tokenize the input.
2. Parse tokens using Recursive Descent Parsing.
3. Generate a Parse Tree.
4. Evaluate the expression.
5. Store and retrieve variables using a Symbol Table.

## Learning Outcomes
- Compiler Design Fundamentals
- Lexical Analysis
- Syntax Analysis
- Parse Tree Construction
- Expression Evaluation
- Symbol Table Implementation
- Error Handling Techniques

## Compilation & Execution

```bash
g++ parser.cpp -o parser
./parser
```

## Future Enhancements
- Floating Point Numbers
- Unary Operators
- Exponentiation (`^`)
- Boolean Expressions
- Functions and Control Statements
- Abstract Syntax Tree (AST)

## Author
Dev

**Domain:** Compiler Design | Programming Languages | Data Structures & Algorithms  
**Language:** C++


## Sample Output

Example execution showing tokenization, parse tree generation, symbol table updates, and expression evaluation.
<img width="1191" height="802" alt="Screenshot 2026-06-06 at 10 00 59" src="https://github.com/user-attachments/assets/87ffd1a3-d104-4ed8-be73-1ceaacecb344" />
<img width="1188" height="783" alt="Screenshot 2026-06-06 at 10 03 05" src="https://github.com/user-attachments/assets/d39f88c8-ac8f-4eac-a865-29664083e06e" />
<img width="1192" height="784" alt="Screenshot 2026-06-06 at 10 03 30" src="https://github.com/user-attachments/assets/da5515fb-971f-44f1-9cd3-87403aa000cb" />
<img width="1193" height="782" alt="Screenshot 2026-06-06 at 10 04 19" src="https://github.com/user-attachments/assets/b0a24361-9a60-467e-b434-698e3b22b063" />
<img width="1189" height="546" alt="Screenshot 2026-06-06 at 10 04 45" src="https://github.com/user-attachments/assets/2a91b873-c05f-4998-bf2a-975398cd6fc0" />
