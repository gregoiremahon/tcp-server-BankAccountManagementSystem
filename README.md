# Bank Account Management System (TCP Server)

This is a student project for the EI2I 3 training at Polytech Sorbonne, Semester 6. The purpose of this project is to create a simple TCP server that simulates a bank account management system.

## Objective

The main objective of this project is to gain hands-on experience with network programming in C using TCP and UDP sockets. The server will handle basic operations like depositing, withdrawing, checking balance, and viewing the last 10 transactions of a bank account.

## Technologies Used

- Standard C libraries :
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
- Socket functions for network communication
