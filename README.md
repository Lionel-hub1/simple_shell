# SUPER ALX SIMPLE SHELL PROJECT
## Introduction
A shell is a command-line interface that allows users to interact with an operating system. It takes user commands and executes them as processes.

## Steps to Create a Simple Shell Project
1. **Write a function to read user input**: The first step is to write a function that can read user input. You can use the standard library function `getline()` to read input from the user.

2. **Parse the user input**: Once you have the user input, you need to parse it to separate the command and the arguments. You can use the `strtok()` function from the `string.h` library to tokenize the input.

3. **Create a child process**: After parsing the input, you need to create a child process to execute the command. You can use the `fork()` function from the **unistd.h** library to create a child process.

4. **Execute the command**: Once the child process is created, you can use the `execve()` function to execute the command. This function takes the command and its arguments as arguments.

5. **Wait for the child process**: After the command is executed, you need to wait for the child process to finish using the `wait()` function.

6. **Repeat**: Finally, you can repeat the above steps to read and execute user commands in a loop.

## Functions Explaination

This code reads user input using `getline()` and tokenizes it using `custom_trtok()`.

It then creates a child process using `fork()` and executes the command using `execve()`.

Finally, it waits for the child process to finish using `waitpid()`.
The loop continues until the user enters the `exit` command.

