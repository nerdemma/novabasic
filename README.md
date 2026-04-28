# Nova-Basic Interpreter

Nova-Basic is a lightweight, modular **BASIC programming language interpreter** developed in C for Linux/UNIX environments. It features a custom **Recursive Descent Parser** that handles complex arithmetic expressions and logical comparisons with proper operator precedence.

---

## 🚀 Features

* **Modular Design**: Code is cleanly separated into `src/` and `include/` directories for better maintainability.
* **Recursive Descent Parser**: Supports PEMDAS (parentheses, exponents, multiplication, division, addition, subtraction).
* **Dynamic Program Storage**: Uses a linked-list data structure to store and sort code lines automatically.
* **Logical Operations**: Built-in support for comparisons (`==`, `<>`, `<`, `>`, `<=`, `>=`).
* **Control Flow**: Includes `GOTO` for jumps and `IF...THEN` for conditional logic.
* **Symbol Table**: Manages variables from `A` to `Z` with floating-point precision.

---

## 📁 Project Structure

```text
nova-basic/
├── include/           # Header files (.h)
│   ├── common.h       # Structs and global constants
│   ├── interpreter.h  # Parser and execution logic
│   └── program.h      # Linked list management
├── src/               # Implementation files (.c)
│   ├── main.c         # REPL (Read-Eval-Print Loop)
│   ├── interpreter.c  # The "Brain" (Parser & Commands)
│   └── program.c      # Program memory management
└── Makefile           # Compilation script

## Installation & Building
* To build Nova-Basic, you need gcc and make installed on your system.

* 1. clone the repository. 

git clone [https://github.com/nerdemma/novabasic.git](https://github.com/nerdemma/novabasic.git)
cd nova-basic

* 2. compile
make

*3. run the interpreter
./nvbasic


## 📜 Language Reference

| Command | Description | Example |
| :--- | :--- | :--- |
| **PRINT** | Displays text or the result of an expression. | `PRINT (A + 5) * 2` |
| **LET** | Assigns a value or expression to a variable (A-Z). | `LET A = 50.5` |
| **IF** | Conditional execution based on a comparison. | `IF A > 10 THEN GOTO 100` |
| **GOTO** | Jumps execution to a specific line number. | `GOTO 20` |
| **INPUT** | Prompts the user to enter a numeric value. | `INPUT B` |
| **LIST** | Prints the current program in memory. | `LIST` |
| **RUN** | Executes the program from the first line. | `RUN` |
| **NEW** | Clears all lines from the current program. | `NEW` |
| **REM** | Adds a comment (ignored during execution). | `REM This is a loop` |
| **EXIT** | Quits the interpreter. | `EXIT` |

---

## 💻 Example Program

Type the following in the terminal to create a simple loop that prints numbers from **1 to 5**:

```basic
> 10 LET A = 1
> 20 PRINT A
> 30 LET A = A + 1
> 40 IF A <= 5 THEN GOTO 20
> 50 PRINT "Done!"
> RUN

## Contributions
* Contributions are welcome! If you find a bug or want to add a new command (like FOR...NEXT or LOAD/SAVE), feel free to fork the repository and submit a pull request.

## License
* This program is under GPL-3 License.
