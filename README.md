# Simple Shell

## Description
Simple Shell is a basic UNIX command interpreter written in C.
It mimics the behavior of `/bin/sh` by reading commands from standard input
and executing them using system calls.

This project was developed as part of the Holberton School curriculum.

---

## Features
- Executes commands using absolute paths
- Executes commands using the PATH environment variable
- Handles interactive and non-interactive modes
- Built-in commands:
  - `exit`
  - `env`

---

## Compilation
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
