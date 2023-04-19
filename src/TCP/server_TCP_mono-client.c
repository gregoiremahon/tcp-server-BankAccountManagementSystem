//
//  server.c
//  Projet_Reseaux_MAHON_LELONG
//
//  Created by Grégoire Mahon on 29/03/2023.
//
// server_tcp.c V1
#include "server.h"


#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h> // "'time' must be declared before it is used (xCode err)"

// See server.h for structs definition

Compte comptes[] = {
    // {id_client, id_compte, password, solde, {{OPERATIONS}}, nombre_operations}
    {1, 1001, "password1", 5000.0, {{"", "", 0}}, 0},
    {2, 1002, "password2", 3000.0, {{"", "", 0}}, 0},
    {3, 0000, "p", 3999.0, {{"", "", 0}}, 0}
};

int nombre_comptes = sizeof(comptes) / sizeof(comptes[0]);

// enregistrer des operations (lorsque le client ajoute ou retire de l'argent uniquement)
void enregistrer_operation(Compte *compte, const char *type_operation, double montant) {
    Operation *operation = &compte->operations[compte->nombre_operations % 10];
    strcpy(operation->type_operation, type_operation);
    time_t t = time(NULL);
    strftime(operation->date_operation, sizeof(operation->date_operation), "%Y-%m-%d %H:%M:%S", localtime(&t));
    operation->montant_operation = montant;
    compte->nombre_operations++;
}

// Trouver un compte par id_client, id_compte et password
Compte *find_accound_by_ID(int id_client, int id_compte, const char *password) {
    for (int i = 0; i < nombre_comptes; i++) {
        if (comptes[i].id_client == id_client && comptes[i].id_compte == id_compte &&
            strcmp(comptes[i].password, password) == 0) {
            return &comptes[i];
        }
    }
    return NULL;
}

// Ajouter une somme à un compte :
/* AJOUT <id_client id_compte password somme> permettra d'ajouter la somme sur le compte identifié par id_compte par le client id_client identifié avec password. */
int AJOUT(int id_client, int id_compte, const char *password, double somme) {
    Compte *compte = find_accound_by_ID(id_client, id_compte, password);
    if (compte) {
        compte->solde += somme;
        // Enregistre l'opération
        enregistrer_operation(compte, "AJOUT", somme);
        return 1;
    }
    return 0;
}

/* RETRAIT <id_client id_compte password somme> permettra de retirer la somme sur le compte identifié par id_compte par le client id_client identifié avec passeword.*/
int RETRAIT(int id_client, int id_compte, const char *password, double somme) {
    Compte *compte = find_accound_by_ID(id_client, id_compte, password);
    if (compte && compte->solde >= somme) {
        compte->solde -= somme;
        enregistrer_operation(compte, "RETRAIT", somme); // Enregistre l'opération
        return 1;
    }
    return 0;
}

/* SOLDE <id_client id_compte password> permettra d'obtenir le solde du compte identifié par id_compte par le client id_client identifié avec password. */
double SOLDE(int id_client, int id_compte, const char *password) {
    Compte *compte = find_accound_by_ID(id_client, id_compte, password);
    if (compte) {
        return compte->solde;
    }
    return -1.0;
}

/* OPERATIONS <id_client id_compte password> permettra d'obtenir les 10 dernières opérations effectuées sur le compte identifié par id_compte. 
Cette opération ne peut être demandée que par le client id_client identifié avec password. */
char *OPERATIONS(int id_client, int id_compte, const char *password, char *buffer, size_t buffer_size) {
    Compte *compte = find_accound_by_ID(id_client, id_compte, password);
    if (compte) {
        int start = (compte->nombre_operations > 10) ? compte->nombre_operations - 10 : 0;
        buffer[0] = '\0';
        for (int i = start; i < compte->nombre_operations; i++) {
            Operation *operation = &compte->operations[i % 10];
            char line[128];
            snprintf(line, sizeof(line), "%s %s %.2lf\n", operation->type_operation, operation->date_operation, operation->montant_operation);
            strncat(buffer, line, buffer_size - strlen(buffer) - 1);
        }
        return buffer;
    }
    return NULL;
}


int main() {
    int server_fd; // server socket
    int client_fd; // client socket
    int addr_len; // client_addr struct size
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE]; // store data receved from client

    // create server socket
    /* AF_INET : IPv4
       SOCK_STREAM : TCP socket
       0 : default SOCK_STREAM protocol : TCP protocol */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (server_fd == -1) {
        //print error if socket creation failed
        perror("socket");
        exit(EXIT_FAILURE);
    }
    
    // Configure server adress
    /* AF_INET : IPv4
       INADDR_ANY : all ip adress available (TBD)
        */
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    // define port and convert it to network byte format (using htons : host-to-network short)
    server_addr.sin_port = htons(PORT);

    // Bind server_addr (adress and port) to socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Listen : accept incoming connections
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    addr_len = sizeof(client_addr);
    
    printf("SERVER STARTED ON PORT : %d\n", PORT);
    printf("WAITING FOR CLIENT REQUESTS...\n");
    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&addr_len);
        if (client_fd < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        int id_client, id_compte;
        char password[32];
        double somme;
        char response[BUFFER_SIZE];
        int keep_client_connected = 1;
        
        do {
            // Traitement de la requête et écriture de la réponse
            // Lecture de la requête du client
            ssize_t bytes_read = read(client_fd, buffer, BUFFER_SIZE);
            if (bytes_read <= 0) {
                keep_client_connected = 0;
                break;
            }
            buffer[BUFFER_SIZE - 1] = '\0'; // ajout du caractère de fin de chaine

            if (sscanf(buffer, "AJOUT %d %d %s %lf", &id_client, &id_compte, password, &somme) == 4) {
                if (AJOUT(id_client, id_compte, password, somme)) {
                    strcpy(response, "OK\n");
                } else {
                    strcpy(response, "KO\n");
                }
                
            } else if (sscanf(buffer, "RETRAIT %d %d %s %lf", &id_client, &id_compte, password, &somme) == 4) {
                if (RETRAIT(id_client, id_compte, password, somme)) {
                    strcpy(response, "OK\n");
                } else {
                    strcpy(response, "KO\n");
                }
                
            } else if (sscanf(buffer, "SOLDE %d %d %s", &id_client, &id_compte, password) == 3) {
                double solde_compte = SOLDE(id_client, id_compte, password);
                if (solde_compte >= 0.0) { // seulement si compte pas en découvert
                    // snprintf : int snprintf(char *str, size_t size, const char *format, …);
                    snprintf(response, BUFFER_SIZE, "SOLDE DE VOTRE COMPTE : %.2lf $", solde_compte);
                } else {
                    strcpy(response, "KO\n");
                }
                
            } else if (sscanf(buffer, "OPERATIONS %d %d %s", &id_client, &id_compte, password) == 3) {
                char operations_buffer[BUFFER_SIZE];
                char *operations_result = OPERATIONS(id_client, id_compte, password, operations_buffer, BUFFER_SIZE);
                /* retourne un pointeur vers un buffer contenant les 10 dernières opérations formatées. Retourne NULL, si la requête n'a pas pu être traitée et envoie "KO" au client.*/
                if (operations_result) {
                    snprintf(response, BUFFER_SIZE, "RES_OPERATIONS : \n%s", operations_result);
                } else {
                    strcpy(response, "KO\n");
                }
                
            } else {
                strcpy(response, "KO\n");
            }

            // Envoi de la réponse au client
            send(client_fd, response, strlen(response), 0);
            //send(client_fd, buffer, strlen(buffer), 0); --> send request back
            
            // if client sends "QUIT", he gets disconnected
            if (strcmp(buffer, "QUIT") == 0) {
                keep_client_connected = 0;
            }

        } while (keep_client_connected);

        close(client_fd);
        
    }
    return 0;
}
