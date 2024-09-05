# Minishell

## Overview

Grade: 125/125

Welcome to **Minishell**, a simple Unix-like shell implemented in C.
The goal of this project is to replicate some core functionalities of a shell, allowing users to execute commands and navigate the file system. This implementation also includes advanced features such as **parentheses**, **logical operators (&&, ||)**, and **wildcards (\*)**, which are part of the bonus section of the project.

## Features

- **Basic Shell Functionality**:
  - Execute commands with their absolute or relative paths.
  - Search and execute commands found in the `PATH` environment variable.
  - Handle arguments and options for commands.
  - Input/output redirection (`>`, `>>`, `<`).
  - Pipe support (`|`) to connect multiple commands.
  - Signal handling for interactive commands (Ctrl+C, Ctrl+D, Ctrl+\).

- **Built-in Commands**:
  - `echo` – Display text to the standard output.
  - `cd` – Change the current working directory.
  - `pwd` – Print the current working directory.
  - `export` – Set environment variables.
  - `unset` – Remove environment variables.
  - `env` – Display the environment variables.
  - `exit` – Exit the shell.

- **Bonus Features**:
  - **Parentheses** – Group commands to control the precedence of execution.
  - **Logical operators (`&&`, `||`)** – Chain commands with logical conditions (execute only if previous command succeeds or fails).
  - **Wildcards (`*`)** – Match patterns in file names, similar to Unix shell globbing.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/AlienRecall/minishell.git
   cd minishell
   ```

2. Compile the project:
   ```bash
   make
   ```

3. Run the shell:
   ```bash
   ./minishell
   ```

## Usage

Once the shell is running, you can type commands as you would in a regular Unix shell. Here are some example commands:

- Basic command execution:
  ```bash
  ls -l
  ```
- Piping commands:
  ```bash
  cat file.txt | grep "search something"
  ```
- Redirection:
  ```bash
  echo "Hello, World!" > output.txt
  ```
- Using parentheses for grouping:
  ```bash
  (echo "First command" && echo "Second command")
  ```
- Logical operators (`&&`, `||`):
  ```bash
  mkdir new_folder && cd new_folder
  ls || echo "Failed to list directory"
  ```
- Wildcards (`*`):
  ```bash
  echo *.c
  ```

## Signals

- **Ctrl+C**: Interrupt the current running process.
- **Ctrl+D**: Exit the shell.
- **Ctrl+\\**: Quit the shell.
