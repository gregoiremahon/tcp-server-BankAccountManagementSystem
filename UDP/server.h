//
//  server.h
//  Projet_Reseaux_MAHON_LELONG
//
//  Created by Grégoire Mahon on 29/03/2023.
//

#ifndef CF1CF397_E2AD_4D07_BC7F_2CB833FD3C32
#define CF1CF397_E2AD_4D07_BC7F_2CB833FD3C32

#ifndef SERVER_H
#define SERVER_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

typedef struct Operation {
    char type_operation[10];
    char date_operation[20];
    double montant_operation;
} Operation;

typedef struct Compte {
    int id_client;
    int id_compte;
    char password[32];
    double solde;
    Operation operations[10];
    int nombre_operations;
} Compte;

void enregistrer_operation(Compte *compte, const char *type_operation, double montant);
Compte *find_accound_by_ID(int id_client, int id_compte, const char *password);
int AJOUT(int id_client, int id_compte, const char *password, double somme);
int RETRAIT(int id_client, int id_compte, const char *password, double somme);
double SOLDE(int id_client, int id_compte, const char *password);
char *OPERATIONS(int id_client, int id_compte, const char *password, char *buffer, size_t buffer_size);

#endif // SERVER_H


#endif /* CF1CF397_E2AD_4D07_BC7F_2CB833FD3C32 */
