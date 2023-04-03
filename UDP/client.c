//
//  client.c
//  Projet_Reseaux_MAHON_LELONG
//
//  Created by Grégoire Mahon on 29/03/2023.
//
// client_udp.c V1

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    // Informations requêtes :
    char AJOUT_Request[48] = "AJOUT <id_client> <id_compte> <password> <somme>";
    char RETRAIT_Request[50] = "RETRAIT <id_client> <id_compte> <password> <somme>";
    char SOLDE_Request[40] = "SOLDE <id_client> <id_compte> <password>";
    char OPERATIONS_Request[45] = "OPERATIONS <id_client> <id_compte> <password>";
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Création du socket (UDP -> SOCK_DGRAM)
    // int socket(famille, type, protocole)
    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Configuration de l'adresse du serveur
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    printf("Bonjour, voici les requêtes disponibles :\nAjouter de l'argent à votre compte : %s\nRetirer de l'argent : %s\nAfficher votre solde : %s\nAfficher les 10 dernieres operations : %s\n", AJOUT_Request, RETRAIT_Request, SOLDE_Request, OPERATIONS_Request);
    while (1) {
        printf("Entrez une requête (Respecter la syntaxe) : ");
        fgets(buffer, BUFFER_SIZE, stdin);

        /*if (buffer[0] == 'q') {
            break;
        }*/

    
        socklen_t addr_len = sizeof(server_addr);
        sendto(client_fd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, addr_len);

        // Réception de la réponse du serveur
        int len = recvfrom(client_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &addr_len);
        buffer[len] = '\0';
        printf("Réponse du serveur : %s\n", buffer);
    
    }

    close(client_fd);
    return 0;
}
