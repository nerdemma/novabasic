# Nova-Basic 

[![License: GPL-3.0](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

A lightweight, modular BASIC programming language interpreter written in C for Linux/UNIX environments. Nova-Basic features a custom **Recursive Descent Parser** capable of handling complex arithmetic expressions and logical comparisons with proper operator precedence.

---

## 🌟 Features

- **Modular Architecture**: Clean separation between source files (`src/`) and headers (`include/`) for enhanced maintainability
- **Recursive Descent Parser**: Full support for PEMDAS operator precedence (Parentheses, Exponents, Multiplication, Division, Addition, Subtraction)
- **Dynamic Program Storage**: Automatic line sorting using linked-list data structures
- **Logical Operations**: Built-in comparison operators (`==`, `<>`, `<`, `>`, `<=`, `>=`)
- **Control Flow**: `GOTO` for unconditional jumps and `IF...THEN` for conditional branching
- **Symbol Table**: Variable management (A-Z) with floating-point precision
- **Interactive REPL**: Read-Eval-Print Loop for immediate code execution

---

## 📁 Project Structure
nova-basic/
├── include/           # Header files
│   ├── common.h       # Shared structs and global constants
│   ├── interpreter.h  # Parser and execution logic declarations
│   └── program.h      # Linked list management interface
├── src/               # Implementation files
│   ├── main.c         # REPL (Read-Eval-Print Loop)
│   ├── interpreter.c  # Core parser and command execution
│   └── program.c      # Program memory management
└── Makefile           # Build automation script

---

## 🛠️ Installation & Building

### Prerequisites

- `gcc` (GNU Compiler Collection)
- `make`
- Linux/UNIX environment

### Build Instructions

1. **Clone the repository**
```bash
   git clone https://github.com/nerdemma/novabasic.git
   cd nova-basic
```

2. **Compile the project**
```bash
   make
```

3. **Run the interpreter**
```bash
   ./nvbasic
```

4. **Clean build artifacts** (optional)
```bash
   make clean
```

---

## 📜 Language Reference

### Commands

| Command | Description | Example |
|---------|-------------|---------|
| `PRINT` | Displays text or evaluates and prints an expression | `PRINT (A + 5) * 2` |
| `LET` | Assigns a value or expression result to a variable (A-Z) | `LET A = 50.5` |
| `IF...THEN` | Executes a statement conditionally based on comparison | `IF A > 10 THEN GOTO 100` |
| `GOTO` | Jumps execution to a specified line number | `GOTO 20` |
| `INPUT` | Prompts user for numeric input and stores in a variable | `INPUT B` |
| `LIST` | Displays all program lines currently in memory | `LIST` |
| `RUN` | Executes the stored program from the first line | `RUN` |
| `NEW` | Clears all program lines from memory | `NEW` |
| `REM` | Comment line (ignored during execution) | `REM This is a loop` |
| `HELP` | List of commands available | `HELP` |
| `HELP` | Version of program, Lisence and info about the author. | `ABOUT` |
| `EXIT` `END` `QUIT` | Terminates the interpreter session | `EXIT` `END` `QUIT` |

### Operators

**Arithmetic**: `+`, `-`, `*`, `/`, `^` (exponentiation)

**Comparison**: `==`, `<>`, `<`, `>`, `<=`, `>=`

**Precedence**: Follows standard mathematical order (PEMDAS/BODMAS)

---

## 💻 Example Programs

### Simple Counter Loop

Prints numbers from 1 to 5:

```basic
10 LET A = 1
20 PRINT A
30 LET A = A + 1
40 IF A <= 5 THEN GOTO 20
50 PRINT "Done!"
```

Run with:
```basic
RUN
```

**Output**:
1
2
3
4
5
Done!

### Interactive Input

```basic
10 PRINT "Enter a number:"
20 INPUT X
30 LET Y = X * 2
40 PRINT "Double of your number is:"
50 PRINT Y
```

---

## 🚧 Roadmap

Future enhancements being considered:

- [ ] `GOSUB`/`RETURN` for subroutines
- [ ] `LOAD`/`SAVE` for program persistence
- [ ] String variable support
- [ ] Array support
- [ ] Enhanced error messages with line numbers

---

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. **Fork** the repository
2. **Create** a feature branch (`git checkout -b feature/amazing-feature`)
3. **Commit** your changes (`git commit -m 'Add some amazing feature'`)
4. **Push** to the branch (`git push origin feature/amazing-feature`)
5. **Open** a Pull Request

### Areas for Contribution

- Bug fixes and error handling improvements
- New BASIC commands (e.g., `FOR`, `GOSUB`, `DATA/READ`)
- Documentation improvements
- Performance optimizations
- Test suite development

---

## 📄 License

This project is licensed under the **GNU General Public License v3.0** - see the [LICENSE](LICENSE) file for details.

---
# 📄 Testing
This interpreter has been tested  with successful results on a Dell Computer 170L Intel Celeron D 2.79 GHz, 1542 MB RAM with OpenBSD 7.0 i386.

---

## 👨‍💻 Author

**nerdemma** - [GitHub Profile](https://github.com/nerdemma)

---

## 🙏 Acknowledgments

- Inspired by classic BASIC interpreters from the 1970s-80s
- Built with educational purposes in mind for learning compiler/interpreter design

---

**Happy Coding! 🚀**
