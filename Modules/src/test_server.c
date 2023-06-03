#include "includes.h"

void testServerP() {
    int etatServeur = 1;

    // Ouverture du fichier d'état du serveur de production
    FILE* fichierEtatServeur = fopen("../Production/EtatServeurProd.txt", "rb");

    // Vérification de l'ouverture du fichier d'état du serveur de production
    if (fichierEtatServeur == NULL) {
        perror("fichierEtatServeur : Erreur d'ouverture du fichier d'état de serveur");
        exit(EXIT_FAILURE);
    }

    // Lecture de l'état initial du serveur
    fscanf(fichierEtatServeur, "%d", &etatServeur);
    rewind(fichierEtatServeur);

    // Tant que le serveur est allumé, on génère des listes toutes les 10 secondes
    if (etatServeur) {
        printf("[Serveur de production] Allumer . . .\n");
        printf("[Serveur de production] ACTIVER\n\n");
    }else
    {
        printf("[Serveur de production] Eteint . . .\n");
        printf("[Serveur de production] DESACTIVER\n\n");
    }
    
    // Fermeture du fichier d'état du serveur de production
    fclose(fichierEtatServeur);
}

void testServerB() {
    int etatServeur = 1;
    int checkEtatServeur = 1;

    // Ouverture du fichier d'état du serveur de production
    FILE* fichierEtatServeurProd = fopen("../Production/EtatServeurProd.txt", "rb");

    // Ouverture du fichier d'état du serveur de backup
    FILE* fichierEtatServeurBack = fopen("../Backup/EtatServeurBack.txt", "rb");

    // Vérification de l'ouverture des fichiers d'état des serveurs
    if (fichierEtatServeurProd == NULL) {
        perror("fichierEtatServeurProd : Erreur d'ouverture du fichier d'état de serveur");
        exit(EXIT_FAILURE);
    }

    if (fichierEtatServeurBack == NULL) {
        perror("fichierEtatServeurBack : Erreur d'ouverture du fichier d'état de serveur");
        exit(EXIT_FAILURE);
    }

    // Lecture de l'état initial des serveurs
    fscanf(fichierEtatServeurBack, "%d", &checkEtatServeur);
    rewind(fichierEtatServeurBack);

    fscanf(fichierEtatServeurProd, "%d", &etatServeur);
    rewind(fichierEtatServeurProd);

    if (checkEtatServeur) {
        printf("[Serveur de backup] Allumer . . .\n");
        if(!etatServeur) {
            printf("[Serveur de backup] ACTIVER\n\n");
        }else
        {
            printf("[Serveur de backup] DESACTIVER\n\n");
        }
        
    } else {
        printf("[Serveur de backup] Allumer . . .\n");
        if(etatServeur) {
            printf("[Serveur de backup] DESACTIVER\n\n");
        }else
        {
            printf("[Serveur de backup] ACTIVER\n\n");
        }
    }

    // Fermeture des fichiers d'état des serveurs
    fclose(fichierEtatServeurProd);
    fclose(fichierEtatServeurBack);
}
