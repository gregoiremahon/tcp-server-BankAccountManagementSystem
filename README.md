# Bank Account Management System (UDP Server)

This is a student project for the EI2I 3 training at Polytech Sorbonne, Semester 6. The purpose of this project is to create a simple UDP server that simulates a bank account management system.

## Objective

The main objective of this project is to gain hands-on experience with network programming in C using TCP and UDP sockets. The server will handle basic operations like depositing, withdrawing, checking balance, and viewing the last 10 transactions of a bank account.

## Technologies Used

- Standard C libraries (socket, time, inet, ...)
- Socket functions for network communication

## How to Run (UNIX only)

1. Clone the git repository:
    `git clone https://github.com/gregoiremahon/tcp-server-BankAccountManagementSystem.git`

2. Compile both server and client code files:
    `cd tcp-server-BankAccountManagementSystem`
    UDP socket :
    `gcc -o server_udp ./UDP/server.c`
    `gcc -o client_udp ./UDP/client.c`
    Or TCP socket : 
    `gcc -o server_tcp ./TCP/server.c`
    `gcc -o client_tcp ./TCP/client.c`
    

3. Run the server in a terminal:
    `./server_udp`


4. Run the client in another terminal:
    `./client_udp`

5. Follow the instructions displayed by the client program to interact with the bank account management system.