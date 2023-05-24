# Bank Account Management System (TCP/UDP Server)

This is a student project for the EI2I 3 training at Polytech Sorbonne, Semester 6. The purpose of this project is to create two simple TCP and UDP servers that simulate a bank account management system.

## Objective

The main objective of this project is to gain hands-on experience with network programming in C using TCP and UDP sockets. The server will handle basic operations like depositing, withdrawing, checking balance, and viewing the last 10 transactions of a bank account.

## Technologies Used

- Standard C libraries (socket, time, inet, ...)
- Socket functions for network communication

## How to Run (UNIX only)

1. Clone the git repository:

    `git clone https://github.com/gregoiremahon/tcp-udp-server-BankAccountManagementSystem.git`

2. Move to the root directory of the project:

    `cd tcp-udp-server-BankAccountManagementSystem`

3. Compile both server and client code files using the makefile:

    `make`

    This will create a new directory named `bin` containing the server and client executables.

4. Run the server in a terminal. 

    - For single client TCP version:

        `./bin/server_TCP_mono-client`

    - For single client UDP version:

        `./bin/server_UDP_mono-client`

    - For multi-threaded TCP version:

        `./bin/server_TCP_multithread`

    - For multi-threaded UDP version:

        `./bin/server_UDP_multithread`

5. Run the client in another terminal. 

    - For TCP:

        `./bin/client_TCP`

    - For UDP:

        `./bin/client_UDP`

6. Follow the instructions displayed by the client program to interact with the bank account management system.
