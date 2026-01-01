# Simple Shell

## 📌 Description
Simple Shell is a basic UNIX command interpreter written in C as part of the Holberton School curriculum.  
It replicates core functionalities of `/bin/sh` by reading commands from standard input, parsing them, and executing them using system calls.

The project focuses on understanding how a shell works internally, including process creation, command execution, environment handling, and interaction with the operating system.

---

## ⚙️ Features
- Executes commands using **absolute paths**
- Executes commands using the **PATH environment variable**
- Supports **interactive mode**
- Supports **non-interactive mode**
- Handles command execution using `fork` and `execve`
- Handles process synchronization using `wait`
- Built-in commands:
  - `exit` – exits the shell
  - `env` – prints the current environment variables

---

## 🧠 How It Works
1. Displays a prompt when running in interactive mode
2. Reads user input using `getline`
3. Tokenizes the input into command and arguments
4. Resolves the command path using the `PATH` variable
5. Creates a child process using `fork`
6. Executes the command using `execve`
7. Parent process waits for the child to finish

---

## 🖥️ Usage

### Interactive mode
```bash
$ ./hsh
#cisfun$ ls
#cisfun$ pwd
#cisfun$ exit
